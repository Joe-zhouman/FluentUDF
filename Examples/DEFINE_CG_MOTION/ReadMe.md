# 动网格相关宏

## DEFINE_CG_MOTION

### 使用

```c
#define DEFINE_CG_MOTION(name, dt, vel, omega, time, dtime)   \
  EXTERN_C void name(Dynamic_Thread *dt, real vel[], real omega[], real time, real time)
```



| Type           | Parameter | Notes                                   |
| -------------- | --------- | --------------------------------------- |
| symbol         | name      | UDF名字                                 |
| Dynamic_Thread | dt        | 指向动网格相关属性结构体的指针          |
| real           | vel[ ]    | 线速度。三个分量为xyz方向速度           |
| real           | omega[ ]  | 角速度。三个分量为以xyz轴为转轴的角速度 |
| real           | time      | 当前时间                                |
| real           | dtime     | 时间步                                  |
| void           | return    | 无返回值                                |

### 样例

#### Example.1 刚体平动

```c
#include "udf.h"
/*刚体平动示例*/
DEFINE_CG_MOTION(move, dt, vel, omega, time, dtime)
{
    /*reset velocity*/
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    /*set v_x = 5e-3m/s*/
    vel[0] = 5e-3;
}
```

#### Example.2 刚体转动

```c
#include "udf.h"
/*刚体转动示例*/
DEFINE_CG_MOTION(rotate, dt, vel, omega, time, dtime) {
    /*reset velocity*/
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    /*set omega_xy = 0.2 rad/s*/
    omega[2] = 0.2;
}
```

#### Example.3 随时间变化的刚体运动

```c
#include "udf.h"
static real v_prev = 0.0;
static real time_prev = 0.0; 
/*刚体运动随时间变化示例*/
DEFINE_CG_MOTION(acceleration, dt, vel, omega, time, dtime)
{
    real dv;
    /*reset velocity*/
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    dv = dtime * 1e-3;
	if(time < 1){
        omega[2] = 0.1;
    }
	else if(time > (time_prev+EPSILON)){
        v_prev += dv;
        time_prev = time;       
    }
    vel[0] = v_prev;
}
```



#### Example.4 实现单向流体-刚体运动耦合

```c
/*实现简单的流体与刚体运动的单向耦合*/
#include "udf.h"

/*****define some constants*****/
#define MASS 1
#define TIME_STEP 0.0001
/********************/

static real current_vel=0;

DEFINE_CG_MOTION(valva, dt, vel, omega, time, dtime)
{
    real dv;
    /* reset velocities */
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    vel[2] = current_vel;
}
/*利用UDF获取作用力*/
DEFINE_EXECUTE_AT_END(compute_vel) {
    Domain *domain=Get_Domain(1);
    int domain_id_send_to_node;
    real force_temp = 0;
    real total_force_z = 0;
    real dv=0;
/*************并行版循环**************/
//此处定义仅在计算节点中使用的变量
#if !RP_HOST
    Thread *thread;
    face_t face;
    real area[ND_ND];
#endif
//将需要进行循环的区域ID分发到节点上
    domain_id_send_to_node = 10;
    /*主机与节点的数据交换
    host_to_node_type_num(var1,var2,...)
    type:变量类型
    num:变量数量
    var1,va2,...:需要传递的变量

    如下面
    int domain_id_send_to_node = 1;
    host_to_node_int_1(domain_id_send_to_node);
    意思就是说把一个名叫domain_id_send_to_node的int型变量送往节点
    */
    /*
    host_to_node_type(var_name,var_num)
    type:数组变量的类型，字符串数组为string而非char
    var_name:数组变量的名字
    var_num:数组的长度

    EXAMPLE 1:
    char my_name[]"satisfactions";
    host_to_node_string(my_name,14);//注意字符串数组后面隐藏有一个'\0'

    EXAMPLE 2:
    int domain_ids[2]={10,15};
    host_to_node_int(domain_id,2);
    */
    /*
    同理，从节点向主机传递数据为
    node_to_host_type_num(var1,var2,...)
    node_to_host_type(var_name,var_num)
    */
    host_to_node_int_1(domain_id_send_to_node);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id_send_to_node);
    begin_f_loop(face, thread)
        /*边界可能进行两次计算，利用PRINCIPAL_FACE_P(face, thread)壁面*/
    if (PRINCIPAL_FACE_P(face, thread)) {
        F_AREA(area, face, thread);
        force_temp += area[2] * F_P(face, thread);
    }
    end_f_loop(face, thread)
#if RP_NODE /* Perform node synchronized actions here */
        /*全局归纳操作
        此类宏的名称由四部分组成
        前缀：均为PRF_G
        数据类型标志：操作的数据的类型
                I--int
                R--real
                L--logical
        操作标志：进行什么操作
                SUM--求和
                HIGH--求最大值
                LOW--求最小值
                AND--逻辑和运算
                OR--逻辑或运算
        版本标志：此类宏有两个版本
                尾缀加1，表示对单个简单变量进行操作，并可返回一个变量。此时宏的使用为
                    output=PRF_G[Type][Operation]1(x);
                尾缀不加1，表示对数组进行操作,不返回变量。此时宏的使用为
                    PRF_G[Type][Operation](x,N,temp_storage)
                    x:进行操作的量级最终的返回值（数组）
                    N:数组的长度
                    temp_storage:操作中需要使用的临时变量，需要和x类型长度相同

        EXAMPLE 1:
        //假定现在已经在每个节点对x进行了求和
        x=PRF_GRSUM1(x);
        表示对一个类型为real的变量x进行全局求和，求和之后的值再赋给x。

        EXAMPLE 2：
        int N = 3;
        real
        x[N]={max_temp,max_press,max_vel};//x的三个成员分别表示温度，压力，速度。
        real temp[N];
        //假定现在已经在每个节点对x的三个分量求得了最大值
        PRF_GRHIGH(x,N,temp);
        */
        force_temp = PRF_GRSUM1(force_temp);
#endif /* RP_NODE */
#endif /* !RP_HOST */
/**********************************/
    total_force_z += force_temp;
    dv = total_force_z / MASS * TIME_STEP;
    current_vel+=dv;
}

/*利用Report definition获取作用力*/
DEFINE_EXECUTE_AT_END(compute_vel_from_definition)
{
    /*使用Get_Report_Definition_Values需要的变量*/
    int nrOfvalues = 0;
    real *values;
    int *ids;
    int index;
    int counter;
    /*计算当前速度需要的变量*/
    real dv;
    real total_force_z;
    /*********获取报告定义值***********
    int Get_Report_Definition_Values(const char* name, int type, int* nrOfvalues, real* values, int* ids, int* index)
    
    [input] const char* name : report definition的名字
    [input] int type : 获取每次迭代数据（0）还是每次时间步的数据（1）。瞬态计算只能用1.
    [output] int* nrOfvalues ：该report definition的变量数
    [output] real* values : 该report definition的变量
    [output] int* ids : 跟该report definition相关的surface/zone的ID。（如果 per-zone 或 per-surface 选项关闭
                        且surfaces/zones数量大于1，将返回-1
    [output] int* index : 该report definition的索引（第几次迭代/时间步）
    [return] 0-获取成功/1-该report definition不存在，获取失败

    *******************************/
    //第一次调用，获取values的个数
    int rv = Get_Report_Definition_Values("report-def-0", 1, &nrOfvalues, NULL,
                                          NULL, NULL);
    if (rv == 0 && nrOfvalues) {
        Message("Report definition evaluated at iteration has %d values\n",
                nrOfvalues);
    /*为 values 和 ids 分配内存.*/
    values = (real *)malloc(sizeof(real) * nrOfvalues);
    ids = (int *)malloc(sizeof(int) * nrOfvalues);
    /*第二次调用，获取 values 和 ids.*/
    rv = Get_Report_Definition_Values("report-def-0", 1, NULL, values, ids,
                                      &index);
    /*calculate current velocity*/
    total_force_z=values[0];
    dv = total_force_z / MASS * TIME_STEP;
    current_vel += dv;
    /*释放内存*/
    free(values);
    free(ids);
    } else {
        /*不存在或还未求值，调用失败.*/
        if (rv == 1) {
            Message("report definition: %s does not exist\n", "report-def-0");
        } else if (nrOfvalues == 0) {
            Message("report definition: %s not evaluated at iteration level\n",
                    "report-def-0");
        }
        return;
    }
}
```

### 补充知识

#### 向量和维度操作

对于2D求解器，将存在`PR_2D`宏定义。对于3D求解器，将存在`PR_3D`宏定义。

```c
#if RP_3D
	/*仅3D求解器可使用的操作*/
#endif
```

##### ND_ 分量操作宏

```c
#if RP_3D
# define ND_ND 3
# define ND_VEC(x,y,z)x,y,z
#else
# define ND_ND 2
# define ND_VEC(x,y,z)x,y
#endif
#define ND_3 3
#define NV_VEC(a)a[ND_ND]
```

对于2D求解器，ND_ND=2`。对于3D求解器，ND_ND=3。

对于2D求解器，`NV_VEC`将忽略第三个分量。

`NV_VEC(a)`定义一个名为a的符合当前维度的向量。

```c
#if RP_3D
# define ND_OP(OP,x,y,z)((x)OP(y)OP(z))
#else
# define ND_OP(OP,x,y,z)((x)OP(y))
#endif
```



```c
/*
D : demension
S : scalar
V : vector
T : Tensor
*/
#define ND_S(a0,a1,a2,EQ,s)ND_VEC((a0)EQ(s),(a1)EQ(s),(a2)EQ(s))
//分量 与 标量 操作
//ND_S(a0,a1,a2,=,2);=>(a0,a1,a2)=(2,2,2);
#define ND_D(a0,a1,a2,EQ,x0,x1,x2)ND_VEC((a0)EQ(x0),(a1)EQ(x1),(a2)EQ(x2))
//分量 与 另一个分量 操作
//ND_D(a0,a1,a2,=,x0,x1,x2);=>(a0,a1,a2)=(x0,x1,x2);
#define ND_V(a0,a1,a2,EQ,x)ND_D(a0,a1,a2,EQ,(x)[0],(x)[1],(x)[2])
//分量 与 向量 操作
//ND_V(a0,a1,a2,=,x); (a0,a1,a2)=x;
#define ND_VS(a0,a1,a2,EQ,x,S,s)ND_VEC((a0)EQ(x)[0]S(s),(a1)EQ(x)[1]S(s),(a2)EQ(x)[2]S(s))
//分量 与 向量 与 标量 操作
//ND_VS(a0,a1,a2,=,x,*,2);=>(a0,a1,a2)=(x[0]*2,x[1]*2,x[2]*2)
#define ND_DS(a0,a1,a2,EQ,x0,x1,x2,S,s)ND_VEC((a0)EQ(x0)S(s),(a1)EQ(x1)S(s),(a2)EQ(x2)S(s))
//分量 与 分量 与 标量 操作
#define ND_DD(a0,a1,a2,EQ,x0,x1,x2,V,y0,y1,y2) ND_VEC((a0)EQ(x0)V(y0),(a1)EQ(x1)V(y1),(a2)EQ(x2)V(y2))
//分量 与 分量 与 分量 操作
#define ND_VV_S(a0,a1,a2,EQ,x,V,y,S,s)ND_VEC((a0)EQ((x)[0]V(y)[0])S(s),(a1)EQ((x)[1]V(y)[1])S(s),(a2)EQ((x)[2]V(y)[2])S(s))
//分量-向量-向量-标量
#define ND_VD_S(a0,a1,a2,EQ,x,V,y0,y1,y2,S,s)ND_VEC((a0)EQ((x)[0]V(y0))S(s),(a1)EQ((x)[1]V(y1))S(s),(a2)EQ((x)[2]V(y2))S(s))
//分量-向量-分量-标量
#define ND_DV_S(a0,a1,a2,EQ,x0,x1,x2,V,y,S,s)ND_VEC((a0)EQ((x0)V(y)[0])S(s),(a1)EQ((x1)V(y)[1])S(s),(a2)EQ((x2)V(y)[2])S(s))
//分量-分量-向量-标量
#define ND_DD_S(a0,a1,a2,EQ,x0,x1,x2,V,y0,y1,y2,S,s)ND_VEC((a0)EQ((x0)V(y0))S(s),(a1)EQ((x1)V(y1))S(s),(a2)EQ((x2)V(y2))S(s))
//分量-分量-分量-标量
#define ND_DS_DS(a0,a1,a2,EQ,x0,x1,x2,SX,sx,V,y0,y1,y2,SY,sy)ND_VEC((a0)EQ(((x0)SX(sx))V((y0)SY(sy))),(a1)EQ(((x1)SX(sx))V((y1)SY(sy))),(a2)EQ(((x2)SX(sx))V((y2)SY(sy))))
//分量-分量-标量-分量-标量
#define ND_DS_VS(a0,a1,a2,EQ,x0,x1,x2,SX,sx,V,y,SY,sy)ND_VEC((a0)EQ(((x0)SX(sx))V((y)[0]SY(sy))),(a1)EQ(((x1)SX(sx))V((y)[1]SY(sy))),(a2)EQ(((x2)SX(sx))V((y)[2]SY(sy))))
//分量-分量-标量-向量-标量


#define ND_SUM(x0,x1,x2) ND_OP(+,x0,x1,x2)
//2D : x0+x1; 3D : x0 + x1 + x2
```




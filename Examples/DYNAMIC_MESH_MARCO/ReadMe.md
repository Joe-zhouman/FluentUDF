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

```c
typedef struct dynamic_thread_struct
{
  Dynamic_Thread_Rigid_Body_State current_state;
  Dynamic_Thread_Rigid_Body_State tmp_state;
  Dynamic_Thread_Rigid_Body_State init_state;

  real dir_ref[3];                         /* reference direction of motion */
  real dir_prev[3];                        /* previous direction of motion */
  real axis[3];                            /* body-fixed axis of motion */
  real refo[3];                            /* reference point */

  real len[3];                             /* length scales (s0, s1, skew) */
  real h[2];                               /* (hmin) (hmax), if applicable */

  real geom_origin[3];                     /* geom.: origin */
  real geom_axis[3];                       /* geom.: axis/normal */
  real geom_radius;                        /* geom.: radius */
  char geometry_name[132];                 /* geometry of geometry function */
  cxboolean geom_feature_p;                /* geom.: use feature detection */
  real geom_feature_angle;                 /* geom.: feature angle */

  cxboolean sop_comp;                      /* solver options for system coupling/six dof switch */
  real sop_scale;                          /* solver option scaling factor */
  char sop_type_name[132];                 /* solver option type name: ap, cell */
  int  sop_type;                           /* 0-volume-based, 1-coefficient-based, 2-udf (not implemented yet) */

  int layer[2];                            /* layering action */
  real layer_factor;                       /* layering split/collapse factor */

  int type;                                /* dynamic zone type */
  int udf_type;                            /* mover, motion, 6DOF */
  int face_remesh_count;                   /* remesh counter */
  int face_remesh_action;                  /* split or collapse */

  cxboolean sliding;                       /* allow nodes to slide/move? */
  cxboolean remesh;                        /* allow faces/cells to be remesh? */
  cxboolean layering;                      /* allow layering? */
  cxboolean moving;                        /* freeze node motion? */
  cxboolean remesh_globals_p;              /* use global remesh parameters */
  int sliding_method;                      /* method to slide */
  int sliding_elements;                    /* spring smoothing element type */
  int remeshing_method;                    /* method(s) to remesh */
  cxboolean boundary_layer_deform;         /* deform/move adjacent prisms
                                              with boundary */
  cxboolean user_defined_deform;           /* allow deformation of user defined
                                              zones */
  cxboolean bc_exclude_motion;             /* option to exclude boundary motion
                                              in boundary condition */

  char profile_udf_name[132];              /* udf or profile name */
  void (*update)();                        /* pointer to motion function */

  struct thread_struct *thread;            /* face/cell thread */

  cxboolean separate_region;               /* remesh region separately? */
  int nloops;                              /* number of moving loops */
  struct edge_loop_struct *loops;          /* loop data structure */
  struct objp_struct *lnodes;              /* pointer to loop nodes */

  cxboolean sdof_p;                        /* use 6DOF to compute motion */
  cxboolean sdof_contribute_p;             /* 6DOF: contribution of thread */

  cxboolean perdisp_p;                     /* use Periodic Displacement to compute motion */
  cxboolean surf_rev_done;                 /* Building surface of revolution done */
  int trim_size;                           /* number of interpolating points for surf revolution */
  real *axcrd;                             /* axial coordinate for surf of revolution */
  real *radcrd;                            /* radial coordinate for surf of revolution */

  cxboolean nested_p;
  struct thread_struct *nest_thread;       /* udf motion is specified on top of the motion of nest_thread */
  cxboolean nested_local_rot_p;            /* relative motion is specifed in local */
  cxboolean nested_local_tran_p;     	   /* coordinates or absolute coordinates */

  char h_udf_name[2][64];                  /* udf name for non-constant layer
                                              height [0], [1] (corresponding
                                              to height0 and height1) */

  char contact_udf_name[64];               /* UDF name for contact detection */

  real (*tmp_cg)[3];
  real *tmp_theta;
  real tmp_omega[3];                       /* zone-motion variables */

  unsigned int update_state;               /* indicates if thread has been
                                              remeshed, smoothed, etc. */

  real gocart_param[5];                    /* GoCart remeshing parameters
                (max, growth rate, skew,
                aspect ratio, remesh interval) */
  cxboolean gocart_prisms_p;               /* remesh GoCart with inflation
                                              layers */
  Prism_Parameters gocart_prism_param;     /* GoCart prism parameters */

  real tmp_r1;                             /* temporary memory */
  real tmp_r2;
  int tmp_i1;

  struct dynamic_thread_struct *next;      /* pointer to next */
} Dynamic_Thread;
```



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

* D : demension
* S : scalar
* V : vector
* T : Tensor
  

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

对于2D求解器，ND_ND=2。对于3D求解器，ND_ND=3。

对于2D求解器，`NV_VEC`将忽略第三个分量。

`NV_VEC(a)`定义一个名为a的符合当前维度的向量。

```c
/********************
第一个运算符只能为等号相关的符号
如=, +=, /=
********************/

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
```



```c
#if RP_3D
# define ND_OP(OP,x,y,z)((x)OP(y)OP(z))
#else
# define ND_OP(OP,x,y,z)((x)OP(y))
#endif
//对所有分量的操作
#define ND_SET(x0,x1,x2,y0,y1,y2)ND_D(x0,x1,x2,=,y0,y1,y2)
//两个分量相等
//(x0,x1,x2)=(y0,y1,y2);
#define ND_SUM(x0,x1,x2) ND_OP(+,x0,x1,x2)
//分量求和
//2D: x0+x1
//3D: x0+x1+x2
#define ND_DOT(x0,x1,x2,y0,y1,y2)ND_OP(+,(x0)*(y0),(x1)*(y1),(x2)*(y2))
//分量点乘
//(x0,x1,x2)·(y0,y1,y2);
#define ND_MAG2(x0,x1,x2)ND_DOT(x0,x1,x2,x0,x1,x2)
//分量模的平方
//|(x0,x1,x2)|^2
#define ND_MAG(x0,x1,x2)sqrt(ND_MAG2(x0,x1,x2))
//分量模
//|(x0,x1,x2)|
#if RP_3D
# define ND_CROSS_X(x0,x1,x2,y0,y1,y2)(((x1)*(y2))-((y1)*(x2)))
//叉乘的x分量
# define ND_CROSS_Y(x0,x1,x2,y0,y1,y2)(((x2)*(y0))-((y2)*(x0)))
//叉乘的y分量
#else
/* (x0,x1,0) X (y0,y1,0) */
# define ND_CROSS_X(x0,x1,x2,y0,y1,y2)(0.0)
# define ND_CROSS_Y(x0,x1,x2,y0,y1,y2)(0.0)
//对2D来说，叉乘的x,y分量均为0
#endif
# define ND_CROSS_Z(x0,x1,x2,y0,y1,y2)(((x0)*(y1))-((y0)*(x1)))
//叉乘的z分量
//分量叉乘
#define NDD_MAX(a0,a1,a2,b0,b1,b2)ND_VEC(MAX((a0),(b0)),MAX((a1),(b1)),MAX((a2),(b2)))
#define NDD_MIN(a0,a1,a2,b0,b1,b2)ND_VEC(MIN((a0),(b0)),MIN((a1),(b1)),MIN((a2),(b2)))
#define ND_MAX(a0,a1,a2,b0,b1,b2)ND_D((a0),(a1),(a2),=,MAX((a0),(b0)),MAX((a1),(b1)),MAX((a2),(b2)))
#define ND_MAX(a0,a1,a2,b0,b1,b2)ND_D((a0),(a1),(a2),=,MAX((a0),(b0)),MAX((a1),(b1)),MAX((a2),(b2)))
#define ND_MIN(a0,a1,a2,b0,b1,b2)ND_D((a0),(a1),(a2),=,MIN((a0),(b0)),MIN((a1),(b1)),MIN((a2),(b2)))
```

##### NV_ 向量操作宏

```c
#define NV_S(a,EQ,s)ND_VEC((a)[0]EQ(s),(a)[1]EQ(s),(a)[2]EQ(s))
//a = (s,s,s)
#define NV_V(a,EQ,x)ND_VEC((a)[0]EQ(x)[0],(a)[1]EQ(x)[1],(a)[2]EQ(x)[2])
//a = x (向量)
#define NV_D(a,EQ,x0,x1,x2)ND_D((a)[0],(a)[1],(a)[2],EQ,x0,x1,x2)
//a = (x0,x1,x2)
#define NV_VS(a,EQ,x,S,s)ND_VEC((a)[0]EQ(x)[0]S(s),(a)[1]EQ(x)[1]S(s),(a)[2]EQ(x)[2]S(s))
#define NV_DS(a,EQ,x0,x1,x2,S,s)ND_VEC((a)[0]EQ(x0)S(s),(a)[1]EQ(x1)S(s),(a)[2]EQ(x2)S(s))
#define NV_VV(a,EQ,x,V,y)ND_VEC((a)[0]EQ(x)[0]V(y)[0],(a)[1]EQ(x)[1]V(y)[1],(a)[2]EQ(x)[2]V(y)[2])
#define NV_DD(a,EQ,x0,x1,x2,V,y0,y1,y2) ND_VEC((a)[0]EQ(x0)V(y0),(a)[1]EQ(x1)V(y1),(a)[2]EQ(x2)V(y2))
#define NV_DV(a,EQ,x0,x1,x2,V,y) ND_VEC((a)[0]EQ(x0)V(y)[0],(a)[1]EQ(x1)V(y)[1],(a)[2]EQ(x2)V(y)[2])
#define NV_VV_S(a,EQ,x,V,y,S,s)ND_VEC((a)[0]EQ((x)[0]V(y)[0])S(s),(a)[1]EQ((x)[1]V(y)[1])S(s),(a)[2]EQ((x)[2]V(y)[2])S(s))
#define NV_DV_S(a,EQ,x0,x1,x2,V,y,S,s)ND_VEC((a)[0]EQ((x0)V(y)[0])S(s),(a)[1]EQ((x1)V(y)[1])S(s),(a)[2]EQ((x2)V(y)[2])S(s))
#define NV_DD_S(a,EQ,x0,x1,x2,V,y0,y1,y2,S,s)ND_VEC((a)[0]EQ((x0)V(y0))S(s),(a)[1]EQ((x1)V(y1))S(s),(a)[2]EQ((x2)V(y2))S(s))
#define NV_V_VS(a,EQ,x,V,y,S,s)ND_VEC((a)[0]EQ(x)[0]V((y)[0]S(s)),(a)[1]EQ(x)[1]V((y)[1]S(s)),(a)[2]EQ(x)[2]V((y)[2]S(s)))
#define NV_VS_VS(a,EQ,x,SX,sx,V,y,SY,sy)ND_VEC((a)[0]EQ(((x)[0]SX(sx))V((y)[0]SY(sy))),(a)[1]EQ(((x)[1]SX(sx))V((y)[1]SY(sy))),(a)[2]EQ(((x)[2]SX(sx))V((y)[2]SY(sy))))

#define NV_OP_V(a,EQ,f,b)ND_VEC((a)[0]EQ(f((b)[0])),(a)[1]EQ(f((b)[1])),(a)[2]EQ(f((b)[2])))
//a=f(b)
//f(b)=(f(b[0]),f(b[1]),f(b[2]))
```





```c
#define NVD_MAX(a,b)ND_VEC(MAX((a)[0],(b)[0]),MAX((a)[1],(b)[1]),MAX((a)[2],(b)[2]))
#define NVD_MIN(a,b)ND_VEC(MIN((a)[0],(b)[0]),MIN((a)[1],(b)[1]),MIN((a)[2],(b)[2]))
#define NV_MAX(a,b)NV_D((a),=,MAX((a)[0],(b)[0]),MAX((a)[1],(b)[1]),MAX((a)[2],(b)[2]))
#define NV_MIN(a,b)NV_D((a),=,MIN((a)[0],(b)[0]),MIN((a)[1],(b)[1]),MIN((a)[2],(b)[2]))

#define NV_MIN_I(v)((v)[0]<(v)[1]?((v)[0]<(v)[2]?0:2):((v)[1]<(v)[2]?1:2))
//向量v最小分量的索引
//v[3]={1,2,3}
//NV_MIN_I(v)=>1;

#define NV_SET(x, y)ND_SET(x[0], x[1], x[2], y[0], y[1], y[2]);
//x=y;
#define NV_DOT(x,y)ND_OP(+,(x)[0]*(y)[0],(x)[1]*(y)[1],(x)[2]*(y)[2])
//x·y
#define NV_MAG2(x)NV_DOT(x,x)
//|x|^2
#define NV_MAG(x)sqrt(NV_MAG2(x))
//|x|
#define NV_DST2(x1,x2)ND_OP(+,SQR((x2)[0]-(x1)[0]),SQR((x2)[1]-(x1)[1]),SQR((x2)[2]-(x1)[2]))
//|x1-x2|^2
#define NV_DST(x1,x2)sqrt(NV_DST2(x1,x2))
//|x1-x2|^2
#define NV_CROSS_X(x,y)ND_CROSS_X(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS_Y(x,y)ND_CROSS_Y(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS_Z(x,y)ND_CROSS_Z(x[0],x[1],x[2],y[0],y[1],y[2])
#define NV_CROSS(a,x,y)NV_D(a,=,NV_CROSS_X(x,y),NV_CROSS_Y(x,y),NV_CROSS_Z(x,y))
//a=x X y
```



#### DEFINE_EXECUTE_AT_END

```c
#define DEFINE_EXECUTE_AT_END(name) EXTERN_C void name(void)
```

在稳态计算的每次迭代后启用。

在瞬态计算的每个时间步后启用。

#### Get_Domain

```c
FLUENT_EXPORT Domain *Get_Domain(int id);
```

1指混合相的区域指针（未开启多相流时所有区域均为混合相）

当开启多相流时，可以为大于1的数。此时id为对应相的id

> id 是相的id而非区域id。


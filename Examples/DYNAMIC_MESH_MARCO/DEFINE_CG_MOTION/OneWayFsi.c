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
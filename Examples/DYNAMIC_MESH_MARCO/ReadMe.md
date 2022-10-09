# 动网格相关宏

## DEFINE_CG_MOTION

### 使用

```c
#define DEFINE_CG_MOTION(name, dt, vel, omega, time, dtime)   \
  EXTERN_C void name(Dynamic_Thread *dt, real vel[], real omega[], real time, real time)
```



| Type            | Parameter | Notes                                   |
| --------------- | --------- | --------------------------------------- |
| symbol          | name      | UDF名字                                 |
| Dynamic_Thread* | dt        | 指向动网格相关属性结构体的指针          |
| real            | vel[ ]    | 线速度。三个分量为xyz方向速度           |
| real            | omega[ ]  | 角速度。三个分量为以xyz轴为转轴的角速度 |
| real            | time      | 当前时间                                |
| real            | dtime     | 时间步                                  |
| void            | return    | 无返回值                                |

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

1. 在每个迭代步末尾计算物体当前所受作用力 $\mathbf{F}$

2. 计算加速度 $a=F/m$
3. 计算当前速度 $v_{t+1}=v_t+a\Delta t$

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
    /*主机与节点的数据交换*/
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

1指混合相的区域指针（未开启多相流时所有流体区域均为混合相）

当开启多相流时，可以为大于1的数。此时id为对应相的id

> id 是相的id而非区域id。

```c
Domain d = *Get_Domain(1);
```

很多UDF需要使用`Domain *`参数，但`DEFINE_EXECUTE_AT_END`不提供该参数。故需要自己生成一个。

#### 并行编程

![image-20220908142643182](https://s2.loli.net/2022/09/08/Ee5zv6XAFi2HIbP.png)

并行编程可以加速求解速度。但由于并行中的数据传递等问题，需要将程序并行化。

例如，求解全局最小，每个节点只知道自己所分配的区域的最小值。所有其他节点只知道节点0，而不知道其他节点。

并行编程相对串行编程，主要有两个步骤：

1. 单节点操作
2. 全局汇总

>fluent19.0（印象中的，不一定准确）以后已经没有串行版本了，均为并行版本。

##### Host 和 Node

* Host：解释来自 Cortex 的命令并将这些命令（和数据）传递给计算Node 0 以进行分发。
* Node 0 ：接受来自Host的命令和数据，并分发给其他节点。同时也进行分布计算。全局汇总操作在Node 0进行。
* Node 1-N：接受来自Node 0分发的数据，进行计算，计算完的数据再传回给Node 0。

有些操作需要由Host完成，而有些操作需要由Node 完成，需要将这些操作区分开

> Host中没有网格的数据，所有网格相关的操作需要在Host之外操作。
>
> 例如求解面平均压强，需要求解总力和总面积，再相处。最后的相处操作若未排除Host，那么就会出现除以0的问题，进而出现 float point exception 错误。

```c
/**********************************************************************/
/* Compiler Directives */
/**********************************************************************/
#if RP_HOST
/* only host process is involved */
#endif
#if RP_NODE
/* only compute nodes are involved */
#endif
/*********************************************************************/
/* Negated forms that are more commonly used */
/*********************************************************************/
#if !RP_HOST
/* only compute nodes are involved */
#endif
#if !RP_NODE
/* only host process is involved */
#endif
```

##### Host 和 Node之间的数据传递

```c
host_to_node_type_num(var1,var2,...)
```

* type:变量类型
* num:变量数量
*  var1,va2,...:需要传递的变量

```c
int domain_id_send_to_node = 1;
host_to_node_int_1(domain_id_send_to_node);
//意思就是说把一个名叫domain_id_send_to_node的int型变量送往节点
```

源码：

```c
/*传递布尔数，最多七个*/
#define host_to_node_boolean_1(a)
#define host_to_node_boolean_2(a,b)
#define host_to_node_boolean_3(a,b,c)
#define host_to_node_boolean_4(a,b,c,d)
#define host_to_node_boolean_5(a,b,c,d,e)
#define host_to_node_boolean_6(a,b,c,d,e,f)
#define host_to_node_boolean_7(a,b,c,d,e,f,g)

/*传递整数数，最多七个*/
#define host_to_node_int_1(a)
#define host_to_node_int_2(a,b)
#define host_to_node_int_3(a,b,c)
#define host_to_node_int_4(a,b,c,d)
#define host_to_node_int_5(a,b,c,d,e)
#define host_to_node_int_6(a,b,c,d,e,f)
#define host_to_node_int_7(a,b,c,d,e,f,g)
#define host_to_node_int64_1(a)
#define host_to_node_int64_2(a,b)
#define host_to_node_long_1(a)
#define host_to_node_long_2(a,b)
#define host_to_node_long_3(a,b,c)
#define host_to_node_long_4(a,b,c,d)
#define host_to_node_long_5(a,b,c,d,e)
#define host_to_node_long_6(a,b,c,d,e,f)
#define host_to_node_long_7(a,b,c,d,e,f,g)
#define host_to_node_long_long_1(a)
#define host_to_node_long_long_2(a,b)
#define host_to_node_long_long_3(a,b,c)
#define host_to_node_long_long_4(a,b,c,d)
#define host_to_node_long_long_5(a,b,c,d,e)
#define host_to_node_long_long_6(a,b,c,d,e,f)
#define host_to_node_long_long_7(a,b,c,d,e,f,g)
/******************************
****传递浮点数，最多传9个变量*******
建议使用real，而不是double和float*/
#define host_to_node_real_1(a)
#define host_to_node_real_2(a,b)
#define host_to_node_real_3(a,b,c)
#define host_to_node_real_4(a,b,c,d)
#define host_to_node_real_5(a,b,c,d,e)
#define host_to_node_real_6(a,b,c,d,e,f)
#define host_to_node_real_7(a,b,c,d,e,f,g)
#define host_to_node_real_8(a,b,c,d,e,f,g,h)
#define host_to_node_real_9(a,b,c,d,e,f,g,h,i)

#define host_to_node_float_1(a)
#define host_to_node_float_2(a,b)
#define host_to_node_float_3(a,b,c)
#define host_to_node_float_4(a,b,c,d)
#define host_to_node_float_5(a,b,c,d,e)
#define host_to_node_float_6(a,b,c,d,e,f)
#define host_to_node_float_7(a,b,c,d,e,f,g)
#define host_to_node_float_8(a,b,c,d,e,f,g,h)
#define host_to_node_float_9(a,b,c,d,e,f,g,h,i)

#define host_to_node_double_1(a)
#define host_to_node_double_2(a,b)
#define host_to_node_double_3(a,b,c)
#define host_to_node_double_4(a,b,c,d)
#define host_to_node_double_5(a,b,c,d,e)
#define host_to_node_double_6(a,b,c,d,e,f)
#define host_to_node_double_7(a,b,c,d,e,f,g)
#define host_to_node_double_8(a,b,c,d,e,f,g,h)
#define host_to_node_double_9(a,b,c,d,e,f,g,h,i)
/**********************************************/
//传递枚举，本质上是一个整数
#define host_to_node_enum_1(a)
//传递文件路径，本质上是一个字符串
#define host_to_node_sync_file(f)
```



    host_to_node_type(var_name,var_num)

* type:数组变量的类型，字符串数组为string而非char
* var_name:数组变量的名字
* var_num:数组的长度

```c
//EXAMPLE 1:
char my_name[]="satisfactions";
host_to_node_string(my_name,14);//注意字符串数组后面隐藏有一个'\0'

//EXAMPLE 2:
int domain_ids[2]={10,15};
host_to_node_int(domain_id,2);
```

源码：

```c
#define host_to_node_real(a,b)
#define host_to_node_float(a,b)
#define host_to_node_double(a,b)

#define host_to_node_int(a,b)
#define host_to_node_long(a,b)
#define host_to_node_long_long(a,b)

#define host_to_node_boolean(a,b)

#define host_to_node_string(a,b)
```



 同理，从节点向主机传递数据为

   ```c
   node_to_host_type_num(var1,var2,...)
   node_to_host_type(var_name,var_num)
   ```

```c
#define node_to_host_boolean_1(a)

#define node_to_host_double_1(a)
#define node_to_host_double_2(a,b)
#define node_to_host_double_3(a,b,c)
#define node_to_host_double_4(a,b,c,d)
#define node_to_host_double_5(a,b,c,d,e)
#define node_to_host_double_6(a,b,c,d,e,f)
#define node_to_host_double_7(a,b,c,d,e,f,g)

#define node_to_host_int_1(a)
#define node_to_host_int_2(a,b)
#define node_to_host_int_3(a,b,c)
#define node_to_host_int_4(a,b,c,d)
#define node_to_host_int_5(a,b,c,d,e)
#define node_to_host_int_6(a,b,c,d,e,f)
#define node_to_host_int_7(a,b,c,d,e,f,g)
/*源码里是这样，怀疑它有问题*/
#define host_to_node_int64_1(a)
#define host_to_node_int64_2(a,b)
/*******************/
#define node_to_host_long_1(a)
#define node_to_host_long_2(a,b)
#define node_to_host_long_3(a,b,c)
#define node_to_host_long_4(a,b,c,d)
#define node_to_host_long_5(a,b,c,d,e)
#define node_to_host_long_6(a,b,c,d,e,f)
#define node_to_host_long_7(a,b,c,d,e,f,g)

#define node_to_host_long_long_1(a)
#define node_to_host_long_long_2(a,b)
#define node_to_host_long_long_3(a,b,c)
#define node_to_host_long_long_4(a,b,c,d)
#define node_to_host_long_long_5(a,b,c,d,e)
#define node_to_host_long_long_6(a,b,c,d,e,f)
#define node_to_host_long_long_7(a,b,c,d,e,f,g)

#define node_to_host_real_1(a)
#define node_to_host_real_2(a,b)
#define node_to_host_real_3(a,b,c)
#define node_to_host_real_4(a,b,c,d)
#define node_to_host_real_5(a,b,c,d,e)
#define node_to_host_real_6(a,b,c,d,e,f)
#define node_to_host_real_7(a,b,c,d,e,f,g)

#define node_to_host_float_1(a)
#define node_to_host_float_2(a,b)
#define node_to_host_float_3(a,b,c)
#define node_to_host_float_4(a,b,c,d)
#define node_to_host_float_5(a,b,c,d,e)
#define node_to_host_float_6(a,b,c,d,e,f)
#define node_to_host_float_7(a,b,c,d,e,f,g) 

#define node_to_host_real(a,b)
#define node_to_host_float(a,b)
#define node_to_host_double(a,b)
#define node_to_host_int(a,b)
#define node_to_host_long(a,b)
#define node_to_host_long_long(a,b)
#define node_to_host_boolean(a,b)
#define node_to_host_string(a,b)
```

> 注意，没有node_to_host_sync_file, node_to_host_enum_1，支持的最大变量数也有差别不一样。

##### 并行循环

并行循环与串行循环不同，其涉及到两个步骤：

1. 节点本地处理
2. 全局汇总操作

###### 节点循环

![image-20220908165220941](https://s2.loli.net/2022/09/08/FQt9ykAKGhZCurI.png)

```c
beging_c_loop_int(cell,thread)
{
    //do somthing
}end_c_loop_int(cell,thread)
```

![image-20220908165822687](https://s2.loli.net/2022/09/08/PzXemtFKhRqG6wC.png)

```c
beging_f_loop(face,thread)
{
    if(PRINCIPAL_FACE_P(face,thread))
    {
        //do somthing
    }
}end_f_loop(face,thread)
```

###### 全局汇总

此类宏的名称由四部分组成
* 前缀：均为PRF_G
*  数据类型标志：操作的数据的类型
     *  I--int
     *  R--real
     *  L--logical 
     *  B–boolean
* 操作标志：进行什么操作
                 * SUM--求和
     * HIGH--求最大值
     * LOW--求最小值
     *  AND--逻辑和运算
     *  OR--逻辑或运算        
* 版本标志：此类宏有两个版本
                  * 尾缀加1，表示对单个简单变量进行操作，并可返回一个变量。此时宏的使用为
                      `output=PRF_G[Type][Operation]1(x);`
                  *  尾缀不加1，表示对数组进行操作,不返回变量。此时宏的使用为
                      ` PRF_G[Type][Operation](x,N,temp_storage)`
                      * x:进行操作的量级最终的返回值（数组）
                      *  N:数组的长度
                      *  temp_storage:操作中需要使用的临时变量，需要和x类型长度相同

```c
//EXAMPLE 1:
//假定现在已经在每个节点对x进行了求和
x=PRF_GRSUM1(x);
//表示对一个类型为real的变量x进行全局求和，求和之后的值再赋给x。

//EXAMPLE 2：
int N = 3;
real x[N]={max_temp,max_press,max_vel};//x的三个成员分别表示温度，压力，速度。
real temp[N];
//假定现在已经在每个节点对x的三个分量求得了最大值
PRF_GRHIGH(x,N,temp);
```

###### Lookup_Thread

```c
FLUENT_EXPORT Thread *Lookup_Thread(Domain *, int id);
```

id : boundaty of cell zone id

###### Example. 1 求某个区域的面积

```c
/*串行版*/
real area[3];
real total_area = 0.0;
begin_f_loop(face, thread)
{
    F_AREA(area, face, thread);
    total_area += NV_MAG(area);
}end_f_loop(face, thread)
    
/*并行版*/
real total_area = 0.0;
#if !RP_HOST
    real area[3];
#endif /* !RP_HOST */
#if !RP_HOST
    begin_f_loop(face, thread)
    {
       if (PRINCIPAL_FACE_P(face, thread)) 
    	{
        	F_AREA(area, face, thread);
        	total_area += NV_MAG(area);
    	} 
    }end_f_loop(face, thread)
#if RP_NODE /* Perform node synchronized actions here */       
    total_area = PRF_GRSUM1(total_area);
#endif /* RP_NODE */
#endif /* !RP_HOST */
```



###### Example. 2 求某个区域的体积

```c
/*串行版*/
real total_vol = 0.0;
begin_c_loop(cell, thread)
{
    total_vol += C_VOLUME(cell,thread);
}end_c_loop(cell, thread)
    
/*并行版*/
real total_vol = 0.0;
#if !RP_HOST
    begin_c_loop_int(cell, thread)
	{
    	total_vol += C_VOLUME(cell,thread);
	}end_c_loop_int(cell, thread)
#if RP_NODE /* Perform node synchronized actions here */       
    total_vol = PRF_GRSUM1(total_vol);
#endif /* RP_NODE */
#endif /* !RP_HOST */
```

#### Get_Report_Definition_Values

```c
FLUENT_EXPORT int Get_Report_Definition_Values(const char *name, int timeStepOrIteration, int *nrOfvalues, real *values, int *ids, int *index);    
```

- **[input]** const char* name : report definition的名字
- **[input]** int type : 获取每次迭代数据（0）还是每次时间步的数据（1）。瞬态计算只能用1.
- **[output]** int* nrOfvalues ：该report definition的变量数
- **[output]** real* values : 该report definition的变量
- **[output]** int* ids : 跟该report definition相关的surface/zone的ID。（如果 per-zone 或 per-surface 选项关闭，且surfaces/zones数量大于1，将返回-1
- **[output]** int* index : 该report definition的索引（第几次迭代/时间步）
- **[return]** 0-获取成功/1-该report definition不存在，获取失败

一般来说，需要调用两次。第一次，获取变量数，并按此分配内存空间。第二次再获取相应的变量。

```c
int nrOfvalues=0;
real *values;
int *ids;
int index;
int counter;

/*第一次调用*/
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
    /***********/
    /***操作*****/
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
```

## DEFINE_SDOF_PROPERTIES

```c
#define DEFINE_SDOF_PROPERTIES(name, properties, dt, time, dtime) \
  EXTERN_C void name(real *properties, Dynamic_Thread *dt, real time, real dtime)
```

| Type            | Parameter  | Notes                          |
| --------------- | ---------- | ------------------------------ |
| symbol          | name       | UDF名字                        |
| real*           | properties | 指向六自由度属性数组的指针     |
| Dynamic_Thread* | dt         | 指向动网格相关属性结构体的指针 |
| real            | time       | 当前时间                       |
| real            | dtime      | 时间步                         |
| void            | return     | 无返回值                       |

### 六自由度求解器

利用物体受到的力和力矩计算物体重心的平动和转动。
$$
\dot{\vec{v}}_G=\frac{1}{m} \sum \left(\vec{f}_{G,e}+\vec{G}\right )
$$

$$
\dot{\vec{\omega}}_B=L^{-1}\left(\sum \vec{M}_B-\vec{\omega}_B \times L \vec{\omega}_B\right)
$$

$$
\vec{M}_B=R \vec{M}_G
$$

$$
R=
\left[\begin{array}{ccc}
C_\theta C_\psi & C_\theta S_\psi & -S_\theta \\
S_\phi S_\theta C_\psi-C_\phi S_\psi & S_\phi S_\theta S_\psi+C_\phi C_\psi & S_\phi C_\theta \\
C_\phi S_\theta C_\psi+S_\phi S_\psi & C_\phi S_\theta S_\psi-S_\phi C_\psi & C_\phi C_\theta
\end{array}\right]
$$

一般来说$C_\chi=\cos (\chi)$ ， $S_\chi=\sin (\chi)$ ; $\phi$, $\theta$,$\psi$为欧拉角。

### 使用

#### 六自由度对象



![image-20220909165038344](https://s2.loli.net/2022/09/09/TemJSvzna62Irl3.png)

```c
/* ,/mesh/six_dof.h */

typedef struct six_dof_object
{

  char name[132];
  real mass;

  real Ixx;
  real Iyy;
  real Izz;
  real Ixy;
  real Iyz;
  real Ixz;
  /*************One DOF Parameters*************/
  cxboolean onedof_t_p;    	//是否开启单自由度平动
  cxboolean onedof_r_p;    	//是否开启单自由度转动
  cxboolean onedof_cons_p; 	//是否开启位置约束

  real dir[3];             	//单自由度平动方向
  real rot_loc[3];			//单自由度旋转中心

  real loc;
  real loc_n;
  real init;
  real min;
  real max;

  real preload;
  real spring;
  /******************One DOF******************/
  struct six_dof_object *next;
} Six_DOF_Object;
```

#### 六自由度属性

```c
typedef enum
{
  //质量
  SDOF_MASS = 0,	
  //转动惯量
  SDOF_IXX,					
  SDOF_IYY,
  SDOF_IZZ,
  SDOF_IXY,
  SDOF_IXZ,
  SDOF_IYZ,
  //六自由度参考系：FALSE-全局坐标系；TRUE-局部坐标系
  SDOF_LOAD_LOCAL,         /* boolean */
      //外力
  SDOF_LOAD_F_X,
  SDOF_LOAD_F_Y,
  SDOF_LOAD_F_Z,
    //外力矩
  SDOF_LOAD_M_X,
  SDOF_LOAD_M_Y,
  SDOF_LOAD_M_Z,
    //TURE-使用自定义变换矩阵；FALSE-不使用
  SDOF_CUSTOM_TRANS,       /* boolean */
      //变换矩阵
  SDOF_CTRANS_11,
  SDOF_CTRANS_12,
  SDOF_CTRANS_13,
  SDOF_CTRANS_21,
  SDOF_CTRANS_22,
  SDOF_CTRANS_23,
  SDOF_CTRANS_31,
  SDOF_CTRANS_32,
  SDOF_CTRANS_33,
    //变换矩阵2
  SDOF_DTRANS_11,
  SDOF_DTRANS_12,
  SDOF_DTRANS_13,
  SDOF_DTRANS_21,
  SDOF_DTRANS_22,
  SDOF_DTRANS_23,
  SDOF_DTRANS_31,
  SDOF_DTRANS_32,
  SDOF_DTRANS_33,
    //平动自由度
  SDOF_ZERO_TRANS_X,       /* all zero switches are boolean */
  SDOF_ZERO_TRANS_Y,
  SDOF_ZERO_TRANS_Z,
    //旋转自由度
  SDOF_ZERO_ROT_X,
  SDOF_ZERO_ROT_Y,
  SDOF_ZERO_ROT_Z,
    //半模型的对称面法向量
  SDOF_SYMMETRY_X,
  SDOF_SYMMETRY_Y,
  SDOF_SYMMETRY_Z,
  SDOF_SIZE_PROP           /* has to be the last entry */
} SDOF_Prop;
```

#### 六自由度属性设置

可以通过类似`properties[SDOF_MASS]`的方法设置六自由度属性

或者通过以下宏设置六自由度属性：

```c
#define SDOFP_MASS(s)         (s[SDOF_MASS])
#define SDOFP_MOI(s)          (s+SDOF_IXX)          /* moments of inertia */
#define SDOFP_POI(s)          (s+SDOF_IXY)          /* products of inertia */
#define SDOFP_LOAD_LOCAL(s)   (s[SDOF_LOAD_LOCAL])  /* load forces/moments */
#define SDOFP_LOAD_F(s)       (s+SDOF_LOAD_F_X)
#define SDOFP_LOAD_M(s)       (s+SDOF_LOAD_M_X)
#define SDOFP_CUSTOM_TRANS(s) (s[SDOF_CUSTOM_TRANS])/* costum transformations */
#define SDOF_CTRANS           SDOF_CTRANS_11
#define SDOF_DTRANS           SDOF_DTRANS_11
#define SDOFP_CTRANS(s)       (s+SDOF_CTRANS)
#define SDOFP_DTRANS(s)       (s+SDOF_DTRANS)
#define SDOFP_ZERO_TRANS(s)   (s+SDOF_ZERO_TRANS_X)
#define SDOFP_ZERO_ROT(s)     (s+SDOF_ZERO_ROT_X)
#define SDOFP_SYMMETRY(s)     (s+SDOF_SYMMETRY_X)   /* symmetry plane normal */
```

#### 获取六自由度对象

```c
sdof_obj = Get_SDOF_Object(DT_PU_NAME(dt));
```

```c
#define DT_PU_NAME(s)          ((s)->profile_udf_name)   //通过动网格指针获取六自由度对象的名字。
FLUENT_EXPORT Six_DOF_Object *Get_SDOF_Object(char[132]);//通过名字获取六自由度对象。
```

#### 设置六自由度对象的属性

可以通过以下宏设置六自由度对象的属性（不推荐直接设置对象属性）

```c
#define SDOFO_NAME(sobj)      ((sobj)->name)
#define SDOFO_MASS(sobj)      ((sobj)->mass)
#define SDOFO_IXX(sobj)       ((sobj)->Ixx)
#define SDOFO_IYY(sobj)       ((sobj)->Iyy)
#define SDOFO_IZZ(sobj)       ((sobj)->Izz)
#define SDOFO_IXY(sobj)       ((sobj)->Ixy)
#define SDOFO_IYZ(sobj)       ((sobj)->Iyz)
#define SDOFO_IXZ(sobj)       ((sobj)->Ixz)
#define SDOFO_1DOF_T_P(sobj)  ((sobj)->onedof_t_p)
#define SDOFO_1DOF_R_P(sobj)  ((sobj)->onedof_r_p)
#define SDOFO_CONS_P(sobj)    ((sobj)->onedof_cons_p)
#define SDOFO_DIR(sobj)       ((sobj)->dir)
#define SDOFO_CENTER_ROT(sobj)((sobj)->rot_loc)
#define SDOFO_INIT(sobj)      ((sobj)->init)
#define SDOFO_LOC(sobj)       ((sobj)->loc)
#define SDOFO_LOC_N(sobj)     ((sobj)->loc_n)
#define SDOFO_MIN(sobj)       ((sobj)->min)
#define SDOFO_MAX(sobj)       ((sobj)->max)
#define SDOFO_F(sobj)         ((sobj)->preload)
#define SDOFO_K(sobj)         ((sobj)->spring)
#define SDOFO_NEXT(sobj)      ((sobj)->next)
```

### 样例

#### Example 1. 定义六自由度属性

```c
#include "udf.h"
DEFINE_SDOF_PROPERTIES(sdof_prop, prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IZZ] = 100.0;
}
```

#### Example 2. 定义半模型的属性

```c
#include "udf.h"
DEFINE_SDOF_PROPERTIES(sdof_prop, prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IZZ] = 100.0;
    prop[SDOF_SYMMETRY_X] = 0;
    prop[SDOF_SYMMETRY_Y] = 0;
    prop[SDOF_SYMMETRY_Z] = 1;
}
```

#### Example 3. 限制转动

```c
#include "udf.h"
DEFINE_SDOF_PROPERTIES(sdof_prop, prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IZZ] = 100.0;
    prop[SDOF_ZERO_ROT_X] = TRUE;
    prop[SDOF_ZERO_ROT_Y] = TRUE;
    prop[SDOF_ZERO_ROT_Z] = FALSE;
}
```

#### Example 4. 限制平动

```c
#include "udf.h"
DEFINE_SDOF_PROPERTIES(sdof_prop, prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IZZ] = 100.0;
    prop[SDOF_ZERO_TRANS_X] = TRUE;
    prop[SDOF_ZERO_TRANS_Y] = TRUE;
    prop[SDOF_ZERO_TRANS_Z] = FALSE;
}
```

#### Example 5. 外力作用

![image-20220916155044644](https://s2.loli.net/2022/09/16/hq2KHxU1BFfIEkd.png)

初始状态：
$$
F_z=1N;
$$

$$
M_z=1N\cdot m
$$

![image-20220916160004534](https://s2.loli.net/2022/09/16/Rk4EfLTyF2mKrUV.png)
$$
F_z=1N;
$$

$$
M_z=F_z\frac{\cos{(\theta + 45^o)}}{\cos{45^o}}
$$


```c
#include "udf.h"

#define F_Z 1
#define DIST 1

DEFINE_SDOF_PROPERTIES(external_force,prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IYY] = 150.0;
    prop[SDOF_IZZ] = 100.0;
    real theta = DT_THETA(dt)[2];
    prop[SDOF_LOAD_F_Z] = F_Z;
    porp[SDOF_LOAD_M_Z] = F_Z/0.70710678*cos(theta+1.570796327);
}
```

#### Example 6. 单自由度平动

```c
#include "udf.h"

DEFINE_SDOF_PROPERTIES(one_dof_trans,prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IYY] = 150.0;
    prop[SDOF_IZZ] = 100.0;
    
    sdof_obj=Get_SDOF_Object(DT_PU_NAME(dt));
    if(NULLP(sdof_obj))
    {
        SDOFO_1DOF_T_P(sdof_obj)=TRUE;		//开启单自由度平动
        SDOFO_1DOF_R_P(sdof_obj)=FALSE;		//关闭单自由度转动
        SDOFO_DIR(sdof_obj)[0]=0.0;			//单自由度平动方向矢量
        SDOFO_DIR(sdof_obj)[1]=0.0;
        SDOFO_DIR(sdof_obj)[2]=1.0;
        SDOFO_CONS_P(sdof_obj)=TRUE;		//位置限制
        
        SDOFO_LOC(sdof_obj)=0.0;			//初始位置
        SDOFO_MIN(sdof_obj)=-0.5;			//最小限制
        SDOFO_MAX(sdof_obj)=0.5;			//最大限制
        SDOFO_F(sdof_onj)=0.0;				//预作用力
        SDOFO_K(sdof_obj)=0.0;				//弹簧常数
        
        SDOFO_INIT(sdof_obj)=SDOF_LOC(sdof_obj);
        SDOFO_LOC_N(sdof_obj)=SDOF_LOC(sdof_obj);
    }   
}
```

#### Example 6. 单自由度转动

```c
#include "udf.h"

DEFINE_SDOF_PROPERTIES(one_dof_rot,prop,dt,time,dtime)
{
    prop[SDOF_MASS] = 800.0;
    prop[SDOF_IXX] = 200.0;
    prop[SDOF_IYY] = 150.0;
    prop[SDOF_IZZ] = 100.0;
    
    sdof_obj=Get_SDOF_Object(DT_PU_NAME(dt));
    if(NULLP(sdof_obj))
    {
        SDOFO_1DOF_T_P(sdof_obj)=TRUE;		//关闭单自由度平动
        SDOFO_1DOF_R_P(sdof_obj)=FALSE;		//开启单自由度转动
        SDOFO_DIR(sdof_obj)[0]=0.0;			//转动中心坐标
        SDOFO_DIR(sdof_obj)[1]=0.0;
        SDOFO_DIR(sdof_obj)[2]=1.0;
        SDOFO_CONS_P(sdof_obj)=TRUE;		//位置限制
        
        SDOFO_LOC(sdof_obj)=0.0;			//初始位置
        SDOFO_MIN(sdof_obj)=-0.5;			//最小限制
        SDOFO_MAX(sdof_obj)=0.5;			//最大限制
        SDOFO_F(sdof_onj)=0.0;				//预作用力矩
        SDOFO_K(sdof_obj)=0.0;				//扭力弹簧常数
        
        SDOFO_INIT(sdof_obj)=SDOF_LOC(sdof_obj);
        SDOFO_LOC_N(sdof_obj)=SDOF_LOC(sdof_obj);
    }   
}
```

#### Example 7. 双向流体-刚体运动耦合

```c
/*实现简单的流体与刚体运动的双向耦合*/
/*需要开启Implict Update*/
/*六自由度求解器一定会考虑重力，不需要手动添加重力的影响*/
/*手动添加的均为外力*/
#include "udf.h"

/*****define some constants*****/
#define MASS 1
/********************/

static real total_force_z;

DEFINE_SDOF_PROPERTIES(one_dof_trans,prop,dt,time,dtime)
{
    prop[SDOF_MASS] = MASS;
    prop[SFOF_LOAD_F_Z] = total_froce_z;
    sdof_obj=Get_SDOF_Object(DT_PU_NAME(dt));
    if(NULLP(sdof_obj))
    {
        SDOFO_1DOF_T_P(sdof_obj)=TRUE;		//开启单自由度平动
        SDOFO_1DOF_R_P(sdof_obj)=FALSE;		//关闭单自由度转动
        SDOFO_DIR(sdof_obj)[0]=0.0;			//单自由度平动方向矢量
        SDOFO_DIR(sdof_obj)[1]=0.0;
        SDOFO_DIR(sdof_obj)[2]=1.0;
        SDOFO_CONS_P(sdof_obj)=TRUE;		//位置限制
        
        SDOFO_LOC(sdof_obj)=0.0;			//初始位置
        SDOFO_MIN(sdof_obj)=-0.5;			//最小限制
        SDOFO_MAX(sdof_obj)=0.5;			//最大限制
        SDOFO_F(sdof_onj)=0.0;				//预作用力
        SDOFO_K(sdof_obj)=0.0;				//弹簧常数
        
        SDOFO_INIT(sdof_obj)=SDOF_LOC(sdof_obj);
        SDOFO_LOC_N(sdof_obj)=SDOF_LOC(sdof_obj);
    }   
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
    /*主机与节点的数据交换*/
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
        
        force_temp = PRF_GRSUM1(force_temp);
#endif /* RP_NODE */
#endif /* !RP_HOST */
/**********************************/
    total_force_z += force_temp;
}

/*利用Report definition获取作用力*/
DEFINE_ADJUST(compute_vel_from_definition)
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

#### 动网格工具宏DT_

```c
/*dynamesh_tools.h*/
typedef struct dynamic_thread_rigid_body_state
{
  real cg[3];                              /* center of gravity
                                              position wrt global */
  quaternion q;                            /* orientation quaternion */
  real theta[3];                           /* orientation angles wrt global,
                                              Euler angles for 6-dof */
  real v_cg[3];                            /* instantaneous cg velocity
                                              vector */
  real omega_cg[3];                        /* instantaneous cg angular
                                              velocity vector */
  real acc_cg[3];                          /* instantaneous
                cg acceleration vector */
  real alpha_cg[3];                        /* instantaneous cg angular
                acceleration vector */
  real dir[3];                             /* direction of motion */

  real W[3];                               /* Convective angular velocity */
  real A[3];                               /* Convective angular acceleration */
  real torque[3];                          /* Torque */
} Dynamic_Thread_Rigid_Body_State;
```



```c
/*dynamesh_tools.h*/
#define DT_THREAD_NEXT(s)      ((s)->next)
#define DT_THREAD(s)           ((s)->thread)

#define DT_RB_CURR_STATE(s)    ((s)->current_state)
#define DT_CG(s)               ((s)->current_state.cg)
//当前重心坐标
#define DT_Q(s)                ((s)->current_state.q)
//当前刚体的四元数
#define DT_VEL_CG(s)           ((s)->current_state.v_cg)
//瞬时重心速度矢量
#define DT_OMEGA_CG(s)         ((s)->current_state.omega_cg)
//瞬时重心角速度矢量
#define DT_ACC_CG(s)           ((s)->current_state.acc_cg)
//瞬时加速度矢量
#define DT_ALPHA_CG(s)         ((s)->current_state.alpha_cg)
//瞬时角加速度矢量
#define DT_THETA(s)            ((s)->current_state.theta)
//随体坐标系欧拉角
#define DT_DIR(s)              ((s)->current_state.dir)
//运动方向矢量
#define DT_W(s)                ((s)->current_state.W)
//Convective angular velocity Omega=R^{-1}*dR/dt
//R:旋转矩阵，随体坐标和全局坐标的转换矩阵
#define DT_A(s)                ((s)->current_state.A)
//对流角加速度
#define DT_TORQUE(s)           ((s)->current_state.torque)
//当前扭矩

/*初始状态宏，和上面一样，但是是初始状态*/
#define DT_RB_INIT_STATE(s)    ((s)->init_state)
#define DT_RB_TMP_STATE(s)     ((s)->tmp_state)

#define DT_INIT_CG(s)          ((s)->init_state.cg)
#define DT_INIT_Q(s)           ((s)->init_state.q)
#define DT_INIT_THETA(s)       ((s)->init_state.theta)
#define DT_INIT_VEL_CG(s)      ((s)->init_state.v_cg)
#define DT_INIT_OMEGA_CG(s)    ((s)->init_state.omega_cg)
#define DT_INIT_ACC_CG(s)      ((s)->init_state.acc_cg)
#define DT_INIT_ALPHA_CG(s)    ((s)->init_state.alpha_cg)
#define DT_INIT_DIR(s)         ((s)->init_state.dir)
/*初始状态宏，和上面一样，但是是初始状态*/


#define DT_DIR_REF(s)          ((s)->dir_ref)
//运动参考方向
#define DT_DIR_PREV(s)         ((s)->dir_prev)
//之前运动的参考方向
#define DT_AXIS(s)             ((s)->axis)
//运动的随体坐标轴
#define DT_GEOM_ORIGIN(s)      ((s)->geom_origin)
#define DT_GEOM_AXIS(s)        ((s)->geom_axis)
#define DT_GEOM_RADIUS(s)      ((s)->geom_radius)
#define DT_FEATURE_P(s)        ((s)->geom_feature_p)
#define DT_FEATURE_ANGLE(s)    ((s)->geom_feature_angle)
#define DT_UPDATE_FNC(s)       ((s)->update)
#define DT_LEN(s)              ((s)->len)
#define DT_MIN_LSCALE(s)       (DT_REMESH_GLOBALS_P(s)?         \
                                remesh_min_lscale:(s)->len[0])
#define DT_MAX_LSCALE(s)       (DT_REMESH_GLOBALS_P(s)?        \
                                remesh_max_lscale:(s)->len[1])
#define DT_MAX_SKEW(s)         (DT_REMESH_GLOBALS_P(s)?                \
                                (CELL_THREAD_P(DT_THREAD(s))?           \
                                 remesh_max_cell_skew:remesh_max_face_skew): \
                                (s)->len[2])
#define DT_REFO(s)             ((s)->refo)
#define DT_PU_NAME(s)          ((s)->profile_udf_name)
#define DT_VLIST(s)            ((s)->lnodes)
#define DT_TYPE(s)             ((s)->type)
#define DT_UDF_TYPE(s)         ((s)->udf_type)
#define DT_HEIGHT(s)           ((s)->h)
#define DT_SLIDE_P(s)          ((s)->sliding)
#define DT_SLIDE_METHOD(s)     ((s)->sliding_method)
#define DT_SLIDE_ELEMENTS(s)   ((s)->sliding_elements)
#define DT_REMESH_P(s)         ((s)->remesh)
#define DT_REMESH_METHOD(s)    ((s)->remeshing_method)
#define DT_REMESH_GLOBALS_P(s) ((s)->remesh_globals_p)
#define DT_LAYER_P(s)          ((s)->layering)
#define DT_BL_DEFORM_P(s)      ((s)->boundary_layer_deform)
#define DT_UDF_DEFORM_P(s)     ((s)->user_defined_deform)
#define DT_BC_EXCLUDE_MOTION_P(s) ((s)->bc_exclude_motion)
#define DT_COUNTER(s)          ((s)->face_remesh_count)
#define DT_LOOPS(s)            ((s)->loops)
#define DT_NLOOPS(s)           ((s)->nloops)
#define DT_LAYER(s)            ((s)->layer)
#define DT_LAY_FAC(s)          ((s)->layer_factor)
#define DT_RACTION(s)          ((s)->face_remesh_action)
#define DT_GEOM_NAME(s)        ((s)->geometry_name)
#define DT_REMESH_SEP(s)       ((s)->separate_region)
#define DT_SDOF_P(s)           ((s)->sdof_p)
#define DT_PERDISP_P(s)        ((s)->perdisp_p)
#define DT_SDOF_CONT_P(s)      ((s)->sdof_contribute_p)
#define DT_HIDEAL_UDF(s)       ((s)->h_udf_name)
#define DT_CONTACT_UDF(s)      ((s)->contact_udf_name)
#define DT_UPDATE_STATE(s)     ((s)->update_state)
#define DT_RTMP1(s)            ((s)->tmp_r1)
#define DT_RTMP2(s)            ((s)->tmp_r2)
#define DT_ITMP1(s)            ((s)->tmp_i1)
#define DT_GOCART(s)           ((s)->gocart_param)
#define DT_GOCART_MAX(s)       ((s)->gocart_param[0])
#define DT_GOCART_RATE(s)      ((s)->gocart_param[1])
#define DT_GOCART_QUALITY(s)   ((s)->gocart_param[2])
#define DT_GOCART_RATIO(s)     ((s)->gocart_param[3])
#define DT_GOCART_INTERVAL(s)  ((s)->gocart_param[4])
#define DT_GOCART_PRISMS_P(s)  ((s)->gocart_prisms_p)
#define DT_GOCART_PRISM_TYPE(s) ((s)->gocart_prism_param.offset_method)
#define DT_GOCART_PRISM_H(s)   ((s)->gocart_prism_param.h)
#define DT_GOCART_PRISM_AR(s)  ((s)->gocart_prism_param.ar)
#define DT_GOCART_PRISM_NLAYER(s) ((s)->gocart_prism_param.nlayer)
#define DT_GOCART_PRISM_RATE(s) ((s)->gocart_prism_param.growth_rate)
#define DT_SOP_SWITCH(s)       ((s)->sop_comp)
#define DT_SOP_METHOD_NAME(s)  ((s)->sop_type_name)
#define DT_SOP_METHOD(s)       ((s)->sop_type)
#define DT_SOP_SCALE(s)        ((s)->sop_scale)
#define DT_NESTED_P(s)         ((s)->nested_p)
#define DT_NEST_THREAD(s)      ((s)->nest_thread)
#define DT_NEST_LOC_ROT_P(s)   ((s)->nested_local_rot_p)
#define DT_NEST_LOC_TRAN_P(s)  ((s)->nested_local_tran_p)
```

## DEFINE_DYNAMIC_ZONE_PROPERTY

```c
#define DEFINE_DYNAMIC_ZONE_PROPERTY(name, dt, lh)  \
  EXTERN_C void name(Dynamic_Thread *dt, real *lh)
```

| Type            | Parameter | Notes                                    |
| --------------- | --------- | ---------------------------------------- |
| symbol          | name      | UDF名字                                  |
| Dynamic_Thread* | dt        | 指向动网格相关属性结构体的指针           |
| real *          | lh        | 指向网格层高的指针或旋转中心数组的指针。 |

##  DEFINE_CONTACT

定义检测到发生接触之后的操作。

```c
#define DEFINE_CONTACT(name, dt, contacts) \
  EXTERN_C void name(Dynamic_Thread *dt, Objp *contacts)
```

| Type            | Parameter | Notes                                                  |
| --------------- | --------- | ------------------------------------------------------ |
| symbol          | name      | UDF名字                                                |
| Dynamic_Thread* | dt        | 指向动网格相关属性结构体的指针                         |
| Objp *          | contacts  | 指向接触检测事件中涉及的单元的链表的指针。以 NULL 结尾 |

### 补充知识

#### 窄缝的控制

窄缝的控制主要有以下四种方法：

1. gap model
2. contact detection
3. dynamic mesh events
4. 手动控制

##### Gap Model

![image-20220914152014536](https://s2.loli.net/2022/09/14/DvCYsxiMhtm4k2o.png)

![image-20220914152308485](https://s2.loli.net/2022/09/14/IqfvhPibMCzKLRZ.png)

###### Flow-Blocking

判定为Gap的地方的流动会完全禁止。

###### Flow-Modeling

$$
\mathrm{Re}_{\mathrm{gap}}=\frac{\rho_{\mathrm{avg}} u_{\mathrm{avg}} L}{\mu_{\mathrm{avg}}}
$$

通过设置的雷诺数控制gap区域的流动

###### Limitations

不能在和以下设置同时使用：

- density-based solver
- axisymmetric swirl
- Eulerian multiphase model
- ablation model
- Eulerian wall film model
- Lagrangian wall film model
- solidification/melting model
- electric potential model
- Lithium-ion battery model
- acoustics models
- structural model
- discrete phase model (DPM)
- radiation models
- species models (with the exception of species transport for mixing but not reacting)
- pollutant formation models
- reactor network model
- decoupled detailed chemistry pollutant model
- multiphase flow with species transport
- the following turbulence models / options: Reynolds stress models (RSM), Scale-Adaptive Simulation (SAS) model, Detached eddy simulation (DES) model, Large Eddy Simulation (LES) model, Scale-Resolving Simulation Options (SAS, DES, or SBES/SDES)
- Green-Gauss Node Based gradient method (for flow-blocking type only)
- QUICK or MUSCL discretization schemes (for flow-blocking type only)
- Non-Iterative Time Advancement (NITA) scheme
- coupled walls are not allowed to be selected for a gap region
- the gap model cannot be used in a case that also has the Flow Control option enabled in the
  Contact Detection
- the porous zone option cannot be enabled in cell zones where gaps are located

##### Contact Detection

![image-20220914153857057](https://s2.loli.net/2022/09/14/UzX2IeELdB9NjRF.png)

![image-20220914153958467](https://s2.loli.net/2022/09/14/FEA37jMW1RPLGOa.png)

![image-20220914154030458](https://s2.loli.net/2022/09/14/JBlmvY6goDGZHqs.png)

###### Contact Marks

将标记区域的边界设置为零质量流量条件

###### Contact Zones

将标记区域单独划分出来，设置为多孔介质，通过设置阻力系数控制内部流动。

##### Dynamic Mesh Events

![image-20220914154731489](https://s2.loli.net/2022/09/14/SUVKyvTFMkmnLXp.png)

![image-20220914154855136](https://s2.loli.net/2022/09/14/O5SXAR1Ynhq82WZ.png)

![image-20220914154941702](https://s2.loli.net/2022/09/14/IjFPUkn9Yw48aTL.png)

在窄缝处手动设置一个边界。初始为wall，阻止流动。在指定时间（此时窄缝已变得足够宽），将该边界的类型由wall修改为interior。

##### 手动控制

###### 手动设置wall边界

不使用Dynamic mesh events，而是按照其思路手动设置壁面，手动修改壁面类型。

###### 手动设置多孔介质区域

按照 `Contact Zones`的思路，将某区域设置为多孔介质区域，在指定时间（此时窄缝已变得足够宽），去除多孔介质设置。



##### 小结

| 方法                            | 是否完全阻止流动 | 是否适用于周期运动 |
| ------------------------------- | :--------------: | :----------------: |
| Gap Model Flow-Blocking         |        √         |         √          |
| Gap Model Flow-Modeling         |        ×         |         √          |
| Contact Detection Contact Marks |        √         |         √          |
| Contact Detection Contact Zones |        ×         |         √          |
| Dynamic Mesh Events             |        √         |         x          |
| 手动边界                        |        √         |         ×          |
| 手动多孔介质                    |        ×         |         ×          |

周期运动：窄缝变宽后还会变窄

单向运动：窄缝变宽后不会变窄

* 能使用 Gap Model 就使用 Gap Model。

* 在不能使用 Gap Model 时：
  * 对于单向运动，优先选择手动多孔介质。
  * 对于周期运动，优先选择Contact Detection Contact Zones。
  * 对于System Coupling，使用Contact Detection。


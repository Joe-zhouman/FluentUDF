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

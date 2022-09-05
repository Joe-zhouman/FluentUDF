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

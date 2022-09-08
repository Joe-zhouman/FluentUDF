#include "udf.h"
/*刚体转动示例*/
DEFINE_CG_MOTION(rotate, dt, vel, omega, time, dtime) {
    /*reset velocity*/
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    /*set omega_xy = 0.2 rad/s*/
    omega[2] = 0.2;
}

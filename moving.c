#include "udf.h"

/*****define some constants*****/

#define NUM_DOMAINS 3

const real vol = 9.6548e-7;      // volumn of the half model of the valva；
const real density = 8030;        // the density of the material of the valva。
const real mass = vol * density;   // the mass of the valva
const real spring_const = 7600;     // the spring constant
const int domain_id_array[] = {};
/********************/

static real v_prev = 0.0;
static real current_accelatation=0.0;
static real time_prev=0.0

DEFINE_CG_MOTION(valva,dt,vel,omega,time,dtime)
{
    real current_posi = DT_CG(dt)[2];
    real dv;
    /* reset velocities */
    NV_S(vel, =, 0.0);
    NV_S(omega, =, 0.0);
    if (!Data_Valid_P())
        return;
    dv = current_accelatation-current_posi*spring_const/mass;
    if (time > (time_prev + EPSILON)) {
        v_prev += dv;
        time_prev = time;
    }
    vel[2]=v_prev;
}

DEFINE_EXECUTE_AT_END(compute_vel)
{
    Domain *domain;
    int domain_id_send_to_node;
    real force_temp = 0;
    real total_force_z = 0;

    int i;
#if !RP_HOST
    Thread *thread;
    face_t face;
    real area[ND_ND];
#endif
    /*get total z comp force*/
    /*which is the total force on valva walls*/
    for (i = 0; i < NUM_DOMAINS; i++) {
        domain_id_send_to_node = domain_id_array[i];
        host_to_node_int_1(domain_id_send_to_node);
#if !RP_HOST
        thread = Lookup_Thread(domain, domain_id_send_to_node);
        begin_f_loop(face, thread) 
        if (PRINCIPAL_FACE_P(face, thread)) {
            F_AREA(area, face, thread);
            force_temp += area[2] * F_P(face, thread);
        }
        end_f_loop(face, thread)
#if RP_NODE /* Perform node synchronized actions here */
            force_temp = PRF_GRSUM1(force_temp);
#endif /* RP_NODE */
#endif /* !RP_HOST */
        total_force_z += force_temp;
        force_temp = 0;
    }
    current_accelatation = total_force_z/mass - 9.81;
}

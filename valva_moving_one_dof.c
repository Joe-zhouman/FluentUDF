#include "udf.h"

DEFINE_SDOF_PROPERTIES(valva, prop, dt, time, dtime) {
    Six_DOF_Object *sdof_obj = NULL;
    real vol = 9.6548e-7;        // volumn of the half model of the valva£»
    real density = 8030;         // the density of the material of the valva¡£
    real mass = vol * density;   // the mass of the valva
    real spring_const = 7600; // the spring constant
    Domain *domain;
    int domain_id = 0;
    real force_temp=0;
    real total_force_z = 0; // the z component of the total external force.

    /******some variables for paralle******/
#if !RP_HOST
    Thread *thread;
    face_t face;
    real area[ND_ND];
#endif
    /*****************/
    prop[SDOF_MASS] = mass; // the mass of the valva

    // the external force of x. y direction is zero
    prop[SDOF_LOAD_F_X] = 0;
    prop[SDOF_LOAD_F_Y] = 0;

    // the translation of x, y direction is zero
    prop[SDOF_ZERO_TRANS_X] = TRUE;
    prop[SDOF_ZERO_TRANS_Y] = TRUE;

    // the rotation of x, y, z axes is zeros
    prop[SDOF_ZERO_ROT_X] = TRUE;
    prop[SDOF_ZERO_ROT_Y] = TRUE;
    prop[SDOF_ZERO_ROT_Z] = TRUE;

    // a half model is used£¬the normal vector of the symmetric is nessesary
    prop[SDOF_SYMMETRY_X] = 1;
    prop[SDOF_SYMMETRY_Y] = 0;
    prop[SDOF_SYMMETRY_Z] = 0;

/*get total z comp force*/
/*which is the total force on valva walls*/
    domain_id = 13;
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
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
    total_force_z+=force_temp;
    force_temp=0;
    domain_id = 14;
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
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
    domain_id = 15;
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
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

    domain_id = 17; // the domains with ID 13,14,15,17 is considered.
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
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
    /**********************/
    prop[SDOF_LOAD_F_Z] = total_force_z;
    sdof_obj = Get_SDOF_Object(DT_PU_NAME(dt));
    if (NULLP(sdof_obj)) {
        /* Allocate_SDOF_Object must be called with the same name as the udf */
        sdof_obj = Allocate_SDOF_Object(DT_PU_NAME(dt));
        SDOFO_1DOF_T_P(sdof_obj) = TRUE; /* one DOF translation */
        SDOFO_1DOF_R_P(sdof_obj) = FALSE;  /* one DOF rotation */
        SDOFO_DIR(sdof_obj)[0] = 0.0;
        SDOFO_DIR(sdof_obj)[1] = 0.0;
        SDOFO_DIR(sdof_obj)[2] = -1.0;
        SDOFO_CONS_P(sdof_obj) = TRUE; /* constrained */
        if (SDOFO_CONS_P(sdof_obj)) {
            SDOFO_LOC(sdof_obj) = 0.0;
            SDOFO_MIN(sdof_obj) = 0;
            SDOFO_MAX(sdof_obj) = 0.03;
            SDOFO_F(sdof_obj) = 0.0; /* spring preload */
            SDOFO_K(sdof_obj) = spring_const; /* spring constant */
            SDOFO_INIT(sdof_obj) = SDOFO_LOC(sdof_obj);
            SDOFO_LOC_N(sdof_obj) = SDOFO_LOC(sdof_obj);
        }
    }
}
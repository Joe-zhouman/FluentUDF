#include "udf.h"
DEFINE_ADJUST(force_total, domain) 
{
    int domain_id = 0;
    real force_temp = 0;
    real total_force_z = 0;
#if !RP_HOST
    Thread *thread;
    face_t face;
    real area[ND_ND];
#endif
    domain_id = 13;
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
    begin_f_loop(face, thread) if (PRINCIPAL_FACE_P(face, thread)) {
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
    domain_id = 14;
    host_to_node_int_1(domain_id);
#if !RP_HOST
    thread = Lookup_Thread(domain, domain_id);
    begin_f_loop(face, thread) if (PRINCIPAL_FACE_P(face, thread)) {
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
    begin_f_loop(face, thread) if (PRINCIPAL_FACE_P(face, thread)) {
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
    begin_f_loop(face, thread) if (PRINCIPAL_FACE_P(face, thread)) {
        F_AREA(area, face, thread);
        force_temp += area[2] * F_P(face, thread);
    }
    end_f_loop(face, thread)
#if RP_NODE /* Perform node synchronized actions here */
        force_temp = PRF_GRSUM1(force_temp);
#endif /* RP_NODE */
#endif /* !RP_HOST */
    total_force_z += force_temp;
    Message("Total Force Is %f\n", total_force_z);
}
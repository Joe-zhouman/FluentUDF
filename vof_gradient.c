#include "udf.h"
#define DOMAIN_ID 2

DEFINE_ADJUST(adjust_gradient, domain)
{
    Thread *t;
    cell_t c;
    cell_t f;
    domain = Get_Domain(DOMAIN_ID);
    thread_loop_c(t,domain)
        {
            begin_c_loop(c,t)
                {
                    C_UDSI(c,t,0)=C_VOF(c,t);
                }
            end_c_loop(c,t)
        }
    thread_loop_f(t,domain)
        {
            if(THREAD_STORAGE(t,SV_UDS_I(0))!=NULL)
                begin_f_loop(f,t)
                {
                    F_UDSI(f,t,0)=F_VOF(f,t);
                }
                end_f_loop(f,t)
        }

}
DEFINE_ON_DEMAND(store_gradient)
{
    Domain *domain;
    cell_t c;
    Thread *t;
    domain = Get_Domain(DOMAIN_ID);
    thread_loop_c(t,domain)
        {
            begin_c_loop(c,t)
                {
                    C_UDMI(c,t,0)=NV_MAG(C_UDSI_G(c,t,0));
                }
            end_c_loop(c,t)
        }
}
/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_LITHIUM_H
#define _FLUENT_LITHIUM_H

extern FLUENT_EXPORT real li_c_i0;
extern FLUENT_EXPORT real li_c_alpha_a;
extern FLUENT_EXPORT real li_c_alpha_c;
extern FLUENT_EXPORT real li_c_Cmax;

extern FLUENT_EXPORT real li_a_i0;
extern FLUENT_EXPORT real li_a_alpha_a;
extern FLUENT_EXPORT real li_a_alpha_c;
extern FLUENT_EXPORT real li_a_Cmax;
extern FLUENT_EXPORT real li_c_alpha1, li_c_alpha2, li_c_alpha3;
extern FLUENT_EXPORT real li_a_alpha1, li_a_alpha2, li_a_alpha3;
extern FLUENT_EXPORT cxboolean li_linearized_bv;

extern FLUENT_EXPORT Echem_Pinput *li_PEeq_a, *li_PEeq_c;
extern FLUENT_EXPORT Echem_Pinput *li_Ptplus, *li_Pactivity;

extern FLUENT_EXPORT real li_c_cinit, li_a_cinit, li_el_cinit;

FLUENT_EXPORT char IS_PHI_ZEROFLUX_WALL_THREAD(Thread *t);
FLUENT_EXPORT char IS_LI_SOLVED_ZONE_THREAD(Thread *t);
FLUENT_EXPORT char IS_CATHODE_WALL_THREAD(Thread *t);
FLUENT_EXPORT char IS_ANODE_WALL_THREAD(Thread *t);
FLUENT_EXPORT char IS_LI_REACTION_WALL_THREAD(Thread *t);
FLUENT_EXPORT char IS_HALF_CELL_BC(Thread *t);
FLUENT_EXPORT char IS_POS_ELECTRODE_ZONE_THREAD(Thread *t);
FLUENT_EXPORT char IS_NEG_ELECTRODE_ZONE_THREAD(Thread *t);
FLUENT_EXPORT char IS_ELECTRODE_ZONE_THREAD(Thread *t);
FLUENT_EXPORT char IS_ELECTROLYTE_ZONE_THREAD(Thread *t);
FLUENT_EXPORT void Add_Lithium_Source_in_Potential_Equaton(Domain *domain);
FLUENT_EXPORT void Init_Lithium_Eq(Pointer x, Pointer y, Pointer z, Pointer w);
FLUENT_EXPORT void Compute_Lithium_Capacity_SOC(Domain *domain);
#endif /* _FLUENT_LITHIUM_H */


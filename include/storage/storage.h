/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_STORAGE_H
#define _FLUENT_STORAGE_H

#include "store.h"

#include "dll.h"

/* #include "mem.h" */   /* Domain */
/* This doesn't work, because mem.h includes this file.
 * --> must make sure that mem.h has been included before this
 * file is included, and include mem.h where this file is needed:
 */
#ifndef _FLUENT_MEM_H
# error Must include mem.h to include storage.h
#endif

#define NULL_INDEX -1

/* segregated solution vars */
#define SV_SOLUTION_VAR(f)\
  SV_##f,\
  SV_##f##_AP,\
  SV_##f##_S,\
  SV_##f##_G,\
  SV_##f##_RG,\
  SV_##f##_RG_AUX,\
  SV_##f##_M1,\
  SV_##f##_M2,\
  SV_##f##_F,\
  SV_##f##_FG,\
  SV_##f##_R

#if RP_FC
#define SV_VAR_WITH_FC(f)\
  SV_##f,\
  SV_##f##_ACFC
#define SV_SOLUTION_VAR_WITH_FC(f)\
  SV_SOLUTION_VAR(f),\
  SV_##f##_ACFC, \
  SV_##f##_PLFC
#else
#define SV_VAR_WITH_FC(f)\
  SV_##f
#define SV_SOLUTION_VAR_WITH_FC(f) SV_SOLUTION_VAR(f)
#endif

/* coupled solution vars: p,u,v,w,T,yi */
/* note: rms and mean are only used for p,u,v,w,T */
#define SV_COUPLED_SOLUTION_VAR(f)\
  SV_SOLUTION_VAR(f),\
  SV_##f##_PR,\
  SV_##f##_WO,\
  SV_##f##_DW,\
  SV_##f##_FW,\
  SV_##f##_WV,\
  SV_##f##_WN,\
  SV_##f##_MEAN,\
  SV_##f##_RMS

#if RP_FC
#define SV_COUPLED_SOLUTION_VAR_WITH_FC(f)\
  SV_COUPLED_SOLUTION_VAR(f),\
  SV_##f##_ACFC,\
  SV_##f##_PLFC
#define SV_COUPLED_SOLUTION_VAR_WITH_BFC(f)\
  SV_COUPLED_SOLUTION_VAR(f),\
  SV_##f##_ACFC,\
  SV_##f##_BCFC,\
  SV_##f##_PLFC
#else
#define SV_COUPLED_SOLUTION_VAR_WITH_FC(f)\
  SV_COUPLED_SOLUTION_VAR(f)
#define SV_COUPLED_SOLUTION_VAR_WITH_BFC(f)\
  SV_COUPLED_SOLUTION_VAR(f)
#endif

#if 0
#define SV_SOLUTION_VAR_I(f,i)SV_SOLUTION_VAR(f##_##i)
#define SV_COUPLED_SOLUTION_VAR_I(f,i)SV_COUPLED_SOLUTION_VAR(f##_##i)
#endif

#define SV_BASE(__sv_rg)     ((Svar)((__sv_rg)   - (SV_P_RG     - SV_P)))
#define SV_RG_AUX(__sv_base) ((Svar)((__sv_base) + (SV_P_RG_AUX - SV_P_RG)))
#define SV_RG(__sv_base)     ((Svar)((__sv_base) + (SV_P_RG     - SV_P)))
#define SV_G(__sv_base)      ((Svar)((__sv_base) + (SV_P_G      - SV_P)))

#define EXPAND_0_TO_0(macro,arg)macro(0,"0",arg)
#define EXPAND_0_TO_2(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_2(macro,arg)
#define EXPAND_0_TO_4(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_4(macro,arg)
#define EXPAND_0_TO_5(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_5(macro,arg)
#define EXPAND_0_TO_9(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_9(macro,arg)
#define EXPAND_0_TO_19(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_19(macro,arg)
#define EXPAND_0_TO_44(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_44(macro,arg)
#define EXPAND_0_TO_49(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_49(macro,arg)
#define EXPAND_0_TO_189(macro,arg)EXPAND_0_TO_0(macro,arg),EXPAND_1_TO_189(macro,arg)

#define EXPAND_1_TO_1(macro,arg)macro(1,"1",arg)
#define EXPAND_1_TO_2(macro,arg)EXPAND_1_TO_1(macro,arg),macro(2,"2",arg)
#define EXPAND_1_TO_3(macro,arg)EXPAND_1_TO_2(macro,arg),macro(3,"3",arg)
#define EXPAND_1_TO_4(macro,arg)EXPAND_1_TO_3(macro,arg),macro(4,"4",arg)
#define EXPAND_1_TO_5(macro,arg)EXPAND_1_TO_4(macro,arg),macro(5,"5",arg)
#define EXPAND_1_TO_6(macro,arg)EXPAND_1_TO_5(macro,arg),macro(6,"6",arg)
#define EXPAND_1_TO_7(macro,arg)EXPAND_1_TO_6(macro,arg),macro(7,"7",arg)
#define EXPAND_1_TO_8(macro,arg)EXPAND_1_TO_7(macro,arg),macro(8,"8",arg)
#define EXPAND_1_TO_9(macro,arg)EXPAND_1_TO_8(macro,arg),macro(9,"9",arg)
#define EXPAND_1_TO_10(macro,arg)EXPAND_1_TO_9(macro,arg),macro(10,"10",arg)
#define EXPAND_1_TO_11(macro,arg)EXPAND_1_TO_10(macro,arg),macro(11,"11",arg)
#define EXPAND_1_TO_12(macro,arg)EXPAND_1_TO_11(macro,arg),macro(12,"12",arg)
#define EXPAND_1_TO_13(macro,arg)EXPAND_1_TO_12(macro,arg),macro(13,"13",arg)
#define EXPAND_1_TO_14(macro,arg)EXPAND_1_TO_13(macro,arg),macro(14,"14",arg)
#define EXPAND_1_TO_15(macro,arg)EXPAND_1_TO_14(macro,arg),macro(15,"15",arg)
#define EXPAND_1_TO_16(macro,arg)EXPAND_1_TO_15(macro,arg),macro(16,"16",arg)
#define EXPAND_1_TO_17(macro,arg)EXPAND_1_TO_16(macro,arg),macro(17,"17",arg)
#define EXPAND_1_TO_18(macro,arg)EXPAND_1_TO_17(macro,arg),macro(18,"18",arg)
#define EXPAND_1_TO_19(macro,arg)EXPAND_1_TO_18(macro,arg),macro(19,"19",arg)
#define EXPAND_1_TO_20(macro,arg)EXPAND_1_TO_19(macro,arg),macro(20,"20",arg)
#define EXPAND_1_TO_21(macro,arg)EXPAND_1_TO_20(macro,arg),macro(21,"21",arg)
#define EXPAND_1_TO_22(macro,arg)EXPAND_1_TO_21(macro,arg),macro(22,"22",arg)
#define EXPAND_1_TO_23(macro,arg)EXPAND_1_TO_22(macro,arg),macro(23,"23",arg)
#define EXPAND_1_TO_24(macro,arg)EXPAND_1_TO_23(macro,arg),macro(24,"24",arg)
#define EXPAND_1_TO_25(macro,arg)EXPAND_1_TO_24(macro,arg),macro(25,"25",arg)
#define EXPAND_1_TO_26(macro,arg)EXPAND_1_TO_25(macro,arg),macro(26,"26",arg)
#define EXPAND_1_TO_27(macro,arg)EXPAND_1_TO_26(macro,arg),macro(27,"27",arg)
#define EXPAND_1_TO_28(macro,arg)EXPAND_1_TO_27(macro,arg),macro(28,"28",arg)
#define EXPAND_1_TO_29(macro,arg)EXPAND_1_TO_28(macro,arg),macro(29,"29",arg)
#define EXPAND_1_TO_30(macro,arg)EXPAND_1_TO_29(macro,arg),macro(30,"30",arg)
#define EXPAND_1_TO_31(macro,arg)EXPAND_1_TO_30(macro,arg),macro(31,"31",arg)
#define EXPAND_1_TO_32(macro,arg)EXPAND_1_TO_31(macro,arg),macro(32,"32",arg)
#define EXPAND_1_TO_33(macro,arg)EXPAND_1_TO_32(macro,arg),macro(33,"33",arg)
#define EXPAND_1_TO_34(macro,arg)EXPAND_1_TO_33(macro,arg),macro(34,"34",arg)
#define EXPAND_1_TO_35(macro,arg)EXPAND_1_TO_34(macro,arg),macro(35,"35",arg)
#define EXPAND_1_TO_36(macro,arg)EXPAND_1_TO_35(macro,arg),macro(36,"36",arg)
#define EXPAND_1_TO_37(macro,arg)EXPAND_1_TO_36(macro,arg),macro(37,"37",arg)
#define EXPAND_1_TO_38(macro,arg)EXPAND_1_TO_37(macro,arg),macro(38,"38",arg)
#define EXPAND_1_TO_39(macro,arg)EXPAND_1_TO_38(macro,arg),macro(39,"39",arg)
#define EXPAND_1_TO_40(macro,arg)EXPAND_1_TO_39(macro,arg),macro(40,"40",arg)
#define EXPAND_1_TO_41(macro,arg)EXPAND_1_TO_40(macro,arg),macro(41,"41",arg)
#define EXPAND_1_TO_42(macro,arg)EXPAND_1_TO_41(macro,arg),macro(42,"42",arg)
#define EXPAND_1_TO_43(macro,arg)EXPAND_1_TO_42(macro,arg),macro(43,"43",arg)
#define EXPAND_1_TO_44(macro,arg)EXPAND_1_TO_43(macro,arg),macro(44,"44",arg)
#define EXPAND_1_TO_45(macro,arg)EXPAND_1_TO_44(macro,arg),macro(45,"45",arg)
#define EXPAND_1_TO_46(macro,arg)EXPAND_1_TO_45(macro,arg),macro(46,"46",arg)
#define EXPAND_1_TO_47(macro,arg)EXPAND_1_TO_46(macro,arg),macro(47,"47",arg)
#define EXPAND_1_TO_48(macro,arg)EXPAND_1_TO_47(macro,arg),macro(48,"48",arg)
#define EXPAND_1_TO_49(macro,arg)EXPAND_1_TO_48(macro,arg),macro(49,"49",arg)

/*
 * Expand upto 189 interaction domains => 20 SUB_DOMAINS
 * -----------------------------------------------------
 */

#define EXPAND_1_TO_59(macro,arg)EXPAND_1_TO_49(macro,arg),\
macro(50,"50",arg),macro(51,"51",arg),macro(52,"52",arg),macro(53,"53",arg),macro(54,"54",arg),\
macro(55,"55",arg),macro(56,"56",arg),macro(57,"57",arg),macro(58,"58",arg),macro(59,"59",arg)
#define EXPAND_1_TO_69(macro,arg)EXPAND_1_TO_59(macro,arg),\
macro(60,"60",arg),macro(61,"61",arg),macro(62,"62",arg),macro(63,"63",arg),macro(64,"64",arg),\
macro(65,"65",arg),macro(66,"66",arg),macro(67,"67",arg),macro(68,"68",arg),macro(69,"69",arg)
#define EXPAND_1_TO_79(macro,arg)EXPAND_1_TO_69(macro,arg),\
macro(70,"70",arg),macro(71,"71",arg),macro(72,"72",arg),macro(73,"73",arg),macro(74,"74",arg),\
macro(75,"75",arg),macro(76,"76",arg),macro(77,"77",arg),macro(78,"78",arg),macro(79,"79",arg)
#define EXPAND_1_TO_89(macro,arg)EXPAND_1_TO_79(macro,arg),\
macro(80,"80",arg),macro(81,"81",arg),macro(82,"82",arg),macro(83,"83",arg),macro(84,"84",arg),\
macro(85,"85",arg),macro(86,"86",arg),macro(87,"87",arg),macro(88,"88",arg),macro(89,"89",arg)
#define EXPAND_1_TO_99(macro,arg)EXPAND_1_TO_89(macro,arg),\
macro(90,"90",arg),macro(91,"91",arg),macro(92,"92",arg),macro(93,"93",arg),macro(94,"94",arg),\
macro(95,"95",arg),macro(96,"96",arg),macro(97,"97",arg),macro(98,"98",arg),macro(99,"99",arg)
#define EXPAND_1_TO_109(macro,arg)EXPAND_1_TO_99(macro,arg),\
macro(100,"100",arg),macro(101,"101",arg),macro(102,"102",arg),macro(103,"103",arg),macro(104,"104",arg),\
macro(105,"105",arg),macro(106,"106",arg),macro(107,"107",arg),macro(108,"108",arg),macro(109,"109",arg)
#define EXPAND_1_TO_119(macro,arg)EXPAND_1_TO_109(macro,arg),\
macro(110,"110",arg),macro(111,"111",arg),macro(112,"112",arg),macro(113,"113",arg),macro(114,"114",arg),\
macro(115,"115",arg),macro(116,"116",arg),macro(117,"117",arg),macro(118,"118",arg),macro(119,"119",arg)
#define EXPAND_1_TO_129(macro,arg)EXPAND_1_TO_119(macro,arg),\
macro(120,"120",arg),macro(121,"121",arg),macro(122,"122",arg),macro(123,"123",arg),macro(124,"124",arg),\
macro(125,"125",arg),macro(126,"126",arg),macro(127,"127",arg),macro(128,"128",arg),macro(129,"129",arg)
#define EXPAND_1_TO_139(macro,arg)EXPAND_1_TO_129(macro,arg),\
macro(130,"130",arg),macro(131,"131",arg),macro(132,"132",arg),macro(133,"133",arg),macro(134,"134",arg),\
macro(135,"135",arg),macro(136,"136",arg),macro(137,"137",arg),macro(138,"138",arg),macro(139,"139",arg)
#define EXPAND_1_TO_149(macro,arg)EXPAND_1_TO_139(macro,arg),\
macro(140,"140",arg),macro(141,"141",arg),macro(142,"142",arg),macro(143,"143",arg),macro(144,"144",arg),\
macro(145,"145",arg),macro(146,"146",arg),macro(147,"147",arg),macro(148,"148",arg),macro(149,"149",arg)
#define EXPAND_1_TO_159(macro,arg)EXPAND_1_TO_149(macro,arg),\
macro(150,"150",arg),macro(151,"151",arg),macro(152,"152",arg),macro(153,"153",arg),macro(154,"154",arg),\
macro(155,"155",arg),macro(156,"156",arg),macro(157,"157",arg),macro(158,"158",arg),macro(159,"159",arg)
#define EXPAND_1_TO_169(macro,arg)EXPAND_1_TO_159(macro,arg),\
macro(160,"160",arg),macro(161,"161",arg),macro(162,"162",arg),macro(163,"163",arg),macro(164,"164",arg),\
macro(165,"165",arg),macro(166,"166",arg),macro(167,"167",arg),macro(168,"168",arg),macro(169,"169",arg)
#define EXPAND_1_TO_179(macro,arg)EXPAND_1_TO_169(macro,arg),\
macro(170,"170",arg),macro(171,"171",arg),macro(172,"172",arg),macro(173,"173",arg),macro(174,"174",arg),\
macro(175,"175",arg),macro(176,"176",arg),macro(177,"177",arg),macro(178,"178",arg),macro(179,"179",arg)
#define EXPAND_1_TO_189(macro,arg)EXPAND_1_TO_179(macro,arg),\
macro(180,"180",arg),macro(181,"181",arg),macro(182,"182",arg),macro(183,"183",arg),macro(184,"184",arg),\
macro(185,"185",arg),macro(186,"186",arg),macro(187,"187",arg),macro(188,"188",arg),macro(189,"189",arg)

#define EXPAND_SV_helper(i,s,base)SV_##base##_##i
#define EXPAND_SV_M1_helper(i,s,base)SV_##base##_##i##_M1
#define EXPAND_SV_M2_helper(i,s,base)SV_##base##_##i##_M2
#define EXPAND_SV_AP_helper(i,add,base)SV_##base##_##i##_AP
#define EXPAND_SV_S_helper(i,add,base)SV_##base##_##i##_S
#define EXPAND_SV_G_helper(i,add,base)SV_##base##_##i##_G
#define EXPAND_SV_RG_helper(i,add,base)SV_##base##_##i##_RG
#define EXPAND_SV_MEAN_helper(i,add,base)SV_##base##_##i##_MEAN
#define EXPAND_SV_RMS_helper(i,add,base)SV_##base##_##i##_RMS
#define EXPAND_SV_MOV_AVG_helper(i,add,base)SV_##base##_##i##_MOV_AVG
#define EXPAND_SV_MIN_helper(i,add,base)SV_##base##_##i##_MIN
#define EXPAND_SV_MAX_helper(i,add,base)SV_##base##_##i##_MAX

#define EXPAND_NSPE_SV_M1(base) EXPAND_0_TO_49(EXPAND_SV_M1_helper,base)
#define EXPAND_NSPE_SV_M2(base) EXPAND_0_TO_49(EXPAND_SV_M2_helper,base)

#define EXPAND_NSPE_SV(base)EXPAND_0_TO_49(EXPAND_SV_helper,base)
#define EXPAND_NUDS_SV(base)EXPAND_0_TO_49(EXPAND_SV_helper,base)
#define EXPAND_NPB_DISC_SV(base)EXPAND_0_TO_49(EXPAND_SV_helper,base)
#define EXPAND_NPB_QMOM_SV(base)EXPAND_0_TO_9(EXPAND_SV_helper,base)
#define EXPAND_L_W_PB_QMOM_SV(base)EXPAND_0_TO_4(EXPAND_SV_helper,base)
#define EXPAND_NPB_SMM_SV(base)EXPAND_0_TO_9(EXPAND_SV_helper,base)
#define EXPAND_PER_MAT_SV(base)EXPAND_0_TO_19(EXPAND_SV_helper,base)

#define EXPAND_CFF_SV_MEAN(base)EXPAND_0_TO_49(EXPAND_SV_MEAN_helper,base)
#define EXPAND_CFF_SV_RMS(base)EXPAND_0_TO_49(EXPAND_SV_RMS_helper,base)
#define EXPAND_STAT_DATASET_SV_MEAN(base)EXPAND_0_TO_49(EXPAND_SV_MEAN_helper,base)
#define EXPAND_STAT_DATASET_SV_RMS(base)EXPAND_0_TO_49(EXPAND_SV_RMS_helper,base)
#define EXPAND_STAT_SEG_DATASET_SV_MOV_AVG(base)EXPAND_0_TO_49(EXPAND_SV_MOV_AVG_helper,base)
#define EXPAND_STAT_DATASET_SV_MIN(base)EXPAND_0_TO_49(EXPAND_SV_MIN_helper,base)
#define EXPAND_STAT_DATASET_SV_MAX(base)EXPAND_0_TO_49(EXPAND_SV_MAX_helper,base)

#define EXPAND_NPROB_SV(base) EXPAND_0_TO_9(EXPAND_SV_helper,base)
#define EXPAND_NCURV_COORD_SV(base) EXPAND_0_TO_9(EXPAND_SV_helper,base)

#define MAX_PROFILE 50
#define EXPAND_NPROFILE_SV(base)EXPAND_0_TO_49(EXPAND_SV_helper,base)

#define EXPAND_ARRAY_helper(i,s,base) base[ i ]
#define EXPAND_NPHASE EXPAND_0_TO_19

#if RP_WALL_FILM
#define EXPAND_EFILM_ARRAY_helper0(i,s,base)base##[##i##]
#define EXPAND_EFILM_ARRAY_helper(i,s,base)base[i]
#define EXPAND_EFILM_HVV_SV(base)EXPAND_0_TO_5(EXPAND_EFILM_ARRAY_helper,base)
#define EXPAND_EFILM_SV_AUX_helper(i, s, base)SV_##base##_AUX_##i

#define SV_EFILM_GSOLUTION_VAR(f)\
  SV_##f,\
  SV_##f##_G

#define SV_EFILM_LSOLUTION_VAR(f)\
  SV_##f,\
  SV_##f##_PREV,\
  SV_##f##_SRC,\
  SV_##f##_SRC_PREV,\
  SV_##f##_SRCM,\
  EXPAND_0_TO_5(EXPAND_EFILM_SV_AUX_helper, f)

#define SV_EFILM_V_INERTIA_VAR(f)\
  SV_##f,\
  SV_##f##_GV

#endif

typedef enum
{
  SV_NULL = -1,
#define SV_MIN ((Svar)(SV_NULL+1))

  SV_COUPLED_SOLUTION_VAR_WITH_BFC(P),
  SV_MASS_IMBALANCE, /* mass imbalance in the cell *after* pressure correction */
  SV_CN_MASS_IMBALANCE,
  SV_CN_MASS_M1,
  SV_S_MASS_USER,
  SV_CVD_MASS,
  SV_PERFORATED_MASS,
  SV_PERFORATED_MFLOWRATE,
  SV_PERFORATED_FLAG,
  SV_PERFORATED_PRESSURE,
  SV_ELECTROLYSIS_MASSSOURCE,
  SV_MASS_SOURCE,
  SV_PP,
  SV_B_FACTOR,
  SV_PP_COEFF,
  SV_FP_COEFF,
  SV_MOM_AP_T,
  SV_MOM_AP_T_M1,
  SV_MOM_AP_T_M2,
  SV_MOM_AP_PTF,
  SV_C0_FP_COEFF,  /* phase flux correction coeff */
  SV_C1_FP_COEFF,
  SV_P_STAGNATION,
  SV_P_G_LIMITED,


  EXPAND_0_TO_19(EXPAND_SV_helper, C0_FPV_COEFF),
#define SV_C0_FPV_MAX SV_C0_FPV_COEFF_19
#define SV_C0_FPV_COEFF(i)((Svar)(SV_C0_FPV_COEFF_0+i))

  EXPAND_0_TO_19(EXPAND_SV_helper, C1_FPV_COEFF),
#define SV_C1_FPV_MAX SV_C1_FPV_COEFF_19
#define SV_C1_FPV_COEFF(i)((Svar)(SV_C1_FPV_COEFF_0+i))


  /* EXPAND_1_TO_19(EXPAND_SV_helper,C0_FPVOF_COEFF),
   * #define SV_C0_FPVOF_MAX SV_C0_FPVOF_COEFF_19
   * #define SV_C0_FPVOF_COEFF(i)((Svar)(SV_C0_FPVOF_COEFF_1+(i-1)))
   *
   * EXPAND_1_TO_19(EXPAND_SV_helper,C1_FPVOF_COEFF),
   * #define SV_C1_FPVOF_MAX SV_C1_FPVOF_COEFF_19
   * #define SV_C1_FPVOF_COEFF(i)((Svar)(SV_C1_FPVOF_COEFF_1+(i-1)))
   */


  EXPAND_0_TO_19(EXPAND_SV_helper, C0_FPVOF_COEFF),
#define SV_C0_FPVOF_MAX SV_C0_FPVOF_COEFF_19
#define SV_C0_FPVOF_COEFF(i)((Svar)(SV_C0_FPVOF_COEFF_0+(i)))


  EXPAND_0_TO_19(EXPAND_SV_helper, C1_FPVOF_COEFF),
#define SV_C1_FPVOF_MAX SV_C1_FPVOF_COEFF_19
#define SV_C1_FPVOF_COEFF(i)((Svar)(SV_C1_FPVOF_COEFF_0+(i)))


  EXPAND_0_TO_19(EXPAND_SV_helper, C0_FF_COEFF),
#define SV_C0_FF_MAX SV_C0_FF_COEFF_19
#define SV_C0_FF_COEFF(i)((Svar)(SV_C0_FF_COEFF_0+i))


  SV_MP_SAVP_V,         /*MP PISO correction*/
  SV_MP_VP_V,
  SV_MP_VP_V_corr,

  SV_MP_FACE_P_S0,     /*special MP face pressure effect on momentum*/
  SV_MP_FACE_P_S1,


#if DRIFT_COUPLED
  EXPAND_1_TO_19(EXPAND_SV_helper, C0_FPV_DRIFT_COEFF),
#define SV_C0_FPV_DRIFT_MAX SV_C0_FPV_DRIFT_COEFF_19
#define SV_C0_FPV_DRIFT_COEFF(i)((Svar)(SV_C0_FPV_DRIFT_COEFF_1+(i-1)))

  EXPAND_1_TO_19(EXPAND_SV_helper, C1_FPV_DRIFT_COEFF),
#define SV_C1_FPV_DRIFT_MAX SV_C1_FPV_DRIFT_COEFF_19
#define SV_C1_FPV_DRIFT_COEFF(i)((Svar)(SV_C1_FPV_DRIFT_COEFF_1+(i-1)))

  SV_MP_DRIFT_FORCE,
  SV_MP_DRIFT_COEFF,
  SV_MP_DRIFT_S_P_COEFF,
#endif

  SV_CAP,
  SV_CAP_G,
  SV_CAP_RG,
  SV_CAP_RG_AUX,

  SV_PREV_FACE_VOF,
  SV_MP_VOF_OLD,
  SV_NET_FLUX_DIFF,

  SV_SOLUTION_VAR(GP),          /* granular pressure */
  SV_GPP,                       /* granular pp */
  SV_C0_FGP_COEFF,              /* phase flux granular correction coeff */
  SV_C1_FGP_COEFF,

  /* momentum equation */
  SV_COUPLED_SOLUTION_VAR_WITH_FC(U),
  SV_COUPLED_SOLUTION_VAR_WITH_FC(V),
  SV_COUPLED_SOLUTION_VAR_WITH_FC(W),
  SV_FLUX,
  SV_FLUX_M1,
  SV_FLUX_M2,
  SV_UBAR_M1,
  SV_V_PREV,                  /* last iterate  of velocity */
  SV_FLUX_FROZEN,
  SV_FLUX_LIMIT,              /* Svar to indicate the face on which flux will be limited */
  SV_SA_V,
  SV_BF_V,
  SV_BFP_V,
  SV_WALL_V,  /* wall velocity             */
  SV_WALL_VV, /* original wall velocity    */
  SV_WALL_SHEAR,
  SV_POROUS_FORCE,
  SV_PSEUDO_DT,

#if RP_3D
  SV_VM_GRAD, /* for VM */
#endif
  SV_SYN_TURB_FLUX,

  SV_UV_MEAN,
  SV_UW_MEAN,
  SV_VW_MEAN,
  SV_WALL_SHEAR_MEAN,
  SV_WALL_PRORUS_ZONE_FORCE_MEAN,

  SV_VEL_ANGLE,
  SV_MACH,
  SV_NORMAL_MACH,

  /* temperature equation */
  SV_COUPLED_SOLUTION_VAR_WITH_BFC(T),
#define SV_WALL_T_OUTER SV_T
#define SV_WALL_T_OUTER_MEAN SV_T_MEAN
  SV_WALL_T_INNER,
  SV_WALL_GAS_T,
  SV_HEAT_FLUX,
  SV_HEAT_FLUX_SENSIBLE,
  SV_RAD_HEAT_FLUX,
  SV_HSRC_VD,
  SV_VAR_WITH_FC(T_STAGNATION),
  SV_PW_PREV,
  SV_PW_CURR,

  SV_UT_MEAN,
  SV_VT_MEAN,
  SV_WT_MEAN,
  SV_HEAT_FLUX_MEAN,

  /* enthalpy equation */
  SV_SOLUTION_VAR(H),
  SV_HS_G,
  SV_HKE,

  SV_ENERGY_M1,    /* energy term at previous time levels */
  SV_ENERGY_M2,

  SV_E_POR_SOLID_M1, /* solid energy contribution for porous media at old time levels */
  SV_E_POR_SOLID_M2,

  /* granular temperature equation */
  SV_SOLUTION_VAR(GRANULAR_TEMP),
  SV_GRANULAR_TEMP_MEAN,
  SV_GRANULAR_TEMP_RMS,

  /* granular flows variables */
  SV_DGP_DVOF,
  SV_VOF_GMAX,

  /* Dynamic SGS model parameters for LES */

  SV_LES_RFG_MATRIX,        /* ND_3 X ND_3 matrix for RFG */
  SV_LES_TFILTER_VOL,       /* test filter volume */
  SV_LES_MUT_CONST,         /* dynamic SGS eddy-viscosity const */
  SV_LES_LSTRESS,           /* Leonard stress */
  SV_LES_TFILTER_TKE,       /* test filtered TKE */
  SV_LES_MSTRESS,           /* Resolved stress */
  SV_LES_TMP_STRESS,        /* temporary stress */
  SV_LES_BETA_STRESS,       /* beta stress */
  SV_LES_TMP_VECTOR,        /* temporary vector */
  SV_LES_TMP_SCALAR,        /* temporary scalar */
  SV_LES_C_EPSILON,         /* dynamic SGS turbulent K.E. model parameter */
  SV_LES_MFLUX,           /* Resolved scalar flux vector */
  SV_LES_LFLUX,           /* Leonard scalar flux vector */
  SV_LES_PRANDTL,           /* dynamic Prandtl number */
  SV_LES_SCHMIDT,           /* dynamic Schmidt number */
  SV_LES_ALG_VAR,           /* dynamic algebraic variance constant */

  /* Subgrid-scale TKE to compute LES resolution quality (really used is ..._MEAN) */
  SV_SGS_TKE,
  SV_SGS_TKE_MEAN,
  SV_SGS_TKE_RMS,

  /* Spalart-Allmaras model */
  SV_SOLUTION_VAR(NUT),

  /* NRBC char. variables */
  SV_NRBC_DC,

  /*for pressure increment due to targeted mass flow rate*/
  SV_DP_TMFR,

  /* General NRBC. variable storage at time level=n*/
  SV_Q_N,


  /*Wet Steam & Moist Air models*/
  SV_SOLUTION_VAR(WSB),
  SV_SOLUTION_VAR(WSN),
  SV_SOLUTION_VAR(WSR),
  SV_MAS_GEN,
  SV_NUCL_RATE,
  SV_REL_HUMD,
  SV_FLX_BAL,

  /* ke & kw & v2f models */
  SV_SOLUTION_VAR_WITH_FC(K),
  SV_SOLUTION_VAR(KL),
  SV_SOLUTION_VAR(KT),
  SV_SOLUTION_VAR_WITH_FC(D),
  SV_SOLUTION_VAR_WITH_FC(O),
  SV_SOLUTION_VAR(V2),
  SV_SOLUTION_VAR(FEL),
  SV_SOLUTION_VAR(INTERMIT),
  SV_SOLUTION_VAR(RETHETA),
  SV_PRODUCTION,
  SV_PRODUCTION_L,
  SV_PROD_CCURV,
  SV_TURB_CCORNER,
  SV_RNG_ALPHA,
  SV_BSL_SST_F1,
  SV_GEKO_CSEP,
  SV_GEKO_CNW,
  SV_GEKO_CMIX,
  SV_GEKO_BF,
  SV_WALL_YPLUS,
  SV_WALL_KS,
  SV_WALL_KCON,
  SV_WALL_YPLUS_UTAU,
  SV_BUOY_PROD,
  SV_K_PREV_IT,
  SV_SBES_BF,
  SV_KESBES_O,
  SV_KESBES_O_G,
  SV_KESBES_O_RG,
  SV_KESBES_O_RG_AUX,
  SV_SQRT_KL,
  SV_SQRT_KL_G,
  SV_SQRT_KL_RG,
  SV_SQRT_KL_RG_AUX,
  SV_SQRT_KT,
  SV_SQRT_KT_G,
  SV_SQRT_KT_RG,
  SV_SQRT_KT_RG_AUX,
  SV_DTERM_T,
  SV_DTERM_L,
  SV_D2U,
  SV_D2V,
  SV_D2W,
  SV_SAS_STRAIN_MAG,
  SV_INTERMIT_EFF,
  SV_INTERMIT_EFF_SMOOTH,
  SV_INTERMIT_ALGEBRAIC,
  SV_INTERMIT_ALGEBRAIC_SMOOTH,
  SV_TRANS_ALG_REC,
  SV_ML_TKE_COEF,
  SV_ML_OMEGA_COEF,
  SV_ML_TRANS_ALG_COEF,
  SV_ML_WJ_EARSM_BETA1,
  SV_ML_WJ_EARSM_BETA3,
  SV_ML_WJ_EARSM_BETA4,
  SV_ML_WJ_EARSM_BETA6,
  SV_VSTG_SBES_FW,
  SV_DEFERRED_CONVECTION_S,
  SV_DEFERRED_DIFFUSION_S,

  /* RSM model */
#define SV_RST(ruu,i)((Svar)((ruu)+(i)*(SV_RVV-SV_RUU)))
  SV_SOLUTION_VAR(RUU),
  SV_SOLUTION_VAR(RVV),
  SV_SOLUTION_VAR(RWW),
  SV_SOLUTION_VAR(RUV),
  SV_SOLUTION_VAR(RVW),
  SV_SOLUTION_VAR(RUW),
  SV_RST_DEFERRED_CONVECTION_S,
  SV_RST_DEFERRED_DIFFUSION_S,

  /* transition model with roughness correlation */
  SV_GEOMETRIC_ROUGHNESS_HEIGHT,

  /* transition algebraic and one-equation model */
  SV_TKE_FOR_TU,
  SV_UINI,
  SV_UINI_RG,
  SV_UINI_RG_AUX,
  SV_UINI_G,
  SV_VORTNORM_X,
  SV_VORTNORM_X_RG,
  SV_VORTNORM_X_RG_AUX,
  SV_VORTNORM_X_G,
  SV_VORTNORM_Y,
  SV_VORTNORM_Y_RG,
  SV_VORTNORM_Y_RG_AUX,
  SV_VORTNORM_Y_G,
  SV_VORTNORM_Z,
  SV_VORTNORM_Z_RG,
  SV_VORTNORM_Z_RG_AUX,
  SV_VORTNORM_Z_G,

  /* storage for turbulence explicitly set variables */
  SV_SET_PHI,

  /* phase change */
  SV_LIQF,
  SV_LIQF_M1,

  /* discrete ordinates */
  SV_DO_I,
  SV_DO_I_SHELL,
  SV_DO_RECON_I,
  SV_DO_RECON_I_SHELL,
  SV_DO_B_AP,
  SV_DO_B_AP_SHELL,
  SV_DO_B_S,
  SV_DO_B_S_SHELL,
  SV_DO_IRRAD,
  SV_DO_IRRAD_SHELL,
  SV_DO_IRRAD_OLD,
  SV_DO_IRRAD_TMP,
  SV_DO_IWX,
  SV_DO_IWY,
#if RP_3D
  SV_DO_IWZ,
#endif
  SV_DO_IW_TMP,
  SV_DO_QMINUS,
  SV_DO_QNET,
  SV_DO_QTRANS,
  SV_DO_QREFL,
  SV_DO_QABS,
  SV_DO_IRR_QTRANS,
  SV_DO_IRR_QREFL,
  SV_DO_IRR_QABS,
  SV_DO_AP,
  SV_DO_S,
  SV_DO_S_SECONDARY,
  SV_DO_S_OLD_SECONDARY,
  SV_DO_RG,
  SV_DO_RG_AUX,
  SV_DO_I_CORR,
  SV_DO_I_TMP,
  SV_DO_S_TMP,
  SV_DO_COEFF01,
  SV_DO_COEFF10,


  /* species */
  SV_COUPLED_SOLUTION_VAR(Y_0),
  SV_COUPLED_SOLUTION_VAR(Y),

  /* set the number of species svars - note that adding additional svars may
   * increase this value.  See update_attributes() in species.c for a complete listing. */
#define SV_Y_LEN  19
#define SV_SOOTSPECIES_LEN  4

  SV_TFM_F,   /* Thickened Flamelet Model thickening factor */


  SV_TFM_E,   /* Thickened Flamelet Model efficiency factor */
  SV_TFM_OMEGA,  /* Thickened Flamelet Model dynamic thickening */

  SV_SOLUTION_VAR(DW),

#define SV_EPDF_I(i)((Svar)((SV_EPDF_0+(i)*(SV_EPDF_1-SV_EPDF_0))))
#define SV_EPDF_RG(i)((Svar)(SV_EPDF_I(i)+SV_EPDF_0_RG-SV_EPDF_0))
#define SV_EPDF_G(i)((Svar)(SV_EPDF_I(i)+SV_EPDF_0_G-SV_EPDF_0))
#define SV_EPDF_AP(i)((Svar)(SV_EPDF_I(i)+SV_EPDF_0_AP-SV_EPDF_0))
#define SV_EPDF_S(i)((Svar)(SV_EPDF_I(i)+SV_EPDF_0_S-SV_EPDF_0))

  SV_SOLUTION_VAR(EPDF_0),
  SV_SOLUTION_VAR(EPDF_1),
  SV_SOLUTION_VAR(EPDF_2),
  SV_SOLUTION_VAR(EPDF_3),
  SV_SOLUTION_VAR(EPDF_4),
  SV_SOLUTION_VAR(EPDF_5),
  SV_SOLUTION_VAR(EPDF_6),
  SV_SOLUTION_VAR(EPDF_7),
  SV_SOLUTION_VAR(EPDF_8),
  SV_SOLUTION_VAR(EPDF_9),
  SV_SOLUTION_VAR(EPDF_10),
  SV_SOLUTION_VAR(EPDF_11),
  SV_SOLUTION_VAR(EPDF_12),
  SV_SOLUTION_VAR(EPDF_13),
  SV_SOLUTION_VAR(EPDF_14),
  SV_SOLUTION_VAR(EPDF_15),
  SV_SOLUTION_VAR(EPDF_16),
  SV_SOLUTION_VAR(EPDF_17),
  SV_SOLUTION_VAR(EPDF_18),
  SV_SOLUTION_VAR(EPDF_19),
  SV_SOLUTION_VAR(EPDF_20),
  SV_SOLUTION_VAR(EPDF_21),
  SV_SOLUTION_VAR(EPDF_22),
  SV_SOLUTION_VAR(EPDF_23),
  SV_SOLUTION_VAR(EPDF_24),
  SV_SOLUTION_VAR(EPDF_25),
  SV_SOLUTION_VAR(EPDF_26),
  SV_SOLUTION_VAR(EPDF_27),
  SV_SOLUTION_VAR(EPDF_28),
  SV_SOLUTION_VAR(EPDF_29),
  SV_SOLUTION_VAR(EPDF_30),
  SV_SOLUTION_VAR(EPDF_31),
  SV_SOLUTION_VAR(EPDF_32),
  SV_SOLUTION_VAR(EPDF_33),
  SV_SOLUTION_VAR(EPDF_34),
  SV_SOLUTION_VAR(EPDF_35),
  SV_SOLUTION_VAR(EPDF_36),
  SV_SOLUTION_VAR(EPDF_37),
  SV_SOLUTION_VAR(EPDF_38),
  SV_SOLUTION_VAR(EPDF_39),
  SV_SOLUTION_VAR(EPDF_40),
  SV_SOLUTION_VAR(EPDF_41),
  SV_SOLUTION_VAR(EPDF_42),
  SV_SOLUTION_VAR(EPDF_43),
  SV_SOLUTION_VAR(EPDF_44),
  SV_SOLUTION_VAR(EPDF_45),
  SV_SOLUTION_VAR(EPDF_46),
  SV_SOLUTION_VAR(EPDF_47),
  SV_SOLUTION_VAR(EPDF_48),
  SV_SOLUTION_VAR(EPDF_49),


#define SV_EPDF_MAX SV_EPDF_49
  EXPAND_NSPE_SV(EPDF_VAR),
  SV_EPDF_YI,
  SV_EPDF_CORR,
  SV_EPDF_MODE,
  EXPAND_NSPE_SV(EPDF_FLUX),
  EXPAND_NSPE_SV(EPDF_STIFF),
  SV_EPDF_TMP,
  SV_SOLUTION_VAR(EPDF_H),
  SV_EPDF_T,
  SV_EPDF_T_VAR,
  SV_EPDF_HSRC_YI,
  SV_SPE_ENTHALPY,
  SV_SPE_JACOBIAN,
  SV_WALL_DR_TOTAL,
  SV_WALL_DIFFUSIVE_BC_MFLUX,
  SV_WALL_SPE,

  EXPAND_NSPE_SV(DR_SURF),    /* deposition rates for surface species */
  EXPAND_NSPE_SV(SITE_F),     /* site coverage */
  EXPAND_NSPE_SV(SITE_OLD),   /* previous time-stepsite coverage */
  EXPAND_NSPE_SV(SURF_F),     /* surface = solid = bulk species */
  SV_SPECIES_FLUX,            /* boundary fluxes */
  SV_CVD_AP,                  /* cvd     Ap -- temp array */
  SV_CVD_S,                   /* cvd source -- temp array */
  SV_DIFF_COEFF,
  SV_THERMAL_DIFF_COEFF,
  EXPAND_NSPE_SV(ECHEM_RX),         /* echem reaction rate */
  EXPAND_NSPE_SV(CORROSION_RATE),   /* Solid species corrosion rate */

  SV_HSRC_YI,   /* heat source due to species diffusion and/or reactions */
  SV_HSRC_YI_RXN,   /* heat source due to species diff. of surf-rxn in porous */
  SV_HSRC_DR,       /* enthalpy loss due to surface deposition */
  SV_TOT_HSRC_DR,   /* term used to calculate total enthalpy heat loss due to surface deposition,
                       used for reporting only */
  SV_TOT_RXN,      /* total enthalpy source due to all types of chemical reactions */

  SV_HSRC_YI_TMP,
  SV_HSRC_YI_RXN_TMP,
  SV_HSRC_DR_TMP,

  SV_YI_EDC,                /* Eddy Dissipation Concept */
  SV_CHEM_TIME_SCALE,       /* Chemical time scale for Characteristic time model */
  SV_RICH_FLAM_FAC,         /* reaction retardation factor for Characteristic time model */
  SV_USER_RTE_TIMESCALE,    /* User-Defined timescale for Relax-to-Equilibrium */

  SV_MP_STIFF_CHEM_MASS_S, /* mass source for inter-phase stiff chemistry */

  SV_KIN_MONITOR,
  /* composition pdf transport */
  SV_MU_T_G,
  SV_MU_T_RG,
  SV_MU_T_RG_AUX,
  SV_PDFT_V,
  SV_PDFT_Q,
  SV_PDFT_Q_G,
  SV_PDFT_Q_TA,
  SV_PDFT_SVOL_TA,
  SV_PDFT_T4_TA, /* T^4 averaging for radiation coupling */
  SV_PDFT_DIFF,
  SV_PDFT_PHI,
  SV_PDFT_PHI_G,
  SV_PDFT_MASS_TA, /* particle mass in cell time averaging */
  SV_PDFT_CORRECT_VEL,
  SV_PDFT_IEM_FLAG,
  SV_N_PDFT_IEM_BASIS0,
  SV_N_PDFT_IEM_BASIS1,
  SV_HEAT_FLUX_PDFT,
  SV_HEAT_FLUX_SENSIBLE_PDFT,

  SV_ISAT_TIME,      /* wall time in isat for dynamic partioning */
  SV_DRG_NSPE,       /* number of species in DRG reduced mechanism */
  SV_DRG_NREACTIONS, /* number of reactions in DRG reduced mechanism */

  /* pdf model */
  SV_SOLUTION_VAR(FMEAN),
  SV_SOLUTION_VAR(FMEAN2),
  SV_SOLUTION_VAR(FVAR),
  SV_SOLUTION_VAR(FVAR2),
  SV_F_MEAN,
  SV_F_RMS,
  SV_FVAR_PROD,
  SV_FVAR2_PROD,
  SV_FVAR_RANS,
  SV_FVAR_RANS_M1,
  SV_FVAR_RANS_M2,
  SV_FVAR2_RANS,
  SV_FVAR2_RANS_M1,
  SV_FVAR2_RANS_M2,
  SV_HYBRID_CVAR,
  SV_HYBRID_SCAD,
  SV_PDF_MW,
  SV_PDF_DEPARTURE_ENTHALPY,
  SV_PDF_DEPARTURE_ENTHALPY_U,
  SV_PDF_CO2,
  SV_PDF_H2O,
  SV_PDF_FUEL0,
  SV_PDF_FUEL1,
  SV_PDF_FUEL2,
  SV_PDF_FUEL3,
  SV_PDF_FUEL4,
  SV_PDF_FUEL5,
  SV_PDF_FUEL6,
  SV_PDF_FUEL7,
  SV_PDF_FUEL8,
  SV_PDF_FUEL9,
  SV_PDF_RBFUEL0, /* Reburn species index */
  SV_PDF_RBFUEL1,
  SV_PDF_RBFUEL2,
  SV_PDF_RBFUEL3,
  SV_PDF_RBFUEL4,
  SV_PDF_SNCRSP, /* SNCR species index */
  SV_PDF_PRECSP0,
  SV_PDF_PRECSP1,
  SV_PDF_PRECSP2,
  SV_PDF_PRECSP3,
  SV_PDF_PRECSP4,
  SV_PDF_SGROWS0,
  SV_PDF_SGROWS1,
  SV_PDF_SGROWS2,
  SV_PDF_SGROWS3,
  SV_PDF_SGROWS4,
  SV_PDF_SOOT_FUEL0,
  SV_PDF_SOOT_FUEL1,
  SV_PDF_SOOT_FUEL2,
  SV_PDF_SOOT_OXID,
  SV_PDF_O2,
  SV_PDF_O,
  SV_PDF_OH,
  SV_PDF_H2,
  SV_PDF_H,
  SV_PDF_MASS_H2O,
  SV_PDF_N2,
  SV_PDF_N,
  SV_PDF_CO,
  SV_PDF_CH,
  SV_PDF_CH2,
  SV_PDF_CH3,
  SV_PDF_S,
  SV_PDF_C2H2,
  SV_PDF_C6H6,
  SV_PDF_C6H5,
  SV_PDF_MASS_CO2,
  SV_PDF_SOOT_FUEL0_MOLE,
  SV_PDF_SOOT_FUEL1_MOLE,
  SV_PDF_SOOT_FUEL2_MOLE,
  SV_PDF_N2O_QUASI,
  SV_PDF_POLLUT0_FWD,
  SV_PDF_POLLUT1_FWD,
  SV_PDF_POLLUT2_FWD,
  SV_PDF_POLLUT3_FWD,
  SV_PDF_POLLUT4_FWD,
  SV_PDF_POLLUT5_FWD,
  SV_PDF_POLLUT6_FWD,
  SV_PDF_POLLUT7_FWD,
  SV_PDF_POLLUT8_FWD,
  SV_PDF_POLLUT9_FWD,
  SV_PDF_POLLUT10_FWD,
  SV_PDF_POLLUT11_FWD,
  SV_PDF_POLLUT12_FWD,
  SV_PDF_POLLUT13_FWD,
  SV_PDF_POLLUT14_FWD,
  SV_PDF_POLLUT15_FWD,
  SV_PDF_POLLUT16_FWD,
  SV_PDF_POLLUT17_FWD,
  SV_PDF_POLLUT18_FWD,
  SV_PDF_POLLUT19_FWD,
  SV_PDF_POLLUT20_FWD,
  SV_PDF_POLLUT21_FWD,
  SV_PDF_POLLUT22_FWD,
  SV_PDF_POLLUT0_REV,
  SV_PDF_POLLUT1_REV,
  SV_PDF_POLLUT2_REV,
  SV_PDF_POLLUT3_REV,
  SV_PDF_POLLUT4_REV,
  SV_PDF_POLLUT5_REV,
  SV_PDF_POLLUT6_REV,
  SV_PDF_POLLUT7_REV,
  SV_PDF_POLLUT8_REV,
  SV_PDF_POLLUT9_REV,
  SV_PDF_POLLUT10_REV,
  SV_PDF_POLLUT11_REV,
  SV_PDF_POLLUT12_REV,
  SV_PDF_POLLUT13_REV,
  SV_PDF_POLLUT14_REV,
  SV_PDF_POLLUT15_REV,
  SV_PDF_POLLUT16_REV,
  SV_PDF_POLLUT17_REV,
  SV_PDF_POLLUT18_REV,
  SV_PDF_POLLUT19_REV,
  SV_PDF_POLLUT20_REV,
  SV_PDF_POLLUT21_REV,
  SV_PDF_POLLUT22_REV,
  SV_PDF_POLLUT_NO0_RATE,
  SV_PDF_POLLUT_NO1_RATE,
  SV_PDF_POLLUT_NO2_RATE,
  SV_PDF_POLLUT_NO3_RATE,
  SV_PDF_POLLUT_NO4_RATE,
  SV_PDF_POLLUT_NO5_RATE,
  SV_PDF_POLLUT_NO6_RATE,
  SV_PDF_POLLUT_SOOTM0_RATE,
  SV_PDF_POLLUT_SOOTM1_RATE,
  SV_PDF_POLLUT_SOOTM2_RATE,
  SV_PDF_POLLUT_NUCLEI0_RATE,
  SV_PDF_POLLUT_NUCLEI1_RATE,

  /* premixed combustion model */
  SV_SOLUTION_VAR(PREMIXC),
  SV_PREMIXC_RATE,
  SV_PREMIXC_T,
  SV_PREMIXC_GMAG,
  SV_C_MEAN,
  SV_C_RMS,
  SV_PREMIXC_TOT_STR,

  SV_SOLUTION_VAR(MICRO_MIX_FVAR1),
  SV_SOLUTION_VAR(MICRO_MIX_FVAR2),
  SV_SOLUTION_VAR(MICRO_MIX_FVAR3),

  /* Unsteady Flamelet Model Slow Product Species */
#define SV_UFLA_YI(i)   ((Svar)((SV_UFLA_YI_0+(i)*(SV_UFLA_YI_1-SV_UFLA_YI_0))))
#define SV_UFLA_YI_M1(i)   ((Svar)( SV_UFLA_YI(i) + SV_UFLA_YI_0_M1-SV_UFLA_YI_0))
#define SV_UFLA_YI_M2(i)   ((Svar)( SV_UFLA_YI(i) + SV_UFLA_YI_0_M2-SV_UFLA_YI_0))
#define SV_UFLA_YI_AP SV_UFLA_YI_0_AP
#define SV_UFLA_YI_S  SV_UFLA_YI_0_S

  SV_SOLUTION_VAR(UFLA_YI_0),
  SV_SOLUTION_VAR(UFLA_YI_1),
  SV_SOLUTION_VAR(UFLA_YI_2),
  SV_SOLUTION_VAR(UFLA_YI_3),
  SV_SOLUTION_VAR(UFLA_YI_4),
  SV_SOLUTION_VAR(UFLA_YI_5),
  SV_SOLUTION_VAR(UFLA_YI_6),
  SV_SOLUTION_VAR(UFLA_YI_7),
  SV_SOLUTION_VAR(UFLA_YI_8),
  SV_SOLUTION_VAR(UFLA_YI_9),
#define SV_UFLA_YI_MAX SV_UFLA_YI_9
  EXPAND_NPROB_SV(UFLA_TEMP_I_NUM),
  EXPAND_NPROB_SV(UFLA_DEN_I),
  EXPAND_NPROB_SV(UFLA_YI_I_NUM),
#define SV_UFLA_YI_I_NUM_MAX SV_UFLA_YI_I_NUM_9

  SV_I_REACTOR_NET,

  SV_SOLUTION_VAR(PHI_1), /* electro-chemistry potential */
  SV_PHI_1_FARADAIC_FLUX,
  SV_PHI_1_CORROSION_RATE,
  SV_PHI_1_VOLTAGE_JUMP,
  SV_PHI_1_CONTACT_RESISTANCE,
  SV_HSRC_PHI,
  SV_PHI_1_SAVED_G,
  SV_PHI_1_ACCU_CORROSION_RATE,

  SV_SOLUTION_VAR(PHI_2),
  SV_PHI_2_SAVED_G,
  SV_TRANSFER_CURRENT,
  SV_CURRENT,
  SV_OVER_POTENTIAL,
  SV_JOULE_HEATING,
  SV_ELECTRO_SOURCE,
  SV_ELECTRO_VOF_AP,
  SV_OSMOTIC_DRAG,
  SV_CP_COEFF,

  SV_SOLUTION_VAR(LITHIUM),
  SV_LITHIUM_MIGRATION_SOURCE,
  SV_LITHIUM_IE,
  SV_LITHIUM_SAVED_G,
  SV_LITHIUM_JUMP,
  SV_LITHIUM_CONTACT_RESISTANCE,
  SV_LITHIUM_WALL,
  SV_LITHIUM_WALL2,

  SV_BATTERY_CURRENT,
  SV_BATTERY_CURR_X,
  SV_BATTERY_CURR_Y,
  SV_BATTERY_CURR_Z,
  SV_BATTERY_OHMIC_SOURCE,
  SV_BATTERY_ECHEM_SOURCE,
  SV_BATTERY_ACTIVATION,
  SV_BATTERY_DISCHARGE_DEPTH,
  SV_BATTERY_CURR_SOURCE,
  SV_BATTERY_CURR_PX,
  SV_BATTERY_CURR_PY,
  SV_BATTERY_CURR_PZ,
  SV_BATTERY_CURR_NX,
  SV_BATTERY_CURR_NY,
  SV_BATTERY_CURR_NZ,
  SV_BATTERY_SHORT_R,
  SV_BATTERY_SHORT_CURR,
  SV_BATTERY_CURR_ECHEM,
  SV_BATTERY_SHORT_SOURCE,
  SV_BATTERY_ROM_PHI_P,
  SV_BATTERY_ROM_PHI_N,
  SV_BATTERY_ROM_JH,
  SV_BATTERY_SEI_REACTION,
  SV_BATTERY_PE_REACTION,
  SV_BATTERY_NE_REACTION,
  SV_BATTERY_E_REACTION,
  SV_BATTERY_ISC_REACTION,
  SV_BATTERY_ABUSE_SOURCE,
  SV_BATTERY_PHI_SOURCE,
  SV_BATTERY_PHI_AP,
  SV_BATTERY_T_SOURCE,
  SV_BATTERY_CELL_U,
  SV_BATTERY_CELL_R,
  SV_BATTERY_NEWMAN_PHIS_P,
  SV_BATTERY_NEWMAN_PHIS_N,
  SV_BATTERY_NEWMAN_PHIE,
  SV_BATTERY_NEWMAN_PHIS_PHIE,
  SV_BATTERY_CLUSTER,
  SV_BATTERY_CLUSTER_ID,
  SV_BATTERY_SWELL_N_REF,
  SV_BATTERY_SWELL_N_DEF,
  SV_BATTERY_SWELL_EPSILON_1D,
  SV_BATTERY_TOTAL_EPSILON_1D,
  SV_BATTERY_TOTAL_SIGMA_1D,
  SV_BATTERY_TOTAL_SIGMA_1D_OLD,

  /* population balance variables */
#define SV_PB_DISC_I(i)((Svar)((SV_PB_DISC_0+(i)*(SV_PB_DISC_1-SV_PB_DISC_0))))
#define SV_PB_DISCI_M1(i)((Svar)(SV_PB_DISC_I(i)+SV_PB_DISC_0_M1-SV_PB_DISC_0))
#define SV_PB_DISCI_M2(i)((Svar)(SV_PB_DISC_I(i)+SV_PB_DISC_0_M2-SV_PB_DISC_0))
#define SV_PB_DISCI_RG(i)((Svar)(SV_PB_DISC_I(i)+SV_PB_DISC_0_RG-SV_PB_DISC_0))
#define SV_PB_DISCI_G(i)((Svar)(SV_PB_DISC_I(i)+SV_PB_DISC_0_G-SV_PB_DISC_0))
#define SV_PB_DISCI_PS(i)((Svar)(SV_PB_DISC_PS_0+i))
  SV_SOLUTION_VAR(PB_DISC_0),
  SV_SOLUTION_VAR(PB_DISC_1),
  SV_SOLUTION_VAR(PB_DISC_2),
  SV_SOLUTION_VAR(PB_DISC_3),
  SV_SOLUTION_VAR(PB_DISC_4),
  SV_SOLUTION_VAR(PB_DISC_5),
  SV_SOLUTION_VAR(PB_DISC_6),
  SV_SOLUTION_VAR(PB_DISC_7),
  SV_SOLUTION_VAR(PB_DISC_8),
  SV_SOLUTION_VAR(PB_DISC_9),
  SV_SOLUTION_VAR(PB_DISC_10),
  SV_SOLUTION_VAR(PB_DISC_11),
  SV_SOLUTION_VAR(PB_DISC_12),
  SV_SOLUTION_VAR(PB_DISC_13),
  SV_SOLUTION_VAR(PB_DISC_14),
  SV_SOLUTION_VAR(PB_DISC_15),
  SV_SOLUTION_VAR(PB_DISC_16),
  SV_SOLUTION_VAR(PB_DISC_17),
  SV_SOLUTION_VAR(PB_DISC_18),
  SV_SOLUTION_VAR(PB_DISC_19),
  SV_SOLUTION_VAR(PB_DISC_20),
  SV_SOLUTION_VAR(PB_DISC_21),
  SV_SOLUTION_VAR(PB_DISC_22),
  SV_SOLUTION_VAR(PB_DISC_23),
  SV_SOLUTION_VAR(PB_DISC_24),
  SV_SOLUTION_VAR(PB_DISC_25),
  SV_SOLUTION_VAR(PB_DISC_26),
  SV_SOLUTION_VAR(PB_DISC_27),
  SV_SOLUTION_VAR(PB_DISC_28),
  SV_SOLUTION_VAR(PB_DISC_29),
  SV_SOLUTION_VAR(PB_DISC_30),
  SV_SOLUTION_VAR(PB_DISC_31),
  SV_SOLUTION_VAR(PB_DISC_32),
  SV_SOLUTION_VAR(PB_DISC_33),
  SV_SOLUTION_VAR(PB_DISC_34),
  SV_SOLUTION_VAR(PB_DISC_35),
  SV_SOLUTION_VAR(PB_DISC_36),
  SV_SOLUTION_VAR(PB_DISC_37),
  SV_SOLUTION_VAR(PB_DISC_38),
  SV_SOLUTION_VAR(PB_DISC_39),
  SV_SOLUTION_VAR(PB_DISC_40),
  SV_SOLUTION_VAR(PB_DISC_41),
  SV_SOLUTION_VAR(PB_DISC_42),
  SV_SOLUTION_VAR(PB_DISC_43),
  SV_SOLUTION_VAR(PB_DISC_44),
  SV_SOLUTION_VAR(PB_DISC_45),
  SV_SOLUTION_VAR(PB_DISC_46),
  SV_SOLUTION_VAR(PB_DISC_47),
  SV_SOLUTION_VAR(PB_DISC_48),
  SV_SOLUTION_VAR(PB_DISC_49),
  EXPAND_NPB_DISC_SV(PB_DISC_PS),
  EXPAND_NPB_DISC_SV(PB_DISC_DIFF_COEFF),
  SV_PB_DISC_IMB,

#define SV_PB_DISC_MAX SV_PB_DISC_49
#define SV_PB_DISCI_AP SV_PB_DISC_0_AP
#define SV_PB_DISCI_S  SV_PB_DISC_0_S

  /*PB QMOM variables*/
#define SV_PB_QMOM_I(i)((Svar)((SV_PB_QMOM_0+(i)*(SV_PB_QMOM_1-SV_PB_QMOM_0))))
#define SV_PB_QMOMI_M1(i)((Svar)(SV_PB_QMOM_I(i)+SV_PB_QMOM_0_M1-SV_PB_QMOM_0))
#define SV_PB_QMOMI_M2(i)((Svar)(SV_PB_QMOM_I(i)+SV_PB_QMOM_0_M2-SV_PB_QMOM_0))
#define SV_PB_QMOMI_RG(i)((Svar)(SV_PB_QMOM_I(i)+SV_PB_QMOM_0_RG-SV_PB_QMOM_0))
#define SV_PB_QMOMI_G(i)((Svar)(SV_PB_QMOM_I(i)+SV_PB_QMOM_0_G-SV_PB_QMOM_0))
#define SV_PB_QMOMI_PS(i)((Svar)(SV_PB_QMOM_PS_0+i))
#define SV_PB_QMOMI_L(i)((Svar)(SV_PB_QMOM_L_0+i))
#define SV_PB_QMOMI_W(i)((Svar)(SV_PB_QMOM_W_0+i))
  SV_SOLUTION_VAR(PB_QMOM_0),
  SV_SOLUTION_VAR(PB_QMOM_1),
  SV_SOLUTION_VAR(PB_QMOM_2),
  SV_SOLUTION_VAR(PB_QMOM_3),
  SV_SOLUTION_VAR(PB_QMOM_4),
  SV_SOLUTION_VAR(PB_QMOM_5),
  SV_SOLUTION_VAR(PB_QMOM_6),
  SV_SOLUTION_VAR(PB_QMOM_7),
  SV_SOLUTION_VAR(PB_QMOM_8),
  SV_SOLUTION_VAR(PB_QMOM_9),
  EXPAND_NPB_QMOM_SV(PB_QMOM_PS),
  EXPAND_NPB_QMOM_SV(PB_QMOM_DIFF_COEFF),
  EXPAND_L_W_PB_QMOM_SV(PB_QMOM_L),
  EXPAND_L_W_PB_QMOM_SV(PB_QMOM_W),
  SV_PB_QMOM_IMB,
  SV_PB_QMOM_real_mom,
  EXPAND_NPB_QMOM_SV(PB_QMOM_ZETA),

#define SV_PB_QMOM_MAX SV_PB_QMOM_9
#define SV_PB_QMOMI_AP SV_PB_QMOM_0_AP
#define SV_PB_QMOMI_S  SV_PB_QMOM_0_S

#define SV_PB_QMOMI_ZETA(i)((Svar)((SV_PB_QMOM_ZETA_0+(i)*(SV_PB_QMOM_ZETA_1-SV_PB_QMOM_ZETA_0))))
#define SV_PB_QMOM_ZETA_MAX SV_PB_QMOM_ZETA_9

  /* PB SMM variables */
#define SV_PB_SMM_I(i)((Svar)((SV_PB_SMM_0+(i)*(SV_PB_SMM_1-SV_PB_SMM_0))))
#define SV_PB_SMMI_M1(i)((Svar)(SV_PB_SMM_I(i)+SV_PB_SMM_0_M1-SV_PB_SMM_0))
#define SV_PB_SMMI_M2(i)((Svar)(SV_PB_SMM_I(i)+SV_PB_SMM_0_M2-SV_PB_SMM_0))
#define SV_PB_SMMI_RG(i)((Svar)(SV_PB_SMM_I(i)+SV_PB_SMM_0_RG-SV_PB_SMM_0))
#define SV_PB_SMMI_G(i)((Svar)(SV_PB_SMM_I(i)+SV_PB_SMM_0_G-SV_PB_SMM_0))
#define SV_PB_SMMI_PS(i)((Svar)(SV_PB_SMM_PS_0+i))
  SV_SOLUTION_VAR(PB_SMM_0),
  SV_SOLUTION_VAR(PB_SMM_1),
  SV_SOLUTION_VAR(PB_SMM_2),
  SV_SOLUTION_VAR(PB_SMM_3),
  SV_SOLUTION_VAR(PB_SMM_4),
  SV_SOLUTION_VAR(PB_SMM_5),
  SV_SOLUTION_VAR(PB_SMM_6),
  SV_SOLUTION_VAR(PB_SMM_7),
  SV_SOLUTION_VAR(PB_SMM_8),
  SV_SOLUTION_VAR(PB_SMM_9),
  EXPAND_NPB_SMM_SV(PB_SMM_PS),
  EXPAND_NPB_SMM_SV(PB_SMM_DIFF_COEFF),
  SV_PB_SMM_IMB,

#define SV_PB_SMM_MAX SV_PB_SMM_9
#define SV_PB_SMMI_AP SV_PB_SMM_0_AP
#define SV_PB_SMMI_S  SV_PB_SMM_0_S

#define DQMOM_T 1
  /* DQMOM */
#if DQMOM_T
  SV_SOLUTION_VAR(PB_DQMOM),
  SV_PB_DQMOM_IMB,
  SV_PB_DQMOM_vof_src,
  SV_PB_DQMOM_vof_src_ng,
  SV_PB_DQMOM_m4_src,
#endif
  SV_PB_DISC_INHOMO_GR,
  SV_PB_DISC_INHOMO_RPI_SRC,
  SV_PB_EXP, /*common to all PB models*/
  SV_PB_MT, /*mass transfer for Inhomogeneous Discrete and DQMOM*/
  SV_MP_MT_KL, /*storage for Kl*/
  SV_VM_V,
  SV_VM_V_TMP,
  SV_VMASS_VFLUX, /*implicit vm*/
  /* interfacial area variables */
  SV_SOLUTION_VAR(IAC),
  SV_IAC_IMB,
  SV_IAC_EXP,
  /*SV_IAC_FP,
    SV_IAC_FP_G,
    SV_IAC_FP_RG,*/
  /*SV_IAC_DIFF_COEFF,*/

  /* level-set */
  SV_SOLUTION_VAR(LSF),
  SV_LSF_STF_V,
  SV_LSF_M1_0,
  SV_LSF_AREA,

  /* user defined scalars */
  SV_UDS_MSMD_ID,
#define SV_UDS_I(i)((Svar)((SV_UDS_0+(i)*(SV_UDS_1-SV_UDS_0))))
#define SV_UDSI_M1(i)((Svar)(SV_UDS_I(i)+SV_UDS_0_M1-SV_UDS_0))
#define SV_UDSI_M2(i)((Svar)(SV_UDS_I(i)+SV_UDS_0_M2-SV_UDS_0))
#define SV_UDSI_RG(i)((Svar)(SV_UDS_I(i)+SV_UDS_0_RG-SV_UDS_0))
#define SV_UDSI_G(i)((Svar)(SV_UDS_I(i)+SV_UDS_0_G-SV_UDS_0))
  SV_SOLUTION_VAR_WITH_FC(UDS_0),
  SV_SOLUTION_VAR_WITH_FC(UDS_1),
  SV_SOLUTION_VAR_WITH_FC(UDS_2),
  SV_SOLUTION_VAR_WITH_FC(UDS_3),
  SV_SOLUTION_VAR_WITH_FC(UDS_4),
  SV_SOLUTION_VAR_WITH_FC(UDS_5),
  SV_SOLUTION_VAR_WITH_FC(UDS_6),
  SV_SOLUTION_VAR_WITH_FC(UDS_7),
  SV_SOLUTION_VAR_WITH_FC(UDS_8),
  SV_SOLUTION_VAR_WITH_FC(UDS_9),
  SV_SOLUTION_VAR_WITH_FC(UDS_10),
  SV_SOLUTION_VAR_WITH_FC(UDS_11),
  SV_SOLUTION_VAR_WITH_FC(UDS_12),
  SV_SOLUTION_VAR_WITH_FC(UDS_13),
  SV_SOLUTION_VAR_WITH_FC(UDS_14),
  SV_SOLUTION_VAR_WITH_FC(UDS_15),
  SV_SOLUTION_VAR_WITH_FC(UDS_16),
  SV_SOLUTION_VAR_WITH_FC(UDS_17),
  SV_SOLUTION_VAR_WITH_FC(UDS_18),
  SV_SOLUTION_VAR_WITH_FC(UDS_19),
  SV_SOLUTION_VAR_WITH_FC(UDS_20),
  SV_SOLUTION_VAR_WITH_FC(UDS_21),
  SV_SOLUTION_VAR_WITH_FC(UDS_22),
  SV_SOLUTION_VAR_WITH_FC(UDS_23),
  SV_SOLUTION_VAR_WITH_FC(UDS_24),
  SV_SOLUTION_VAR_WITH_FC(UDS_25),
  SV_SOLUTION_VAR_WITH_FC(UDS_26),
  SV_SOLUTION_VAR_WITH_FC(UDS_27),
  SV_SOLUTION_VAR_WITH_FC(UDS_28),
  SV_SOLUTION_VAR_WITH_FC(UDS_29),
  SV_SOLUTION_VAR_WITH_FC(UDS_30),
  SV_SOLUTION_VAR_WITH_FC(UDS_31),
  SV_SOLUTION_VAR_WITH_FC(UDS_32),
  SV_SOLUTION_VAR_WITH_FC(UDS_33),
  SV_SOLUTION_VAR_WITH_FC(UDS_34),
  SV_SOLUTION_VAR_WITH_FC(UDS_35),
  SV_SOLUTION_VAR_WITH_FC(UDS_36),
  SV_SOLUTION_VAR_WITH_FC(UDS_37),
  SV_SOLUTION_VAR_WITH_FC(UDS_38),
  SV_SOLUTION_VAR_WITH_FC(UDS_39),
  SV_SOLUTION_VAR_WITH_FC(UDS_40),
  SV_SOLUTION_VAR_WITH_FC(UDS_41),
  SV_SOLUTION_VAR_WITH_FC(UDS_42),
  SV_SOLUTION_VAR_WITH_FC(UDS_43),
  SV_SOLUTION_VAR_WITH_FC(UDS_44),
  SV_SOLUTION_VAR_WITH_FC(UDS_45),
  SV_SOLUTION_VAR_WITH_FC(UDS_46),
  SV_SOLUTION_VAR_WITH_FC(UDS_47),
  SV_SOLUTION_VAR_WITH_FC(UDS_48),
  SV_SOLUTION_VAR_WITH_FC(UDS_49),

  EXPAND_NUDS_SV(UDS_DIFF_COEFF),
  EXPAND_NUDS_SV(UDS_ANISO_DCOEFF),
  EXPAND_NUDS_SV(UDS_FLUX),

#define SV_UDS_MAX SV_UDS_49
#define SV_UDSI_AP SV_UDS_0_AP
#define SV_UDSI_S  SV_UDS_0_S

  /*hybrid initialization vars*/
#define SV_ADS_I(i)((Svar)((SV_ADS_0+(i)*(SV_ADS_1-SV_ADS_0))))
#define SV_ADSI_RG(i)((Svar)(SV_ADS_I(i)+SV_ADS_0_RG-SV_ADS_0))
#define SV_ADSI_G(i)((Svar)(SV_ADS_I(i)+SV_ADS_0_G-SV_ADS_0))
  SV_SOLUTION_VAR(ADS_0),
  SV_SOLUTION_VAR(ADS_1),
#define SV_ADS_MAX SV_ADS_1
#define SV_ADSI_AP SV_ADS_0_AP
#define SV_ADSI_S  SV_ADS_0_S

  SV_UDM_I,                     /* user defined memory */
  SV_NODE_UDM_I,                /* user defined node memory */

  /* storage for runtime DFT */
  SV_RTDFT_RP_I,
  SV_RTDFT_IP_I,

  /* p1 radiation model */
  SV_SOLUTION_VAR(P1),
#define SV_WALL_G_OUTER SV_P1
  SV_WALL_G_INNER,
  SV_P1_DIFF,
  SV_P1_IRRAD,
#define SV_WALL_G_OUTER_IRRAD SV_P1_IRRAD

  SV_UP,
  SV_UP_AP,
  SV_UP_S,
  SV_UP_G,
  SV_UP_RG,
  SV_UP_RG_AUX,
  SV_VP,
  SV_WP,

  EXPAND_NSPE_SV(YI_MELT),
  EXPAND_NSPE_SV_M1(YI_MELT),
  EXPAND_NSPE_SV_M2(YI_MELT),
  SV_YIL,
  SV_YIL_RG,
  SV_YIL_RG_AUX,
  SV_YIL_G,
  EXPAND_NSPE_SV(MELT_KP),
  SV_SOLID_BETA,
  /* 2d swirl */
  SV_OMEGA_G,
  SV_SP_WSWIRL,
  /*scalar transport with combustion*/
  SV_TSS_SCALAR_0,
  SV_TSS_SCALAR_1,
  SV_TSS_SCALAR_2,
  SV_TSS_SCALAR_3,
  SV_TSS_SCALAR_4,
  SV_TSS_SCALAR_5,
  SV_TSS_SCALAR_6,
  SV_TSS_SCALAR_7,
  SV_TSS_SCALAR_8,
  SV_TSS_SCALAR_9,
  SV_TSS_SCALAR_AP,
  SV_TSS_SCALAR_S,
  SV_TSS_SCALAR_RG,
  SV_TSS_SCALAR_RG_AUX,
  SV_TSS_SCALAR_G,
  SV_TSS_SCALAR_0_M1,
  SV_TSS_SCALAR_0_M2,
  SV_TSS_SCALAR_1_M1,
  SV_TSS_SCALAR_1_M2,
  SV_TSS_SCALAR_2_M1,
  SV_TSS_SCALAR_2_M2,
  SV_TSS_SCALAR_3_M1,
  SV_TSS_SCALAR_3_M2,
  SV_TSS_SCALAR_4_M1,
  SV_TSS_SCALAR_4_M2,
  SV_TSS_SCALAR_5_M1,
  SV_TSS_SCALAR_5_M2,
  SV_TSS_SCALAR_6_M1,
  SV_TSS_SCALAR_6_M2,
  SV_TSS_SCALAR_7_M1,
  SV_TSS_SCALAR_7_M2,
  SV_TSS_SCALAR_8_M1,
  SV_TSS_SCALAR_8_M2,
  SV_TSS_SCALAR_9_M1,
  SV_TSS_SCALAR_9_M2,
  SV_TSS_SCALAR_FWD_RATE_0,
  SV_TSS_SCALAR_FWD_RATE_1,
  SV_TSS_SCALAR_FWD_RATE_2,
  SV_TSS_SCALAR_FWD_RATE_3,
  SV_TSS_SCALAR_FWD_RATE_4,
  SV_TSS_SCALAR_FWD_RATE_5,
  SV_TSS_SCALAR_FWD_RATE_6,
  SV_TSS_SCALAR_FWD_RATE_7,
  SV_TSS_SCALAR_FWD_RATE_8,
  SV_TSS_SCALAR_FWD_RATE_9,
  SV_TSS_SCALAR_REV_RATE_0,
  SV_TSS_SCALAR_REV_RATE_1,
  SV_TSS_SCALAR_REV_RATE_2,
  SV_TSS_SCALAR_REV_RATE_3,
  SV_TSS_SCALAR_REV_RATE_4,
  SV_TSS_SCALAR_REV_RATE_5,
  SV_TSS_SCALAR_REV_RATE_6,
  SV_TSS_SCALAR_REV_RATE_7,
  SV_TSS_SCALAR_REV_RATE_8,
  SV_TSS_SCALAR_REV_RATE_9,
  SV_TSS_SCALAR_NET_RATE_0,
  SV_TSS_SCALAR_NET_RATE_1,
  SV_TSS_SCALAR_NET_RATE_2,
  SV_TSS_SCALAR_NET_RATE_3,
  SV_TSS_SCALAR_NET_RATE_4,
  SV_TSS_SCALAR_NET_RATE_5,
  SV_TSS_SCALAR_NET_RATE_6,
  SV_TSS_SCALAR_NET_RATE_7,
  SV_TSS_SCALAR_NET_RATE_8,
  SV_TSS_SCALAR_NET_RATE_9,

  /* pollutant models */
  SV_POLLUT0,
  SV_POLLUT1,
  SV_POLLUT2,
  SV_POLLUT3,
  SV_POLLUT4,
  SV_POLLUT5,
  SV_POLLUT6,
  SV_POLLUT7,
  SV_POLLUT8,
  SV_POLLUT9,
  SV_POLLUT10,
  SV_POLLUT11,
  SV_POLLUT12,
  SV_POLLUT13,
  SV_POLLUT14,
  SV_POLLUT15,
  SV_POLLUT16,
  SV_POLLUT17,
  SV_POLLUT18,
  SV_POLLUT19,
  SV_POLLUT20,
  SV_POLLUT21,
  SV_POLLUT22,
  SV_POLLUT_AP,
  SV_POLLUT_S,
  SV_POLLUT_RG,
  SV_POLLUT_RG_AUX,
  SV_POLLUT_G,
  SV_POLLUT0_M1,
  SV_POLLUT0_M2,
  SV_POLLUT1_M1,
  SV_POLLUT1_M2,
  SV_POLLUT2_M1,
  SV_POLLUT2_M2,
  SV_POLLUT3_M1,
  SV_POLLUT3_M2,
  SV_POLLUT4_M1,
  SV_POLLUT4_M2,
  SV_POLLUT5_M1,
  SV_POLLUT5_M2,
  SV_POLLUT6_M1,
  SV_POLLUT6_M2,
  SV_POLLUT7_M1,
  SV_POLLUT7_M2,
  SV_POLLUT8_M1,
  SV_POLLUT8_M2,
  SV_POLLUT9_M1,
  SV_POLLUT9_M2,
  SV_POLLUT10_M1,
  SV_POLLUT10_M2,
  SV_POLLUT11_M1,
  SV_POLLUT11_M2,
  SV_POLLUT12_M1,
  SV_POLLUT12_M2,
  SV_POLLUT13_M1,
  SV_POLLUT13_M2,
  SV_POLLUT14_M1,
  SV_POLLUT14_M2,
  SV_POLLUT15_M1,
  SV_POLLUT15_M2,
  SV_POLLUT16_M1,
  SV_POLLUT16_M2,
  SV_POLLUT17_M1,
  SV_POLLUT17_M2,
  SV_POLLUT18_M1,
  SV_POLLUT18_M2,
  SV_POLLUT19_M1,
  SV_POLLUT19_M2,
  SV_POLLUT20_M1,
  SV_POLLUT20_M2,
  SV_POLLUT21_M1,
  SV_POLLUT21_M2,
  SV_POLLUT22_M1,
  SV_POLLUT22_M2,
  SV_VAR1_POLLUT,
  SV_VAR2_POLLUT,
  SV_VAR3_POLLUT,
  SV_VAR4_POLLUT,
  SV_VAR5_POLLUT,
  SV_SOLUTION_VAR(TVAR),
  SV_TVAR_PROD,
  SV_ITMP_POLLUT,
  SV_SOLUTION_VAR(SOOT_MOM_0),
  SV_SOLUTION_VAR(SOOT_MOM_1),
  SV_SOLUTION_VAR(SOOT_MOM_2),
  SV_SOLUTION_VAR(SOOT_MOM_3),
  SV_SOLUTION_VAR(SOOT_MOM_4),
  SV_SOLUTION_VAR(SOOT_MOM_5),
  SV_SOLUTION_VAR(SOOT_MOM_6),
  SV_SOLUTION_VAR(SOOT_MOM_7),
  SV_SOLUTION_VAR(SOOT_MOM_8),
  SV_SOLUTION_VAR(SOOT_MOM_9),
#define SV_SOOT_MOM_MAX SV_SOOT_MOM_9
  SV_SOLUTION_VAR(SOOT_MOM_AGG_0),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_1),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_2),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_3),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_4),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_5),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_6),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_7),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_8),
  SV_SOLUTION_VAR(SOOT_MOM_AGG_9),
#define SV_SOOT_MOM_AGG_MAX SV_SOOT_MOM_AGG_9
  SV_SOLUTION_VAR(SOOT_MOM_AREA),
  SV_SOOT_DIAM,
  SV_SOOT_AREA,
  SV_SOOT_VOL,
  /* DTRM */
  SV_VGS_DTRM,       /* volume glob source */
  SV_VGF_DTRM,       /* volume glob factor */
  SV_F_GLOB_ID,

  /* S2S */
  SV_F_SGLOB_ID,
  SV_S2S_RADSUM,
  SV_N_S2S_ID,
#if PARALLEL
  SV_F_SGLOB_ID_MAP,
#endif
  /* sitespecies model */
  /*SV_SOLUTION_VAR(SOOTSPECIES),*/
  SV_SOOTSPECIES,
  SV_SOOTSPECIES_M1,
  SV_SOOTSPECIES_M2,
  SV_SOOTSPECIES_S,
  SV_SOOTSPECIES_AP,
  SV_SOOTSPECIES_R,
  SV_SOOTSPECIES_FLUX,
  SV_SOOTSPECIES_DENSITY,
  SV_SOOTSPECIES_OCCUPANCY,

  SV_SOOTSPECIES_0,
  SV_SOOTSPECIES_0_M1,
  SV_SOOTSPECIES_0_M2,
  SV_SOOTSPECIES_0_S,
  SV_SOOTSPECIES_0_AP,
  SV_SOOTSPECIES_0_RG,
  SV_SOOTSPECIES_0_RG_AUX,
  SV_SOOTSPECIES_0_G,
  SV_SOOTSPECIES_0_R,
  /* temporary storages for explicit source terms in sootspecies equation */
  SV_SOOTSPECIES_AREA_TMP,
  SV_SOOTSPECIES_SK_TMP,
  SV_SOOTSPECIES_AREA_G,
  SV_SOOTSPECIES_AREA_RG,
  SV_SOOTSPECIES_AREA_RG_AUX,
  SV_SOOTSPECIES_SK_G,
  SV_SOOTSPECIES_SK_RG,
  SV_SOOTSPECIES_SK_RG_AUX,
  /* solar load model */
  SV_SOLAR_SOURCE,
  SV_SOLAR_BIN,
  SV_SOLAR_QTRANS,
  SV_SOLAR_QABS,
  SV_SOLAR_QREFL,

  /* DPM */
  SV_DPMS_MASS,      /* mass source */
  SV_DPMS_MOM_S,     /* momentum sources explicit */
  SV_DPMS_MOM_AP,    /* momentum sources implicit */
  SV_DPMS_WSWIRL_S,  /* swirl equation source explicit */
  SV_DPMS_WSWIRL_AP, /* swirl equation source implicit */
  SV_DPMS_ENERGY,    /* energy source */
  SV_DPMS_ENERGY_AP, /* energy source, implicit */

  SV_DPMS_TKE,       /* TKE source */
  SV_DPMS_D,         /* Epsilon (dissipation) source */
  SV_DPMS_O,         /* Omega source */
  SV_DPMS_TKE_RUU,   /* Reynolds stress RUU source */
  SV_DPMS_TKE_RVV,   /*                 RVV source */
  SV_DPMS_TKE_RWW,   /*                 RWW source */
  SV_DPMS_TKE_RUV,   /*                 RUV source */
  SV_DPMS_TKE_RVW,   /*                 RVW source */
  SV_DPMS_TKE_RUW,   /*                 RUW source */

  SV_N_NORMAL,         /* face normal at the nodes */
  SV_N_CORRECT,        /* boolean flag indicating that node velocity needs correcting */
  SV_FILM_HEIGHT,      /* film height */
  SV_FILM_HEIGHT_M0,   /* film height at the beginning of tracking */
  SV_N_FILM_HEIGHT,    /* film height at nodes */
  SV_FILM_MASS,        /* film mass */
  SV_FILM_MASS_M0,     /* film mass at beginning of tracking */
  SV_FILM_TEMP,        /* film temperature */
  SV_FILM_SURFACE_TEMP,/* film surface temperature */
  SV_FILM_SURFACE_TEMP_M0,/* film surface temperature at beginning of tracking */
  SV_FILM_HFLUX,       /* film wall heat flux */
  SV_FILM_TEMP_M0,     /* film temperature at beginning of tracking */
  SV_FILM_HFLUX_M0,    /* film wall heat flux at beginning of tracking */
  SV_REFLECT_HFLUX,    /* reflect wall heat flux */
  SV_FILM_H_WALL,      /* film heat flux leaving the wall*/
  SV_FILM_VELOCITY,    /* film velocity */
  SV_FILM_VELOCITY_M0, /* film velocity at beginning of tracking */
  SV_FILM_M_IMP_M0,    /* mass impinged this time step */
  SV_FILM_M_IMP_M1,    /* mass impinged at prior time step */
  SV_FILM_MU,          /* average film viscosity on face */
  SV_FILM_SURF_TENSION,/* average film surface tension on face */
  SV_FILM_MU_M0,       /* average film viscosity on face at beginning of tracking*/
  SV_FILM_SURF_TENSION_M0,/* average film surface tension on face at beginning of tracking*/
  SV_FILM_STRIPPED,    /* % mass fraction stripped from the film surface on the face */
  EXPAND_PER_MAT_SV(FILM_MASS_OF), /* droplet material mass fraction in wall film */
  SV_FILM_LEIDENFROST, /* leidenfrost temperature limit */
  SV_DPMS_SPECIES,     /* species sources */
  SV_DPMS_SPECIES_AP,  /* species sources, implicit */
  EXPAND_NSPE_SV(DPMS_SURFACE_SPECIES),   /* surface species concentrations*/
  EXPAND_NSPE_SV(DPMS_REACTION_RATE_POST), /* multiple particle reaction rates*/
  EXPAND_PER_MAT_SV(DPMS_VAP_PER_MAT), /* release rates per material */
  EXPAND_PER_MAT_SV(DPMS_DEVOL_PER_MAT),
  EXPAND_PER_MAT_SV(DPMS_BURN_PER_MAT),
  SV_DPMS_PDF_1,     /* pdf stream 1 source */
  SV_DPMS_PDF_2,     /* pdf stream 2 source */
  SV_DPMS_INERT,
  SV_DPMS_PDF_1_AP,     /* pdf stream 1 source, implicit */
  SV_DPMS_PDF_2_AP,     /* pdf stream 2 source, implicit */
  SV_DPMS_INERT_AP,     /* inert source, implicit */
  SV_DPMS_EMISS,     /* particle emission source */
  SV_DPMS_ABS,       /* particle absorption */
  SV_DPMS_SCAT,      /* particle scattering */
  SV_DPMS_BURNOUT,            /* burnout rate for combusting particles */
  SV_DPMS_CONCENTRATION,      /* particles concentration */
  SV_DPMS_EROSION,      /* particles erosion (at walls) */
  SV_DPMS_EROSION_MDM,   /* particles erosion data used as input to MDM (at walls) */
  SV_DPMS_ACCRETION,     /* particles accretion (at walls) */
  SV_DPMS_EROSION_SHIELDING,     /* shielding function to account for presence of granular phases near wall */
  SV_T_AUX,              /* auxilliary temperature used in limiter */
  SV_T_AP_AUX,           /* auxilliary ap coefficient used in limiter */

  SV_DPM_PARTICLE_BIN,    /* store pointers to particles for cell binning */
  SV_DPM_PARTICLE_NUMBER, /* total number of particles in bin */
  SV_DPM_PARTICLE_VOLUME, /* total volume of particles in bin */
  SV_DPM_PARCEL_NUMBER,   /* number of parcels in bin */
  SV_DPM_MAX_RELVEL,      /* maximum relative velocity */
  SV_DPM_MAX_CROSS,       /* maximum collision cross section */
  SV_DPM_MAX_PARTICLE_N,  /* maximum np of particles in the cell */
  SV_DPM_N_COLLISIONS,    /* number of collisions in bin over the dpm step */
  SV_DPM_VIS_0,           /* visualization storage for dpm (particle filtering) */
  SV_DPM_VIS_1,           /* visualization storage for dpm (twisted ribbons) */

  SV_DPMS_WALL_FORCE,     /* force acting on wall caused by DPM particles */

  /* for update at every flow iteration _DS_ arrays are needed */
  SV_DPMS_DS_MASS,      /* mass source */
  SV_DPMS_DS_MOM_S,     /* momentum sources explicit */
  SV_DPMS_DS_MOM_AP,    /* momentum sources implicit */
  SV_DPMS_DS_WSWIRL_S,  /* swirl equation source explicit */
  SV_DPMS_DS_WSWIRL_AP, /* swirl equation source implicit */
  SV_DPMS_DS_ENERGY,    /* energy source */
  SV_DPMS_DS_ENERGY_AP, /* energy source, implicit */

  SV_DPMS_DS_TKE,       /* TKE source */
  SV_DPMS_DS_D,         /* Epsilon (dissipation) source */
  SV_DPMS_DS_O,         /* Omega source */
  SV_DPMS_DS_TKE_RUU,   /* Reynolds stress RUU source */
  SV_DPMS_DS_TKE_RVV,   /*                 RVV source */
  SV_DPMS_DS_TKE_RWW,   /*                 RWW source */
  SV_DPMS_DS_TKE_RUV,   /*                 RUV source */
  SV_DPMS_DS_TKE_RVW,   /*                 RVW source */
  SV_DPMS_DS_TKE_RUW,   /*                 RUW source */
  SV_DPMS_DS_SPECIES,    /* species sources */
  SV_DPMS_DS_SPECIES_AP, /* species sources, implicit */
  EXPAND_NSPE_SV(DPMS_DS_SURFACE_SPECIES),  /* surface species concentrations*/
  EXPAND_PER_MAT_SV(DPMS_DS_VAP_PER_MAT), /* release rates per material */
  EXPAND_PER_MAT_SV(DPMS_DS_DEVOL_PER_MAT),
  EXPAND_PER_MAT_SV(DPMS_DS_BURN_PER_MAT),
  SV_DPMS_DS_PDF_1,     /* pdf stream 1 source */
  SV_DPMS_DS_PDF_2,     /* pdf stream 2 source */
  SV_DPMS_DS_INERT,
  SV_DPMS_DS_PDF_1_AP,  /* pdf stream 1 source, implicit */
  SV_DPMS_DS_PDF_2_AP,  /* pdf stream 2 source, implicit */
  SV_DPMS_DS_INERT_AP,  /* inert model source, implicit */
  SV_DPMS_DS_EMISS,     /* particle emission source */
  SV_DPMS_DS_ABS,       /* particle absorption */
  SV_DPMS_DS_SCAT,      /* particle scattering */
  SV_DPMS_DS_BURNOUT,   /* burnout rate for combusting particles */

  SV_DPM_BNDRY_DIST,  /* dpm distributions framework storage: boundary faces  *//* DE29924 */
  SV_DPM_DIST,        /* dpm distributions framework storage: cells and nodes */
  SV_DPM_DIST_TIME_STAT,
  SV_DPM_SOLVE_EULERIAN,  /* marks cells where Eulerian solution is to be used */
  SV_DPM_CELLSTEPS,       /* number of particle steps in cell */
  SV_DPM_FACESTEPS,       /* number of particle face intersections */
  SV_DPM_PARTITION,       /* the dpm domain partition for cells */
  SV_DPM_VP_V,            /* velocity correction for DDPM phases like SV_VP_V */
  SV_DPM_TURB_KE,         /* turbulent kinetic energy for DPM */
  SV_DPM_TURB_ED,         /* turbulent dissipation rate for DPM */
  SV_DPM_STRAIN_RATE_MAG, /* magnitude of strain rate for Saffman lift force */
  SV_DPM_NODE,            /* variable storage for nodal interpolation */
  SV_DPM_NODE_M1,         /* nodal variables from previous time step */
  SV_DPM_NODE_PATH,       /* nodal variables for path lines */

  SV_DPM_Y_I,           /* species mass fractions for DPM calculated from pdf and premixed models */
  SV_DPM_P_LIQ,         /* pressure of DPM particles in a cell when applying a Cole equation of state */
  SV_DPM_P_LIQ_G,       /* its gradient will be applied to particles as additional force */
  SV_DPM_P_LIQ_RG,      /* reconstruction gradient */
  SV_DPM_VOF,           /* DPM density computed as mass of all particles in a cell divided by cell volume, needed for interpolation */
  SV_DPM_VOF_G,         /* its gradient */
  SV_DPM_VOF_RG,        /* reconstruction gradient */

  /* for moving mesh */
  SV_DVOLUME_DT,
  SV_DVOLUME_M2_DT,
  SV_GRID_FLUX,         /* grid face flux */
  SV_GRID_FLUX_M2,        /* grid face flux - second order in time  */
  SV_BND_GRID_V,        /* boundary velocity due to grid motion */
  SV_CELL_GRID_V,       /* cell velocity due to grid motion */
  SV_VOLUME_M1,         /* temporary storage for m1 volume */
  SV_VOLUME_M2,         /* volume at n-2 level (for second order solver) */
  SV_AREA_MAG_M1,       /* area magnitude at m1 level (for layering only) */

  /* SCR urea deposition risk analysis postprocessing variable array: */
  /* SV_SCR_UREA_DEPO_RISK_POST, */
  SV_SCR_UREA_DEPO_RISK_MEAN,

  /* lump detection, e.g. in VOF solution */
  SV_LUMP_ID,
  SV_LUMP_POSTPROC,
  /* SV_LUMP_DIA,
   * SV_LUMP_RHO,
   * SV_LUMP_ASPHITY_BY_AV_RADIUS,
   * SV_LUMP_ASPHITY_BY_SURF_AREA,
   * SV_LUMP_ASPHITY_BY_SIGMA_RAD,
   * SV_LUMP_ASPHITY_BY_ORTHOGITY,
   */
  /* DPM-to-VOF conversion: */
  SV_DPM_TO_VOF_P_ICLE_ID,
  SV_DPM_TO_VOF_PRELIMARK,
  SV_DPM_TO_VOF_ORIG_VOF,
  SV_DPM_TO_VOF_CELL_PICLE_LIST,

  SV_SP_PACK_FLAG,   /* static pile-up feature, flag telling whether cell can become "packed" */
  SV_VOF_NODE_MAX,   /* dummy never allocated, used e.g. in DDPM "static pile-up" feature.. */
  /* volume fraction of fluid */
  SV_VOF,
  SV_VOF_NORM,
  SV_VOF_M1,
  SV_VOF_M2,
  SV_MP_EXP_VOF_M1,
  SV_MP_EXP_RHO_M1,
  SV_VOF_PH,
  SV_VOF_NH,
  SV_VOF_AP,
  SV_VOF_S,
  SV_VOF_RG,
  SV_VOF_RG_AUX,
  SV_VOF_G,
  SV_VOF_R,
  SV_VOF_MEAN,
  SV_VOF_RMS,
  SV_VOF_INST,
  SV_SMOOTHED_VOF,
  SV_SMOOTHED_VOF_TMP,
  SV_VOF_SOURCES,
  SV_VOF_MASS_SOURCES,
  SV_VOF_DIFF_SOURCE,
  SV_WEIGHT,                  /* tmp sv for weight in face sum*/
  SV_C_FLOTSAM_I,             /* storage for flotsam indicator (temporary) */
  SV_C_VOF_RG_MAG,        /* storage for max vof recon grad (temporary) */
  SV_HR_BETA_FACTOR,        /* storage for compressive scheme beta factor */
  SV_HR_BETA_MAX,       /* storage for compressive scheme beta max */
  SV_VOF_SO_CORR,             /* storage for second order term for coupled vof */
  SV_AP_FALSE,               /* storage for false time step linearization for coupled vof */
  SV_BF_SURF_TENS,            /* storage for body force due to surface tension (multi-fluid VOF)*/
  SV_BF_MARANGONI,            /* storage for marangoni forces due to surface tension (multi-fluid VOF)*/
  SV_VOF_CURVATURE,              /* storage for phase specific curvature in surface tension */
  SV_VOF_SMOOTHED_GRAD,      /* storage for phase specific smoothed gradients for surface tension */
  SV_SM_VOF_CSS,              /* storage for phase specific smoothed vof for css method */
  SV_MU_INTERFACE,            /* storage for artifical viscosity for vof */
  SV_MP_PHI_SMOOTHED,         /* storage for temporary variable having self storage */
  SV_FLUX_SUM,               /*  temporary storage for storing flux sum */
  SV_DFLUX_SUM,              /*  temporary storage for storing diffusive flux sum */
  SV_CONVECTIVE_CFL,         /*  temporary storage for storing convective cfl */
  SV_MP_DT_LOCAL,           /*   storage for local time scales  */
  SV_MP_C_TMP_V_0,           /* storage for temporary vector having self storage */
  SV_MP_C_TMP_0,              /* storage for temporary variable having self storage */
  SV_N_MP_PHI,               /* node thread temporary storage for VOF */
  SV_N_MP_WT,                /* node thread temporary storage for VOF */

  /* GENTOP ST */
  SV_VOF_GX,
  SV_VOF_GY,
  SV_VOF_GZ,
  SV_VOF_GX_RG,
  SV_VOF_GX_RG_AUX,
  SV_VOF_GY_RG,
  SV_VOF_GY_RG_AUX,
  SV_VOF_GZ_RG,
  SV_VOF_GZ_RG_AUX,
  SV_VOF_GX_G,
  SV_VOF_GY_G,
  SV_VOF_GZ_G,

  /* SV_C_TMP_0 temporary storage, used extensively now for setting c_tmp value
     based on area average of face value. */
  SV_C_TMP_0,
  SV_C_TMP_1,                 /* temporary storage for sum of fluxes */
  SV_C_TMP_2,
  SV_C_TMP_3,                 /* temporary storage used for residual scaling */
  SV_C_TMP_V_0,               /* cell tmp vector storage for smoothed vof grad*/
  SV_F_TMP_0,                 /* temporary real on faces */
  SV_F_TMP_1,                 /* temporary real on faces */
  SV_FI_TMP_0,                /* temporary integer on faces */
  SV_POST_VAR,                /*post-processing real variable for faces and cells*/
  SV_WALL_SURF_TENSION,       /* to store surface tension force at walls */
  SV_WALL_FACE_FORCE,              /* to store force at faces */
  SV_ARTIFICIAL_WALL_FLAG,     /* face flag to control the build of artificial walls on inlet/outlet */
  SV_GCM_VEL_SCALE,
  SV_GCM_TMP_0,
  SV_GCM_TMP_1,
  SV_SFC,
  SV_SFC_RG,
  SV_SFC_RG_AUX,
  SV_SFC_G,
  SV_BETA_COEFF,
  SV_F_S,                     /* parallel uses to store fluxes/sources for
                                 second-order algorithms */
  SV_F_CONV_S,
  SV_F_DIFF_S,

  SV_CX_C_MARK,               /* tmp used in cortex code */
  SV_CX_ID,                   /* tmp id used in cortex code */
#if PARALLEL
  SV_F_S_V,                   /* parallel uses to store fluxes/sources for
                                 second-order vector algorithms */
#endif
  SV_F_S_RST,                 /* parallel uses to store fluxes/sources for
                                 second-order Reynolds Stress algorithms */
  SV_F_CONV_S_RST,
  SV_F_DIFF_S_RST,

  SV_SLIP_U,                  /* drift flux model */
  SV_SLIP_V,
#if RP_3D
  SV_SLIP_W,
#endif
  SV_RELAX_TIME,              /*particle relaxation time*/
  SV_MT_VOF_AP,               /* mass transfer VOF linearization term */
  SV_MP_MT_VOF_S,             /* inter-phase mass transfer in vof eqn */
  SV_MP_P_S,                  /* phase interaction source in pressure eqn */
  SV_MT_DS_DP,                 /* gradient of mass trans source in pp-eqn */
  SV_VOF_S_M1,                /* soure for cn_time_scheme */
  SV_SLIP_FLUX,
  SV_PHASE_MASS,              /* cavitation mass source*/
  SV_THIN_FILM,               /* thin liquid film mass source */
  SV_VAPOR_PRESS,              /* vapor pressure specific to caviation  */
  SV_MT_VAPOR_PRESS,           /* vapor pressure for all mass transfer mechanisms  */
  SV_SAT_TEMPERATURE,         /* boiling model */
  SV_MT_SAT_TEMPERATURE,      /* evaporation-condensation */
  SV_SAT_TEMP_DEW,            /* evap-cond: dew point saturation temperature */
  SV_LATENT_HEAT,
  SV_MT_QSP_TOTAL_FLUX,       /* sbm: total single phase heat flux */
  SV_MT_QNUC_TOTAL_FLUX,      /* sbm: total nucleate boiling heat flux */
  SV_MT_QSP_FLUX,             /* sbm: mech specific single phase heat flux */
  SV_MT_QNUC_FLUX,            /* sbm: mech specific nucleate heat flux */
  SV_MT_QSP_FAC1,             /* sbm: mech specific single phase htc factor-1 */
  SV_MT_QSP_FAC2,             /* sbm: mech specific single phase htc factor-2 */
  SV_MT_QNUC_FAC,            /* sbm: mech specific nucleate htc factor */
  SV_MT_WALL_LIQ_FRAC,       /* sbm: mech specific wall liquid fraction */
  SV_MT_LREF,                /* sbm: mech specific ref length */
  SV_MT_UREF,                /* sbm: mech specific ref velocity */
  SV_MT_TREF,                /* sbm: mech specific ref temperature */
  SV_MT_SUPHT_MIN,           /* sbm: mech specific min superheat */
  SV_BL_DS_DP,

  SV_VFLUX,
  SV_VFLUX_M1,
  SV_VFLUX_M2,
  SV_VFLUX_PREV,
#if 0 /*MP_TEST*/
  SV_FLUX_PREV,
#endif
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF),
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_XX),
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_YY),
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_ZZ),
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_XY),
#if RP_3D
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_XZ),
  EXPAND_0_TO_189(EXPAND_SV_helper, DRAG_COEFF_ANISO_YZ),
#endif
  SV_VOF_PREV,
  SV_VOF_DIFF_COEFF,
  SV_VOF_DIFF_FLUX,
  SV_MASS_TRANSFER,
  SV_WALL_MASS_TRANSFER,
  SV_PBM_RPI_MT,
  SV_SPECIES_FROM,
  SV_SPECIES_TO,
  SV_SPECIES_MT_S,
  SV_HET_RXN_RATE,
  SV_HET_RXN_HEAT,
  SV_F_TCOEFF,               /* face transport coefficient */
  SV_F_TCOEFF_RS,            /* extra face transport coefficient for RSM */
  SV_F_BVIS,                 /* face transport for bulk viscosity */
  SV_VP_V,                   /*piso: SV_VP_V, SV_SAVP_V, SV_PP_STORE */
  SV_SAVP_V,
  SV_PP_STORE,
  SV_VEC01_COEFF,            /* face coefficients for mom equations for */
  SV_VEC10_COEFF,            /* rotational  periodics */

  SV_MP_AREA_DENSITY,

  /* GENTOP variables */
  SV_MP_GENTOP_PHI_SURF,
  SV_MP_GENTOP_PHI_MORPH,
  SV_MP_GENTOP_PHI_BGND,
  SV_MP_GENTOP_PHI_COAL,

  SV_RECON_MIN,
  SV_RECON_MAX,
  SV_RECON_PHI,

  /* properties */
  SV_DENSITY,
  SV_DENSITY_M1,
  SV_DENSITY_M2,
  SV_DENSITY_PH,
  SV_DENSITY_NH,
  SV_DENSITY_RG,
  SV_DENSITY_RG_AUX,
  SV_DENSITY_G,
  SV_MU_LAM,
  SV_MU_FLUID,
  SV_PHASE_DIAMETER,
  SV_PHASE_DIAMETER_MEAN,
  SV_PHASE_DIAMETER_RMS,
  SV_MU_T,
  SV_MU_TL,
  SV_MU_TS,
  SV_MU_T_LES_ZONE,
  SV_MU_T_SBES_RANS,

  SV_BETA_PH,  /* time limiters */
  SV_BETA_NH,
  SV_BETA_FACE_PH,  /* time limiters */
  SV_BETA_FACE_NH,

  SV_POROSITY,
  SV_POROSITY_M1,
  SV_POROSITY_M2,

  SV_CP,
  SV_RGAS,
  SV_SOUND_SPEED,
  SV_DT,
  /*  SV_DT_SOURCE,   */
  SV_DT_BC_SOURCE,
  SV_NLBF_AVG_TEMP,
  SV_EVAP_FLUX,
  SV_THIN_FILM_FLUX,
  SV_WALL_ABLATION_RATE,
  SV_QUENCH_FLUX,
  SV_LIQUID_PHASE_FLUX,
  SV_VAPOR_PHASE_FLUX,
  SV_DT_SCALE,
  SV_UREF2,
  SV_DISCONT,
  SV_KTC,
  SV_KTC_ANISO_UDF,
  SV_KTC_por,
  SV_KTC_ORTHO,
  SV_KTC_ORTHO_por,
  SV_KTC_TRANSVERSE,
  SV_REF_INDEX,
  SV_ABS_COEFF,
  SV_BAND_ABS_COEFF,
  SV_SCAT_COEFF,
  SV_LAM_FLAME_SPEED,
  SV_LAM_FLAME_THICK,
  SV_CRITICAL_STRAIN_RATE,
  SV_PREMIX_ADIABATIC_TEMP,
  SV_PREMIX_FUEL_MF,
  SV_TSOLID,
  SV_TLIQ,
  /* EM properties */
  SV_ELEC_COND,
  SV_LITHIUM_DIFF,
  SV_DUAL_ELEC_COND,

  SV_WALL_DIST,
  SV_WALL_DIST_G,
  SV_WALL_DIST_RG,
  SV_WALL_DIST_RG_AUX,
  SV_WALL_DIST_SKIP,
  SV_WALL_NORMAL,

  SV_ROUGH_SIZE,

  SV_VOLUME,
#if RP_2D
  SV_VOLUME_2D,
#endif
  SV_CENTROID,
  SV_CENTROID_M1,
  SV_CENTROID_SLIDE,
  SV_CENTROID_COMP,
  SV_CENTROID_X_G,
  SV_CENTROID_X_RG,
  SV_CENTROID_X_RG_AUX,
  SV_CENTROID_Y_G,
  SV_CENTROID_Y_RG,
  SV_CENTROID_Y_RG_AUX,
#if RP_3D
  SV_CENTROID_Z_G,
  SV_CENTROID_Z_RG,
  SV_CENTROID_Z_RG_AUX,
#endif
  /* this is not enthalpy
   * instead, the correction matrix is called H
   */
  SV_H_RG_NORM,
  SV_H_G_NORM,
  SV_GRAD_QUALITY,
  SV_CELL_QUALITY_CHANGE,
  SV_SOLUTION_AND_CELL_QUALITY,
  SV_SKEW,
  SV_CELL_SURF_AREA,

  SV_CELL,
  SV_FACE,

  SV_C_FACE_NEIGHBOR,
  SV_C_FACE_THREAD_NEIGHBOR,

  /* "compressed row" edge storage */
  SV_CR_EDGE,

  SV_AREA, /* area vector */
# if RP_AXI
  SV_AREA_2D,      /* 2d area vector */
# endif

  SV_ZERO_VOLUME_M1,

  SV_SURFACE_DEFORMATION,
  SV_SURFACE_INIT_AREA,

  /* extra face metrics for INTERIOR_FACE_GEOMETRY */
  SV_FACE_DR0,
  SV_FACE_DR1,
  SV_FACE_DS,
  SV_FACE_ES,
  SV_FACE_ABYES,

  SV_C0,
  SV_C1,
  SV_GHOSTLINK,                 /* link to store original cell  */
  SV_GHOST_MARK,                /* marker for ghost cells       */
  SV_C0_INDEX,
  SV_C1_INDEX,
  SV_STATUS,
  SV_F_INTERIOR, /* marker for faces referenced by interior cells */
  SV_TREE_LEVEL,
  SV_STATE,
  SV_SHADOW,
  SV_SHADOW_INDEX,
  /* For Gambit Export */
  SV_GEOM_NODE_ID,

#define SV_PROFILES()EXPAND_NPROFILE_SV(PROFILE)
  SV_PROFILES(),

  SV_F_A0,
  SV_F_A1,
  SV_F_GHOSTLINK,
  SV_C_INDEX,
  SV_C_COARSE_INDEX,

  SV_COARSE_CELL,       /* FAS multigrid: coarse cell */
  SV_COARSE_FACE,
  SV_FINE_FACE,         /* FAS multigrid: fine face */
  SV_PARTNER_FACE,      /* FAS multigrid: fine face */

  SV_PARTITION,
  SV_LAPLACE_GROUP,
  SV_LAPLACE_GROUP_ID,
  SV_LAPLACE_GROUP_ID_TEMP,
  SV_PARTITION_DEST,
  SV_PARTITION_OWNER, /* cell owner used during repartition */
  SV_PARTITION_CACHE,
  SV_NUMKIDS,
  SV_C_WEIGHT,          /* cell or face weight  during parallel partitioning */
#if RP_METIS
  SV_METIS,
#endif
  SV_C_PART_BIT,
  SV_INTERFACE_INFO,  /* partition tmp */
  SV_CLUSTER,
  SV_NEXT_IN_CLUSTER, /* cluster tmp */
  SV_DEGREE,
  SV_ECCENTRICITY,
  SV_DIST,
  SV_LEVEL,
  SV_ID,
  SV_LAYER,
  SV_F_LAYER,

  /* real tmp's */
  SV_RTMP_0,

  SV_RTMP_1,
  SV_RTMP_2,
  SV_RTMP_3,
  SV_RTMP_4,
  SV_RTMP_5,
  SV_RTMP_6,
  SV_RTMP_7,
  SV_RTMP_8,
  SV_RTMP_9,

  /* used by high-speed-numerics */
  SV_HSN_TMP0,
  SV_HSN_TMP1,
  SV_HSN_TMP2,

  /*Two temperature thermal non-equilibrium model*/
  SV_SOLUTION_VAR(TWOTT),
  SV_SOLUTION_VAR(TWOTE),
  SV_TWOTK,
  SV_TWOT_HEAT_FLUX,
  SV_TWOTTAU,
  SV_FROZEN_SOUND_SPEED,
  SV_TWOT_SCV,

  /* used by Broadband noise optimization */
  SV_SNGR_SELF,
  SV_SNGR_SHEAR,
  SV_SNGR_TOTAL,
  SV_SNGR_SELF_Y,
  SV_SNGR_SHEAR_Y,
  SV_SNGR_TOTAL_Y,
#if RP_3D
  SV_SNGR_SELF_Z,
  SV_SNGR_SHEAR_Z,
  SV_SNGR_TOTAL_Z,
#endif

  SV_VIS_1,
  SV_VIS_2,
  SV_VIS_3,

  /* used by Broadband noise optimization */
  SV_VIS_4,
  SV_VIS_5,
  SV_VIS_6,
#if RP_3D
  SV_VIS_7,
  SV_VIS_8,
  SV_VIS_9,
#endif

  SV_SF_NORMAL,

  /* integer tmp's */
  SV_ITMP_0,
  SV_ITMP_1,
  SV_ITMP_11,
  SV_ITMP_2,
  SV_ID_TMP,
  SV_ID_SC,  /*system coupling face/cell ids*/
  SV_F_MARK,
  SV_ISO_MARK,

  /* pointer tmp */
  SV_PTMP_0,

  /* face/cell flag */
  SV_FLAGS,

  /* flag to mark boundary cells for multidimensional limiter and NB reconstruction*/
  SV_FLAGS_CELL_MARK,

  /* bit tmp's */
  SV_ACTIVE,

  SV_MARKING_REGISTER,

#if RP_HOLS
  SV_HOLS_MARK,
  SV_HOLS_BOUND,
#endif

  SV_C0_COLLECT,
  SV_C1_COLLECT,

  /* for FAS aggomeration */
  SV_C_LIST,
  SV_F_LIST,        /* temporary */
  SV_FACE_LIST,
  SV_NUCLEUS_NODE,
  SV_DUAL_NODE,

  SV_F_VIRTUAL,
  SV_F_NDUALS,
  SV_F_DUAL,

  SV_COMPACTED_OFFSET,

  /* marking */
  SV_C_NRMDIST,
  SV_C_EQLENSQ,
  SV_C_SPONGE_DIST,
  SV_SPONGE_OBJ,
  SV_F_VISITED,
  SV_C_VISITED,
  SV_UD_CELL_MARK,   /* user defined cell mark, from "mesh_user_defined_cell" list */

  /* contact numerics */
  SV_CONTACT_FILL_LEVEL,   /* reports contact flood-filling levels */
  SV_CONTACT_FILL_NDONORS, /* indicate number of donors used for contact interpolation */
  SV_CONTACT_EXT_MARK,      /* to do reverse exchange between paritions during flood filling process */

  /* narrow-gap model */
  SV_NARROW_GAP_BND_FACE,
  SV_NARROW_GAP_TYPE,
  SV_NARROW_GAP_TYPE_M1,
  SV_NARROW_GAP_TYPE_POST,
  SV_NARROW_GAP_ID,
  SV_NARROW_GAP_ID_M1,
  SV_NARROW_GAP_ID_POST,
  SV_NARROW_GAP_INTENSITY,
  SV_NARROW_GAP_ITMP0,
  SV_NARROW_GAP_ITMP1,
  SV_NARROW_GAP_ITMP2,
  SV_NARROW_GAP_ITMP3,
  SV_NARROW_GAP_RTMP0,
  SV_NARROW_GAP_RTMP1,
  SV_NARROW_GAP_FTMP0,
  SV_NARROW_GAP_FTMP1,
  SV_NARROW_GAP_BLOCKING_LEVEL,
  SV_NARROW_GAP_MODELING_LEVEL,
  SV_NARROW_GAP_INTP_MARK,
  SV_NARROW_GAP_EXT_MARK,
  SV_NARROW_GAP_LAYER1_LEVEL,
  SV_NARROW_GAP_LAYER2_LEVEL,
  SV_NARROW_GAP_INTP_LAYER,
  SV_NARROW_GAP_INTP_NDONORS,
  SV_NARROW_GAP_DETACHED_LAYER,
  SV_NARROW_GAP_DETACHED_NDONORS,
  SV_NARROW_GAP_STAB_FACTOR,
  SV_NARROW_GAP_SPONGE_COEF,
  SV_NARROW_GAP_SPONGE_VISCOSITY,
  SV_NARROW_GAP_WEIGHT_FACTOR,
  SV_NARROW_GAP_ORIG_VISCOSITY,
  /* sliding interface */
  SV_SPF0,
  SV_SPF1,
  SV_SPF0_THREAD,
  SV_SPF1_THREAD,
  SV_CHILDS,
  SV_CHILD_THREADS,
  SV_NCHILDS,
#if 1
  SV_AREA_FRACTION,        /* to_do: replaced with SV_AREA_FRACTION_SIDE0                  */
#endif
#if 0
  SV_AREA_FRACTION_SIDE0,  /* for coupled wall interfaces, need SIDE0 only                 */
#endif
  SV_AREA_FRACTION_SIDE1,  /* for interior type mesh interfaces, need both SIDE0 and SIDE1 */
  SV_N_NODE_COORDS,        /* node coordinates on the intersected threads for post-processing only */
  SV_NODE_COORDS,
  /* mapped interface */
  SV_N_MAPPED_FACES,
  SV_MAPPED_FACES,
  SV_MAPPED_FACE_THREADS,
  SV_MAPPED_FACE_AREAS,
  SV_TOT_MAPPED_AREA,
  SV_MAPPED_CELL_MARK,
  SV_TOT_HEATFLUX_COEFFS,
  SV_RADFLUX_COEFFS,

#if RP_SHELL
  /* shell junction faces */
  SV_JUNCTION_FACE_LIST,
  SV_SHADOW_JUNCTION_FACE_LIST,
  SV_SHELL_CELL_T,
  SV_SHELL_CELL_ENERGY_M1,
  SV_SHELL_CELL_ENERGY_M2,
  SV_SHELL_FACE_T,
  SV_SHADOW_JUNCTION,
#endif

  /* hanging node adaption */
  SV_CHILD,
  SV_CHILD_INDEX,
  SV_CHILD_THREAD,
  SV_HAS_PARENT_CELL,
  SV_EDGE,
  SV_INTERIOR_THREAD,
  SV_F_PARENT,
  SV_C_PARENT,

  SV_F_NEIGHBOR,

  /* node thread vars */

  SV_N_SHADOW,                  /* Node * */

  /* SV_N_TMP0, SV_N_TMP1 should replace n1, n2 in node struct */
  SV_N_TMP_0,     /* TempUnion */
  SV_N_TMP_1,     /* TempUnion */
  SV_N_TMP_2,     /* TempUnion */
  SV_N_TMP_3,
  SV_N_RTMP_0,
  SV_N_RTMP_1,
  SV_N_RTMP_2,
  SV_N_POST_MARK,

  /* For System coupling(Two-way FSI) only  */
  SV_F_SC_MEAN_HTC,
  SV_F_SC_MEAN_QDOT,
  SV_F_SC_MEAN_TREF,
  SV_F_SC_MEAN_QRAD,
  SV_N_SC_ID,     /* int; for system coupling node ids*/
  SV_F_SC_THERM,  /* real; for system coupling thermal data at face_center*/
  SV_F_SC_NWT,
  SV_F_SC_TRAD,

  /* dynamic mesh */
  SV_N_XINIT,                   /* real[ND] */
  SV_N_X_M1,                    /* real[ND] Nodal coordinates at the
           beginning of the time step*/
  SV_N_XN,      /* real[ND] Nodal coordinates at the
           beginning of dynamic mesh*/
  SV_N_X_REF,                   /* reference node position
           for diffusion smoothing */
  SV_N_XNI,     /* real[ND] */
  SV_N_DX,      /* real[ND] */
  SV_N_DX1,     /* real[ND] */
  SV_N_NEST,                    /* real[ND] */
  SV_N_ITMP,      /* int */
  SV_N_NEXT,      /* Node* */
  SV_N_PREV,      /* Node* */
  SV_N_PERDISP,   /* Node periodic displacement* */
  SV_N_PERIMAG,   /* Node periodic imaginary displacement* */
  SV_N_PNUMBER,   /* Node passage number */
  SV_DM_ID,                     /* int */
  SV_EXT_ID,                    /* don't use in Fluent! */
  /* for code coupling (e.g. MPCCI) only */

#if RP_POLYHEDRA
  /* polyhedra refinement */
  SV_REFINE_LEVEL,
  SV_PARENT_INDEX,
#endif
  SV_ADAPT_OBJECT,

#if LSQ_RECON
  SV_N_G,     /* real[ND] */
  SV_N_I,     /* real[ND] */
  SV_N_Ixy,     /* real */
  SV_N_Lambda,                  /* real[ND] */
#if RP_3D
  SV_N_Iyz,     /* real */
  SV_N_Izx,     /* real */
#endif
  SV_NODE_WT,
  SV_CR_NODE_WT,                /* compressed row */
  SV_N_VEL,     /* real[ND] */
  SV_N_PHI,     /* real */
  SV_NODE_WT_GX,                /* real */
  SV_NODE_WT_GY,                /* real */
#if RP_3D
  SV_NODE_WT_GZ,                /* real */
#endif
  SV_CR_NODE_WT_GX,             /* compressed row */
  SV_CR_NODE_WT_GY,             /* compressed row */
#if RP_3D
  SV_CR_NODE_WT_GZ,             /* compressed row */
#endif
  SV_N_PHI_G,                   /* real[ND]*/
  SV_N_VEL_U_G,     /* real[ND] */
  SV_N_VEL_V_G,     /* real[ND] */
#if RP_3D
  SV_N_VEL_W_G,     /* real[ND] */
#endif
  SV_N_SUM,
  SV_N_RST_XX,                  /* real rsm stress xx */
  SV_N_RST_XY,                  /* real rsm stress xx */
  SV_N_RST_XZ,                  /* real rsm stress xx */
  SV_N_RST_YY,                  /* real rsm stress xx */
  SV_N_RST_YZ,                  /* real rsm stress xx */
  SV_N_RST_ZZ,                  /* real rsm stress xx */
#endif

  SV_N_MIN,                     /* for new limiter implementation */
  SV_N_MAX,

  SV_LSQ_M00,                   /* cb-lsq reconstruction */
  SV_LSQ_M01,
  SV_LSQ_M11,
#if RP_3D
  SV_LSQ_M02,
  SV_LSQ_M12,
  SV_LSQ_M22,
#endif

  SV_ARATIO,                    /*use in alternate time-step impl in dbns cpld*/
  SV_CMIN_DIST,

#if 0
  SV_LSQ_CHK,
#endif

  SV_LSQ_WT0,
  SV_LSQ_WT1,
  SV_LSF_GGWT0,
  SV_LSF_GGWT1,
  SV_LSF_WT0,
  SV_LSF_WT1,

  SV_PHI_H_X,                   /* scalars for hessian reconstruction */
  SV_PHI_H_Y,
  SV_PHI_H_Z,
  SV_PHI_H_RG,                  /* vectors for two step hessian reconstruction */
  SV_PHI_H_RG_AUX,
  SV_PHI_HX_RG,
  SV_PHI_HX_RG_AUX,
  SV_PHI_HY_RG,
  SV_PHI_HY_RG_AUX,
  SV_PHI_HZ_RG,
  SV_PHI_HZ_RG_AUX,
  SV_PHI_H_G,
  SV_PHI_HX_G,
  SV_PHI_HY_G,
  SV_PHI_HZ_G,

  SV_HESS_IND,                  /* Hessian based error indicator */
  SV_HESS_ANISO,                /* Hessian anisotropic ratio */
  SV_HESS_VEC,                  /* Hessian dominant direction */

#if RP_GEOM
  SV_N_OBJP,                    /* Objp ** for list of threads the node belongs to*/
#endif

  SV_C_BRIDGE_NODES,            /* cell bridge node struct */
  SV_C_BRIDGE_NNODES,           /* number of bridge nodes */

  SV_N_MSN,                       /* multiple shadow nodes */

  SV_BCD_NORM_VAR,
  SV_BCD_BOUND,

  SV_DPDT_RMS,                  /* acoustics source */

  SV_FWH_P,                     /* Input data for FW-H acoustics solver, */
  SV_FWH_P_M1,                  /* added to avoid conflicts with the standard */
  SV_FWH_P_M2,                  /* pressure, velocity and density on faces */
  SV_FWH_U,
  SV_FWH_U_M1,
  SV_FWH_U_M2,
  SV_FWH_V,
  SV_FWH_V_M1,
  SV_FWH_V_M2,
#if RP_3D
  SV_FWH_W,
  SV_FWH_W_M1,
  SV_FWH_W_M2,
#endif
  SV_FWH_R,
  SV_FWH_R_M1,
  SV_FWH_R_M2,

#if RP_3D
  SV_R_TETA_Z,                  /* export of Fluent geometry data for SYSNOISE */
#endif

  SV_CREV_MASS,                 /* mass source from the crevice model */
  SV_CREV_MOM,                  /* momentum source "               "  */
  SV_CREV_ENRG,                 /* energy source   "               "  */
  EXPAND_NSPE_SV(CREV_SPECIES), /* species sources "               "  */

  SV_HSRC_SPARK,                /* spark energy source */
  SV_DIFF_SPARK,                /* spark diffusion coefficient */

  SV_SOLUTION_VAR(IGNITE),      /* tracer species for single equation autoignition */
  SV_IGNITE_RATE,

#if RP_3D
  SV_IMACRO,
  SV_MM_SOURCE,
#endif
  SV_DC_SOURCE, /*Dual Cell Heat Exchanger source*/
  SV_DC_NBR_ID,/*Dual Cell Hxc connectivity info*/
  SV_DC_NBR_DATA,/*Dual Cell Hxc nbr svar value*/

  SV_DC_NBR,/*Dual Cell id (local)*/
  SV_DC_FLUID_POR,/*Dual Cell Zone porosity profile*/
#if PARALLEL
  SV_DC_NBR_NODE,/*Dual Cell compute node*/
#endif
  SV_WD_PHI,
  SV_WD_PHI_AP,
  SV_WD_PHI_S,
  SV_WD_PHI_RG,
  SV_WD_PHI_RG_AUX,
  SV_WD_PHI_G,
  SV_POR,                       /* porosity */
  SV_F_NORMAL,                  /* acoustics face normal for initial surface grid (for sliding mesh) */
  SV_F_CENTROID,                /* acoustics face centroid for initial surface grid (for sliding mesh)*/

  SV_SOLUTION_VAR(SOUND_VAR),
  SV_SOUND_P_MEAN,
  SV_SOUND_P_RMS,
  SV_SOUND_DDT,
  SV_SOUND_DDT_G,
  SV_SOUND_DDT_RG,
  SV_SOUND_DDT_RG_AUX,
  SV_SOUND_DDT_M1,
  SV_SOUND_D2DT2,
  SV_SOUND_D2DT2_M1,
  SV_SOUND_SPACE_TERM,
  SV_SOUND_SPACE_TERM_M1,
  SV_SOUND_MODEL_SRC,
  SV_SOUND_MODEL_SRC_M1,
  SV_SOUND_MODEL_SRC_M2,
  SV_SOUND_MODEL_SRC_M3,
  SV_SOUND_MODEL_SRC_M4,
  SV_SOUND_MODEL_SRC_M5,
  SV_SOUND_MODEL_SRC_M6,
  SV_SOUND_MODEL_SRC_MEAN,
  SV_SOUND_MODEL_SRC_RMS,
  SV_SOUND_MODEL_SRC_SMOOTH,
  SV_SOUND_MODEL_SRC_FINAL,
  SV_SOUND_MODEL_SRC_MASK,
  SV_SOUND_SPONGE,
  SV_SOUND_TMP_SCALAR,
  /** TODO Remove || 1 when QUADRATIC_FIT_SCHEME is enabled on Windows */
#if QUADRATIC_FIT_SCHEME || 1  /* QUADRATIC_FIT_SCHEME is defined in store.h */
  SV_CELL_CELLS_LIST,
  SV_QUAD_FIT_MATRIX,
#endif

#define SV_SPL_OCTAVE_(f) SV_SPL_OCTAVE_##f##HZ
#define SV_PSD_DPDT_OCTAVE_(f) SV_PSD_DPDT_OCTAVE_##f##HZ
#define EXPAND_MACRO_SV_OCTAVE(m) \
  m(1),m(2),m(4),m(8),m(16),m(31p5),m(63),m(125),m(250),\
  m(500),m(1k),m(2k),m(4k),m(8k),m(16k),m(31p5k),m(63k),
  EXPAND_MACRO_SV_OCTAVE(SV_SPL_OCTAVE_)
  EXPAND_MACRO_SV_OCTAVE(SV_PSD_DPDT_OCTAVE_)

#define SV_SPL_THIRD_(f) SV_SPL_THIRD_##f##HZ
#define SV_PSD_DPDT_THIRD_(f) SV_PSD_DPDT_THIRD_##f##HZ
#define EXPAND_MACRO_SV_THIRD(m) \
  m(0p5),m(0p63),m(0p8),m(1),m(1p25),m(1p6),m(2),m(2p5),m(3p15),m(4),\
  m(5),m(6p3),m(8),m(10),m(12p5),m(16),m(20),m(25),m(31p5),m(40),\
  m(50),m(63),m(80),m(100),m(125),m(160),m(200),m(250),m(315),m(400),\
  m(500),m(630),m(800),m(1k),m(1p25k),m(1p6k),m(2k),m(2p5k),m(3p15k),m(4k),\
  m(5k),m(6p3k),m(8k),m(10k),m(12p5k),m(16k),m(20k),m(25k),m(31p5k),m(40k),\
  m(50k),m(63k),m(80k),m(100k),
  EXPAND_MACRO_SV_THIRD(SV_SPL_THIRD_)
  EXPAND_MACRO_SV_THIRD(SV_PSD_DPDT_THIRD_)

  EXPAND_0_TO_19(EXPAND_SV_helper, P_SPECT_RE),
#define SV_P_SPECT_RE_MAX SV_P_SPECT_RE_19
#define SV_P_SPECT_RE(i)((Svar)(SV_P_SPECT_RE_0+i))

  EXPAND_0_TO_19(EXPAND_SV_helper, P_SPECT_IM),
#define SV_P_SPECT_IM_MAX SV_P_SPECT_IM_19
#define SV_P_SPECT_IM(i)((Svar)(SV_P_SPECT_IM_0+i))

  EXPAND_0_TO_19(EXPAND_SV_helper, SPL_BAND),
#define SV_SPL_BAND_MAX SV_SPL_BAND_19
#define SV_SPL_BAND(i)((Svar)(SV_SPL_BAND_0+i))
  EXPAND_0_TO_19(EXPAND_SV_helper, PSD_DPDT_BAND),
#define SV_PSD_DPDT_BAND_MAX SV_PSD_DPDT_BAND_19
#define SV_PSD_DPDT_BAND(i)((Svar)(SV_PSD_DPDT_BAND_0+i))

  SV_AC_POSTPROC_M1,
  SV_AC_POSTPROC_M2,
  SV_AC_POSTPROC_M3,
  SV_AC_POSTPROC_M4,
  SV_AC_POSTPROC_M5,

  SV_AC_MODESAN_M_0,  /* Acoustics postprocessing for Modal Analysis model */
  SV_AC_MODESAN_M_1,
  SV_AC_MODESAN_M_2,
  SV_AC_MODESAN_M_3,
  SV_AC_MODESAN_M_4,
  SV_AC_MODESAN_M_5,
  SV_AC_MODESAN_M_6,
  SV_AC_MODESAN_M_7,
  SV_AC_MODESAN_M_8,
  SV_AC_MODESAN_M_9,
  SV_AC_MODESAN_M_10,
  SV_AC_MODESAN_M_11,
  SV_AC_MODESAN_M_12,
  SV_AC_MODESAN_M_13,
  SV_AC_MODESAN_M_14,
  SV_AC_MODESAN_M_15,
  SV_AC_MODESAN_M_16,
  SV_AC_MODESAN_M_17,
  SV_AC_MODESAN_M_18,
  SV_AC_MODESAN_M_19,
  SV_AC_MODESAN_M_20,
  SV_AC_MODESAN_M_21,
  SV_AC_MODESAN_M_22,
  SV_AC_MODESAN_M_23,
  SV_AC_MODESAN_M_24,
  SV_AC_MODESAN_M_25,
  SV_AC_MODESAN_M_26,
  SV_AC_MODESAN_M_27,
  SV_AC_MODESAN_M_28,
  SV_AC_MODESAN_M_29,

  SV_SOLUTION_VAR(ECFM_SIGMA),      /* Flame area density model */
  SV_ECFM_SIGMA_P,                  /* Overall production term for ECFM */
  SV_ECFM_SIGMA_P2,                 /* Dillitation production */
  SV_ECFM_U_TEMP,                   /* Local unburnt temperature*/
  SV_ECFM_B_TEMP,                   /* Local burnt temperature*/
  SV_ECFM_B_DEN,                    /* Local burnt density*/
  SV_PREMIXCM,                      /* mean progress var by vol */
  SV_PREMIXCM_G,                    /* grad of mean progress var by vol */
  SV_PREMIXCM_RG,                   /* recon grad mean progress var by vol */
  SV_PREMIXCM_RG_AUX,
  SV_ECFM_SLES,                     /* brush thickness factor for ecfm les */

  SV_SOLUTION_VAR(GEQN),            /* g equation model */
  SV_SOLUTION_VAR(GVAR),            /* g equation variance */

  SV_SOLUTION_VAR(INERT),           /* Inert stream for dilution (EGR) */
  SV_INERT_H,                       /* Overall enthalpy conditioned with inert */

  /* Laplace mesh smoothing */
  SV_SOLUTION_VAR(LMS_U),
  SV_SOLUTION_VAR(LMS_V),
#if RP_3D
  SV_SOLUTION_VAR(LMS_W),
#endif
  SV_SOLUTION_VAR(LMS_BD),

  /* FEM mesh smoothing */
  SV_N_FEMS_X,
  SV_N_FEMS_Y,
#if RP_3D
  SV_N_FEMS_Z,
#endif

  /* RBF mesh smoothing */
  SV_N_RBF_X,
  SV_N_RBF_Y,
  SV_N_RBF_Z,

  /* Overset mesh */
#if RP_OVERSET
  SV_OVERSET_NDONOR,
  SV_OVERSET_DONOR,
  SV_OVERSET_NRECEPTOR,
  SV_OVERSET_RECEPTOR,
  SV_OVERSET_BD,
  SV_OVERSET_BCELL,
  SV_OVERSET_WEIGHT,
  SV_OVERSET_SIZE_RATIO,
#if PARALLEL
  SV_DCI_TYPE,
  SV_DCI_DONOR,
  SV_DCI_WEIGHT,
#endif
#endif

  /* HTC */
#if RP_HTC
  SV_HTC_MARK,
  SV_HTC_INDEX,
  SV_HTC_TMP,
  /* HTC Lattice Boltzmann variables */
  SV_HTC_LB_VOF,
  SV_HTC_LB_BNDR,
  SV_HTC_LB_CNTR_PRED,
  SV_HTC_LB_BNDR_CNT,
  SV_HTC_LB_BNDR_PTR,
  SV_HTC_LB_OCT,
  SV_HTC_LB_NODE_CELL,
  SV_HTC_LB_OCT_FACES,
  SV_HTC_LB_POST,
#endif

#if RP_WALL_FILM
  /* Eulerian Wall Film Model */
  SV_EFILM_GSOLUTION_VAR(EFILM_HEIGHT),
  SV_EFILM_GSOLUTION_VAR(EFILM_U),
  SV_EFILM_GSOLUTION_VAR(EFILM_V),
  SV_EFILM_GSOLUTION_VAR(EFILM_W),
  SV_EFILM_GSOLUTION_VAR(EFILM_T),
  SV_EFILM_GSOLUTION_VAR(EFILM_S),

  SV_EFILM_P,
  SV_EFILM_US,
  SV_EFILM_VS,
  SV_EFILM_WS,
  SV_EFILM_TS,

  SV_EFILM_DENSITY,

  SV_EFILM_CFL,
  SV_EFILM_WEBER,

  SV_EFILM_DPM_MASS_SRC,
  SV_EFILM_DPM_MOM_X_SRC,
  SV_EFILM_DPM_MOM_Y_SRC,
  SV_EFILM_DPM_MOM_Z_SRC,

  SV_EFILM_DPM_ENERGY_SRC,
  SV_EFILM_DPM_PRESSURE,

  SV_EFILM_SEPARATING_SRC,     /* rate at current time step */
  SV_EFILM_SEPARATED_DIAM,     /* count averaged */
  SV_EFILM_SEPARATED_MASS,     /* cumulative over injection interval */
  SV_EFILM_SEPARATED_MASS_SUM, /* cumulative over film elapsed time */
  SV_EFILM_STRIPPING_SRC,
  SV_EFILM_STRIPPED_DIAM,
  SV_EFILM_STRIPPED_MASS,
  SV_EFILM_STRIPPED_MASS_SUM,

  SV_EFILM_OUTFLOW_MASS_SUM,

  SV_EFILM_PHS2_MASS_SRC,
  SV_EFILM_PHS2_MOMS_SRC,
  SV_EFILM_PHS2_ENERGY_SRC,
  SV_EFILM_MASS_PHS2_S,

  SV_EFILM_F2V_MASS_SRC,
  SV_EFILM_F2V_MOMS_SRC,
  SV_EFILM_F2V_ENERGY_SRC,
  SV_EFILM_V2F_MASS_SRC,
  SV_EFILM_V2F_MOMS_SRC,
  SV_EFILM_V2F_ENERGY_SRC,
  SV_EFILM_VOF_MASS_XCHG_SUM,
  SV_EFILM_MASS_VOF_S,

  SV_EFILM_T_ALPHA,
  SV_EFILM_T_BETA,
  SV_EFILM_TS_FLUX,

  SV_EFILM_VAPOR_MASS_SRC,
  SV_EFILM_VAPOR_MASS_APP,
  SV_EFILM_MASS_VAPOR_S,

  /* These are un-stored variables for the film model */
  SV_EF_TRANS_M,
#define SV_EF_MIN ((Svar)(SV_EF_TRANS_M))
  SV_EF_ORIGIN,
  SV_EF_NORMD0,
#define SV_EF_ESSENTIAL_MIN ((Svar)(SV_EF_NORMD0+1))
  SV_EFILM_LSOLUTION_VAR(EF_HEIGHT),
  SV_EFILM_LSOLUTION_VAR(EF_HVEL_X),
  SV_EFILM_LSOLUTION_VAR(EF_HVEL_Y),
  SV_EFILM_LSOLUTION_VAR(EF_HT),
  SV_EFILM_LSOLUTION_VAR(EF_HS),

  SV_EF_HTVEL_X,
  SV_EF_HTVEL_Y,

  SV_EF_HSVEL_X,
  SV_EF_HSVEL_Y,

  SV_EF_SVEL_X,
  SV_EF_SVEL_Y,

  SV_EF_HVELA_X,
  SV_EF_HVELA_Y,

  SV_EF_Z_ACC,
  SV_EF_H_COV,

  SV_EF_H_CURV,
  SV_EF_H_NVEC,

  SV_EF_HEIGHT_SMOOTH,
  SV_EF_H_CURV_SMOOTH,
  SV_EF_EPRESS_SMOOTH,

  SV_EFILM_V_INERTIA_VAR(EF_HVV_0), /* tensor */
  SV_EFILM_V_INERTIA_VAR(EF_HVV_1),
  SV_EFILM_V_INERTIA_VAR(EF_HVV_2),
  SV_EFILM_V_INERTIA_VAR(EF_HVV_3),
  SV_EFILM_V_INERTIA_VAR(EF_HVV_4),

  SV_EF_HVV_DIV, /* vector */
  SV_EF_VEC_DIV,
#define SV_EF_ESSENTIAL_MAX ((Svar)(SV_EF_VEC_DIV+1))

  SV_EF_PRESS_G,
  SV_EF_Z_ACC_G,
  SV_EF_H_COV_G,
  SV_EF_H_CUR_G,

  SV_EF_VOF_MASS_XCHG,

  SV_EF_SCA,
  SV_EF_SCA_G,
  SV_EF_SCA_RG,

  SV_EF_VEC_X_G,
  SV_EF_VEC_Y_G,
  SV_EF_VEC_Z_G,
  SV_EF_VEC_X_RG,
  SV_EF_VEC_Y_RG,
  SV_EF_VEC_Z_RG,

  SV_EF_TEMP_R_NV,
  SV_EF_RECON_MIN,
  SV_EF_RECON_MAX,
  SV_EF_RECON_PHI,

  SV_EF_SMOOTH_WT,
  SV_EF_SMOOTH_SC,
  SV_EF_SMOOTH_WS,

  SV_EF_FTMP,
  SV_EF_FTMP_NV,
  SV_EF_CTMP,
  SV_EF_CTMP_NV,
#define SV_EF_MAX ((Svar)(SV_EF_CTMP_NV+1))
#endif

  SV_JAVG_INFO_P,
  SV_JAVG_LEVEL,

#define SV_CFF_MEAN(i) ((Svar)((SV_CFF_0_MEAN+(i)*(SV_CFF_1_MEAN-SV_CFF_0_MEAN))))
#define SV_CFF_RMS(i) ((Svar)((SV_CFF_0_RMS+(i)*(SV_CFF_1_RMS-SV_CFF_0_RMS))))
#define SV_CFF_MAX_RMS SV_CFF_49_RMS
#define SV_CFF_MAX_MEAN SV_CFF_49_MEAN
  EXPAND_CFF_SV_MEAN(CFF),
  EXPAND_CFF_SV_RMS(CFF),
  /* Ansoft (Maxwell/HFSS/Q3D) contribution to source terms */
  SV_T_MAXWELL,

  /* Adjoint variables */
  SV_ADJOINT_U,
  SV_ADJOINT_V,
  SV_ADJOINT_W,
  SV_ADJOINT_P,
  SV_ADJOINT_T,
  SV_ADJOINT_AP,
  SV_ADJOINT_K,
  SV_ADJOINT_O,
  SV_ADJOINT_STD_AP,
  SV_ADJOINT_U_G,
  SV_ADJOINT_V_G,
  SV_ADJOINT_W_G,
  SV_ADJOINT_U_RG,
  SV_ADJOINT_V_RG,
  SV_ADJOINT_W_RG,
  SV_ADJOINT_P_G,
  SV_ADJOINT_P_RG,
  SV_ADJOINT_H,
  SV_ADJOINT_DH,
  SV_ADJOINT_T_G,
  SV_ADJOINT_T_RG,
  SV_ADJOINT_H_RG,
  SV_ADJOINT_K_RG,
  SV_ADJOINT_K_G,
  SV_ADJOINT_O_RG,
  SV_ADJOINT_O_G,
  SV_ADJOINT_DU_G,
  SV_ADJOINT_DV_G,
  SV_ADJOINT_DW_G,
  SV_ADJOINT_DP_G,
  SV_ADJOINT_DK_G,
  SV_ADJOINT_DO_G,
  SV_ADJOINT_DP_RG,
  SV_ADJOINT_DT,
  SV_ADJOINT_DT_G,
  SV_ADJOINT_DU_RG,
  SV_ADJOINT_DV_RG,
  SV_ADJOINT_DW_RG,
  SV_ADJOINT_DT_RG,
  SV_ADJOINT_DH_RG,
  SV_ADJOINT_DK_RG,
  SV_ADJOINT_DO_RG,
  SV_ADJOINT_DXC,
  SV_ADJOINT_DVOL,
  SV_ADJOINT_DA,
  SV_ADJOINT_HMAX,
  SV_ADJOINT_DHMAX,
  SV_ADJOINT_SCALE_X,
  SV_ADJOINT_SCALE_Y,
  SV_ADJOINT_SCALE_Z,
  SV_ADJOINT_SCALE_T,
  SV_ADJOINT_SCALE_H,
  SV_ADJOINT_SCALE_P,
  SV_ADJOINT_SCALE_K,
  SV_ADJOINT_SCALE_O,
  SV_ADJOINT_ILIMIT_X,
  SV_ADJOINT_ILIMIT_Y,
  SV_ADJOINT_ILIMIT_Z,
  SV_ADJOINT_ILIMIT_T,
  SV_ADJOINT_ILIMIT_H,
  SV_ADJOINT_ILIMIT_P,
  SV_ADJOINT_ILIMIT_K,
  SV_ADJOINT_ILIMIT_O,
  SV_ADJOINT_DU,
  SV_ADJOINT_DV,
  SV_ADJOINT_DW,
  SV_ADJOINT_DP,
  SV_ADJOINT_DAp,
  SV_ADJOINT_DK,
  SV_ADJOINT_DO,
  SV_ADJOINT_DFACE_FLUX,
  SV_ADJOINT_DHEAT_FLUX,
  SV_ADJOINT_DRHO,
  SV_ADJOINT_DMU_EFF,
  SV_ADJOINT_DMU,
  SV_ADJOINT_DKTC,
  SV_ADJOINT_DCP,
  SV_ADJOINT_DPRODUCTION,
  SV_ADJOINT_DWALL_DIST,
  SV_ADJOINT_DOMEGA_G,
  SV_ADJOINT_GEKO_CSEP,
  SV_ADJOINT_GEKO_CNW,
  SV_ADJOINT_GEKO_CMIX,
  SV_ADJOINT_GEKO_BF,
  SV_ADJOINT_CCURV,
  SV_ADJOINT_CCORNER,
  SV_ADJOINT_DGEKO_CSEP,
  SV_ADJOINT_DGEKO_CNW,
  SV_ADJOINT_DGEKO_CMIX,
  SV_ADJOINT_DGEKO_BF,
  SV_ADJOINT_DCCURV,
  SV_ADJOINT_DCCORNER,
  SV_ADJOINT_DBSL_SST_F1,
  SV_ADJOINT_DINTERMIT_ALGEBRAIC,
  SV_ADJOINT_DTRANS_ALG_REC,
  SV_ADJOINT_DML_TKE_COEF,
  SV_ADJOINT_DML_OMEGA_COEF,
  SV_ADJOINT_DML_TRANS_ALG_COEF,
  SV_ADJOINT_DML_WJ_EARSM_BETA1,
  SV_ADJOINT_DML_WJ_EARSM_BETA3,
  SV_ADJOINT_DML_WJ_EARSM_BETA4,
  SV_ADJOINT_DML_WJ_EARSM_BETA6,
  SV_ADJOINT_DWALL_NORMAL,
  SV_ADJOINT_DUINI,
  SV_ADJOINT_DUINI_RG,
  SV_ADJOINT_DUINI_G,
  SV_ADJOINT_SCALE_WALL_DIST,
  SV_ADJOINT_ILIMIT_WALL_DIST,
  SV_ADJOINT_SCALE_UINI,
  SV_ADJOINT_ILIMIT_UINI,
  SV_ADJOINT_MOMENTUM_X_RES,
  SV_ADJOINT_MOMENTUM_Y_RES,
  SV_ADJOINT_MOMENTUM_Z_RES,
  SV_ADJOINT_CONTINUITY_RES,
  SV_ADJOINT_ENERGY_RES,
  SV_ADJOINT_AP_RES,
  SV_ADJOINT_K_RES,
  SV_ADJOINT_O_RES,
  SV_ADJOINT_HISTORY_0,
  SV_ADJOINT_HISTORY_1,
  SV_ADJOINT_HISTORY_2,
  SV_ADJOINT_HISTORY_3,
  SV_ADJOINT_HISTORY_4,
  SV_ADJOINT_MARKER_0,
  SV_ADJOINT_CELL_MARKER,
  SV_ADJOINT_ART_DISSIPATION,
  SV_ADJOINT_HISTORY_TMP_0,
  SV_ADJOINT_HISTORY_TMP_1,
  SV_ADJOINT_HISTORY_TMP_2,
  SV_ADJOINT_HISTORY_TMP_3,
  SV_ADJOINT_HISTORY_TMP_4,
  SV_ADJOINT_DF_LSQ_WT0,
  SV_ADJOINT_DF_LSQ_WT1,
  SV_ADJOINT_TEMP_0,
  SV_ADJOINT_TEMP_1,
  SV_ADJOINT_RTMP_0,
  SV_ADJOINT_RTMP_1,
  SV_ADJOINT_RTMP_2,
  SV_ADJOINT_RTMP_3,
  SV_ADJOINT_RTMP_4,
  SV_ADJOINT_RTMP_5,
  SV_ADJOINT_RTMP_6,
  SV_ADJOINT_RTMP_7,
  SV_ADJOINT_RTMP_8,
  SV_ADJOINT_TEST_DP,
  SV_ADJOINT_TEST_DU,
  SV_ADJOINT_TEST_DV,
  SV_ADJOINT_TEST_DW,
  SV_ADJOINT_TEST_DAP,
  SV_ADJOINT_TOPOLOGY_DENSITY,
  SV_ADJOINT_DTOPOLOGY_DENSITY,
  SV_ADJOINT_TOPOLOGY_DENSITY_RC,
  SV_ADJOINT_DTOPOLOGY_DENSITY_RC,
  SV_ADJOINT_DTOPOLOGY_DENSITY1,
  SV_ADJOINT_DTOPOLOGY_DENSITY2,
  SV_ADJOINT_DTOPOLOGY_DENSITY3,
  SV_ADJOINT_DTOPOLOGY_DENSITY4,
  SV_ADJOINT_DTOPOLOGY_DENSITY5,
  SV_ADJOINT_DTOPOLOGY_DENSITY6,
  SV_ADJOINT_DTOPOLOGY_DENSITY7,
  SV_ADJOINT_DTOPOLOGY_DENSITY8,
  SV_ADJOINT_DTOPOLOGY_DENSITY9,
  SV_ADJOINT_DTOPOLOGY_DENSITY10,
  SV_ADJOINT_TOPOLOGY_DENS_CHANGE,
  SV_ADJOINT_OPT_CHANGE1,
  SV_ADJOINT_OPT_CHANGE2,
  SV_ADJOINT_OPT_CHANGE3,
  SV_ADJOINT_OPT_CHANGE4,
  SV_ADJOINT_OPT_CHANGE5,

  /* impedance boundary condition */
  SV_IMP_W5,
  SV_IMP_W5_M1,
  SV_IMP_W1,
  SV_IMP_W1_M1,
  EXPAND_0_TO_9(EXPAND_SV_helper, IMP_RP),
  EXPAND_0_TO_9(EXPAND_SV_M1_helper, IMP_RP),
  EXPAND_0_TO_9(EXPAND_SV_helper, IMP_RE),
  EXPAND_0_TO_9(EXPAND_SV_M1_helper, IMP_RE),
  EXPAND_0_TO_9(EXPAND_SV_helper, IMP_IM),
  EXPAND_0_TO_9(EXPAND_SV_M1_helper, IMP_IM),

  /* face coeff */
  SV_F_COEFF,
  SV_FIXED_VEL_COEFF_01,
  SV_FIXED_VEL_COEFF_10,

  /*Monte Carlo*/
  SV_MC_SOURCE,
  SV_MC_I,
  SV_MC_SDV,
  SV_MC_CID,
  SV_MC_FID,
  SV_MC_SP_C0,
  SV_MC_SP_C1,
  SV_MC_FPRIM,
  SV_MC_NPRIM,
  SV_MC_IRR_QTRANS,
  SV_MC_IRR_QREFL,
  SV_MC_IRR_QABS,
  SV_MC_QTRANS,
  SV_MC_QREFL,
  SV_MC_QABS,
  SV_MC_QMINUS,
  /* managed tmp svars, please don't use these svars directly. For usage, please refer to
   * tmp_manager.c, where you have the interface to get/return tmp variables
   *
   * If the type is not enough, you can add new types, or new ones winin a type here.
   * Then add the definition in storage.c
   */
  SV_TMP_MANAGED_START,
  SV_ITMP_MANAGED_0 = SV_TMP_MANAGED_START,
  SV_ITMP_MANAGED_1,
  SV_ITMP_MANAGED_2,
  SV_ITMP_MANAGED_3,
  SV_ITMP_MANAGED_4,
  SV_ITMP_MANAGED_5,
  SV_ITMP_MANAGED_6,
  SV_ITMP_MANAGED_7,
  SV_ITMP_MANAGED_8,
  SV_RTMP_MANAGED_0,
  SV_RTMP_MANAGED_1,
  SV_RTMP_MANAGED_2,
  SV_RTMP_MANAGED_3,
  SV_RTMP_MANAGED_4,
  SV_NDTMP_MANAGED_0,
  SV_NDTMP_MANAGED_1,
  SV_ND3TMP_MANAGED_0,
  SV_NDNDTMP_MANAGED_0,
  SV_NDNDTMP_MANAGED_1,
  SV_OBJPTMP_MANAGED_0,
  SV_OBJPTMP_MANAGED_1,
  SV_OBJPTMP_MANAGED_2,
  SV_TMPINDEX_MANAGED_0,
  SV_TMPINDEX_MANAGED_1,
  SV_TMPUNION_MANAGED_0,
  SV_TMPUNION_MANAGED_1,
  SV_TMPUNION_MANAGED_2,
  SV_TMP_MANAGED_END = SV_TMPUNION_MANAGED_2,
  /* sedm variables */
  SV_CONTINUITY_S,
  SV_CONTINUITY_FMEAN_S,
  SV_CONTINUITY_FVAR_S,
  SV_INV_DENSITY_D_FMEAN,
  SV_INV_DENSITY_D_FVAR,

  /* outflow boundary variables */
  SV_OUTFLOW_DEFICIT,
  SV_OUTFLOW_DEFICIT_M1,
  SV_OUTFLOW_DEFICIT_M2,

#if USE_FEMCORE
  /* element (cell or face) interpolation nodes*/
  SV_ELEMENT_IN_INTERP_BEGIN,
  SV_ELEMENT_IN_CONST_PER_ELEMENT = SV_ELEMENT_IN_INTERP_BEGIN,
  SV_ELEMENT_IN_LINEAR,
  SV_ELEMENT_IN_SERENDIP,
  SV_ELEMENT_IN_QUADRATIC,
  SV_ELEMENT_IN_INTERP_END = SV_ELEMENT_IN_QUADRATIC,  /* Pay attention to the last one. */
  SV_CINZ_BEGIN,
  SV_CINZ_IDX = SV_CINZ_BEGIN,
  SV_CINZ_SOLVER_IDX,
  SV_CINZ_X,
  SV_CINZ_Y,
  SV_CINZ_Z,
  SV_CINZ_SHADOW,
  SV_CINZ_END = SV_CINZ_SHADOW, /* Pay attention to the last one. */
#endif

  /* nodal zone related */
  SV_N_CNZ_IDX,      /* int, node_thread svar for the index in the cnz */
  SV_CNZ_NODEP,      /* Node*, CNZ svar for the node pointers */
  SV_FNZ_IDX,        /* int, FNZ svar for the index in the cnz */
  SV_CNZ_RTMP_0,     /* real, CNZ TMP Real svar */

  /* Structural solver */
  SV_STRUCTURE_START,
  SV_N_DISP_X = SV_STRUCTURE_START,
  SV_N_DISP_X_R,
  SV_N_DISP_X_M1,
  SV_N_DISP_X_DOT1,
  SV_N_DISP_X_DOT1_M1,
  SV_N_DISP_X_DOT2,
  SV_N_DISP_X_DOT2_M1,

  SV_N_DISP_Y,
  SV_N_DISP_Y_R,
  SV_N_DISP_Y_M1,
  SV_N_DISP_Y_DOT1,
  SV_N_DISP_Y_DOT1_M1,
  SV_N_DISP_Y_DOT2,
  SV_N_DISP_Y_DOT2_M1,

  SV_N_DISP_Z,
  SV_N_DISP_Z_R,
  SV_N_DISP_Z_M1,
  SV_N_DISP_Z_DOT1,
  SV_N_DISP_Z_DOT1_M1,
  SV_N_DISP_Z_DOT2,
  SV_N_DISP_Z_DOT2_M1,

  SV_SIGMA_XX,
  SV_SIGMA_YY,
  SV_SIGMA_XY,
  SV_SIGMA_ZZ,
  SV_SIGMA_YZ,
  SV_SIGMA_XZ,

  SV_N_INIT_STRUCTURE_X,
  SV_N_INIT_STRUCTURE_Y,
  SV_N_INIT_STRUCTURE_Z,
  SV_N_T_INTERP,
  SV_STRUCTURE_END,
  SV_RELATIVE_PERMEABILITY = SV_STRUCTURE_END,

  /* storage for statistics data set */
#define SV_STAT_DATASET_MEAN(i) ((Svar)((SV_STAT_DATASET_0_MEAN+(i)*(SV_STAT_DATASET_1_MEAN-SV_STAT_DATASET_0_MEAN))))
#define SV_STAT_DATASET_RMS(i) ((Svar)((SV_STAT_DATASET_0_RMS+(i)*(SV_STAT_DATASET_1_RMS-SV_STAT_DATASET_0_RMS))))
#define SV_STAT_DATASET_MAX_RMS SV_STAT_DATASET_49_RMS
#define SV_STAT_DATASET_MAX_MEAN SV_STAT_DATASET_49_MEAN
  EXPAND_STAT_DATASET_SV_MEAN(STAT_DATASET),
  EXPAND_STAT_DATASET_SV_RMS(STAT_DATASET),

#define SV_STAT_SEG_DATASET_MOV_AVG(i) ((Svar)((SV_STAT_SEG_DATASET_0_MOV_AVG+(i)*(SV_STAT_SEG_DATASET_1_MOV_AVG-SV_STAT_SEG_DATASET_0_MOV_AVG))))
#define SV_STAT_SEG_DATASET_MAX_MOV_AVG SV_STAT_SEG_DATASET_49_MOV_AVG
  EXPAND_STAT_SEG_DATASET_SV_MOV_AVG(STAT_SEG_DATASET),
  SV_SOLUTION_VAR(CDS),
  EXPAND_NCURV_COORD_SV(CURV_COORD),

#define SV_STAT_DATASET_MIN(i) ((Svar)((SV_STAT_DATASET_0_MIN+(i)*(SV_STAT_DATASET_1_MIN-SV_STAT_DATASET_0_MIN))))
#define SV_STAT_DATASET_MAX(i) ((Svar)((SV_STAT_DATASET_0_MAX+(i)*(SV_STAT_DATASET_1_MAX-SV_STAT_DATASET_0_MAX))))
#define SV_STAT_DATASET_MAX_MIN SV_STAT_DATASET_49_MIN
#define SV_STAT_DATASET_MAX_MAX SV_STAT_DATASET_49_MAX
  EXPAND_STAT_DATASET_SV_MIN(STAT_DATASET),
  EXPAND_STAT_DATASET_SV_MAX(STAT_DATASET),

  SV_POWER_MAP,

  /* aero-optics storage variables */
  SV_OPL,
  SV_OPL_MEAN,
  SV_OPL_FLUCTUATION,
  SV_OPD,

  SV_MAX
} Svar;

/* Macros for generic tmp storage on entities */
#define CELL_MANAGED_TMP(_c, _t, _svar, _type) \
  C_STORAGE(_c, _t, _svar, _type *)
#define FACE_MANAGED_TMP(_f, _t, _svar, _type) \
  F_STORAGE(_f, _t, _svar, _type *)
#define NODE_MANAGED_TMP(_v, _svar, _type) \
  N_STORAGE(NODE_INDEX(_v), NODE_THREAD(_v), _svar, _type *)

/* access managed tmp svars on cells */
#define CELL_MANAGED_TMP_INT(_c, _t, _svar) \
  CELL_MANAGED_TMP(_c, _t, _svar, int)
#define CELL_MANAGED_TMP_REAL(_c, _t, _svar) \
  CELL_MANAGED_TMP(_c, _t, _svar, real)
#define CELL_MANAGED_TMP_OBJP(_c, _t, _svar) \
  CELL_MANAGED_TMP(_c, _t, _svar, Objp *)
#define CELL_MANAGED_TMP_INDEX(_c, _t, _svar) \
  CELL_MANAGED_TMP(_c, _t, _svar, cxindex)
#define CELL_MANAGED_TMP_TMPUNION(_c, _t, _svar) \
  CELL_MANAGED_TMP(_c, _t, _svar, TempUnion)
#define CELL_MANAGED_TMP_ND(_c, _t, _svar) \
  C_STORAGE_R_NV(_c, _t, _svar)

/* access managed tmp svars on faces */
#define FACE_MANAGED_TMP_INT(_f, _t, _svar)     \
  FACE_MANAGED_TMP(_f, _t, _svar, int)
#define FACE_MANAGED_TMP_REAL(_f, _t, _svar)    \
  FACE_MANAGED_TMP(_f, _t, _svar, real)
#define FACE_MANAGED_TMP_OBJP(_f, _t, _svar)    \
  FACE_MANAGED_TMP(_f, _t, _svar, Objp *)
#define FACE_MANAGED_TMP_INDEX(_f, _t, _svar)   \
  FACE_MANAGED_TMP(_f, _t, _svar, cxindex)
#define FACE_MANAGED_TMP_TMPUNION(_f, _t, _svar)        \
  FACE_MANAGED_TMP(_f, _t, _svar, TempUnion)
#define FACE_MANAGED_TMP_ND(_f, _t, _svar)      \
  F_STORAGE_R_NV(_f, _t, _svar)
#define FACE_MANAGED_TMP_ND_3(_f, _t, _svar)      \
  F_STORAGE_R_N3V(_f, _t, _svar)

/* access managed tmp svars on nodes */
#define NODE_MANAGED_TMP_INT(_v, _svar) \
  NODE_MANAGED_TMP(_v, _svar, int)
#define NODE_MANAGED_TMP_REAL(_v, _svar) \
  NODE_MANAGED_TMP(_v, _svar, real)
#define NODE_MANAGED_TMP_OBJP(_v, _svar) \
  NODE_MANAGED_TMP(_v, _svar, Objp *)
#define NODE_MANAGED_TMP_INDEX(_v, _svar) \
  NODE_MANAGED_TMP(_v, _svar, cxindex)
#define NODE_MANAGED_TMP_TMPUNION(_v, _svar) \
  NODE_MANAGED_TMP(_v, _svar, TempUnion)
#define NODE_MANAGED_TMP_ND(_v, _svar) \
  N_STORAGE_R_NV(NODE_INDEX(_v), NODE_THREAD(_v), _svar)
#define NODE_MANAGED_TMP_ND_3(_v, _svar)                        \
  N_STORAGE_R_N3V(NODE_INDEX(_v), NODE_THREAD(_v), _svar)

/* arg to sv->residual_p should be one of these */
typedef enum sv_residual_code
{
  RESIDUAL_STORE = 0,
  RESIDUAL_DISPLAY = 1,
  RESIDUAL_INDEX
} SV_Residual_Code;

/* result of sv->store_p should be of this type */
typedef enum sv_store_type
{
  SV_STORE_SELF = -1,
  SV_STORE_NULL =  0
} SV_Store_Type;

#define SV_STORE_TYPE(t,nv,gibberish)\
((gibberish) ? store_shared(t,nv) : SV_STORE_NULL)

#define SV_STORE_TYPE_SELF(t,nv,gibberish)\
((gibberish) ? SV_STORE_SELF : SV_STORE_NULL)

/* dimension types for storage variables */
typedef enum sv_dimension
{
  SV_DIM_NULL,
  SV_DIM_REAL,
  SV_DIM_DOUBLE,
  SV_DIM_INT,
  SV_DIM_BIT,
  SV_DIM_POINTER,
  SV_DIM_OBJP,
  SV_DIM_CELL_T,
  SV_DIM_FACE_T,
  SV_DIM_ND,
  SV_DIM_ND_DOUBLE,
  SV_DIM_ND_3,
  SV_DIM_ND_BY_ND,
  SV_DIM_ND_3_BY_ND_3,
  SV_DIM_NSPE,
  SV_DIM_NSPE_ND,
  SV_DIM_NSPE_BY_NSPM,
  SV_DIM_SPE_DIFF_COEFF,
  SV_DIM_NSPE_SURF,
  SV_DIM_NSPE_SITE,
  SV_DIM_NSPE_SITE_AREA,
  SV_DIM_NSPE_AVE,
  SV_DIM_UDM,
  SV_DIM_NODE_UDM,
  SV_DIM_DO,
  SV_DIM_DO_NBAND,
  SV_DIM_SOLAR_BAND,
  SV_DIM_NODE,
  SV_DIM_NODE_REAL,
  SV_DIM_C_FACE,
  SV_DIM_C_FACE_THREAD,
  SV_DIM_NNODES,
  SV_DIM_NFACES,
  SV_DIM_UCHAR,
  SV_DIM_F_GRID_FLUX,
  SV_DIM_C_COARSE,
  SV_DIM_CHILD,     /* hanging node cell and face children array */
  SV_DIM_CHILD_INDEX,
  SV_DIM_CHILD_THREAD,
  SV_DIM_EDGE,      /* hanging node face edges */
  SV_DIM_RST,
#if RP_SHELL
  SV_DIM_SHELL,
  SV_DIM_DO_SHELL,
  SV_DIM_DO_NBAND_SHELL,
  /*SV_DIM_ND_4,*/
#endif
  SV_DIM_ND_5,
  SV_DIM_TMPUNION,
  SV_DIM_NEIGHBOR,

  SV_DIM_MP_AREA_DENSITY, /* mphase area density segregated vector*/

  SV_DIM_MASS_T, /* mass transfer segregated vector */
  SV_DIM_HET_RXN, /* heter. reactions segregated vector */

  SV_DIM_MANAGED,
#if RP_FC
  SV_DIM_ACFC,
  SV_DIM_BCFC,
  SV_DIM_PLFC,
#endif
  SV_DIM_EPDF,
  SV_DIM_INDEX,
  SV_DIM_PB_MT, /*PB mass transfer for Inhomogeneous Discrete and DQMOM*/
#if 0
  SV_DIM_IMP_RP, /* real poles number */
  SV_DIM_IMP_CP, /* complex poles number */
#endif
  SV_DIM_DPM_Y_I,     /* number of dpm species from pdf models */
  SV_DIM_DPMS,        /* number of dpm species sources */
  SV_DIM_VMASS_VFLUX, /*virtual mass source for implicit*/
  SV_DIM_EROSION, /* number of wall erosion models */
  SV_DIM_LUMPS,   /* number of lump characteristics / properties */
  SV_DIM_SCR_UREA_DEPO_RISK_ANAL, /* SCR urea deposition risk analysis postprocessing variable array */
#if QUADRATIC_FIT_SCHEME || 1  /** TODO Remove || 1 when QUADRATIC_FIT_SCHEME is enabled on Windows */
  SV_DIM_QUAD_FIT_MATRIX,
#endif
  SV_DIM_RTDFT,
  SV_DIM_MOVING_AVG,

  SV_DIM_MAX

} SV_Dimension;

/* case SV_DIM_N_REAL: any storage that is a simple chunk of reals. */
#define SV_DIM_N_REAL SV_DIM_REAL: \
                 case SV_DIM_ND: \
                 case SV_DIM_ND_3: \
                 case SV_DIM_RST: \
                 case SV_DIM_ND_BY_ND: \
                 case SV_DIM_NSPE_SURF: \
                 case SV_DIM_NSPE_SITE: \
                 case SV_DIM_NSPE_SITE_AREA: \
                 case SV_DIM_NSPE_BY_NSPM: \
                 case SV_DIM_DO: \
                 case SV_DIM_DO_NBAND: \
                 case SV_DIM_UDM:\
                 case SV_DIM_NODE_UDM:\
                 case SV_DIM_EPDF:\
                 case SV_DIM_DPMS:\
                 case SV_DIM_LUMPS

/* case SV_DIM_N_REAL_NONSPE: any storage that is a simple chunk of reals, no
                              species svars */
#define SV_DIM_N_REAL_NONSPE SV_DIM_REAL: \
                 case SV_DIM_ND: \
                 case SV_DIM_ND_3: \
                 case SV_DIM_RST: \
                 case SV_DIM_ND_BY_ND: \
                 case SV_DIM_DO: \
                 case SV_DIM_DO_NBAND: \
                 case SV_DIM_UDM:\
                 case SV_DIM_NODE_UDM:\
                 case SV_DIM_EPDF:\
                 case SV_DIM_DPMS:\
                 case SV_DIM_LUMPS

/* comparison for SV_DIM_N_REAL */
#define IS_SV_DIM_N_REAL(sdim)\
   (sdim == SV_DIM_REAL || \
    sdim == SV_DIM_ND|| \
    sdim == SV_DIM_ND_3|| \
    sdim == SV_DIM_RST|| \
    sdim == SV_DIM_ND_BY_ND|| \
    sdim == SV_DIM_NSPE|| \
    sdim == SV_DIM_NSPE_ND|| \
    sdim == SV_DIM_NSPE_SURF|| \
    sdim == SV_DIM_NSPE_SITE|| \
    sdim == SV_DIM_NSPE_SITE_AREA|| \
    sdim == SV_DIM_NSPE_BY_NSPM|| \
    sdim == SV_DIM_DO|| \
    sdim == SV_DIM_DO_NBAND|| \
    sdim == SV_DIM_UDM || \
    sdim == SV_DIM_NODE_UDM || \
    sdim == SV_DIM_MANAGED || \
    sdim == SV_DIM_EPDF || \
    sdim == SV_DIM_DPMS || \
    sdim == SV_DIM_LUMPS )

/* comparison for SV_DIM_NS_REAL */
#define IS_SV_DIM_NSPE_REAL(sdim)\
   (sdim == SV_DIM_NSPE|| \
    sdim == SV_DIM_NSPE_ND)

/* change both in sync */
#define VAR_NAME_MAX_LEN 128
#define VAR_NAME_MAX_LEN_X2 256

typedef struct variable_attribute_struct
{
  Svar nv;
  char enumeration_name[32];
  char pick[VAR_NAME_MAX_LEN];
  char print_name[VAR_NAME_MAX_LEN];
  SV_Dimension dimension;

  int flags;

  void (*init)(Domain *, struct variable_attribute_struct *);
  SV_Store_Type (*store_type)(Thread *, Svar);
  int (*residual_p)(Domain *, struct variable_attribute_struct *, SV_Residual_Code );

  int residual_index;
  int data_section_id;
  int residual_section_id;
  int ns;
} Var_Attribute ;

#define SV_METHOD(sv,method)((sv)->method)

extern FLUENT_EXPORT int sv_unsteady_size;
extern FLUENT_EXPORT Svar sv_unsteady_index[][4];

extern FLUENT_EXPORT Var_Attribute sv_master[SV_MAX];
extern FLUENT_EXPORT Var_Attribute *sv_spe;
extern FLUENT_EXPORT Var_Attribute *sv_edc;
extern FLUENT_EXPORT Var_Attribute sv_pdf_tss[MAX_TSS_SCALAR_EQNS];
extern FLUENT_EXPORT Var_Attribute *sv_sootspecies;


enum
{
  SV_FL_DEFAULT    = 0x000000,  /* allocated temporary storage */
  SV_FL_PERMANENT  = 0x000001,  /* allocated permanent storage */
  SV_FL_PATCHABLE  = 0x000002,  /* can be patched */
  SV_FL_UNSTEADY   = 0x000004,  /* store previous time level(s) */
  SV_FL_SEG_VECTOR = 0x000010,  /* store as a segregated vector */
  SV_FL_PARENT     = 0x000020,  /* storage needed for parent */
  SV_FL_INTENSIVE  = 0x000100,  /* intensive property (size independent) */
  SV_FL_EXTENSIVE  = 0x000200,  /* extensive property (size dependent)   */
  SV_FL_AWEIGHTED  = 0x000400,  /* weighted by area vector, eg. flux     */
  SV_FL_NWEIGHTED  = 0x000800,  /* weighted by normal vector, eg, flux_m1 */
  SV_FL_NOINTERP   = 0x001000,  /* no interpolation, eg. nodes           */
  SV_FL_VOFINTERP  = 0x002000,  /* requires geometric interpolation, eg. vof */
  SV_FL_RESIDUAL   = 0x004000,  /* stores resiudal of a solved equation */
  SV_FL_DUAL       = 0x008000,  /* on dual thread */
  SV_FL_EXTRAPOLATE = 0X010000  /* need extrapolation */
};

#define PERMANENT_SV_P(sv)((sv)->flags & SV_FL_PERMANENT)
#define PATCHABLE_SV_P(sv)((sv)->flags & SV_FL_PATCHABLE)
#define UNSTEADY_SV_P(sv) ((sv)->flags & SV_FL_UNSTEADY)
#define SEGREGATED_VECTOR_SV_P(sv)((sv)->flags & SV_FL_SEG_VECTOR)
#define PARENT_SV_P(sv)   ((sv)->flags & SV_FL_PARENT)
#define DUAL_SV_P(sv)     ((sv)->flags & SV_FL_DUAL)
#define INTENSIVE_SV_P(sv)((sv)->flags & SV_FL_INTENSIVE)
#define EXTENSIVE_SV_P(sv)((sv)->flags & SV_FL_EXTENSIVE)
#define AWEIGHTED_SV_P(sv)((sv)->flags & SV_FL_AWEIGHTED)
#define NWEIGHTED_SV_P(sv)((sv)->flags & SV_FL_NWEIGHTED)
#define NOINTERP_SV_P(sv) ((sv)->flags & SV_FL_NOINTERP)
#define VOFINTERP_SV_P(sv)((sv)->flags & SV_FL_VOFINTERP)
#define RESIDUAL_SV_P(sv)(((sv)->flags) & SV_FL_RESIDUAL)
#define EXTRAPOLATE_SV_P(sv)(((sv)->flags) & SV_FL_EXTRAPOLATE)

#define NO_COPY_MESH_SVAR(_nv) ((_nv == SV_CELL || _nv == SV_FACE))

/* begin storage definition section */

/*
 * Parallel calls new_c() to build exterior cells before materials are
 * set.  This eventually invokes the FLUID_THREAD_P macro which
 * breaks if the thread material is not set.  A quick work-around
 * is to first check if the material is set.  If not, return TRUE if
 * thread storage for the variable in question has already been
 * allocated.
 */
#if PARALLEL
# define FLUID_THREAD_OR_STORAGE_P(t,nv) ((NULLP(THREAD_MATERIAL(t))) ? (NNULLP(THREAD_STORAGE(t,nv))) : FLUID_THREAD_P(t))
# define SOLID_THREAD_OR_STORAGE_P(t,nv) ((NULLP(THREAD_MATERIAL(t))) ? (NNULLP(THREAD_STORAGE(t,nv))) : SOLID_THREAD_P(t))
# define FLUID_CELL_THREAD_OR_STORAGE_P(t,nv) (CELL_THREAD_P(t) && FLUID_THREAD_OR_STORAGE_P(t,nv))
# define SOLID_CELL_THREAD_OR_STORAGE_P(t,nv) (CELL_THREAD_P(t) && SOLID_THREAD_OR_STORAGE_P(t,nv))
#else
# define FLUID_THREAD_OR_STORAGE_P(t,nv) FLUID_THREAD_P(t)
# define FLUID_CELL_THREAD_OR_STORAGE_P(t,nv) FLUID_CELL_THREAD_P(t)
# define SOLID_CELL_THREAD_OR_STORAGE_P(t,nv) SOLID_CELL_THREAD_P(t)
#endif

/* stringify the enumeration name
   sv:    storage var enum
   pick:  picking string
   name:  display name
   dim:   dimension enum for sizeof
   flag:  allocation flags?
   init:  initialization function pointer
   store:
   residual:
   eqn:   associated equation?
   xfd:   data id enum
 */

#define SV(sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
{sv,#sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr,0}


/* expand solution vars */

/* NOTE: enumeration_name is a char[32].  Take care not to exceed the allocated memory. */

#define SV_SOLUTION(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_F, pick"-f", "Filtered "name, SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", "Filtered "name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_ND, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL)

#if RP_FC
# define SV_SOLUTION_WITH_FC(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV_SOLUTION(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr), \
  \
  SV(sv##_ACFC, pick"-acfc", name" Fourier Coefficients", SV_DIM_ACFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_acfc, store, no_residual, \
     EQ_NULL, xfd##_ACFC, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PLFC, pick"-plfc", name" Fourier Coefficients", SV_DIM_PLFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_plfc, store, no_residual, \
     EQ_NULL, xfd##_PLFC, XF_RF_RESIDUAL_NULL)
# define SV_WITH_FC(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_ACFC, pick"-acfc", name" Fourier Coefficients", SV_DIM_ACFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_acfc, store, no_residual, \
     EQ_NULL, xfd##_ACFC, XF_RF_RESIDUAL_NULL)
#else
#define SV_SOLUTION_WITH_FC SV_SOLUTION
# define SV_WITH_FC(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr)
#endif

/*------------------- Unsteady Statistics --------------------------------------------- */
#define SV_CFF(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_REAL, \
   flag, init, store, residual, eqn, xfd##_MEAN, xfr), \
\
SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_REAL, \
   flag, init, store, residual, eqn, xfd##_RMS, xfr)
/* --------------------------------------------------------------------------------------*/

/*------------------- Statistics datasets--------------------------------------------- */
#define SV_STAT_DATASET(sv,pick,name,flag,init_mean_rmse,init_min,init_max,store,residual,eqn,xfd,xfr) \
SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_REAL, \
   flag, init_mean_rmse, store, residual, eqn, xfd##_MEAN, xfr), \
\
SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_REAL, \
   flag, init_mean_rmse, store, residual, eqn, xfd##_RMS, xfr), \
\
SV(sv##_MIN, pick"-min", name" min", SV_DIM_REAL, \
   flag, init_min, store, residual, eqn, xfd##_MIN, xfr), \
\
SV(sv##_MAX, pick"-max", name" max", SV_DIM_REAL, \
   flag, init_max, store, residual, eqn, xfd##_MAX, xfr)
/* --------------------------------------------------------------------------------------*/

/*------------------- Statistics segregated datasets for moving average----------------- */
#define SV_STAT_SEG_DATASET(sv,pick,name,dimension, flag,init,store,residual,eqn,xfd,xfr) \
SV(sv##_MOV_AVG, pick"-moving-avg", name" moving avg", dimension, \
   flag, init, store, residual, eqn, xfd##_MOV_AVG, xfr)
/* --------------------------------------------------------------------------------------*/

/* note: had to put SV_SOLUTION directly into this
 * to work around a hpux10p8 cpp bug */

#define SV_COUPLED_SOLUTION(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_F, pick"-f", name" Filtered", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", name" Filtered-Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_ND, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PR, pick"-pr", name" pr", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_pr, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WO, pick"-wo", name" wo", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DW, pick"-dw", name" dw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FW, pick"-fw", name" fw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WV, pick"-wv", name" wv", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WN, pick"-wn", name" wn", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_MEAN, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_RMS, XF_RF_RESIDUAL_NULL)

#define SV_COUPLED_SOLUTION_STRUCTURE(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE | SV_FL_NOINTERP, init_disp_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DOT1, pick"-dot1", name" dot1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE | SV_FL_NOINTERP, init_disp_m1, store, residual, \
     EQ_NULL, xfd##_DOT1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DOT1_M1, pick"-dot1-m1", name" dot1 m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE | SV_FL_NOINTERP, init_disp_m1, store, residual, \
     EQ_NULL, xfd##_DOT1_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DOT2, pick"-dot2", name" dot2", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE | SV_FL_NOINTERP, init_disp_m1, store, residual, \
     EQ_NULL, xfd##_DOT2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DOT2_M1, pick"-dot2-m1", name" dot2 m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE | SV_FL_NOINTERP, init_disp_m1, store, residual, \
     EQ_NULL, xfd##_DOT2_M1, XF_RF_RESIDUAL_NULL)

#define SV_COUPLED_SOLUTION_SPE(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_NSPE, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_NSPE_ND, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_NSPE_ND, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_NSPE_ND, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_NSPE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, init_solution_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_NSPE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, init_solution_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_F, pick"-f", name" Filtered", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", name" Filtered-Gradient", SV_DIM_NSPE_ND, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_NSPE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_dim_vector, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PR, pick"-pr", name" pr", SV_DIM_NSPE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, init_solution_pr, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WO, pick"-wo", name" wo", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DW, pick"-dw", name" dw", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FW, pick"-fw", name" fw", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WV, pick"-wv", name" wv", SV_DIM_NSPE, \
     SV_FL_DEFAULT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, NULL, store, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WN, pick"-wn", name" wn", SV_DIM_NSPE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_NSPE_AVE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, zero_init_dim_vector, store, residual, \
     EQ_NULL, xfd##_MEAN, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_NSPE_AVE, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, zero_init_dim_vector, store, residual, \
     EQ_NULL, xfd##_RMS, XF_RF_RESIDUAL_NULL)

#if RP_FC
# define SV_COUPLED_SOLUTION_WITH_FC(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_F, pick"-f", name" Filtered", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", name" Filtered-Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_ND, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PR, pick"-pr", name" pr", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_pr, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WO, pick"-wo", name" wo", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DW, pick"-dw", name" dw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FW, pick"-fw", name" fw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WV, pick"-wv", name" wv", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WN, pick"-wn", name" wn", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_MEAN, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_RMS, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_ACFC, pick"-acfc", name" Fourier Coefficients", SV_DIM_ACFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_acfc, store, no_residual, \
     EQ_NULL, xfd##_ACFC, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PLFC, pick"-plfc", name" Fourier Coefficients", SV_DIM_PLFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_plfc, store, no_residual, \
     EQ_NULL, xfd##_PLFC, XF_RF_RESIDUAL_NULL)

# define SV_COUPLED_SOLUTION_WITH_BFC(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_REAL, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_F, pick"-f", name" Filtered", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", name" Filtered-Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_ND, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PR, pick"-pr", name" pr", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, init_solution_pr, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WO, pick"-wo", name" wo", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_DW, pick"-dw", name" dw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FW, pick"-fw", name" fw", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WV, pick"-wv", name" wv", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, NULL, store, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_WN, pick"-wn", name" wn", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_MEAN, pick"-mean", name" mean", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_MEAN, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RMS, pick"-rms", name" rms", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_INTENSIVE, zero_init_scalar, store, residual, \
     EQ_NULL, xfd##_RMS, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_ACFC, pick"-acfc", name" Fourier Coefficients", SV_DIM_ACFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_acfc, store, no_residual, \
     EQ_NULL, xfd##_ACFC, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_BCFC, pick"-bcfc", name" Fourier Coefficients", SV_DIM_BCFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_bcfc, store, no_residual, \
     EQ_NULL, xfd##_BCFC, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_PLFC, pick"-plfc", name" Fourier Coefficients", SV_DIM_PLFC, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, init_plfc, store, no_residual, \
     EQ_NULL, xfd##_PLFC, XF_RF_RESIDUAL_NULL)
#else
# define SV_COUPLED_SOLUTION_WITH_FC SV_COUPLED_SOLUTION
# define SV_COUPLED_SOLUTION_WITH_BFC SV_COUPLED_SOLUTION
#endif


#define SV_I(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv##_##i, pick"-"num, "Phase "num" "name, dim, \
     flag, init, store, residual, \
     eqn+i, xfd##i, xfr##i)

#define SV_I_AP(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_AP,pick"-"num"-ap","Phase "num" "name" ap", dim, \
     flag, init, store, residual, \
     eqn, xfd, xfr)

#define SV_I_S(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_S,pick"-"num"-s","Phase "num" "name" s", dim, \
     flag, init, store, residual, \
     eqn, xfd, xfr)

#define SV_I_G(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_G,pick"-"num"-g","Phase "num" "name" g", dim, \
     flag, init, store, residual, \
     eqn, xfd, xfr)

#define SV_I_RG(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_RG,pick"-"num"-rg","Phase "num" "name" rg", dim, \
     flag, init, store, residual, \
     eqn, xfd, xfr)

#define SV_I_RG_AUX(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_RG_AUX,pick"-"num"-rg-aux","Phase "num" "name" rg Auxiliary", dim, \
     flag, init, store, residual, \
     eqn, xfd, xfr)

#define SV_I_M1(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_M1,pick"-"num"-m1","Phase "num" "name" m1", dim, \
     flag, init, store, residual, \
     eqn, xfd##i##_M1, xfr)

#define SV_I_M2(i,num,sv,pick,name,dim,flag,init,store,residual,eqn,xfd,xfr) \
 SV(sv##_##i##_M2,pick"-"num"-m2","Phase "num" "name" m2", dim, \
     flag, init, store, residual, \
     eqn, xfd##i##_M2, xfr)




#define SV_EPDF_VAR(sv,pick,name,flag,init,store,residual,eqn,xfd,xfr) \
  SV(sv, pick, name, SV_DIM_EPDF, \
     flag, init, store, residual, \
     eqn, xfd, xfr), \
  \
  SV(sv##_F, pick"-f", "Filtered "name, SV_DIM_EPDF, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_AP, pick"-ap", name" Ap", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_S, pick"-s", name" Source", SV_DIM_REAL, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_G, pick"-g", name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_FG, pick"-fg", "Filtered "name" Gradient", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG, pick"-rg", name" Reconstruction", SV_DIM_ND, \
     SV_FL_DEFAULT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_RG_AUX, pick"-rg-aux", name" Reconstruction Auxiliary", SV_DIM_ND, \
     SV_FL_PERMANENT | SV_FL_NOINTERP, no_init, store, residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M1, pick"-m1", name" m1", SV_DIM_EPDF, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, init_solution_epdf_m1, store, residual, \
     EQ_NULL, xfd##_M1, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_M2, pick"-m2", name" m2", SV_DIM_EPDF, \
     SV_FL_PERMANENT | SV_FL_SEG_VECTOR | SV_FL_INTENSIVE, init_solution_epdf_m2, store, residual, \
     EQ_NULL, xfd##_M2, XF_RF_RESIDUAL_NULL), \
  \
  SV(sv##_R, pick"-residual", name" Residual", SV_DIM_REAL, \
     SV_FL_PERMANENT | SV_FL_NOINTERP | SV_FL_RESIDUAL, zero_init_scalar, store_residual, no_residual, \
     EQ_NULL, XF_RF_DATA_NULL, XF_RF_RESIDUAL_NULL)

/* ------------Unsteady Stat-------------------------- */
#define EXPAND_MACRO_CFF_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9"),m(10,"10")
#define EXPAND_MACRO_CFF_TIMES_b(m) \
  m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),m(15,"15"),\
  m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19"),m(20,"20")
#define EXPAND_MACRO_CFF_TIMES_c(m) \
  m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),m(25,"25"),\
  m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29"),m(30,"30")
#define EXPAND_MACRO_CFF_TIMES_d(m) \
  m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),m(35,"35"),\
  m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39"),m(40,"40")
#define EXPAND_MACRO_CFF_TIMES_e(m) \
  m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),m(45,"45"),\
  m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
/* ---------------------------------------------------- */

/* ------------Statistics dataset-------------------------- */
#define EXPAND_MACRO_STAT_DATASET_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9"),m(10,"10")
#define EXPAND_MACRO_STAT_DATASET_TIMES_b(m) \
  m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),m(15,"15"),\
  m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19"),m(20,"20")
#define EXPAND_MACRO_STAT_DATASET_TIMES_c(m) \
  m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),m(25,"25"),\
  m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29"),m(30,"30")
#define EXPAND_MACRO_STAT_DATASET_TIMES_d(m) \
  m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),m(35,"35"),\
  m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39"),m(40,"40")
#define EXPAND_MACRO_STAT_DATASET_TIMES_e(m) \
  m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),m(45,"45"),\
  m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
/* ---------------------------------------------------- */

/* note: had to put SV_SOLUTION directly into this*/


#define EXPAND_MACRO_NSPE_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_NSPE_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_NSPE_TIMES_c(m) \
  m(20,"20"),m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),\
  m(25,"25"),m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29")
#define EXPAND_MACRO_NSPE_TIMES_d(m) \
  m(30,"30"),m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),\
  m(35,"35"),m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39")
#define EXPAND_MACRO_NSPE_TIMES_e(m) \
  m(40,"40"),m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),\
  m(45,"45"),m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
#define EXPAND_MACRO_NSPE_TIMES(m) \
  EXPAND_MACRO_NSPE_TIMES_a(m), EXPAND_MACRO_NSPE_TIMES_b(m), \
  EXPAND_MACRO_NSPE_TIMES_c(m), EXPAND_MACRO_NSPE_TIMES_d(m), \
  EXPAND_MACRO_NSPE_TIMES_e(m)

#define EXPAND_MACRO_NPROB_TIMES(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")

/* HP compiler bug: cpp is dying. Have to split this up. */
#define EXPAND_MACRO_NUDS_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_NUDS_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_NUDS_TIMES_c(m) \
  m(20,"20"),m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),\
  m(25,"25"),m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29")
#define EXPAND_MACRO_NUDS_TIMES_d(m) \
  m(30,"30"),m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),\
  m(35,"35"),m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39")
#define EXPAND_MACRO_NUDS_TIMES_e(m) \
  m(40,"40"),m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),\
  m(45,"45"),m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")

/* HP compiler bug: cpp is dying. Have to split this up. */
#define EXPAND_MACRO_NPB_DISC_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_NPB_DISC_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_NPB_DISC_TIMES_c(m) \
  m(20,"20"),m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),\
  m(25,"25"),m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29")
#define EXPAND_MACRO_NPB_DISC_TIMES_d(m) \
  m(30,"30"),m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),\
  m(35,"35"),m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39")
#define EXPAND_MACRO_NPB_DISC_TIMES_e(m) \
  m(40,"40"),m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),\
  m(45,"45"),m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
#define EXPAND_MACRO_NPB_QMOM_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_NPB_QMOM_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_NPB_QMOM_TIMES_c(m) \
  m(20,"20"),m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),\
  m(25,"25"),m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29")
#define EXPAND_MACRO_NPB_QMOM_TIMES_d(m) \
  m(30,"30"),m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),\
  m(35,"35"),m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39")
#define EXPAND_MACRO_NPB_QMOM_TIMES_e(m) \
  m(40,"40"),m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),\
  m(45,"45"),m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
#define EXPAND_MACRO_NPB_SMM_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_NPB_SMM_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_NPB_SMM_TIMES_c(m) \
  m(20,"20"),m(21,"21"),m(22,"22"),m(23,"23"),m(24,"24"),\
  m(25,"25"),m(26,"26"),m(27,"27"),m(28,"28"),m(29,"29")
#define EXPAND_MACRO_NPB_SMM_TIMES_d(m) \
  m(30,"30"),m(31,"31"),m(32,"32"),m(33,"33"),m(34,"34"),\
  m(35,"35"),m(36,"36"),m(37,"37"),m(38,"38"),m(39,"39")
#define EXPAND_MACRO_NPB_SMM_TIMES_e(m) \
  m(40,"40"),m(41,"41"),m(42,"42"),m(43,"43"),m(44,"44"),\
  m(45,"45"),m(46,"46"),m(47,"47"),m(48,"48"),m(49,"49")
#define EXPAND_MACRO_5_TIMES(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4")

#define EXPAND_MACRO_10_TIMES_a(m) \
  m(0,"0"),m(1,"1"),m(2,"2"),m(3,"3"),m(4,"4"),\
  m(5,"5"),m(6,"6"),m(7,"7"),m(8,"8"),m(9,"9")
#define EXPAND_MACRO_10_TIMES_b(m) \
  m(10,"10"),m(11,"11"),m(12,"12"),m(13,"13"),m(14,"14"),\
  m(15,"15"),m(16,"16"),m(17,"17"),m(18,"18"),m(19,"19")
#define EXPAND_MACRO_20_TIMES(m) \
  EXPAND_MACRO_10_TIMES_a(m), EXPAND_MACRO_10_TIMES_b(m)
#define EXPAND_MACRO_DPM_MATERIAL_TIMES EXPAND_MACRO_20_TIMES
/* end storage definition section */


/************************************************************************
 * storage.c prototypes
 ************************************************************************/

/*
 * alloc/update storage
 */
FLUENT_EXPORT void alloc_thread_sv(Thread *t, Var_Attribute *sv);
FLUENT_EXPORT void alloc_temporary_thread_sv_for_io(Thread *t, Var_Attribute *sv);
FLUENT_EXPORT void Alloc_Thread_Storage_Vars(Thread *, ...);
FLUENT_EXPORT void MD_Alloc_Thread_Storage_Vars(Thread *, ...);
FLUENT_EXPORT void Alloc_Storage_Vars(Domain *, ...);
FLUENT_EXPORT void MD_Alloc_Storage_Vars(Domain *, ...);

FLUENT_EXPORT void Alloc_Thread_Storage(Thread *, const int);

FLUENT_EXPORT void update_thread_storage(Thread *);
FLUENT_EXPORT void update_shell_thread_storage(Thread *);
FLUENT_EXPORT void md_update_thread_storage(Domain *, const int);
FLUENT_EXPORT void Update_Storage(Domain *);
FLUENT_EXPORT void Update_Storage_After_Solver_Changed(Domain *);
FLUENT_EXPORT void Update_Node_Storage (Domain *);
FLUENT_EXPORT void Update_Shared_Storage_Vars (Domain *, ...);
FLUENT_EXPORT void Null_Thread_Storage(Thread *);
#if RP_NODE && RP_HANG
FLUENT_EXPORT void Merge_Storage_Layers (Domain *);
#endif

/*
 * free storage
 */
FLUENT_EXPORT void free_thread_sv(Thread *t, Var_Attribute *sv);
FLUENT_EXPORT void free_temporary_thread_sv_for_io(Thread *t, Var_Attribute *sv);
FLUENT_EXPORT void Free_Thread_Storage(Thread *);
FLUENT_EXPORT void Free_Thread_Storage_Vars(Thread *, ...);
FLUENT_EXPORT void Free_Storage_Vars(Domain *, ...);
FLUENT_EXPORT void MD_Free_Storage_Vars(Domain *, ...);
FLUENT_EXPORT void VOF_G_Free_Storage_Vars(Domain *, ...);

FLUENT_EXPORT void MD_Free_Thread_Storage_Vars(Thread *, ...);
FLUENT_EXPORT void MD_Free_Thread_Storage(Thread *thread);
FLUENT_EXPORT void MD_Alloc_Thread_Storage(Thread *thread, const int length);

/*
 * initialize storage
 */
FLUENT_EXPORT void Initialize_Storage_Var(Domain *, Svar nv);
FLUENT_EXPORT void Initialize_Storage_Vars(Domain *, ...);
FLUENT_EXPORT void Initialize_Storage(Domain *);

/*
 * mark storage as un-initialized
 */
FLUENT_EXPORT void Uninitialize_Storage_Var(Domain *, Svar nv);
FLUENT_EXPORT void Uninitialize_Storage_Vars(Domain *, ...);
FLUENT_EXPORT void Uninitialize_Storage(Domain *);
FLUENT_EXPORT void Reset_Init_Flag(Domain *);
/*
 * storage compaction
 */
FLUENT_EXPORT void Compact_Storage(Domain *);
FLUENT_EXPORT void Display_Storage(Domain *);
FLUENT_EXPORT void Display_Shared_Storage(Domain *);
#if RP_TOUCH_MEMORY
FLUENT_EXPORT void Delete_Untouched_Storage(Domain *);
FLUENT_EXPORT void Display_Untouched_Storage(Domain *);
#endif
FLUENT_EXPORT void Display_Constant_Storage(Domain *);
FLUENT_EXPORT void Display_Infinite_Storage(Domain *);
FLUENT_EXPORT void Minimize_Storage(Domain *);
FLUENT_EXPORT void compact_thread_storage(Thread *);
FLUENT_EXPORT void Compact_Memory_Blocks (Domain *, cxboolean);
FLUENT_EXPORT void Set_Compact_Memory_Blocks_Dual_Faces (cxboolean);

FLUENT_EXPORT void Display_Thread_SV(Thread *, Var_Attribute *, char *);
FLUENT_EXPORT void Display_Thread_SV_Data(Thread *, Var_Attribute *);
FLUENT_EXPORT cxboolean Is_Target_Variable(Store *s);

FLUENT_EXPORT Var_Attribute *Lookup_SV_By_Enumeration_Name(const char *);
FLUENT_EXPORT Var_Attribute *Lookup_SV_By_Pick_Name(const char *);
#if !RP_NODE
FLUENT_EXPORT void Mark_Svars_with_Suffix(cxboolean _svar[], const char *suffix, cxboolean verbosity, char *message, cxboolean deflt);
#endif
FLUENT_EXPORT size_t malloc_storage(Thread *t, Var_Attribute *sv, size_t nbytes_request, int dimension);
FLUENT_EXPORT size_t realloc_storage(Thread *t, Var_Attribute *sv, size_t nbytes_request, int dimension);

#if 0 /* Not used */
FLUENT_EXPORT void Allocate_Node_Storage (int *, ...);
FLUENT_EXPORT void Deallocate_Node_Storage (int *, ...);
#endif

/*
 * various `store_type', `residual_p', `init' functions:
 */
FLUENT_EXPORT void map_compacted_offset(Domain *);
FLUENT_EXPORT cxboolean if_fluid_cell(Thread *t, Svar nv);
FLUENT_EXPORT cxboolean if_fluid_face(Thread *t, Svar nv);
FLUENT_EXPORT cxboolean if_interior_fluid_face(Thread *t, Svar nv);
FLUENT_EXPORT cxboolean if_porous_interfaces(Thread *t, Svar nv);
FLUENT_EXPORT cxboolean if_porous_medium(Thread *t, Svar nv);
FLUENT_EXPORT SV_Store_Type store_fluid_cell(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_fluid_cell_self(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_fluid_face(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cell(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cell_or_face(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cell_or_boundaryface(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_face(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_face_out(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_boundary_face(Thread *, Svar);
FLUENT_EXPORT SV_Store_Type store_node(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cnz(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_fnz(Thread *t, Svar n);
#if USE_FEMCORE
FLUENT_EXPORT SV_Store_Type store_cinz(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_finz(Thread *t, Svar n);
#endif
FLUENT_EXPORT SV_Store_Type store_node_face(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_all(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_shared(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cell_shared(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_face_shared(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_cell_face_shared(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_node_shared(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_shared_or_atsubdomain(Thread *t, Svar n, cxboolean shared_p);
FLUENT_EXPORT SV_Store_Type store_wall_shared_or_subdomain(Thread *t, Svar n, cxboolean shared_p);
FLUENT_EXPORT  SV_Store_Type store_at_subdomain(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_shared_or_self(Thread *t, Svar n, cxboolean shared_p);
FLUENT_EXPORT SV_Store_Type store_cell_or_lbface(Thread *t, Svar n);
FLUENT_EXPORT SV_Store_Type store_type(Thread *, Var_Attribute *);


FLUENT_EXPORT SV_Store_Type store_residual(Thread *t, Svar n);

FLUENT_EXPORT cxboolean no_residual(Domain *, Var_Attribute *, SV_Residual_Code);

FLUENT_EXPORT void const_init_thread_storage(Thread *thread, Svar sv, int len, real *w);
FLUENT_EXPORT void zero_init_thread_real_storage(Thread *thread, Svar sv);
FLUENT_EXPORT void pntr_init_thread_storage(Thread *thread, Svar sv, int len, void **w);
FLUENT_EXPORT int const_init(Domain *domain, Var_Attribute *sv, int len, real *w, int ok_to_set_init);
FLUENT_EXPORT int const_int_init(Domain *domain, Var_Attribute *sv, int len, int *w, int ok_to_set_init);
FLUENT_EXPORT int pntr_init(Domain *domain, Var_Attribute *sv, int len, void **w, int ok_to_set_init);
FLUENT_EXPORT void no_init(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_props(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_solution_m1(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_solution_m2(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_solution_epdf_m1(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_solution_epdf_m2(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_solution_pr(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_porosity(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_porosity_m1(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_porosity_m2(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_init_scalar(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_int_init_scalar(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void min_init_scalar(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void max_init_scalar(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_init_vector(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT int  zero_check_vector(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_init_vector_gradient(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_scalar(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_vector(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_init_dim_vector(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void zero_dim_vector(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void null_pointer(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void null_init_pointer(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_sootspecies_mn_array(Domain *domain, const Svar nv, const Svar nv_0, const Svar nv_mn, const Svar nv_0_mn);
#if RP_FC
FLUENT_EXPORT void init_acfc(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_bcfc(Domain *domain, Var_Attribute *sv);
FLUENT_EXPORT void init_plfc(Domain *domain, Var_Attribute *sv);
#endif

FLUENT_EXPORT void Copy_Thread_Svar_Data(Thread *thread, Svar from_sv, Svar to_sv);
FLUENT_EXPORT void Copy_Svar_Data       (Domain *domain, Svar from_sv, Svar to_sv);
FLUENT_EXPORT void Copy_Svar_Cell_Data  (Domain *domain, Svar from_sv, Svar to_sv);
FLUENT_EXPORT void Copy_Svar_Face_Data  (Domain *domain, Svar from_sv, Svar to_sv);

FLUENT_EXPORT void init_flags(Domain *domain, Var_Attribute *sv);

FLUENT_EXPORT void Set_SV_Initialized(Thread *, Svar, cxboolean);
FLUENT_EXPORT cxboolean SV_Initialized_P(Thread *, Svar);

#define SV_INITIALIZED_P SV_Initialized_P
#define SET_SV_INITIALIZED Set_SV_Initialized

/* shared by 'pressure' and 'grannular_pressure' Svars */
FLUENT_EXPORT SV_Store_Type store_pressure_var(Thread *t, Svar nv, cxboolean mixture_var);
FLUENT_EXPORT cxboolean residual_pressure(Domain *, Var_Attribute *, SV_Residual_Code);

/*
 * Var_Attribute (sv_master) interrogation/management utilities:
 */
FLUENT_EXPORT size_t SV_Size(Var_Attribute *, Thread *);
FLUENT_EXPORT void SV_Check_Master(void);
FLUENT_EXPORT void SV_Register_Definition(Var_Attribute *var, int nvar);
FLUENT_EXPORT int Count_Unique_Svars_Incl(Svar **svar_list, Svar nv1, ...);
FLUENT_EXPORT int Append_Svars_To_List(Svar **to, int l1, Svar nv1, ...);

FLUENT_EXPORT cxboolean Is_RG_Svar(Svar);

/*
 * Eqn labels
 */
FLUENT_EXPORT void Init_Eqn_Labels(Domain *);

#define ALLOCATE_NODE_SVAR(node_thread, svar)          \
  {                  \
                       \
    cxboolean svar##_free_n_sv = FALSE;          \
    if (!SV_ALLOCATED_P_NEW (node_thread, svar)) {         \
      Alloc_Thread_Storage_Vars (node_thread, svar, SV_NULL);    \
      svar##_free_n_sv = TRUE;               \
    }

#define DEALLOCATE_NODE_SVAR(node_thread, svar)          \
  if (svar##_free_n_sv)              \
    Free_Thread_Storage_Vars (node_thread, svar, SV_NULL);     \
                       \
  }

#if 0 && !UDF_COMPILER /* not needed anymore */
/* variadic macros aren't supported on aix51_64 */
# if sys_aix51_64
#  define ALLOCATE_NODE_SVARS(args)                 \
    {               \
      int svTest[3] = {0};          \
      Allocate_Node_Storage(svTest, args)           \

#  define DEALLOCATE_NODE_SVARS(args)               \
      Deallocate_Node_Storage(svTest, args);        \
    }
# else
#  define ALLOCATE_NODE_SVARS(...)                  \
    {               \
      int svTest[3] = {0};          \
      Allocate_Node_Storage(svTest, __VA_ARGS__)    \

#  define DEALLOCATE_NODE_SVARS(...)                \
      Deallocate_Node_Storage(svTest, __VA_ARGS__); \
    }
# endif
#endif /* !UDF_COMPILER */

FLUENT_EXPORT void Allocate_Storage_If_Any(Thread *, size_t);
FLUENT_EXPORT int Get_SVar_Index(const char *var);
FLUENT_EXPORT int Save_Domain_Residual(Domain *domain, Svar sv);
#endif /* _FLUENT_STORAGE_H */

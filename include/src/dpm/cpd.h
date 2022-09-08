/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/* Header file for the CPD devolatilization model */
/* flag: coal_cpd */

#define ab_cpd      2.602e+15  /* 1/s */
#define eb0_cpd     2.3179e+08 /* J/KMole */
#define ebsig_cpd   7.5312e+06

#define ac_cpd      0.9
#define ec0_cpd     0.0

#define ag_cpd      3.e+15
#define eg0_cpd     2.88696e+08
#define egsig_cpd   3.389e+07
#define acr_cpd     3.e+15
#define ecr_cpd     2.7196e+08
#define afl_cpd     8.8213545e+09  /* Pa */
#define bfl_cpd     299.
#define gfl_cpd     0.590

#define smal1_cpd   1.e-5
#define small_cpd   5.e-4
#define SMALL_cpd   1.e-3
#define ZERO_cpd    0.
#define nmax_cpd    20


/*cpd model function prototypes */
static void perks (Tracked_Particle *tp);
static real inverf(real y);
static void perkp (Tracked_Particle *tp);
static void flash (Tracked_Particle *tp);
static void rachford_rice(int ntot, real zf[], real kf[], Tracked_Particle *tp);
static real gamln (real x);


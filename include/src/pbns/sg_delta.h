/*
 * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SG_DELTA
#define _FLUENT_SG_DELTA

#include "global.h"
#include "mem.h"

typedef enum delta_form_enum
{
  DELTA_FORM_DISABLED = 0,
  DELTA_FORM_ENABLED
} Delta_Form;

#define DIRECT_DELTA_FORM_P ((momentum_delta_form && !delta_form_post_discretization) ? DELTA_FORM_ENABLED : DELTA_FORM_DISABLED)

/**
  * ADD_C_SRC_PATANKAR and ADD_C_SRC_FULL are equivalent.
  * You can choose based on preference.
  * ADD_C_SRC_PATANKAR takes the source components
  * Sc and Sp as parameters separately as in Patankar's book.
  * ADD_C_SRC_FULL takes the full source Scfull
  * and the linearization coefficient Sp as parameters.
  * This is the notation used in DEFINE_SOURCE udfs
  * and is more convenient for direct delta form discretization.
  * Both macros will respect the Delta_Form parameter and
  * handle both situations correctly.
  */

#define ADD_C_SRC_PATANKAR(_c, _Sc, _Sp, _sv_p_s_, _sv_p_ap_, _sv_p_, _df) \
{ \
  real * _sv_p_ap = (real *)(_sv_p_ap_); \
  real * _sv_p_s = (real *)(_sv_p_s_); \
  real * _sv_p = (real *)(_sv_p_); \
  \
  if ((_df == DELTA_FORM_ENABLED)) \
  { \
    if ((_Sp) < 0.0) \
    { \
      (_sv_p_ap)[(_c)] += (_Sp); \
    } \
    (_sv_p_s)[(_c)] += (_Sc) + (_Sp) * (_sv_p)[(_c)]; \
  } \
  else \
  { \
    if ((_Sp) < 0.0) \
    { \
      (_sv_p_ap)[(_c)] += (_Sp); \
      (_sv_p_s)[(_c)] += (_Sc); \
    } \
    else \
    { \
      (_sv_p_s)[(_c)] += (_Sc); \
      if (NNULLP(_sv_p)) \
        (_sv_p_s)[(_c)] += (_Sp) * (_sv_p)[(_c)]; \
    } \
  } \
}

#define ADD_C_SRC_FULL(_c, _Scfull, _Sp, _sv_p_s_, _sv_p_ap_, _sv_p_, _df) \
{ \
  real * _sv_p_ap = (real *)(_sv_p_ap_); \
  real * _sv_p_s = (real *)(_sv_p_s_); \
  real * _sv_p = (real *)(_sv_p_); \
  \
  if ((_df == DELTA_FORM_ENABLED)) \
  { \
    if ((_Sp) < 0.0) \
    { \
      (_sv_p_ap)[(_c)] += (_Sp); \
    } \
    (_sv_p_s)[(_c)] += (_Scfull); \
  } \
  else \
  { \
    if ((_Sp) < 0.0) \
    { \
      (_sv_p_ap)[(_c)] += (_Sp); \
      (_sv_p_s)[(_c)] += (_Scfull) - (_Sp) * (_sv_p)[(_c)]; \
    } \
    else \
    { \
      (_sv_p_s)[(_c)] += (_Scfull); \
    } \
  } \
}

#define ADD_C_SRC_NO_LIN(_c, _Sfull, _sv_p_s_) \
{ \
  real * _sv_p_s = (real *)(_sv_p_s_); \
  (_sv_p_s)[(_c)] += (_Sfull); \
}

#define ADD_SOURCE_AND_COEFF_NO_LIN(_c, _Sc, _Sp, _sv_p_ap_, _sv_p_s_, _sv_p_, _df) \
{ \
  real * _sv_p_s = (real *)(_sv_p_s_); \
  real * _sv_p_ap = (real *)(_sv_p_ap_); \
  real * _sv_p = (real *) (_sv_p_); \
  (_sv_p_s)[(_c)] += (_Sc); \
  if (_Sp < 0.0) \
    (_sv_p_ap)[(_c)] += (_Sp); \
  if ((_df == DELTA_FORM_ENABLED)) \
    (_sv_p_s)[(_c)] += (_Sp) * (_sv_p)[(_c)]; \
}



#define C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s0)  \
{                                                             \
  (_u_s0)[(_c0)] += (_coeff) * ((_u1)[(_c1)] - (_u0)[(_c0)]); \
}
#define C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s1)  \
{                                                             \
  (_u_s1)[(_c1)] -= (_coeff) * ((_u1)[(_c1)] - (_u0)[(_c0)]); \
}

#define C0_DISCRETIZE_SRC_RM(_coeff0, _coeff1, _c0, _c1, _u0, _u1, _u_s0) \
{                                                                         \
  (_u_s0)[(_c0)] += (_coeff1) * (_u1)[(_c1)] - (_coeff0) * (_u0)[(_c0)];  \
}
#define C1_DISCRETIZE_SRC_RM(_coeff0, _coeff1, _c0, _c1, _u0, _u1, _u_s1) \
{                                                                         \
  (_u_s1)[(_c1)] -= (_coeff1) * (_u1)[(_c1)] - (_coeff0) * (_u0)[(_c0)];  \
}

#define C0_DISCRETIZE_SRC_COUNTER_DIFFUSION(_coeffn, _coeff, _c0, _c1, _u0, _u1, _u_s0)  \
{                                                             \
  (_u_s0)[(_c0)] += ((_coeffn) * (_u1)[(_c1)] - (_coeff) * (_u0)[(_c0)]); \
}
#define C1_DISCRETIZE_SRC_COUNTER_DIFFUSION(_coeffn, _coeff, _c0, _c1, _u0, _u1, _u_s1)  \
{                                                             \
  (_u_s1)[(_c1)] -= ((_coeffn) * (_u1)[(_c1)] - (_coeff) * (_u0)[(_c0)]); \
}

#if RP_3D
#define C0_DISCRETIZE_ND_VEC_SRC(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
{                                                      \
  C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s0) \
  C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _v0, _v1, _v_s0) \
  C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _w0, _w1, _w_s0) \
}
#define C1_DISCRETIZE_ND_VEC_SRC(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
{                                                      \
  C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s1) \
  C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _v0, _v1, _v_s1) \
  C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _w0, _w1, _w_s1) \
}
#else
#define C0_DISCRETIZE_ND_VEC_SRC(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
{                                                      \
  C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s0) \
  C0_DISCRETIZE_SRC(_coeff, _c0, _c1, _v0, _v1, _v_s0) \
}
#define C1_DISCRETIZE_ND_VEC_SRC(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
{                                                      \
  C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _u0, _u1, _u_s1) \
  C1_DISCRETIZE_SRC(_coeff, _c0, _c1, _v0, _v1, _v_s1) \
}
#endif

#if RP_3D
#define FILL_ANB_MOM(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
  {                                                                     \
    if (amg_id == AMG_SCALAR)                                           \
      {                                                                 \
        F_COEFF_01(f,t) = (coeff_01);                                   \
        F_COEFF_10(f,t) = (coeff_10);                                   \
        if (DIRECT_DELTA_FORM_P)                                        \
        {                                                               \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
        }                                                               \
      }                                                                 \
    else if (amg_id == AMG_PVT)                                         \
      {                                                                 \
        if (amg_i >= 0) /* mp-mfluid */                                 \
          {                                                             \
            int const i = amg_i;                                        \
            if(!amg_mp_coupled)                                         \
              {                                                         \
                MATRIX(F_A01(f,t),i,i,mp_n) = (coeff_01);               \
                MATRIX(F_A10(f,t),i,i,mp_n) = (coeff_10);               \
                if (DIRECT_DELTA_FORM_P)                                \
                {                                                       \
                  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
                  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
                }                                                       \
              }                                                         \
            else                                                        \
              {                                                         \
                int ju = W_U + amg_i;                                   \
                int jv = W_U + mp_n + amg_i;                            \
                int jw = W_U + 2*mp_n + amg_i;                          \
                int coupled_set = BAMG_BLK_SIZE(amg_id);                \
                MATRIX(F_A01(f,t),ju,ju,coupled_set) = (coeff_01);      \
                MATRIX(F_A10(f,t),ju,ju,coupled_set) = (coeff_10);      \
                MATRIX(F_A01(f,t),jv,jv,coupled_set) = (coeff_01);      \
                MATRIX(F_A10(f,t),jv,jv,coupled_set) = (coeff_10);      \
                MATRIX(F_A01(f,t),jw,jw,coupled_set) = (coeff_01);      \
                MATRIX(F_A10(f,t),jw,jw,coupled_set) = (coeff_10);      \
                if (DIRECT_DELTA_FORM_P)                                \
                {                                                       \
                  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
                  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
                }                                                       \
              }                                                         \
          }                                                             \
        else                                                            \
          {                                                             \
            int neq = BAMG_BLK_SIZE(amg_id);                            \
            MATRIX(F_A01(f,t),W_U,W_U,neq) = (coeff_01);                \
            MATRIX(F_A10(f,t),W_U,W_U,neq) = (coeff_10);                \
            MATRIX(F_A01(f,t),W_V,W_V,neq) = (coeff_01);                \
            MATRIX(F_A10(f,t),W_V,W_V,neq) = (coeff_10);                \
            MATRIX(F_A01(f,t),W_W,W_W,neq) = (coeff_01);                \
            MATRIX(F_A10(f,t),W_W,W_W,neq) = (coeff_10);                \
            if (DIRECT_DELTA_FORM_P)                                    \
            {                                                           \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
            }                                                           \
          }                                                             \
      }                                                                 \
    else                                                                \
      Internal_Error("unknown amg solver id");                          \
  }
#else /* RP_2D */
#define FILL_ANB_MOM(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
  {                                                                     \
    if (amg_id == AMG_SCALAR)                                           \
      {                                                                 \
        F_COEFF_01(f, t) = (coeff_01);                                  \
        F_COEFF_10(f, t) = (coeff_10);                                  \
        if (DIRECT_DELTA_FORM_P)                                        \
        {                                                               \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
        }                                                               \
      }                                                                 \
    else if (amg_id == AMG_PVT)                                         \
      {                                                                 \
        if (amg_i >= 0) /* mp-mfluid */                                 \
          {                                                             \
            int const i = amg_i;                                        \
            if (!amg_mp_coupled)                                        \
              {                                                         \
                MATRIX(F_A01(f, t), i, i, mp_n) = (coeff_01);           \
                MATRIX(F_A10(f, t), i, i, mp_n) = (coeff_10);           \
                if (DIRECT_DELTA_FORM_P)                                \
                  {                                                     \
                    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
                    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
                  }                                                     \
              }                                                         \
            else                                                        \
              {                                                         \
                int ju = W_U + amg_i;                                   \
                int jv = W_U + mp_n + amg_i;                            \
                int jw = W_U + 2 * mp_n + amg_i;                        \
                int coupled_set = BAMG_BLK_SIZE(amg_id);                \
                MATRIX(F_A01(f, t), ju, ju, coupled_set) = (coeff_01);  \
                MATRIX(F_A10(f, t), ju, ju, coupled_set) = (coeff_10);  \
                MATRIX(F_A01(f, t), jv, jv, coupled_set) = (coeff_01);  \
                MATRIX(F_A10(f, t), jv, jv, coupled_set) = (coeff_10);  \
                if (DIRECT_DELTA_FORM_P)                                \
                  {                                                     \
                    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
                    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
                  }                                                     \
              }                                                         \
          }                                                             \
        else                                                            \
          {                                                             \
            int neq = BAMG_BLK_SIZE(amg_id);                            \
            MATRIX(F_A01(f, t), W_U, W_U, neq) = (coeff_01);            \
            MATRIX(F_A10(f, t), W_U, W_U, neq) = (coeff_10);            \
            MATRIX(F_A01(f, t), W_V, W_V, neq) = (coeff_01);            \
            MATRIX(F_A10(f, t), W_V, W_V, neq) = (coeff_10);            \
            if (DIRECT_DELTA_FORM_P)                                    \
              {                                                         \
                C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
                C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
              }                                                         \
          }                                                             \
      }                                                                 \
    else                                                                \
      Internal_Error("unknown amg solver id");                          \
  }
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_DELTA(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  if (amg_id == AMG_SCALAR)                                           \
    {                                                                 \
      F_COEFF_01(f,t) = (coeff_01);                                   \
      F_COEFF_10(f,t) = (coeff_10);                                   \
      C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
      C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
    }                                                                 \
  else                                        \
    {                                                                 \
      if (amg_i >= 0) /* mp-mfluid */                                 \
        {                                                             \
          int const i = amg_i;                                        \
          if(!amg_mp_coupled)                                         \
            {                                                         \
              MATRIX(F_A01(f,t),i,i,mp_n) = (coeff_01);               \
              MATRIX(F_A10(f,t),i,i,mp_n) = (coeff_10);               \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
            }                                                         \
          else                                                        \
            {                                                         \
              int ju = W_U + amg_i;                                   \
              int jv = W_U + mp_n + amg_i;                            \
              int jw = W_U + 2*mp_n + amg_i;                          \
              int coupled_set = BAMG_BLK_SIZE(amg_id);                \
              MATRIX(F_A01(f,t),ju,ju,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),ju,ju,coupled_set) = (coeff_10);      \
              MATRIX(F_A01(f,t),jv,jv,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),jv,jv,coupled_set) = (coeff_10);      \
              MATRIX(F_A01(f,t),jw,jw,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),jw,jw,coupled_set) = (coeff_10);      \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
            }                                                         \
        }                                                             \
      else                                                            \
        {                                                             \
          int neq = BAMG_BLK_SIZE(amg_id);                            \
          MATRIX(F_A01(f,t),W_U,W_U,neq) = (coeff_01);                \
          MATRIX(F_A10(f,t),W_U,W_U,neq) = (coeff_10);                \
          MATRIX(F_A01(f,t),W_V,W_V,neq) = (coeff_01);                \
          MATRIX(F_A10(f,t),W_V,W_V,neq) = (coeff_10);                \
          MATRIX(F_A01(f,t),W_W,W_W,neq) = (coeff_01);                \
          MATRIX(F_A10(f,t),W_W,W_W,neq) = (coeff_10);                \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
        }                                                             \
    }                                                                 \
}
#else /* RP_2D */
#define FILL_ANB_MOM_DELTA(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  if (amg_id == AMG_SCALAR)                                           \
    {                                                                 \
      F_COEFF_01(f, t) = (coeff_01);                                  \
      F_COEFF_10(f, t) = (coeff_10);                                  \
        C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
        C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
    }                                                                 \
  else                                          \
    {                                                                 \
      if (amg_i >= 0) /* mp-mfluid */                                 \
        {                                                             \
          int const i = amg_i;                                        \
          if (!amg_mp_coupled)                                        \
            {                                                         \
              MATRIX(F_A01(f, t), i, i, mp_n) = (coeff_01);           \
              MATRIX(F_A10(f, t), i, i, mp_n) = (coeff_10);           \
                  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
                  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
            }                                                         \
          else                                                        \
            {                                                         \
              int ju = W_U + amg_i;                                   \
              int jv = W_U + mp_n + amg_i;                            \
              int jw = W_U + 2 * mp_n + amg_i;                        \
              int coupled_set = BAMG_BLK_SIZE(amg_id);                \
              MATRIX(F_A01(f, t), ju, ju, coupled_set) = (coeff_01);  \
              MATRIX(F_A10(f, t), ju, ju, coupled_set) = (coeff_10);  \
              MATRIX(F_A01(f, t), jv, jv, coupled_set) = (coeff_01);  \
              MATRIX(F_A10(f, t), jv, jv, coupled_set) = (coeff_10);  \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
            }                                                         \
        }                                                             \
      else                                                            \
        {                                                             \
          int neq = BAMG_BLK_SIZE(amg_id);                            \
          MATRIX(F_A01(f, t), W_U, W_U, neq) = (coeff_01);            \
          MATRIX(F_A10(f, t), W_U, W_U, neq) = (coeff_10);            \
          MATRIX(F_A01(f, t), W_V, W_V, neq) = (coeff_01);            \
          MATRIX(F_A10(f, t), W_V, W_V, neq) = (coeff_10);            \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
        }                                                             \
    }                                                                 \
}
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_COUPLED_MP(f,t,neq,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  MATRIX(F_A01(f,t),W_U,W_U,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_U,W_U,neq) = (coeff_10);                \
  MATRIX(F_A01(f,t),W_V,W_V,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_V,W_V,neq) = (coeff_10);                \
  MATRIX(F_A01(f,t),W_W,W_W,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_W,W_W,neq) = (coeff_10);                \
  if (DIRECT_DELTA_FORM_P)                                    \
   {                                                           \
    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
   }                                                           \
}
#else /* RP_2D */
#define FILL_ANB_MOM_COUPLED_MP(f,t,neq,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  MATRIX(F_A01(f, t), W_U, W_U, neq) = (coeff_01);            \
  MATRIX(F_A10(f, t), W_U, W_U, neq) = (coeff_10);            \
  MATRIX(F_A01(f, t), W_V, W_V, neq) = (coeff_01);            \
  MATRIX(F_A10(f, t), W_V, W_V, neq) = (coeff_10);            \
  if (DIRECT_DELTA_FORM_P)                                    \
   {                                                         \
    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
   }                                                         \
}
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_SEG_MP(f,t,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  F_COEFF_01(f,t) = (coeff_01);                                   \
  F_COEFF_10(f,t) = (coeff_10);                                   \
  if (DIRECT_DELTA_FORM_P)                                        \
   {                                                               \
    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
   }                                                               \
}
#else /* RP_2D */
#define FILL_ANB_MOM_SEG_MP(f,t,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  F_COEFF_01(f, t) = (coeff_01);                                  \
  F_COEFF_10(f, t) = (coeff_10);                                  \
  if (DIRECT_DELTA_FORM_P)                                        \
   {                                                               \
    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
   }                                                               \
}
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_DELTA_MP_MFLUID(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  if (amg_id == AMG_SCALAR)                                           \
    {                                                                 \
      F_COEFF_01(f,t) = (coeff_01);                                   \
      F_COEFF_10(f,t) = (coeff_10);                                   \
      C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
      C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
    }                                                                 \
  else                                         \
    {                                                                 \
      if (amg_i >= 0) /* mp-mfluid */                                 \
        {                                                             \
          int const i = amg_i;                                        \
          if(!amg_mp_coupled)                                         \
            {                                                         \
              MATRIX(F_A01(f,t),i,i,mp_n) = (coeff_01);               \
              MATRIX(F_A10(f,t),i,i,mp_n) = (coeff_10);               \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
            }                                                         \
          else                                                        \
            {                                                         \
              int ju = W_U + amg_i;                                   \
              int jv = W_U + mp_n + amg_i;                            \
              int jw = W_U + 2*mp_n + amg_i;                          \
              int coupled_set = BAMG_BLK_SIZE(amg_id);                \
              MATRIX(F_A01(f,t),ju,ju,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),ju,ju,coupled_set) = (coeff_10);      \
              MATRIX(F_A01(f,t),jv,jv,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),jv,jv,coupled_set) = (coeff_10);      \
              MATRIX(F_A01(f,t),jw,jw,coupled_set) = (coeff_01);      \
              MATRIX(F_A10(f,t),jw,jw,coupled_set) = (coeff_10);      \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
            }                                                         \
        }                                                             \
    }                                                                 \
}
#else /* RP_2D */
#define FILL_ANB_MOM_DELTA_MP_MFLUID(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  if (amg_id == AMG_SCALAR)                                           \
    {                                                                 \
      F_COEFF_01(f, t) = (coeff_01);                                  \
      F_COEFF_10(f, t) = (coeff_10);                                  \
      C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
      C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
    }                                                                 \
  else                                         \
    {                                                                 \
      if (amg_i >= 0) /* mp-mfluid */                                 \
        {                                                             \
          int const i = amg_i;                                        \
          if (!amg_mp_coupled)                                        \
            {                                                         \
              MATRIX(F_A01(f, t), i, i, mp_n) = (coeff_01);           \
              MATRIX(F_A10(f, t), i, i, mp_n) = (coeff_10);           \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
            }                                                         \
          else                                                        \
            {                                                         \
              int ju = W_U + amg_i;                                   \
              int jv = W_U + mp_n + amg_i;                            \
              int jw = W_U + 2 * mp_n + amg_i;                        \
              int coupled_set = BAMG_BLK_SIZE(amg_id);                \
              MATRIX(F_A01(f, t), ju, ju, coupled_set) = (coeff_01);  \
              MATRIX(F_A10(f, t), ju, ju, coupled_set) = (coeff_10);  \
              MATRIX(F_A01(f, t), jv, jv, coupled_set) = (coeff_01);  \
              MATRIX(F_A10(f, t), jv, jv, coupled_set) = (coeff_10);  \
              C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
              C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
            }                                                         \
        }                                                             \
}
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_DELTA_COUPLED_SP(f,t,neq,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  MATRIX(F_A01(f,t),W_U,W_U,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_U,W_U,neq) = (coeff_10);                \
  MATRIX(F_A01(f,t),W_V,W_V,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_V,W_V,neq) = (coeff_10);                \
  MATRIX(F_A01(f,t),W_W,W_W,neq) = (coeff_01);                \
  MATRIX(F_A10(f,t),W_W,W_W,neq) = (coeff_10);                \
  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
}
#else /* RP_2D */
#define FILL_ANB_MOM_DELTA_COUPLED_SP(f,t, neq, coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
  MATRIX(F_A01(f, t), W_U, W_U, neq) = (coeff_01);            \
  MATRIX(F_A10(f, t), W_U, W_U, neq) = (coeff_10);            \
  MATRIX(F_A01(f, t), W_V, W_V, neq) = (coeff_01);            \
  MATRIX(F_A10(f, t), W_V, W_V, neq) = (coeff_10);            \
  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
}
#endif /* RP_3D */

#if RP_3D
#define FILL_ANB_MOM_DELTA_SEG_SP(f,t,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
      F_COEFF_01(f,t) = (coeff_01);                                   \
      F_COEFF_10(f,t) = (coeff_10);                                   \
      C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
      C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
}
#else /* RP_2D */
#define FILL_ANB_MOM_DELTA_SEG_SP(f,t,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
{                                                                     \
      F_COEFF_01(f, t) = (coeff_01);                                  \
      F_COEFF_10(f, t) = (coeff_10);                                  \
      C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
      C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
}
#endif /* RP_3D */

#if RP_3D
#define C0_DISCRETIZE_ND_VEC_SRC_RM(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _rm) \
{                                                                     \
  real _coeff_uu0, _coeff_uv0, _coeff_uw0;                            \
  real _coeff_vu0, _coeff_vv0, _coeff_vw0;                            \
  real _coeff_wu0, _coeff_wv0, _coeff_ww0;                            \
  real _coeff_uu1, _coeff_uv1, _coeff_uw1;                            \
  real _coeff_vu1, _coeff_vv1, _coeff_vw1;                            \
  real _coeff_wu1, _coeff_wv1, _coeff_ww1;                            \
  ND_DS(_coeff_uu0,                                                   \
        _coeff_uv0,                                                   \
        _coeff_uw0, =, 1.0, 0.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_vu0,                                                   \
        _coeff_vv0,                                                   \
        _coeff_vw0, =, 0.0, 1.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_wu0,                                                   \
        _coeff_wv0,                                                   \
        _coeff_ww0, =, 0.0, 0.0, 1.0, *, (_coeff));                   \
  ND_DS(_coeff_uu1,                                                   \
        _coeff_uv1,                                                   \
        _coeff_uw1, =, _rm[0][0], _rm[1][0], _rm[2][0], *, (_coeff)); \
  ND_DS(_coeff_vu1,                                                   \
        _coeff_vv1,                                                   \
        _coeff_vw1, =, _rm[0][1], _rm[1][1], _rm[2][1], *, (_coeff)); \
  ND_DS(_coeff_wu1,                                                   \
        _coeff_wv1,                                                   \
        _coeff_ww1, =, _rm[0][2], _rm[1][2], _rm[2][2], *, (_coeff)); \
                                                                      \
  C0_DISCRETIZE_SRC_RM(_coeff_uu0, _coeff_uu1, _c0, _c1, _u0, _u1, _u_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_uv0, _coeff_uv1, _c0, _c1, _u0, _v1, _u_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_uw0, _coeff_uw1, _c0, _c1, _u0, _w1, _u_s0) \
                                                                      \
  C0_DISCRETIZE_SRC_RM(_coeff_vu0, _coeff_vu1, _c0, _c1, _v0, _u1, _v_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_vv0, _coeff_vv1, _c0, _c1, _v0, _v1, _v_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_vw0, _coeff_vw1, _c0, _c1, _v0, _w1, _v_s0) \
                                                                      \
  C0_DISCRETIZE_SRC_RM(_coeff_wu0, _coeff_wu1, _c0, _c1, _w0, _u1, _w_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_wv0, _coeff_wv1, _c0, _c1, _w0, _v1, _w_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_ww0, _coeff_ww1, _c0, _c1, _w0, _w1, _w_s0) \
}
#define C1_DISCRETIZE_ND_VEC_SRC_RM(_coeff, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1, _rm) \
{                                                                     \
  real _coeff_uu0, _coeff_uv0, _coeff_uw0;                            \
  real _coeff_vu0, _coeff_vv0, _coeff_vw0;                            \
  real _coeff_wu0, _coeff_wv0, _coeff_ww0;                            \
  real _coeff_uu1, _coeff_uv1, _coeff_uw1;                            \
  real _coeff_vu1, _coeff_vv1, _coeff_vw1;                            \
  real _coeff_wu1, _coeff_wv1, _coeff_ww1;                            \
  ND_DS(_coeff_uu0,                                                   \
        _coeff_uv0,                                                   \
        _coeff_uw0, =, _rm[0][0], _rm[0][1], _rm[0][2], *, (_coeff)); \
  ND_DS(_coeff_vu0,                                                   \
        _coeff_vv0,                                                   \
        _coeff_vw0, =, _rm[1][0], _rm[1][1], _rm[1][2], *, (_coeff)); \
  ND_DS(_coeff_wu0,                                                   \
        _coeff_wv0,                                                   \
        _coeff_ww0, =, _rm[2][0], _rm[2][1], _rm[2][2], *, (_coeff)); \
  ND_DS(_coeff_uu1,                                                   \
        _coeff_uv1,                                                   \
        _coeff_uw1, =, 1.0, 0.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_vu1,                                                   \
        _coeff_vv1,                                                   \
        _coeff_vw1, =, 0.0, 1.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_wu1,                                                   \
        _coeff_wv1,                                                   \
        _coeff_ww1, =, 0.0, 0.0, 1.0, *, (_coeff));                   \
                                                                      \
  C1_DISCRETIZE_SRC_RM(_coeff_uu0, _coeff_uu1, _c0, _c1, _u0, _u1, _u_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_uv0, _coeff_uv1, _c0, _c1, _v0, _u1, _u_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_uw0, _coeff_uw1, _c0, _c1, _w0, _u1, _u_s1) \
                                                                      \
  C1_DISCRETIZE_SRC_RM(_coeff_vu0, _coeff_vu1, _c0, _c1, _u0, _v1, _v_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_vv0, _coeff_vv1, _c0, _c1, _v0, _v1, _v_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_vw0, _coeff_vw1, _c0, _c1, _w0, _v1, _v_s1) \
                                                                      \
  C1_DISCRETIZE_SRC_RM(_coeff_wu0, _coeff_wu1, _c0, _c1, _u0, _w1, _w_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_wv0, _coeff_wv1, _c0, _c1, _v0, _w1, _w_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_ww0, _coeff_ww1, _c0, _c1, _w0, _w1, _w_s1) \
}
#else /* RP_2D */
#define C0_DISCRETIZE_ND_VEC_SRC_RM(_coeff, _c0, _c1, _u0, _v0, _u1, _v1, _u_s0, _v_s0, _rm) \
{                                                                     \
  real _coeff_uu0, _coeff_uv0, _coeff_uw0;                            \
  real _coeff_vu0, _coeff_vv0, _coeff_vw0;                            \
  real _coeff_wu0, _coeff_wv0, _coeff_ww0;                            \
  real _coeff_uu1, _coeff_uv1, _coeff_uw1;                            \
  real _coeff_vu1, _coeff_vv1, _coeff_vw1;                            \
  real _coeff_wu1, _coeff_wv1, _coeff_ww1;                            \
  ND_DS(_coeff_uu0,                                                   \
        _coeff_uv0,                                                   \
        _coeff_uw0, =, 1.0, 0.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_vu0,                                                   \
        _coeff_vv0,                                                   \
        _coeff_vw0, =, 0.0, 1.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_wu0,                                                   \
        _coeff_wv0,                                                   \
        _coeff_ww0, =, 0.0, 0.0, 1.0, *, (_coeff));                   \
  ND_DS(_coeff_uu1,                                                   \
        _coeff_uv1,                                                   \
        _coeff_uw1, =, _rm[0][0], _rm[1][0], _rm[2][0], *, (_coeff)); \
  ND_DS(_coeff_vu1,                                                   \
        _coeff_vv1,                                                   \
        _coeff_vw1, =, _rm[0][1], _rm[1][1], _rm[2][1], *, (_coeff)); \
  ND_DS(_coeff_wu1,                                                   \
        _coeff_wv1,                                                   \
        _coeff_ww1, =, _rm[0][2], _rm[1][2], _rm[2][2], *, (_coeff)); \
                                                                      \
  C0_DISCRETIZE_SRC_RM(_coeff_uu0, _coeff_uu1, _c0, _c1, _u0, _u1, _u_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_uv0, _coeff_uv1, _c0, _c1, _u0, _v1, _u_s0) \
                                                                      \
  C0_DISCRETIZE_SRC_RM(_coeff_vu0, _coeff_vu1, _c0, _c1, _v0, _u1, _v_s0) \
  C0_DISCRETIZE_SRC_RM(_coeff_vv0, _coeff_vv1, _c0, _c1, _v0, _v1, _v_s0) \
}
#define C1_DISCRETIZE_ND_VEC_SRC_RM(_coeff, _c0, _c1, _u0, _v0, _u1, _v1, _u_s1, _v_s1, _rm) \
{                                                                     \
  real _coeff_uu0, _coeff_uv0, _coeff_uw0;                            \
  real _coeff_vu0, _coeff_vv0, _coeff_vw0;                            \
  real _coeff_wu0, _coeff_wv0, _coeff_ww0;                            \
  real _coeff_uu1, _coeff_uv1, _coeff_uw1;                            \
  real _coeff_vu1, _coeff_vv1, _coeff_vw1;                            \
  real _coeff_wu1, _coeff_wv1, _coeff_ww1;                            \
  ND_DS(_coeff_uu0,                                                   \
        _coeff_uv0,                                                   \
        _coeff_uw0, =, _rm[0][0], _rm[0][1], _rm[0][2], *, (_coeff)); \
  ND_DS(_coeff_vu0,                                                   \
        _coeff_vv0,                                                   \
        _coeff_vw0, =, _rm[1][0], _rm[1][1], _rm[1][2], *, (_coeff)); \
  ND_DS(_coeff_wu0,                                                   \
        _coeff_wv0,                                                   \
        _coeff_ww0, =, _rm[2][0], _rm[2][1], _rm[2][2], *, (_coeff)); \
  ND_DS(_coeff_uu1,                                                   \
        _coeff_uv1,                                                   \
        _coeff_uw1, =, 1.0, 0.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_vu1,                                                   \
        _coeff_vv1,                                                   \
        _coeff_vw1, =, 0.0, 1.0, 0.0, *, (_coeff));                   \
  ND_DS(_coeff_wu1,                                                   \
        _coeff_wv1,                                                   \
        _coeff_ww1, =, 0.0, 0.0, 1.0, *, (_coeff));                   \
                                                                      \
  C1_DISCRETIZE_SRC_RM(_coeff_uu0, _coeff_uu1, _c0, _c1, _u0, _u1, _u_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_uv0, _coeff_uv1, _c0, _c1, _v0, _u1, _u_s1) \
                                                                      \
  C1_DISCRETIZE_SRC_RM(_coeff_vu0, _coeff_vu1, _c0, _c1, _u0, _v1, _v_s1) \
  C1_DISCRETIZE_SRC_RM(_coeff_vv0, _coeff_vv1, _c0, _c1, _v0, _v1, _v_s1) \
}
#endif /* if RP_3D */

#if RP_3D
#define FILL_ANB_MOM_RM(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1, _rm) \
  {                                                                     \
    if (amg_id == AMG_SCALAR)                                           \
      {                                                                 \
        F_COEFF_01(f,t) = (coeff_01);                                   \
        F_COEFF_10(f,t) = (coeff_10);                                   \
        if (DIRECT_DELTA_FORM_P)                                        \
        {                                                               \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
        }                                                               \
      }                                                                 \
    else if (amg_id == AMG_PVT)                                         \
      {                                                                 \
        if (amg_i >= 0) /* mp-mfluid */                                 \
          {                                                             \
            int const i = amg_i;                                        \
            if(!amg_mp_coupled)                                         \
              {                                                         \
                MATRIX(F_A01(f,t),i,i,mp_n) = (coeff_01);               \
                MATRIX(F_A10(f,t),i,i,mp_n) = (coeff_10);               \
                if (DIRECT_DELTA_FORM_P)                                \
                {                                                       \
                  C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
                  C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
                }                                                       \
              }                                                         \
            else                                                        \
              {                                                         \
                int ju = W_U + amg_i;                                   \
                int jv = W_U + mp_n + amg_i;                            \
                int jw = W_U + 2*mp_n + amg_i;                          \
                int neq = BAMG_BLK_SIZE(amg_id);                        \
                ND_DS(MATRIX(F_A01(f,t),W_U_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_U_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_U_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][0], _rm[1][0], _rm[2][0], *, (coeff_01)); \
                ND_DS(MATRIX(F_A01(f,t),W_V_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_V_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_V_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][1], _rm[1][1], _rm[2][1], *, (coeff_01)); \
                ND_DS(MATRIX(F_A01(f,t),W_W_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_W_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_W_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][2], _rm[1][2], _rm[2][2], *, (coeff_01)); \
                \
                ND_DS(MATRIX(F_A10(f,t),W_U_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_U_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_U_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][0], _rm[0][1], _rm[0][2], *, (coeff_10)); \
                ND_DS(MATRIX(F_A10(f,t),W_V_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_V_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_V_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[1][0], _rm[1][1], _rm[1][2], *, (coeff_10)); \
                ND_DS(MATRIX(F_A10(f,t),W_W_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_W_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_W_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[2][0], _rm[2][1], _rm[2][2], *, (coeff_10)); \
                \
                if (DIRECT_DELTA_FORM_P)                                \
                {                                                       \
                  C0_DISCRETIZE_ND_VEC_SRC_RM(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _rm)\
                  C1_DISCRETIZE_ND_VEC_SRC_RM(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1, _rm)\
                }                                                       \
              }                                                         \
          }                                                             \
        else                                                            \
          {                                                             \
            int neq = BAMG_BLK_SIZE(amg_id);                            \
            ND_DS(MATRIX(F_A01(f,t),W_U,W_U,neq),                       \
                  MATRIX(F_A01(f,t),W_U,W_V,neq),                       \
                  MATRIX(F_A01(f,t),W_U,W_W,neq), =, _rm[0][0], _rm[1][0], _rm[2][0], *, (coeff_01)); \
            ND_DS(MATRIX(F_A01(f,t),W_V,W_U,neq),                       \
                  MATRIX(F_A01(f,t),W_V,W_V,neq),                       \
                  MATRIX(F_A01(f,t),W_V,W_W,neq), =, _rm[0][1], _rm[1][1], _rm[2][1], *, (coeff_01)); \
            ND_DS(MATRIX(F_A01(f,t),W_W,W_U,neq),                       \
                  MATRIX(F_A01(f,t),W_W,W_V,neq),                       \
                  MATRIX(F_A01(f,t),W_W,W_W,neq), =, _rm[0][2], _rm[1][2], _rm[2][2], *, (coeff_01)); \
            \
            ND_DS(MATRIX(F_A10(f,t),W_U,W_U,neq),                       \
                  MATRIX(F_A10(f,t),W_U,W_V,neq),                       \
                  MATRIX(F_A10(f,t),W_U,W_W,neq), =, _rm[0][0], _rm[0][1], _rm[0][2], *, (coeff_10)); \
            ND_DS(MATRIX(F_A10(f,t),W_V,W_U,neq),                       \
                  MATRIX(F_A10(f,t),W_V,W_V,neq),                       \
                  MATRIX(F_A10(f,t),W_V,W_W,neq), =, _rm[1][0], _rm[1][1], _rm[1][2], *, (coeff_10)); \
            ND_DS(MATRIX(F_A10(f,t),W_W,W_U,neq),                       \
                  MATRIX(F_A10(f,t),W_W,W_V,neq),                       \
                  MATRIX(F_A10(f,t),W_W,W_W,neq), =, _rm[2][0], _rm[2][1], _rm[2][2], *, (coeff_10)); \
            \
            if (DIRECT_DELTA_FORM_P)                                    \
            {                                                           \
              C0_DISCRETIZE_ND_VEC_SRC_RM(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _rm)\
              C1_DISCRETIZE_ND_VEC_SRC_RM(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1, _rm)\
            }                                                           \
          }                                                             \
      }                                                                 \
    else                                                                \
      Internal_Error("unknown amg solver id");                          \
  }
#else /* RP_2D */
#define FILL_ANB_MOM_RM(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1, _rm) \
  {                                                                     \
    if (amg_id == AMG_SCALAR)                                           \
      {                                                                 \
        F_COEFF_01(f, t) = (coeff_01);                                  \
        F_COEFF_10(f, t) = (coeff_10);                                  \
        if (DIRECT_DELTA_FORM_P)                                        \
        {                                                               \
          C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
          C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
        }                                                               \
      }                                                                 \
    else if (amg_id == AMG_PVT)                                         \
      {                                                                 \
        if (amg_i >= 0) /* mp-mfluid */                                 \
          {                                                             \
            int const i = amg_i;                                        \
            if (!amg_mp_coupled)                                        \
              {                                                         \
                MATRIX(F_A01(f, t), i, i, mp_n) = (coeff_01);           \
                MATRIX(F_A10(f, t), i, i, mp_n) = (coeff_10);           \
                if (DIRECT_DELTA_FORM_P)                                \
                  {                                                     \
                    C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0)\
                    C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1)\
                  }                                                     \
              }                                                         \
            else                                                        \
              {                                                         \
                int ju = W_U + amg_i;                                   \
                int jv = W_U + mp_n + amg_i;                            \
                int jw = W_U + 2 * mp_n + amg_i;                        \
                int neq = BAMG_BLK_SIZE(amg_id);                        \
                ND_DS(MATRIX(F_A01(f,t),W_U_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_U_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_U_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][0], _rm[1][0], _rm[2][0], *, (coeff_01)); \
                ND_DS(MATRIX(F_A01(f,t),W_V_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_V_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A01(f,t),W_V_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][1], _rm[1][1], _rm[2][1], *, (coeff_01)); \
                \
                ND_DS(MATRIX(F_A10(f,t),W_U_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_U_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_U_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[0][0], _rm[0][1], _rm[0][2], *, (coeff_10)); \
                ND_DS(MATRIX(F_A10(f,t),W_V_MP(amg_i),W_U_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_V_MP(amg_i),W_V_MP(amg_i),neq),                       \
                      MATRIX(F_A10(f,t),W_V_MP(amg_i),W_W_MP(amg_i),neq), =, _rm[1][0], _rm[1][1], _rm[1][2], *, (coeff_10)); \
                \
                if (DIRECT_DELTA_FORM_P)                                \
                  {                                                     \
                    C0_DISCRETIZE_ND_VEC_SRC_RM(coeff_01, _c0, _c1, _u0, _v0, _u1, _v1, _u_s0, _v_s0, _rm) \
                    C1_DISCRETIZE_ND_VEC_SRC_RM(coeff_10, _c0, _c1, _u0, _v0, _u1, _v1, _u_s1, _v_s1, _rm) \
                  }                                                     \
              }                                                         \
          }                                                             \
        else                                                            \
          {                                                             \
            int neq = BAMG_BLK_SIZE(amg_id);                            \
            ND_DS(MATRIX(F_A01(f,t),W_U,W_U,neq),                       \
                  MATRIX(F_A01(f,t),W_U,W_V,neq),                       \
                  MATRIX(F_A01(f,t),W_U,W_W,neq), =, _rm[0][0], _rm[1][0], _rm[2][0], *, (coeff_01)); \
            ND_DS(MATRIX(F_A01(f,t),W_V,W_U,neq),                       \
                  MATRIX(F_A01(f,t),W_V,W_V,neq),                       \
                  MATRIX(F_A01(f,t),W_V,W_W,neq), =, _rm[0][1], _rm[1][1], _rm[2][1], *, (coeff_01)); \
            \
            ND_DS(MATRIX(F_A10(f,t),W_U,W_U,neq),                       \
                  MATRIX(F_A10(f,t),W_U,W_V,neq),                       \
                  MATRIX(F_A10(f,t),W_U,W_W,neq), =, _rm[0][0], _rm[0][1], _rm[0][2], *, (coeff_10)); \
            ND_DS(MATRIX(F_A10(f,t),W_V,W_U,neq),                       \
                  MATRIX(F_A10(f,t),W_V,W_V,neq),                       \
                  MATRIX(F_A10(f,t),W_V,W_W,neq), =, _rm[1][0], _rm[1][1], _rm[1][2], *, (coeff_10)); \
            \
            if (DIRECT_DELTA_FORM_P)                                    \
              {                                                         \
                C0_DISCRETIZE_ND_VEC_SRC_RM(coeff_01, _c0, _c1, _u0, _v0, _u1, _v1, _u_s0, _v_s0, _rm) \
                C1_DISCRETIZE_ND_VEC_SRC_RM(coeff_10, _c0, _c1, _u0, _v0, _u1, _v1, _u_s1, _v_s1, _rm) \
              }                                                         \
          }                                                             \
      }                                                                 \
    else                                                                \
      Internal_Error("unknown amg solver id");                          \
  }
#endif /* RP_3D */


#if RP_3D
#define FILL_ANB_MOM_MP_ADD_COEFF(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
  {                                                                     \
    int const i = amg_i;                                                \
    if(!amg_mp_coupled)                                                 \
      {                                                                 \
        MATRIX(F_A01(f,t),i,i,mp_n) += (coeff_01);                      \
        MATRIX(F_A10(f,t),i,i,mp_n) += (coeff_10);                      \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
            C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
          }                                                             \
      }                                                                 \
    else                                                                \
      {                                                                 \
        int ju = W_U + amg_i;                                           \
        int jv = W_U + mp_n + amg_i;                                    \
        int jw = W_U + 2*mp_n + amg_i;                                  \
        int coupled_set = BAMG_BLK_SIZE(amg_id);                        \
        MATRIX(F_A01(f,t),ju,ju,coupled_set) += (coeff_01);             \
        MATRIX(F_A10(f,t),ju,ju,coupled_set) += (coeff_10);             \
        MATRIX(F_A01(f,t),jv,jv,coupled_set) += (coeff_01);             \
        MATRIX(F_A10(f,t),jv,jv,coupled_set) += (coeff_10);             \
        MATRIX(F_A01(f,t),jw,jw,coupled_set) += (coeff_01);             \
        MATRIX(F_A10(f,t),jw,jw,coupled_set) += (coeff_10);             \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
            C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
          }                                                             \
      }                                                                 \
  }
#else /* RP_2D */
#define FILL_ANB_MOM_MP_ADD_COEFF(f,t,amg_id,amg_i,amg_mp_coupled,coeff_01,coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0, _u_s1, _v_s1, _w_s1) \
  {                                                                     \
    int const i = amg_i;                                                \
    if (!amg_mp_coupled)                                                \
      {                                                                 \
        MATRIX(F_A01(f, t), i, i, mp_n) += (coeff_01);                  \
        MATRIX(F_A10(f, t), i, i, mp_n) += (coeff_10);                  \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
            C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
          }                                                             \
      }                                                                 \
    else                                                                \
      {                                                                 \
        int ju = W_U + amg_i;                                           \
        int jv = W_U + mp_n + amg_i;                                    \
        int jw = W_U + 2 * mp_n + amg_i;                                \
        int coupled_set = BAMG_BLK_SIZE(amg_id);                        \
        MATRIX(F_A01(f, t), ju, ju, coupled_set) += (coeff_01);         \
        MATRIX(F_A10(f, t), ju, ju, coupled_set) += (coeff_10);         \
        MATRIX(F_A01(f, t), jv, jv, coupled_set) += (coeff_01);         \
        MATRIX(F_A10(f, t), jv, jv, coupled_set) += (coeff_10);         \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_ND_VEC_SRC(coeff_01, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s0, _v_s0, _w_s0) \
            C1_DISCRETIZE_ND_VEC_SRC(coeff_10, _c0, _c1, _u0, _v0, _w0, _u1, _v1, _w1, _u_s1, _v_s1, _w_s1) \
          }                                                             \
      }                                                                 \
  }
#endif /* RP_3D */

#define FILL_ANB_VOF(f,t,neq,phase,mp_coupled,sp_coupled,coeff_01,coeff_10,coeff_00,coeff_11, _c0, _c1, _vof0, _vof1, _vof_s0, _vof_s1) \
  {                                                                     \
    if (mp_coupled)                                                     \
      {                                                                 \
        MATRIX(F_A01(f,t),W_VOF_MP(phase),W_VOF_MP(phase),neq) += (coeff_01); \
        MATRIX(F_A10(f,t),W_VOF_MP(phase),W_VOF_MP(phase),neq) += (coeff_10); \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_SRC(coeff_01, _c0, _c1, _vof0, _vof1, _vof_s0) \
            C1_DISCRETIZE_SRC(coeff_10, _c0, _c1, _vof0, _vof1, _vof_s1) \
          }                                                             \
      }                                                                 \
    else if (sp_coupled)                                                \
      {                                                                 \
        MATRIX(F_A01(f,t),W_VOF(phase),W_VOF(phase),neq) = (coeff_01);  \
        MATRIX(F_A10(f,t),W_VOF(phase),W_VOF(phase),neq) = (coeff_10);  \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_SRC_COUNTER_DIFFUSION(coeff_01, coeff_00, _c0, _c1, _vof0, _vof1, _vof_s0) \
            C1_DISCRETIZE_SRC_COUNTER_DIFFUSION(coeff_11, coeff_10, _c0, _c1, _vof0, _vof1, _vof_s1) \
          }                                                             \
      }                                                                 \
    else                                                                \
      {                                                                 \
        F_COEFF_01(f,t) = (coeff_01);                                   \
        F_COEFF_10(f,t) = (coeff_10);                                   \
        if (DIRECT_DELTA_FORM_P)                                        \
          {                                                             \
            C0_DISCRETIZE_SRC_COUNTER_DIFFUSION(coeff_01, coeff_00, _c0, _c1, _vof0, _vof1, _vof_s0) \
            C1_DISCRETIZE_SRC_COUNTER_DIFFUSION(coeff_11, coeff_10, _c0, _c1, _vof0, _vof1, _vof_s1) \
          }                                                             \
      }                                                                 \
  }

#endif /* _FLUENT_SG_DELTA */

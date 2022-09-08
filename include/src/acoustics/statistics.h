/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include "global.h"

#ifdef RAG_TGMATH

#if RP_DOUBLE
typedef double complex REAL_COMPLEX;
#else
typedef float complex REAL_COMPLEX;
#endif

typedef double complex DOUBLE_COMPLEX;

#else

typedef struct _complexStruct
{
  real r, i;
} complex;

#define REAL_COMPLEX complex

typedef struct _double_complexStruct
{
  double r, i;
} double_complex;

#define DOUBLE_COMPLEX double_complex

#endif

typedef enum
{
  WINDOW_OFF = 0,
  HAMMING,
  HANNING,
  BARLETT,
  BLACKMAN,
  MAX_WINDOW
} Window;

typedef enum
{
  SURF_FFT_RE_IM = 0,
  SURF_FFT_MAGN,
  SURF_FFT_PSD,
  SURF_FFT_SPL,
  SURF_FFT_PSD_DPDT
} SurfFFT_VarType;

typedef struct octavestruct
{
  double low;
  double cen;
  double high;
  double A;
  double B;
  double C;
} Octave;

#define N_INTERP (2)

#define convert_to_db(psd,power_ref) 10.0*(log10(MAX(1.e-14,psd/power_ref)))
#define convert_to_psd(db,power_ref) power_ref*(pow(10.0,db/10.0))

void Signal_Statistics (double *signalIn, int n_samples,
                        real *avg, real *var, real *fmin, real *fmax);

FLUENT_EXPORT
void Read_Signal (FILE *read_port, cxboolean is_multi, int, int, int);

FLUENT_EXPORT
void
Finish_FFT_Process(void);

FLUENT_EXPORT
int Process_and_Plot ( const char *write_filename,
                       const char *window_fn_string, cxboolean must_filter, cxboolean print_oaspl,
                       cxboolean fft_andnot_signal, cxboolean plot_signal,
                       const char *x_function, const char *y_function,
                       cxboolean whole_data,  real min, real max, real *statistics,
                       real *time_step_out, int *n_samples_out, int subtract_mean,
                       cxboolean segments, int segm_length, real segm_overlap);
FLUENT_EXPORT
int Process_and_Plot_Signal ( int n_samples, double *, double *, int single_signal,
                              int *index1, int *index2, real *rxaxis, real *ryaxis,
                              const char *write_filename, const char *window_fn_string, cxboolean must_filter,
                              cxboolean print_oaspl, cxboolean fft_andnot_signal, cxboolean plot_signal,
                              const char *x_function, const char *y_function,
                              cxboolean whole_data,  real min, real max, real *statistics,
                              real *time_step_out, int *n_samples_out, int subtract_mean,
                              cxboolean segments, int segm_length, real segm_overlap);
FLUENT_EXPORT
void Process_Spectrum_SPL_Octaves(SurfFFT_VarType var_type, int nband_total, int nspec, int *index1, int *index2,
                                  real *rxaxis, real *ryaxis, real *psd_bands, real *spl_bands);
FLUENT_EXPORT
void Process_Spectrum_SPL_Thirds(SurfFFT_VarType var_type, int nband_total, int nspec, int *index1, int *index2,
                                 real *rxaxis, real *ryaxis, real *psd_bands, real *spl_bands);
FLUENT_EXPORT
void Process_Spectrum_SPL_Bands(SurfFFT_VarType var_type, int nbands, int nspec, int ifrq_first, int freq_per_band,
                                real *rxaxis, real *ryaxis, real *psd_bands, real *spl_bands);

FLUENT_EXPORT
int npfa_max_even(int nmax);

FLUENT_EXPORT Window Inquire_Window_Fn (const char *window_fn_string);

#endif

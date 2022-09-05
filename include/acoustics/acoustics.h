/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _ACOUSTICS_H_
#define _ACOUSTICS_H_

#include "mem_grid.h" /* only for MAX_NAME_LENGTH in t_n_vars */
#include "statistics.h" /* only for SurfFFT_VarType in surface FFT function prototypes */

#define CGNS_MAPDL 1

/* Number of variables used by the FW-H solver: p,u,v,(w),rho */
#if RP_3D
#define AC_VAR_MAX 5
#else
#define AC_VAR_MAX 4
#endif

#define SMALL_SOUND 1.e-12
#define SMALL_MACH 1.e-3

#define AC_SRC_STORED_MODES 20
#define AC_SRC_STORED_BANDS 20

/* time-differencing MACRO */
/* first-order backward */
#define TIME_DERIVATIVE_EULER(var,f,dt)\
(var[f] - var##_m1[f])/dt
/* second-order backward */
#define TIME_DERIVATIVE_TL(var,f,dt)\
(1.5*var[f] - 2.*var##_m1[f] + 0.5*var##_m2[f])/dt

#define acoustic_required_source_thread_loop(n)\
for(n=0 ; n<length_req_threads_n_vars; n++)

typedef struct  thread_n_vars
{
  int tid;
  char name[MAX_NAME_LENGTH];
  Svar svarslist[AC_VAR_MAX];
  int adj_id;
  int num_svars;
} t_n_vars;

extern FLUENT_EXPORT int ac_n_per;

extern FLUENT_EXPORT cxboolean sources_changed_p;
extern FLUENT_EXPORT Acoustics_Model rp_acoustics;
extern FLUENT_EXPORT t_n_vars *avail_threads_n_vars;
extern FLUENT_EXPORT t_n_vars *req_threads_n_vars;
extern FLUENT_EXPORT int length_avail_threads_n_vars;
extern FLUENT_EXPORT int length_req_threads_n_vars;

void Acoustics_Model_Ini(void);
char *Acoustics_Model_Name(Acoustics_Model);
FLUENT_EXPORT void Set_Acoustics_Receivers(Domain *domain, Pointer, Pointer);
FLUENT_EXPORT void Extract_Acoustics_Signals (Domain *domain, double time, double delt,
                                              double dt_sound, cxboolean on_the_fly);
FLUENT_EXPORT void Compute_Sound_Pressure(Domain *domain);
FLUENT_EXPORT void Compute_Sound_Pressure_On_Steady_Solution(Domain *domain);
FLUENT_EXPORT void Write_Sound_Pressure(Domain *domain);
FLUENT_EXPORT void Initialize_Acoustic_Writable_Thread_List(Domain *domain);
FLUENT_EXPORT cxboolean Read_Ac_FWH_Receivers_Data(FILE *, int);
FLUENT_EXPORT cxboolean Read_Ac_FWH_Receivers_Data_Pre_V64(FILE *fd, int section);
FLUENT_EXPORT void Write_Ac_FWH_Receivers_Data(FILE *, cxboolean);
FLUENT_EXPORT void Compute_FWH_Var(Thread *t, Svar nv);

FLUENT_EXPORT void Flush_Waveeq_Receivers(Domain *domain);
FLUENT_EXPORT void Acoustics_Waveeq_Data_Ini(Domain *domain);
FLUENT_EXPORT void Acoustics_Waveeq_Ini(Domain *domain);
FLUENT_EXPORT void Acoustics_Waveeq_Iter(Domain *domain, int sub_iter, real *residual_norm);
FLUENT_EXPORT void Acoustics_Waveeq_Fin(Domain *domain);
FLUENT_EXPORT void Acoustics_Waveeq_Write_Signals(Domain *domain);
FLUENT_EXPORT void Read_Ac_Waveeq_Receivers_Data(FILE *, Domain *, int);
FLUENT_EXPORT void Write_Ac_Waveeq_Receivers_Data(FILE *, Domain *, cxboolean);
FLUENT_EXPORT cxboolean if_rp_acoustics_waveeq(void);
FLUENT_EXPORT cxboolean if_rp_acoustics_waveeq_pressure(void);
FLUENT_EXPORT cxboolean if_rp_acoustics_waveeq_potential(void);
FLUENT_EXPORT void Grid_Oscillations_Filter(Domain *domain, Svar sv, Svar svf, real sign);
FLUENT_EXPORT void init_waveeq_output(Domain *domain);
FLUENT_EXPORT void Compute_Kirchhoff_Surface_Integrals(Domain *domain);

#if PARALLEL
FLUENT_EXPORT void Write_HDF_Ac_Receivers_Data(const char *);
FLUENT_EXPORT void Read_HDF_Ac_Receivers_Data(const char *);
#endif

#if MPI_IO
FLUENT_EXPORT cxboolean Read_MPI_Ac_Receivers_Data(int fhandle, int *headerbuf);
FLUENT_EXPORT void Write_MPI_Ac_Receivers_Data(int fhandle);
#endif
FLUENT_EXPORT cxboolean if_rp_acoustics(void);
FLUENT_EXPORT void Pick_Recs_For_Read_And_Compute(Domain *domain, Pointer);
/*FLUENT_EXPORT cxboolean if_rot_periodic_thread(Thread*);*/
FLUENT_EXPORT void Process_Receiver(const char *write_filename,
                                    const char *window_fn_string, cxboolean must_filter, cxboolean print_oaspl,
                                    cxboolean fft_andnot_signal, cxboolean plot_signal,
                                    const char *x_function, const char *y_function, cxboolean whole_data,
                                    real min, real max, real *statistics, real *time_step_out,
                                    int *n_samples_out, int rec_no, int subtract_mean,
                                    cxboolean segments, int segm_length, real segm_overlap);
FLUENT_EXPORT cxboolean is_single_rotating_reference(void);
FLUENT_EXPORT cxboolean is_rot_periodic_model(void);
FLUENT_EXPORT void Acoustics_Do_After_Initialize(Domain *domain);
FLUENT_EXPORT cxboolean Flush_Acoustics_Receivers(Domain *domain);
FLUENT_EXPORT void Compute_Ac_N_Per(void);
FLUENT_EXPORT void Set_Ac_Auto_Prune (cxboolean flag);

FLUENT_EXPORT void Extract_Probe(Domain *domain, const char *filename, int node_id, int izone_nearest, int face_nearest,
                                 real point_x, real point_y, real point_z);
FLUENT_EXPORT void Nearest_Face_To_Point(Domain *domain, real point_x, real point_y, real point_z,
                                         int *node_id, int *izone_nearest, int *face_nearest,
                                         real *face_x, real *face_y, real *face_z, real *mismatch);
FLUENT_EXPORT void Acoustic_Sources_FFT_ReadASD(Domain *domain, Pointer filenames, Pointer threads, Pointer names,
                                                int *n_samples_out, double *tmin, double *tmax, double *tstep);
FLUENT_EXPORT void Acoustic_Sources_FFT_Compute(Domain *domain, real tmin, real tmax, const char *window_fn_string,
                                                cxboolean overwrite);
#if CGNS_MAPDL
FLUENT_EXPORT void Acoustic_Sources_FFT_Write(Domain *domain, const char *filename, int freqperfile,
                                              real freqmin, real freqmax, int freqskip,
                                              const char *unit_mass, const char *unit_length, const char *unit_time,
                                              const char *unit_tempeature, const char *unit_angle);
#endif
FLUENT_EXPORT int Acoustic_Sources_FFT_Create_Octaves(Domain *domain, SurfFFT_VarType var_type, int nb, int *bands,
                                                      cxboolean write_areaav, const char *filename, int *n_active,
                                                      real *central_freq, real *spl_bands_area_output);
FLUENT_EXPORT int Acoustic_Sources_FFT_Create_Thirds(Domain *domain, SurfFFT_VarType var_type, int nb, int *bands,
                                                     cxboolean write_areaav, const char *filename, int *n_active,
                                                     real *central_freq, real *spl_bands_area_output);
FLUENT_EXPORT void Acoustic_Sources_FFT_Create_Modes(Domain *domain, real fmin, real fmax, int fskip, int *nmodes);
FLUENT_EXPORT int Acoustic_Sources_FFT_Create_Bands(Domain *domain, SurfFFT_VarType var_type, real fmin, real fmax,
                                                    real bwidth, int *nbands,
                                                    cxboolean write_areaav, const char *filename, int *n_active,
                                                    real *central_freq, real *spl_bands_area_output);
FLUENT_EXPORT void Acoustic_Sources_FFT_RemoveVars(Domain *domain, int nb, int *bands, SurfFFT_VarType *var_types);
FLUENT_EXPORT void Acoustic_Sources_FFT_CleanupMem(cxboolean overwrite, cxboolean keep_signals);

FLUENT_EXPORT void Model_Initialize_acoustics_fwh(void);
FLUENT_EXPORT void Model_Initialize_acoustics_waveeq(void);
FLUENT_EXPORT void Model_Initialize_acoustics_broadband(void);
FLUENT_EXPORT void Model_Initialize_acoustics_surface_fft(void);
FLUENT_EXPORT void Model_Initialize_acoustics_modal_analysis(void);
/** Functions which are made global for modularisation */
cxboolean if_sound_source_thread(const Thread *const t);
cxboolean if_source_band_analysis(void);
#endif

/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SOURCES_H
#define _FLUENT_SOURCES_H

#include "sys_master.h"

#if RP_AMG_V5
# define SOURCES_SOLVER_C amg.c amg_v5.c amg_s.c cg.c matrix_tools.c rpm.c
# define SOURCES_SOLVER_H amg.h amginc.c amginc1.c amg_v5.h cg.h matrix_tools.h rpm.h
#else
# define SOURCES_SOLVER_C amg.c amg_s.c cg.c matrix_tools.c rpm.c amg_hybrid.c krylov.c amg_gpu.c
# define SOURCES_SOLVER_H amg.h amginc.c amginc1.c cg.h matrix_tools.h rpm.h amg_hybrid.h krylov.h amg_gpu.h
#endif
#define SOURCES_ALL_SOLVER_C amg.c amg_v5.c amg_s.c cg.c matrix_tools.c rpm.c amg_hybrid.c krylov.c amg_gpu.c
#define SOURCES_ALL_SOLVER_H amg.h amginc.c amginc1.c amg_v5.h cg.h matrix_tools.h rpm.h amg_hybrid.h krylov.h amg_gpu.h

#if RP_HOLS
#define SOURCES_HOLS_C sg_hols.c
#define SOURCES_HOLS_H sg_hols.h
#else
#define SOURCES_HOLS_C
#define SOURCES_HOLS_H
#endif

#define SOURCES_SHELL_C multi_layer_shell.c shell_conduction.c
#define SOURCES_SHELL_H multi_layer_shell.h shell_conduction.h

/* Eulerian Wall Film */
#if RP_3D
#define SOURCES_WALL_FILM_C sg_film.c
#define SOURCES_WALL_FILM_H sg_film.h
#else
#define SOURCES_WALL_FILM_C
#define SOURCES_WALL_FILM_H
#endif

#define SOURCES_DPM_DIST_C dpm_dist.c
#define SOURCES_DPM_DIST_H dpm_dist.h

#define SOURCES_ECFM_C sg_ecfm.c sg_inert.c
#define SOURCES_ECFM_H sg_ecfm.h sg_inert.h

#define SOURCES_FEM_C fem.c
#define SOURCES_FEM_H fem.h

#define SOURCES_GEQN_C sg_geqn.c sg_gvar.c
#define SOURCES_GEQN_H sg_geqn.h sg_gvar.h

#define SOURCES_DPM_VOF_C dpm_vof.c
#define SOURCES_DPM_VOF_H dpm_vof.h

#define SOURCES_RK_C redlich_kwong.c
#define SOURCES_RK_H redlich_kwong.h

#define SOURCES_CXLIB_C cx_vis.c cx_surf.c cx_dtrm.c cx_s2s.c
#define SOURCES_CXLIB_H surf.h

#define SOURCES_CLLIB_C cl_dpm.c
#define SOURCES_CLLIB_H

#define SOURCES_DPM_H dpm.h dpm_laws.h dpm_mem.h dpm_path.h dpm_tools.h dpm_types.h dpm_breakup.h dpm_dem_wall.h dpm_dem.h unsteady_dpm.h dpm_domain.h dpm_injections.h

#define SOURCES_REPGRAD_C repair_svar.c
#define SOURCES_REPGRAD_H repair_svar.h

#define SOURCES_ALL_NODE_C coarse_par.c \
grid_par.c grid_par_ext.c migrate.c neighbor.c debug_tools.c balance.c amg_par.c ansmeshimport.c

#define SOURCES_ALL_NODE_H coarse_par.h \
grid_par.h grid_par_ext.h migrate.h neighbor.h pconfig.h pmain.c balance.h amg_par.h ansmeshimport.h

#if RP_NODE
# define SOURCES_NODE_C SOURCES_ALL_NODE_C
# define SOURCES_NODE_H SOURCES_ALL_NODE_H
#else
# define SOURCES_NODE_C
# define SOURCES_NODE_H
#endif

#define SOURCES_ALL_HOST_C grid_par.c migrate.c balance.c ansmeshimport.c

#define SOURCES_ALL_HOST_H coarse_par.h \
grid_par.h migrate.h pconfig.h pmain.c balance.h ansmeshimport.h

#if RP_HOST
# define SOURCES_HOST_C SOURCES_ALL_HOST_C
# define SOURCES_HOST_H SOURCES_ALL_HOST_H
#else
# define SOURCES_HOST_C
# define SOURCES_HOST_H
#endif

#if !RP_NODE
# define SOURCES_NOT_NODE_C md5c.c stamp_fluent.c
# define SOURCES_NOT_NODE_H md5global.h  md5.h  md5wrap.h
#else
# define SOURCES_NOT_NODE_C
# define SOURCES_NOT_NODE_H
#endif

#define SOURCES_ALL_DM_C remesh.c remesh_local.c \
remesh_region.c dynamesh_tools.c dynamesh_smooth.c dynamesh_events.c \
remesh_tools.c remesh_layer.c remesh_par.c remesh_bnd.c remesh_sf.c six_dof.c \
dynamesh_contact.c
#define SOURCES_ALL_DM_H remesh.h remesh_local.h \
remesh_region.h dynamesh_tools.h dynamesh_smooth.h dynamesh_events.h \
remesh_tools.h remesh_layer.h remesh_par.h remesh_bnd.h remesh_sf.h six_dof.h \
dynamesh_contact.h

#define SOURCES_DM_C SOURCES_ALL_DM_C
#define SOURCES_DM_H SOURCES_ALL_DM_H

#if RP_OVERSET
# define SOURCES_OVERSET_C overset.c
# define SOURCES_OVERSET_H overset.h
#else
# define SOURCES_OVERSET_C
# define SOURCES_OVERSET_H
#endif

#define SOURCES_NRMP_C nrbc.c nrbc2.c sg_nrbc.c sponge.c
#define SOURCES_NRMP_H nrbc.h nrbc2.h sponge.h

#define SOURCES_STEAM_C sg_wetsteam.c
#define SOURCES_STEAM_H sg_wetsteam.h

#if WORKING_CXX
# define SOURCES_MAIN main.c cxxmain.cpp
#else
# define SOURCES_MAIN main.c
#endif
# define LIB_SOURCE_MAIN flmain.c

/* .o files made for these */
#define SOURCES_C \
acoustics.c adjoint.c amark.c aniso_ref.c arrays.c \
c_fluid.c case.c casecheck.c check.c chemkin.c chip.c compare.c cudf.c domains.c dual_cell.c dx.c dx_abaqus.c \
dx_cgns.c dx_ascii.c dx_icemcfd.c dx_icecore.c dx_ansys.c dx_explorer.c dx_avs.c dx_fv.c \
dx_nastran.c dx_patran.c dx_ideas.c dx_tecplot.c dx_ensight.c dx_feamap.c dx_plot3d.c dx_gambit.c dx_maxwell.c event.c oned.c \
f_exterior.c f_fluid.c f_jump.c f_mfi.c f_periodic.c f_pfar.c f_pi.c f_po.c \
f_slide.c f_sym.c f_vi.c f_wall.c f_outflow.c \
filter.c cgns_imp.c flow.c flowf.c fluent_sc.c \
graph.c grid.c grid_rep_imp.c hang.c \
id.c intf_stretch.c lap_wd.c lmain.c \
machine.c materials.c mem.c memblock.c metric.c \
modal_analysis.c models.c msn.c \
para.c part.c poly.c poly_util.c profile.c prop.c prox.c \
real_gas.c reactor_network.c reorder.c rnglib.c roe.c rwdata.c rwdata_par.c \
rp_agglom.c rp_mg.c rp_mstage.c rp_recon.c rp_species.c rp_step.c rp_visc.c \
rp_amg.c amgif.c amg_hybrid.c amg_gpu.c krylov.c sg_reacting_channel.c sg_potential.c sg_li_battery.c battery.c \
sg_recon.c sg_deriv.c sg_init.c sg_update.c sg_mom.c sg_flux.c \
sg_press.c sg_mfp.c sg_dp.c sg_temp.c sg_ke.c sg_dtrm.c sg_melt.c \
sg_fmean.c sg_fvar.c sg_network.c sg_premixed.c sg_enthalpy.c sg_p1.c flcai.c \
sg_pdf.c pdf_graphics.c pdf_props.c pdf_properties.c pdf_table.c pdf_io.c pdf_table_auto_refine.c \
sg_species.c sg_sootspecies.c sg_swirl.c pscale.c coppalle.c smith.c wsggm.c \
sg_pollut.c pollut_hg.c pollut_nox.c pollut_soot.c pollut_sox.c pollut_soot_mom.c\
sg_disco.c coupled_disco.c sg_rstress.c sg_nut.c sg_uds.c sg_udm.c sg_vfr.c sg_s2s.c sg_cluster.c morpher.c \
sg_crev.c sg_spark.c flamelet.c sg_ignite.c  kinetics.c \
sg_glob.c sg_s2s_glob.c sg_heatxc.c splinemod.c piso.c turb_lib.c turb_wall.c turb_vm.c \
sg_dqmom.c pdf_transport.c phase_lag.c statistics.c solpos.c sg_solar.c tg_utils.c tg_mesh_part.c \
SOURCES_SOLVER_C \
sectio.c buffered_reader.c sect_write.c sect_read.c slide.c kd_tree.c virtpoly.c bsp.c dyn_bsearch.c smuswap.c species.c \
storage.c store.c storeif.c strf.c \
threads.c thread_tools.c turbo.c turbo_contour.c turbo_geom.c turbo_utils.c \
var.c unsteady.c velocity.c version.c visual_kinematics.c sg_exp_vof.c sg_openchannel.c \
sg_donor.c sg_drift.c sg_grvof.c sg_mphase.c sg_pb.c sg_iac.c sg_stens.c sg_vof.c mp_press.c \
mp_ke.c granular.c vof_dist.c vof_scale.c vof_casecheck.c mp_interact.c mp_mt.c mp_rxn.c granular_lib.c \
vof_to_dpm.c  dpm_to_vof.c       \
SOURCES_HOST_C SOURCES_NODE_C SOURCES_NOT_NODE_C \
SOURCES_CLLIB_C SOURCES_CXLIB_C \
drawpath.c dpm_film.c dpm.c dpm_mem.c dpm_laws.c dpm_tools.c dpm_path.c dpm_parallel.c dpm_breakup.c dpm_dem_wall.c dpm_dem.c dpm_domain.c isat.c random.c path.c sample.c unsteady_dpm.c dpm_injections.c \
root_utils.c linalg.c lsq.c cgeigen.c rp_steering.c hybrid_init.c mix_plane.c \
monitor.c error_handlers.c rp_post.c \
sg_ls.c \
SOURCES_SHELL_C \
SOURCES_DM_C \
SOURCES_NRMP_C \
SOURCES_HOLS_C \
SOURCES_STEAM_C \
SOURCES_OVERSET_C \
SOURCES_DPM_DIST_C \
SOURCES_ECFM_C \
SOURCES_FEM_C \
SOURCES_GEQN_C \
SOURCES_DPM_VOF_C \
SOURCES_RK_C \
SOURCES_REPGRAD_C \
SOURCES_WALL_FILM_C

/* The assembly code for lnia64 amg smooth1 */
#define SOURCES_S jgs_forward_dbl.s  jgs_forward_flt.s  jgs_reverse_dbl.s  jgs_reverse_flt.s

/* Add source files here that are to be compiled at a lower optimization level.
 * Files are to be specified in a platform specific manner and are compiled
 * using the flags in C_SWITCH_LOW_OPTIMIZE. Any C_SWITCH_LOW_OPTIMIZE definition
 * here overrides the default setting in makefile.c.
 * !!!! note that the .o files are actually listed here !!!! */
#if sys_debug && !sys_ntx86 && !sys_win64
#  define SOURCES_LOW_OPT src_low_opt_place_holder.o
#  define SOURCES_MID_OPT src_mid_opt_place_holder.o
#elif sys_lnia64
#  define C_SWITCH_LOW_OPTIMIZE -O1
#  define SOURCES_LOW_OPT sg_temp.o rp_step.o dx_ascii.o dynamesh.o mp_press.o reorder.o part.o sg_mom.o sg_ke.o smith.o
#  define C_SWITCH_LOW1_OPTIMIZE -tpp2 -ftz -O2 -mp
#  define SOURCES_LOW1_OPT prop.o sg_press.o check.o
#  define C_SWITCH_MID_OPTIMIZE -O2
#  define SOURCES_MID_OPT rp_recon.o sg_mphase.o virtpoly.o
#elif sys_lnamd64
# if _INTEL_CC
#  define C_SWITCH_LOW_OPTIMIZE -O1 -restrict -fp-model strict
#  define C_SWITCH_MID_OPTIMIZE -O3 -restrict  -ip -w -vec-report0 -no-vec
#  define C_SWITCH_MID1_OPTIMIZE -O3 -restrict -fp-model strict -ip -w -vec-report0
#  define SOURCES_MID_OPT sg_mfp.o
#  define SOURCES_MID1_OPT thread_tools.o
# else
#  define C_SWITCH_LOW_OPTIMIZE -O1 -restrict
# endif
#  define SOURCES_LOW_OPT pollut_nox.o
#elif sys_lnx86 || sys_lnx86_rh8
#  define C_SWITCH_LOW_OPTIMIZE -O1
#  define SOURCES_LOW_OPT grid.o mp_press.o bsp.o sg_press.o
#  define C_SWITCH_MID_OPTIMIZE
#  define SOURCES_MID_OPT turb_vm.o
#elif sys_hpux11_ia64
#  define C_SWITCH_MID_OPTIMIZE -O2
#  define SOURCES_MID_OPT part.o dpm_film.o
#  define C_SWITCH_LOW_OPTIMIZE -O1
#if RP_DOUBLE
#  define SOURCES_LOW_OPT dynamesh_tools.o
#endif
#elif sys_hpux11
#  define C_SWITCH_LOW_OPTIMIZE -O2
#  define SOURCES_LOW_OPT sectio.o
#elif sys_ultra_64
#  define C_SWITCH_LOW_OPTIMIZE -xtarget=ultra3 -xprefetch_level=2 -xdepend=no -W2,-Apf:pdl=1 -W2,-Apf:outer -Wc,-Qlp-ol=1
#  define SOURCES_LOW_OPT sg_wetsteam.o
#  define C_SWITCH_LOW1_OPTIMIZE -xtarget=ultra3 -xmaxopt=5 -xprefetch_level=2 -W2,-Apf:pdl=1 -W2,-Apf:outer -Wc,-Qlp-ol=1
#  define SOURCES_LOW1_OPT granular_lib.o turbo.o storage.o
#if RP_DOUBLE
#  define C_SWITCH_MID_OPTIMIZE -xtarget=ultra3 -xprefetch_level=2 -xdepend=no -W2,-Apf:pdl=1 -W2,-Apf:outer -Wc,-Qlp-ol=1
#  define C_SWITCH_MID1_OPTIMIZE -xO4 -xtarget=ultra3 -xmaxopt=5 -xprefetch_level=2 -xdepend=no -W2,-Apf:pdl=1 -W2,-Apf:outer -Wc,-Qlp-ol=1
#  define SOURCES_MID1_OPT f_wall.o rp_recon.o sg_temp.o sg_species.o
#else
#  define C_SWITCH_MID_OPTIMIZE -xtarget=ultra3 -xmaxopt=5 -xprefetch_level=2 -W2,-Apf:pdl=1 -W2,-Apf:outer -Wc,-Qlp-ol=1
#endif
#  define SOURCES_MID_OPT sg_mom.o
#elif sys_ntx86|| sys_win64
C_SWITCH_LOW_OPTIMIZE = / O1
                          SOURCES_LOW_OPT = amgif.obj
                                            C_SWITCH_MID_OPTIMIZE = / O3 / Op
                                                                      SOURCES_MID_OPT = sg_mphase.obj
#elif sys_irix65_mips4_64
/*#  define C_SWITCH_LOW_OPTIMIZE -O3 -OPT:IEEE_arithmetic=3:roundoff=3:Olimit=8000:alias=typed:alias=restrict -LNO:fusion=2:fission=0:prefetch=2*/
#  define SOURCES_LOW_OPT amg.o sg_deriv.o sg_mom.o sg_press.o sg_recon.o visual_kinematics.o
#elif sys_aix51
#if RP_DOUBLE
#  define C_SWITCH_LOW_OPTIMIZE
#  define SOURCES_LOW_OPT visual_kinematics.o
#endif
#elif sys_aix51 || sys_aix51_64
#  define C_SWITCH_MID_OPTIMIZE -O2 -DAIX_C_OPT_PRAGMA -U__STR__ -U__MATH__
#  define SOURCES_MID_OPT poly.o
#  define C_SWITCH_MID1_OPTIMIZE -O3 -qstrict -DAIX_C_OPT_PRAGMA
#  define SOURCES_MID1_OPT redlich_kwong.o dynamesh_tools.o
#  define C_SWITCH_LOW_OPTIMIZE -O3 -DAIX_C_OPT_PRAGMA  -qinline+evaluate_polynomial:evaluate_polynomial_integral:evaluate_polynomial_plinear
#  define SOURCES_LOW_OPT dpm.o f_jump.o f_pi.o f_po.o prop.o rp_mstage.o sg_heatxc.o sg_init.o sg_mom.o sg_network.o sg_press.o sg_solar.o sg_stens.o sg_temp.o dpm_film.o sg_species.o
#  define C_SWITCH_LOW1_OPTIMIZE -DAIX_C_OPT_PRAGMA
#  define SOURCES_LOW1_OPT sg_pollut.o pollut_hg.o pollut_nox.o pollut_soot.o pollut_sox.o mp_mt.o
#  if sys_aix51_64
#    define C_SWITCH_OMP_OPTIMIZE -O3 -DAIX_C_OPT_PRAGMA -qsmp=omp
#    define SOURCES_OMP_OPT amg.o
#  endif
#else
#  define SOURCES_LOW_OPT src_low_opt_place_holder.o
#  define SOURCES_LOW1_OPT src_low1_opt_place_holder.o
#  define SOURCES_MID1_OPT src_mid1_opt_place_holder.o
#  define SOURCES_MID_OPT src_mid_opt_place_holder.o
#endif

#define SOURCES_H \
amark.h aniso_ref.h arrays.h \
c_fluid.h case.h mem_dump.h casecheck.h check.h compare.h config.h cudf.h udf_util.h sg_udms.h \
domains.h dual_cell.h dx.h dx_abaqus.h dx_cgns.h dx_ascii.h dx_icemcfd.h dx_icecore.h  dx_ansys.h dx_avs.h dx_fv.h \
dx_explorer.h dx_nastran.h dx_patran.h dx_ideas.h dx_tecplot.h dx_ensight.h dx_plot3d.h dx_gambit.h dx_maxwell.h event.h oned.h \
f_exterior.h f_fluid.h f_jump.h f_mfi.h f_periodic.h f_pfar.h f_pi.h f_po.h \
f_slide.h f_sym.h f_vi.h f_wall.h f_outflow.h \
filter.h cgns_imp.h flow.h flowf.h fluent_sc.h \
global.h graph.h grid.h grid_rep_imp.h hang.h \
id.h intf_stretch.h lmain.h \
machine.h materials.h mem_grid.h mem.h memblock.h metric.h \
modal_analysis.h models.h mix_plane.h\
para.h part.h poly.h prf.h profile.h prop.h prox.h \
real_gas.h reorder.h rng.h roe.h rwdata.h drawpath.h \
rp_agglom.h rp_mem.h rp_mg.h rp_mstage.h rp_steering.h \
rp_amg.h amgif.h \
sg.h sg_dtrm.h sg_network.h chemkin.h pscale.h coppalle.h smith.h wsggm.h \
sg_pdf.h sg_sootspecies.h pdf_graphics.h pdf_props.h pdf_table.h \
sg_pollut.h pollut_hg.h pollut_nox.h pollut_soot.h pollut_sox.h \
sg_press.h sg_mem.h sg_disco.h sg_vfr.h sg_s2s.h sg_glob.h sg_cluster.h morpher.h \
sg_heatxc.h blackbf.h  solpos.h sg_solar.h flcai.h \
sg_crev.h sg_spark.h flamelet.h sg_ignite.h kinetics.h \
turb_ke.h turb_rst.h turb_wall.h turb.h sg_ke.h pdf_transport.h acoustics.h statistics.h tg_utils.h tg_mesh_part.h sg_reacting_channel.h \
SOURCES_SOLVER_H \
sectio.h slide.h kd_tree.h virtpoly.h bsp.h dyn_bsearch.h smuswap.h species.h sg_li_battery.h battery.h \
storage.h store.h storeif.h \
threads.h thread_tools.h turbo.h udf.h unsteady.h var.h version.h visual_kinematics.h \
sg_mphase.h sg_vof.h granular.h sg_pb.h sg_iac.h \
SOURCES_HOST_H SOURCES_NODE_H SOURCES_NOT_NODE_H \
SOURCES_CLLIB_H SOURCES_CXLIB_H SOURCES_DPM_H \
cpd.h root_utils.h cbk.h dpm_parallel.h random.h sample.h reduce_sample_data.h \
linalg.h lsq.h sg_ls.h \
monitor.h error_handlers.h \
SOURCES_SHELL_H \
SOURCES_DM_H \
SOURCES_NRMP_H \
SOURCES_HOLS_H \
SOURCES_STEAM_H \
SOURCES_OVERSET_H \
SOURCES_ECFM_H \
SOURCES_FEM_H \
SOURCES_GEQN_H \
SOURCES_DPM_DIST_H \
SOURCES_DPM_VOF_H \
SOURCES_RK_H \
SOURCES_REPGRAD_H \
SOURCES_WALL_FILM_H

/* used for 'make sources' */
#define SOURCES_ALL_C SOURCES_MAIN SOURCES_C SOURCES_ALL_HOST_C SOURCES_ALL_NODE_C SOURCES_ALL_DM_C SOURCES_ALL_SOLVER_C SOURCES_DPM_DIST_C SOURCES_ECFM_C SOURCES_GEQN_C SOURCES_RK_C Makefile.udf makefile.udf

#define SOURCES_ALL_H SOURCES_H SOURCES_ALL_HOST_H SOURCES_ALL_NODE_H SOURCES_ALL_DM_H SOURCES_ALL_SOLVER_H SOURCES_ECFM_H SOURCES_GEQN_H SOURCES_RK_H sources.h

#endif /* _FLUENT_SOURCES_H */

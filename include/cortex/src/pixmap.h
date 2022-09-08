/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#include <xpm.h>
#include <ansys_fluent.xpm>
#include <autoScaledisabled.xpm>
#include <autoScale.xpm>
#include <helpdisabled.xpm>
#include <help.xpm>
#include <isometricdisabled.xpm>
#include <isometric.xpm>
#include <viewplusx.xpm>
#include <viewplusy.xpm>
#include <viewplusz.xpm>
#include <viewminusx.xpm>
#include <viewminusy.xpm>
#include <viewminusz.xpm>
#include <viewcomponentsdisabled.xpm>
#include <viewcomponents.xpm>
#include <graphicslayout.xpm>
#include <graphicslayoutdisabled.xpm>
#include <probedisabled.xpm>
#include <rollzoomdisabled.xpm>
#include <rollzoom.xpm>
#include <readdisabled.xpm>
#include <read.xpm>
#include <rotatedisabled.xpm>
#include <savePicturedisabled.xpm>
#include <savePicture.xpm>
#include <rotate.xpm>
#include <translatedisabled.xpm>
#include <translate.xpm>
#include <writedisabled.xpm>
#include <write.xpm>
#include <zoomdisabled.xpm>
#include <zoom.xpm>
#include <probe.xpm>
#include <down.xpm>
#include <downdisabled.xpm>
#include <ansys_tgrid.xpm>
#include <model.xpm>
#include <model_disabled.xpm>
#include <setup.xpm>
#include <setup_disabled.xpm>
#include <meshdisplayconfigurations.xpm>
#include <meshdisplayconfigurationsdisabled.xpm>
#include <faceoptions.xpm>
#include <faceoptions_disabled.xpm>
#include <objectoptions.xpm>
#include <objectoptions_disabled.xpm>
#include <fl_mesh_generation.xpm>
#include <fl_setup.xpm>
#include <fl_general.xpm>
#include <fl_materials.xpm>
#include <fl_models.xpm>
#include <fl_cell_zones.xpm>
#include <fl_boundary_zones.xpm>
#include <fl_mesh_interface.xpm>
#include <fl_reference_values.xpm>
#include <fl_dynamic_mesh.xpm>
#include <fl_models_node.xpm>
#include <fl_materials_node.xpm>
#include <fl_cell_zones_node.xpm>
#include <fl_boundary_zones_node.xpm>
#include <fl_solution.xpm>
#include <fl_solution_methods.xpm>
#include <fl_solution_controls.xpm>
#include <fl_monitors.xpm>
#include <fl_solution_initialization.xpm>
#include <fl_calculation_activities.xpm>
#include <fl_run_calculation.xpm>
#include <fl_results.xpm>
#include <fl_graphics.xpm>
#include <fl_mesh.xpm>
#include <fl_contours.xpm>
#include <fl_vectors.xpm>
#include <fl_pathlines.xpm>
#include <fl_particle_tracks.xpm>
#include <fl_animations.xpm>
#include <fl_plots.xpm>
#include <fl_reports.xpm>
#include <fl_parameters_and_customization.xpm>
#include <fl_parameters.xpm>
#include <fl_custom_field_functions.xpm>
#include <fl_user_defined_functions.xpm>
#include <fl_user_defined_scalars.xpm>
#include <fl_user_defined_memory.xpm>
#include <plus.xpm>
#include <minus.xpm>
#include <meshermodel.xpm>
#include <geometry.xpm>
#include <geomobj.xpm>
#include <mesh.xpm>
#include <meshobj.xpm>
#include <parts.xpm>
#include <meshpart.xpm>
#include <regions.xpm>
#include <meshregion.xpm>
#include <unreferenced.xpm>
#include <graphicsview1.xpm>
#include <graphicsview2h.xpm>
#include <graphicsview2v.xpm>
#include <graphicsview3h.xpm>
#include <graphicsview3v.xpm>
#include <graphicsview4.xpm>
#include <fluent_logo.xpm>
#include <tgrid_logo.xpm>
#include <viewNavConsole.xpm>
#include <viewTaskConsole.xpm>
#include <viewGraphicsConsole.xpm>
#include <viewTreeTaskbelowConsole.xpm>
#include <viewTreeTasksideConsole.xpm>
#include <viewTaskGraphicsConsole.xpm>
#include <viewNavGraphicsConsole.xpm>
#include <viewAllwithTaskbelow.xpm>
#include <viewAllwithTaskside.xpm>
#include <viewConsole.xpm>
#include <meshoperations.xpm>
#include <parameters.xpm>
#include <refresh.xpm>
#include <reloadsetup.xpm>
#include <syncwb.xpm>
#include <bodyinactive.xpm>
#include <component.xpm>
#include <componentinactive.xpm>
#include <hierarchy.xpm>
#include <label.xpm>
#include <labelinactive.xpm>
#include <suppressed.xpm>
#include <objupdate.xpm>


typedef struct
{
  char *name ;
  char **data ;
} PixmapData ;

#define PIXMAP(name) {QUOTE(name), (char **)CAT(name,_xpm)}

static PixmapData pixmaps [] =
{
  PIXMAP(ansys_fluent),
  PIXMAP(autoscale_disabled),
  PIXMAP(autoscale),
  PIXMAP(help),
  PIXMAP(help_disabled),
  PIXMAP(isometric),
  PIXMAP(isometric_disabled),
  PIXMAP(viewplusx),
  PIXMAP(viewplusy),
  PIXMAP(viewplusz),
  PIXMAP(viewminusx),
  PIXMAP(viewminusy),
  PIXMAP(viewminusz),
  PIXMAP(viewcomponents),
  PIXMAP(viewcomponents_disabled),
  PIXMAP(graphicslayout),
  PIXMAP(graphicslayout_disabled),
  PIXMAP(probe_disabled),
  PIXMAP(probe),
  PIXMAP(read),
  PIXMAP(read_disabled),
  PIXMAP(rollzoom_disabled),
  PIXMAP(rollzoom),
  PIXMAP(rotate_disabled),
  PIXMAP(savepicture_disabled),
  PIXMAP(savepicture),
  PIXMAP(rotate),
  PIXMAP(translate_disabled),
  PIXMAP(translate),
  PIXMAP(write),
  PIXMAP(write_disabled),
  PIXMAP(zoom_disabled),
  PIXMAP(zoom),
  PIXMAP(savepicture),
  PIXMAP(autoscale),
  PIXMAP(down),
  PIXMAP(down_disabled),
  PIXMAP(ansys_tgrid),
  PIXMAP(model),
  PIXMAP(model_disabled),
  PIXMAP(setup),
  PIXMAP(setup_disabled),
  PIXMAP(meshdisplayconfigurations),
  PIXMAP(meshdisplayconfigurations_disabled),
  PIXMAP(faceoptions),
  PIXMAP(faceoptions_disabled),
  PIXMAP(objectoptions),
  PIXMAP(objectoptions_disabled),
  PIXMAP(fl_mesh_generation),
  PIXMAP(fl_setup),
  PIXMAP(fl_general),
  PIXMAP(fl_materials),
  PIXMAP(fl_models),
  PIXMAP(fl_cell_zones),
  PIXMAP(fl_boundary_zones),
  PIXMAP(fl_mesh_interface),
  PIXMAP(fl_reference_values),
  PIXMAP(fl_dynamic_mesh),
  PIXMAP(fl_models_node),
  PIXMAP(fl_materials_node),
  PIXMAP(fl_cell_zones_node),
  PIXMAP(fl_boundary_zones_node),
  PIXMAP(fl_solution),
  PIXMAP(fl_solution_methods),
  PIXMAP(fl_solution_controls),
  PIXMAP(fl_monitors),
  PIXMAP(fl_solution_initialization),
  PIXMAP(fl_calculation_activities),
  PIXMAP(fl_run_calculation),
  PIXMAP(fl_results),
  PIXMAP(fl_graphics),
  PIXMAP(fl_mesh),
  PIXMAP(fl_contours),
  PIXMAP(fl_vectors),
  PIXMAP(fl_pathlines),
  PIXMAP(fl_particle_tracks),
  PIXMAP(fl_animations),
  PIXMAP(fl_plots),
  PIXMAP(fl_reports),
  PIXMAP(fl_parameters_and_customization),
  PIXMAP(fl_parameters),
  PIXMAP(fl_custom_field_functions),
  PIXMAP(fl_user_defined_functions),
  PIXMAP(fl_user_defined_scalars),
  PIXMAP(fl_user_defined_memory),
  PIXMAP(plus),
  PIXMAP(minus),
  PIXMAP(meshermodel),
  PIXMAP(geometry),
  PIXMAP(geomobj),
  PIXMAP(mesh),
  PIXMAP(meshobj),
  PIXMAP(parts),
  PIXMAP(meshpart),
  PIXMAP(regions),
  PIXMAP(meshregion),
  PIXMAP(unreferenced),
  PIXMAP(graphicsview1),
  PIXMAP(graphicsview1_disabled),
  PIXMAP(graphicsview2h),
  PIXMAP(graphicsview2h_disabled),
  PIXMAP(graphicsview2v),
  PIXMAP(graphicsview2v_disabled),
  PIXMAP(graphicsview3v),
  PIXMAP(graphicsview3v_disabled),
  PIXMAP(graphicsview3h),
  PIXMAP(graphicsview3h_disabled),
  PIXMAP(graphicsview4),
  PIXMAP(graphicsview4_disabled),
  PIXMAP(tgrid_logo),
  PIXMAP(fluent_logo),
  PIXMAP(viewNavConsole),
  PIXMAP(viewNavConsole_disabled),
  PIXMAP(viewTaskConsole),
  PIXMAP(viewTaskConsole_disabled),
  PIXMAP(viewGraphicsConsole),
  PIXMAP(viewGraphicsConsole_disabled),
  PIXMAP(viewTreeTaskbelowConsole),
  PIXMAP(viewTreeTaskbelowConsole_disabled),
  PIXMAP(viewTreeTasksideConsole),
  PIXMAP(viewTreeTasksideConsole_disabled),
  PIXMAP(viewTaskGraphicsConsole),
  PIXMAP(viewTaskGraphicsConsole_disabled),
  PIXMAP(viewNavGraphicsConsole),
  PIXMAP(viewNavGraphicsConsole_disabled),
  PIXMAP(viewAllwithTaskbelow),
  PIXMAP(viewAllwithTaskbelow_disabled),
  PIXMAP(viewAllwithTaskside),
  PIXMAP(viewAllwithTaskside_disabled),
  PIXMAP(viewConsole),
  PIXMAP(viewConsole_disabled),
  PIXMAP(reloadsetup),
  PIXMAP(reloadsetup_disabled),
  PIXMAP(refresh),
  PIXMAP(refresh_disabled),
  PIXMAP(parameters),
  PIXMAP(parameters_disabled),
  PIXMAP(meshoperations),
  PIXMAP(meshoperations_disabled),
  PIXMAP(syncwb),
  PIXMAP(syncwb_disabled),
  PIXMAP(bodyinactive),
  PIXMAP(component),
  PIXMAP(componentinactive),
  PIXMAP(hierarchy),
  PIXMAP(label),
  PIXMAP(labelinactive),
  PIXMAP(suppressed),
  PIXMAP(objupdate),

  {NULL, NULL},
} ;

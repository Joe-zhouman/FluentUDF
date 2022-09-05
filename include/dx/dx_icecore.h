/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef DX_ICECORE_H
#define DX_ICECORE_H

#include "dll.h"

#if SEEM
#if HDF_LIB
#include "hdf5.h"

/* Export data in given hdf file.
 * filename      : hdf filename
 * casefilename  : Needs to be supplied from scheme side.
 * solutionName  : Name of solution
 * stepName      : Name of the current time step data       [default is step.N_TIME]
 * overWrite     : whether to create a new hdf file or append in the file if already exits
 */

FLUENT_EXPORT void      H5Ice_write_IceCore(Domain *domain, char *filename,, char *casefilename, char *solutionName, char *stepName, cxboolean overWrite);

/* Enable printing of error/warning messages from hdf library */
FLUENT_EXPORT cxboolean H5Ice_print_Hdf_Error(const cxboolean enable);

#endif  /* HDF_LIB */
#endif  /*  SEEM */

#endif

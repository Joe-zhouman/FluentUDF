/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_ADJOINT_H_
#define _FLUENT_ADJOINT_H_

FLUENT_EXPORT int Open_Adjoint_Library(void);
FLUENT_EXPORT void InitializeAdjointPrimitives(void);

FLUENT_EXPORT void adjoint_write_residuals( FILE *fp );
FLUENT_EXPORT void adjoint_read_residual_section( FILE *fp );

FLUENT_EXPORT void Write_Sparse_Field_Data_Section( FILE *fp, cxboolean binary );
FLUENT_EXPORT void adjoint_read_sparse_data_section( FILE *fp, cxboolean binary );

FLUENT_EXPORT void adjoint_adjustment(void);
#endif

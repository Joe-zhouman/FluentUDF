/*
* Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "global.h"
#include "seem.h"

FLUENT_EXPORT int Get_Report_Definition_Values(const char *name, int timeStepOrIteration, int *nrOfvalues, real *values, int *ids, int *index);

FLUENT_EXPORT Pointer Show_File_Permission(const char *path, const char *mode);
FLUENT_EXPORT Pointer Show_Folder_Permission(const char *path, const char *mode);
/* Function to add ReportDefinition set*/
FLUENT_EXPORT void Add_ReportClient(const char *type, const char *reportDefinitionSetName, Pointer p);

FLUENT_EXPORT void Delete_ReportClient(const char *type, const char *reportDefinitionSetName);
FLUENT_EXPORT void Rename_ReportClient(const char *type, const char *reportDefinitionSetName, const char *reportDefinitionSetNewName);

/*Function to set ReportDefinition set properties*/
/*Pointer will be list which must contain following items:
     frequency <int>
     file-name <string>
*/
FLUENT_EXPORT void Set_ReportClient_Properties(const char *type, const char *reportDefinitionSetName, Pointer p);



/* Function to add ReportDefinition to a ReportDefinition set*/
/*Pointer will be list which must contain following items:
     reportDefinition-type  <string> (volume, surface, force, moment, ..)
     function-type <string> (min, max, average,..)
*/
FLUENT_EXPORT void Add_ReportDefinition(const char *reportDefinitionName, const char *reportDefinitionType, Pointer p);

FLUENT_EXPORT void Delete_ReportDefinition(const char *reportDefinitionName);

FLUENT_EXPORT void Rename_ReportDefinition(const char *reportDefinitionName, const char *reportDefinitionNewName);

/* Function to set properties to a ReportDefinition*/
/*Pointer will be list which should contain following items:
      field        <string> (temperature, pressure...)
      zone-ids     <int>
      surface-ids  <int>
      average-over <int>
      per-zone?    <bool>

*/
FLUENT_EXPORT void Set_ReportDefinition_Properties(const char *reportDefinitionName, Pointer p);



FLUENT_EXPORT int Is_Any_ReportDefinition_Active(size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT Pointer Get_Active_ReportDefinitions(size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT Pointer Get_Next_Flow_Time_For_ReportDefinitions(double flowTime);

FLUENT_EXPORT Pointer Get_Active_ReportDefinitions_Field(size_t itrIndex, size_t timeIndex, int withNodeValues);

FLUENT_EXPORT void Evaluate_Mesh_ReportDefinitions(size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT void Evaluate_Field_ReportDefinitions(const char *fieldName, int locationType, size_t itrIndex, size_t timeIndex, int hasNodeValue);

FLUENT_EXPORT void Evaluate_Field_ReportDefinitions_With_Custom_Vector(const char *fieldName, const char *customVector, size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT void Evaluate_Non_Field_ReportDefinitions_With_Custom_Vector(const char *customVector, size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT void Evaluate_Force_Moment_ReportDefinitions(size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT Pointer Get_Custom_Vectors(const char *fieldName, size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT void Evaluate_Non_Field_ReportDefinitions(size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT void Evaluate_Udf_ReportDefinitions(size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT void Evaluate_Aerodamping_ReportDefinitions(size_t itrIndex, size_t timeIndex);
FLUENT_EXPORT void Evaluate_ModalForce_ReportDefinitions(size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT Pointer Get_ReportDefinitions_Data(size_t itrIndex, size_t timeIndex);

FLUENT_EXPORT Pointer Get_Average_Over_State();
FLUENT_EXPORT Pointer Get_Average_Over_Data();

FLUENT_EXPORT Pointer Get_Integrate_Over_State();
FLUENT_EXPORT void Set_Integrate_Over_State(Pointer p);

FLUENT_EXPORT void Clear_ReportDefinition_Set_History(const char *reportDefinitionSetName);

FLUENT_EXPORT void Set_Average_Over_Data(Pointer args);
FLUENT_EXPORT void Set_Average_Over_State(Pointer p);

FLUENT_EXPORT Pointer Recompute_Moving_Average(const char *reportDefinitionName, const char *freqof);
FLUENT_EXPORT void Read_Report_Definition_History(const char *reportDefinitionName, const int datasize);

FLUENT_EXPORT void Report_Definition_Init(int);

FLUENT_EXPORT void Write_ReportDefinition_Data_To_File(size_t itrIndex, size_t timeIndex, int previousIteration);

FLUENT_EXPORT void Write_ReportDefinition_Data_To_File_GPUAPP(size_t itrIndex, size_t timeIndex, int previousIteration, Pointer p);

FLUENT_EXPORT Pointer Read_Report_Definition_Data_From_File(const char *reportDefName,  const char *freqof, const char *xaxis, size_t size);

FLUENT_EXPORT Pointer Read_Data_From_Report_File(const char *reportDefinitionSetName, size_t size);

FLUENT_EXPORT Pointer Create_ReportDefinition_Set_File(const char *reportDefinitionSetName);

FLUENT_EXPORT void Release_File_Handle(const char *reportDefinitionName);

FLUENT_EXPORT void Print_ReportDefinitions();
#ifdef __cplusplus
}
#endif

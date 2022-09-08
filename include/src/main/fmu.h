/*
 *  *  *  * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 *   *   *   */

#ifndef _FLUENT_FMU_H_
#define _FLUENT_FMU_H_

#include "FMULib/fmuLib.h"

extern FLUENT_EXPORT FMUid fmu_id;
extern FLUENT_EXPORT InstanceID fmu_instance_ID;
extern FLUENT_EXPORT fmi2String fmu_modelName;
extern FLUENT_EXPORT fmi2String fmu_instanceName;
extern FLUENT_EXPORT struct CoSimulation fmu_cosim;
extern FLUENT_EXPORT size_t fmu_numScalarVar;
extern FLUENT_EXPORT size_t fmu_numInput;
extern FLUENT_EXPORT size_t fmu_numOutput;
extern FLUENT_EXPORT size_t fmu_numPara;
extern FLUENT_EXPORT size_t fmu_numLocal;

extern FLUENT_EXPORT fmi2FMUstate fmu_FMUstate;
extern FLUENT_EXPORT size_t fmu_statesize;
extern FLUENT_EXPORT int fmu_statesize_writeout;
extern FLUENT_EXPORT fmi2Byte *fmu_serializedState;
extern FLUENT_EXPORT fmi2Byte *fmu_serializedState_writeout;

extern FLUENT_EXPORT fmi2Type fmuType;

extern FLUENT_EXPORT cxboolean fmu_isrestart;

extern FLUENT_EXPORT fmi2String *fmu_inputVariableNames, *fmu_outputVariableNames, *fmu_paraVariableNames, *fmu_localVariableNames;
extern FLUENT_EXPORT fmi2String *fmu_inputVariableUnitNames, *fmu_outputVariableUnitNames;
extern FLUENT_EXPORT fmi2ValueReference *fmu_valueRefsIn, *fmu_valueRefsOut;
extern FLUENT_EXPORT fmi2Real *fmu_inputValues, *fmu_outputValues;

extern FLUENT_EXPORT struct ScalarVariable *fmu_parameters, *fmu_localvariables;

FLUENT_EXPORT void Register_FMU_HDF_IO_Manager(void);
FLUENT_EXPORT void Deregister_FMU_HDF_IO_Manager(void);
#endif

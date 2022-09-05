/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

typedef struct KIN_Function_struct
{
  void (*KINGetProcessID)(double *kin_dpid);
  void (*KINSetProcessID)(int *kin_ipid);
  int (*KINPreProcess)(int *bSurface, int *bTransport, char *sGasInFile, char *sSurfInFile,
                       char *sThermoFile, char *sTranFile, char *sGasLinkFile,
                       char *sSurfLinkFile, char *sTranLinkFile, char *sDiagnosticsFile,
                       int *iChemSetIndex);
  int (*KINPreProcessWithXML)(int *bSurface, int *bTransport, char *sGasInFile, char *sSurfInFile,
                              char *sThermoFile, char *sTranFile, char *sGasLinkFile,
                              char *sSurfLinkFile, char *sTranLinkFile, char *sXMLFile,
                              char *sDiagnosticsFile, int *iChemSetIndex);
  char *(*KINGetErrorMessages)(int *iErrorIndex);
  void (*KINEraseErrorMessages)(void);
  int (*KINReLink)(int *bSurface, int *bTransport, char *sGasLinkFile, char *sSurfLinkFile,
                   char *sTranLinkFile, char *sDiagnosticsFile, int *iChemSetIndex);
  int (*KINInitialize)(int *iChemSetIndex, int *bSteady);
  int (*KINSetTransientFormulation) (int *iChemSetIndex, int *iTransientFormulation);
  int (*KINSetPrintLevel)(int *iChemSetIndex, int *iPrintLevel);
  int (*KINSetAuxiliaryInputFile)(int *iChemSetIndex, char *sAuxiliaryInputFile);
  int (*KINSetDefaultTolerances)(int *iChemSetIndex, double *dAbsoluteTolerance,
                                 double *dRelativeTolerance, int *iCellType);
  int (*KINSetInitialTimeStep)(int *iChemSetIndex, double *dInitialTimeStep);
  int (*KINSetMaximumTimeStep)(int *iChemSetIndex, double *dMaximumTimeStep);
  int (*KINSetMinimumTimeStep)(int *iChemSetIndex, double *dMinimumTimeStep);
  int (*KINSetMaxAttempts)(int *iChemSetIndex, int *iMaxAttempts);
  int (*KINSetParameter)(int *iChemSetIndex, char *sParameterString, double *dParameterValue);
  int (*KINSetCellSurface)(int *iChemSetIndex, int *iFaceIndex, int *iMaterialIndex, double *dSurfaceArea,
                           double *dSurfaceTemperature, double *pInitialSiteFractions,
                           double *pInitialBulkActivities);
  int (*KINSetSurfaceAreaFactor)(int *iChemSetIndex, int *iFaceIndex, double *dFactor);
  int (*KINCalculateCell)(int *iChemSetIndex, int *bMonitorCell, int *iCellID, int *iClosureModel,
                          int *bUseInitialTimeSteps, double *dCFDTimeStep, int *iNumberFaces, double *dVolume,
                          double *dPressure, double *dTemperature, double *pMassFractions,
                          double *dEnthalpyFlowIn, double *dTMultiplier, double *pSpeciesFlowIn,
                          double *pYMultiplier, double *dMassFlowIn);
  int (*KINApplyAdaptiveChemistry)(int *iChemSetIndex, double *dPressure, double *dTemperature, double *dMassFractions,
                                   int *ntargetspecies, int *targetspeciesindex, int *Base0, double *dac_torr);
  int (*KINGetActiveChemistry)(int *iChemSetIndex, int *Base0, int *nActiveSpecies, int   *pActiveSpecies, int *nActiveRXN, int *pActiveRXN);
  int (*KINGetCellState)(int *iChemSetIndex, double *dTemperature, double *pMassFractions,
                         double *dGasEnthalpyProdRate, double *pGasSpeciesProdRate);
  int (*KINGetCellSurface)(int *iChemSetIndex, int *iFaceIndex, double *pSiteFractions,
                           double *pBulkActivities, double *dSurfEnthalpyProdRate,
                           double *pSurfSpeciesProdRate, double *pSiteProdRate,
                           double *pBulkProdRate);
  int (*KINGetGasROP) (int *iChemSetIndex, double *dTemperature, double *dPressure,
                       double *dMassFractions, double *dGasROP);
  int (*KINGetViscosity) (int *iChemSetIndex, double *dTemperature, double *pViscosity);
  int (*KINGetConductivity) (int *iChemSetIndex, double *dTemperature, double *pConductivity);
  int (*KINGetDiffusionCoeffs) (int *iChemSetIndex, double *dPressure, double *dTemperature, double *pDiffusionCoeffs);
  int (*KINGetMixtureConductivity) (int *iChemSetIndex, double *dTemperature, double *pMassFractions,
                                    double *dMixtureConductivity);
  int (*KINGetMixtureDiffusionCoeffs) (int *iChemSetIndex, double *dPressure, double *dTemperature, double *pMassFractions,
                                       double *pMixtureDiffusionCoeffs);
  int (*KINGetMixtureViscosity) (int *iChemSetIndex, double *dTemperature, double *pMassFractions, double *dMixtureViscosity);
  int (*KINGetThermalDiffusionRatio) (int *iChemSetIndex, double *dTemperature, double *pMassFractions,
                                      double *pThermalDiffusionRatio);
  int (*KINGetOrdinaryDiffusionCoeffs) (int *iChemSetIndex, double *dPressure, double *dTemperature, double *pMassFractions,
                                        double *pOrdinaryDiffusionCoeffs);
  int (*KINGetThermalDiffusionCoeffs) (int *iChemSetIndex, double *dPressure, double *dTemperature, double *pMassFractions,
                                       double *pThermalDiffusionCoeffs, double *dMixtureThermalConductivity);
  int (*KINGetGasSpecificHeat) (int *iChemSetIndex, double *dTemperature, double *pGasSpecificHeat);
  int (*KINGetGasSpeciesEnthalpy) (int *iChemSetIndex, double *dTemperature, double *pGasEnthalpy);
  int (*KINGetGasMixtureEnthalpy) (int *iChemSetIndex, double *dTemperature, double *pMassFractions, double *dGasMixtureEnthalpy);
  void (*KINFinish)(void);
  void (*KINFinalize)(int *kin_ipid);
  int (*KINGetChemistrySizes) (int *iChemSetIndex, int *iNumElements, int *iNumGasSpecies, int *
                               iNumGasReactions, int *iNumMaterials, int *iMaxSiteSpecies, int *
                               iMaxBulkSpecies, int *iMaxPhases, int *iMaxSurfReactions);
  int (*KINGetMaterialSizes) (int *iChemSetIndex, int *iMaterialIndex, int *iNumSiteSpecies,
                              int *iNumBulkSpecies, int *iNumPhases, int *iNumSurfReactions) ;
  int (*KINGetElementNames) (int *iChemSetIndex, char **sElementNames);
  int (*KINGetAtomicWeights) (int *iChemSetIndex, double *dAtomicWeights);
  int (*KINGetGasSpeciesNames) (int *iChemSetIndex, char **sGasSpeciesNames);
  int (*KINGetGasMolecularWeights) (int *iChemSetIndex, double *dGasMolWeights);
  int (*KINGetThermodynamicFits) (int *iChemSetIndex, double *dTemperature, double *dThermodynamicFits);
  int (*KINGetNumGasThermoFitRanges) (int *iChemSetIndex, int *nMaxRanges);
  int (*KINGetNumGasThermoFitCoefficients) (int *iChemSetIndex, int *nMaxCoef);
  int (*KINGetNumGasThermoSpeciesFitTemp) (int *iChemSetIndex, int *nFitTemps);
  int (*KINGetNumSurfThermoFitRanges) (int *iChemSetIndex, int *iMaterialIndex, int *nMaxRanges);
  int (*KINGetTransportPropertyData) (int *iChemSetIndex, double *dEpsilon, double *dSigma,
                                      double *dDipoleMoment, double *dPolarizability,
                                      double *dzRotationalNumer, int *iNonlinearity);
  int (*KINGetMaterialNames) (int *iChemSetIndex, char **sMaterialNames);
  int (*KINGetPhaseSizes) (int *iChemSetIndex, int *iMaterialIndex, int *iNumPhases, int *iNumSitePhases,
                           int *iNumBulkPhases);
  int (*KINGetPhaseNames) (int *iChemSetIndex, int *iMaterialIndex, char **sPhaseNames);
  int (*KINGetPhaseSpeciesIndices) (int *iChemSetIndex, int *iMaterialIndex, int *pNumSpecies, int *pFirstSpecies,
                                    int *pLastSpecies, int *bBase0);
  int (*KINGetSiteNames) (int *iChemSetIndex, int *iMaterialIndex, char **sSiteNames);
  int (*KINGetSiteMolecularWeights) (int *iChemSetIndex, int *iMaterialIndex, double *dSiteMolWeights);
  int (*KINGetSiteDensity) (int *iChemSetIndex, int *iMaterialIndex, double *dSiteDensity);
  int (*KINGetParticleBulkDensity) (int *iChemSetIndex, int *iMaterialIndex, double *dParticleBulkDensity);
  int (*KINGetBulkNames) (int *iChemSetIndex, int *iMaterialIndex, char **sBulkNames);
  int (*KINGetBulkMolecularWeights) (int *iChemSetIndex, int *iMaterialIndex, double *dBulkMolWeights);
  int (*KINGetSurfaceThermodynamicFits) (int *iChemSetIndex, int *iMaterialIndex, double *dTemperature,
                                         double *dThermodynamicFits);
  int (*KINGetSpeciesOccupancy) (int *iChemSetIndex, int *iMaterialIndex, int *pSpeciesOccupancy);
  int (*KINGetGasSpeciesComposition) (int *iChemSetIndex, int *pGasSpeciesComposition);
  int (*KINGetGasEnthalpy) (int *iChemSetIndex, double *dGasEnthalpy);
  int (*KINSetSolverOptions) (int *iChemSetIndex, int *iSolver, int *iTurbulenceModel);
  int (*KINInitializeDCC) (int *iChemSetIndex);
  int (*KINSetDCCPhiControls) (double *DCC_MaxCluster, double *DCC_MinCluster, double *DCC_ReactLimit);
  int (*KINApplyDCC) (int *iChemSetIndex, int *iNumberFeatures, int *iNumberCellsIn, double *dKineticsTimeStep,
                      double *dClusterThreshold, double *dPressures, double *dTemperatures, double *dVolumes,
                      double *dMassFractions, double *dMixTimeScale, int *iSolver, int *iNumInitialSpecies,
                      int *iInitialSpeciesList, double *dSearchThreshold, int *iTurbulence, int *iNumberClusters,
                      int *ClusterIndex);
  int (*KINClustering) (int *iChemSetIndex, int *iNumberFeatures, int *iNumberCellsIn,
                        double *dClusterThreshold, double *dPressures, double *dTemperatures,
                        double *dMassFractions, double *dMixTimeScale, int *iNumberClusters, int *ClusterIndex);
  int (*KINSetupCellClustering) (int *iNumberCellsIn, int *iNumberClusters, int *ClusterIndex);
  int (*KINAveraging) (int *iChemSetIndex, double *dPressures, double *dTemperatures, double *dVolumes,
                       double *dMassFractions, double *dMixTimeScale, double *dAvgPressures, double *dAvgTemperatures,
                       double *dAvgMassFractions, double *dTotalVolumes, double *dAvgMixTimeScales);
  int (*KINCalculateCluster) (int *iChemSetIndex, int *iClusterID, double *dKineticsTimeStep, double *dAvgPressures,
                              double *dAvgTemperatures, double *dTotalVolumes, double *dAvgMassFractions,
                              int *iSolver, int *iNumInitialSpecies, int *iInitialSpeciesList,
                              double *dSearchThreshold, int *iTurbulence, double *dAvgMixTimeScales);
  int (*KINSaveAverageSolution) (int *iChemSetIndex, double *dAvgSpeciesDensities);
  int (*KINGetDCCResult) (int *iChemSetIndex, double *dKineticsTimeStep, double *dTemperatures,
                          double *dSpeciesDensities, double *dGasEnthalpyProdRates, double *dGasSpeciesProdRates);
  int (*KINGetDCCSpeciesDensity) (int *iChemSetIndex, double *dSpeciesDensities);
  int (*KINInitializeDCCSavedData) (int *iChemSetIndex, int *iNumberCellsIn, double *dPressures,
                                    double *dTemperatures, double *dSpeciesDensities);
  int (*KINSetSpeciesDiffusivity) (int *nGasSpecies, double *myDiff);
  int (*KINSetInitialMassFractionsAtWall) (int *nGasSpecies, double *Ywall);
  int (*KINGetMassFractionsAtWall) (int *iChemSetIndex, int *nGasSpecies, double *Ywall);
  int (*KINSetTransientSensitivity) (int *iChemSetIndex, int *iComputeSens, int *iEndPointOnly, int *iUseErrTest, int *iexp,
                                     int *iGetTimeStepSens);
  int (*KINSetNumSensParameters) (int *iNumGasSpecies, double *dTvar, double *dYvar, double *dPvar, double *dDvar);
  int (*KINGetNumSensParameters) (int *inSensPar);
  int (*KINSetNumSensClusters) (int *iNumSensClusters);
  int (*KINSetCurrentSensCluster) (int *iNumSensClusters);
  int (*KINGetSensitivityMatrixTranspose) (int *inSensPar, int *NEQ, double *AsensT);
  int (*KINGetTimeStepSensitivity) (int *NEQ, double *AsensdT);
  int (*KINCalculateEquil) (int *iChemSetIndex, double *dPressure, double *dTemperature,
                            double *dMassFractions, double *dEquilMassFractions);
  int (*KINLFS_GetNumberOfFuelsInLibrary) (int *numFuelsInLib);
  int (*KINLFS_GetFuelSpeciesNameLength)  (int *iFuelNameLength);
  int (*KINLFS_GetNamesOfFuelSpeciesInLibrary) (int *iFuelNameLength, int *numFuelsInLib, char **sFuelName);
  int (*KINLFS_GetFuelsInSpeciesArray) (int *iSpecNameLen, int *nSpecies, char **speciesList, int *iFuelCount, int *isFuel);
  int (*KINLFS_SetUp) (int *nFuels, int *iLEN_of_TableNameStrings, int *iFuelSpeciesMechID, char **OneDarray_of_FlameSpeedTableNamesWithFullPath);
  int (*KINLFS_GetTableRange) (double *Pmin, double *Pmax, double *Tmin, double *Tmax, double *PHImin, double *PHImax, double *EGRmin, double *EGRmax);
  int (*KINLFS_SetExtrapolationOption)  (int *iUseExtrapolate);
  int (*KINLFS_GetFlamespeed) (int *nsp, double *Y, double *T, double *P, double *Phi, double *EGR, double *FS);
  int (*KINLFS_Finish) (void);
  int (*KINEQR_SetSpeciesAndElementIndices) (int *kkO2, int *kkCO2, int *kkH2O, int *keleO, int *keleC, int *keleH);
  int (*KINEQR_SetElementalComposition) (int *nElements, int *nGasSpecies, int **EleNum);
  int (*KINEGR_SetN2index) (int *kkN2);
  int (*KINEQR_GetPhiAndEGRfraction) (int *nGasSpecies, double *Ymass, double *EQRatio, double *EGRfrac);
  int (*KINLFS_GetNumberOfFuelElements) (int *nElements);
  int (*KINLFS_GetFuelSpeciesElementalComposition) (int *nElements, int *numFuels, int **EN);
  int (*KINLFS_GetFuelSpeciesStoichiometryRatio) (int *numFuels, double *PhiRatio);
  /* For usage of ISAT with CKCFD*/
  int(*KINSetUpISAT) (int *iChemSetIndex);
  int(*KINGetInitialISATstate) (int *iChemSetIndex, double *Pi, double *Ti, double *Yi, double *dt, double *X);
  int(*KINGetFinalISATstate) (int *iChemSetIndex, int *nf, double *fa);
  int(*KINGetISATsensMatrix) (int *iChemSetIndex, int *nx, int *nf, double *ga);

  /* For usage of ISAT within CKCFD*/
  int(*KINCalculateCellWithISAT) (int *iChemSetIndex, int *bMonitorCell, int *iCellID,
                                  int *iClosureModel, int *bUseInitialTimeSteps,
                                  double *dCFDTimeStep, int *iNumberFaces, double *dVolume,
                                  double *dPressure, double *dTemperature, double *pMassFractions,
                                  double *dEnthalpyFlowIn, double *dTMultiplier, double *pSpeciesFlowIn,
                                  double *pYMultiplier, double *dMassFlowIn);
  int(*KINGetCellStateWithISAT)  (int *iChemSetIndex, double *dTemperature, double *pMassFractions,
                                  double *dFinalSensibleEnthalpy);
  int(*KINGetISATstats) (int *iChemSetIndex, int *nQueries, int *nPrimaryRet, int *nSecondRet, int *nGrows, int *nAdds, int *nReplaced, int *nEvals, int *nUnresolved, int *nLeaves);
  int(*KINReleaseISATtable) (int *iChemSetIndex);
  int(*KINSetFilmBLThickness) (double *BoundaryLayerThickness);

  int (*KINGetMixtureDiffusionCoeffsForFluent) (int *iChemSetIndex, double *dPressure, double *dTemperature,
                                                double *pMoleFractions, double *pMixtureDiffusionCoeffs);

  int (*KINGetOrdinaryDiffusionCoeffsForFluent) (int *iChemSetIndex, double *dPressure, double *dTemperature,
                                                 double *pMoleFractions, double *pMassFractions,
                                                 double *pOrdinaryDiffusionCoeffs);
  int(*KINPremix_CalculateFlame) (int *lout, int *iChemistrySet, double *dPressure, double *dTemperature,
                                  double *pMassFractions, double *Xstart, double *Xend);
  int(*KINPremix_GetSolutionGridPoints) (int *FlameNp);
  int(*KINPremix_GetSolution)  (int *FlameNp, int *nGasSpecies, double *FlameX, double *FlameT, double *FlameY);
  int(*KINPremix_SetFlameletGridPoints) (int *FlameletNp);
  int(*KINPremix_SetFlameletPVweights) (int *nGasSpecies, double *PVwt);
  int(*KINPremix_GetFlamelet)  (int *lout, int *nGasspecies, int *FlameletNp, double *FlameletX,
                                double *FlameletT, double *FlameletY, double *FlameletROP);
  int(*KINPremix_SetParameter) (char *param, double *param_Val);
  int(*KINPremix_SetUserDefinedFlameletgrid) (int *numcpts, double *pv_grid);
  int(*KINPremix_TurnOffContinuation) (void);
  int(*KINPremix_SetOutputControl) (int *iwriteoutput);

  /* For usage of solving transport equation of soot species providing a general soot mechanism */
  int(*KINSetNumberDensityCutoff)(int *iChemSetIndex, int *iDispersedMaterialIndex, double *Coagolation_Cutoff);
  int(*KINSetParticleCoagulationParameters)(int *iChemSetIndex, int *iDispersedMaterialIndex, int *iFormulationType, double *Coagolation_EnhanceFactor);
  int(*KINSetNumberMoments)(int *iChemSetIndex, int *iNumberMoments);
  int(*KINGetMomentsSourceTerms)(int *iChemSetIndex, int *iDispersedMaterialIndex, int *iApplyActiveFractions,
                                 double *dGasTemperature, double *dPressure, double *pGasMassFractions,
                                 double *pSurfaceData, double *pMoments, double *pMomentsSourceTerms,
                                 double *pGasSpeciesProductionRates, double *pSootSpeciesProductionRates);

  int(*KINGetMomentsAreaSourceTerms)(int *iChemSetIndex, int *iDispersedMaterialIndex, int *iApplyActiveFractions,
                                     double *dGasTemperature, double *dPressure, double *pGasMassFractions,
                                     double *pSurfaceData, int *iSurfaceDataType, double *pMoments, double *pMomentsSourceTerms,
                                     double *pGasSpeciesProductionRates, double *pSootSpeciesProductionRates, double *dParticleArea, double *dAreaGenerationRate);

  int(*KINRetrieveMomentSourceComponents)(int *iNumberMoments,
                                          double *pMoM_Nucl_api, double *pMoM_Coag_api, double *pMoM_Surf_api);

  int(*KINPremix_GetFlameMassFlux) (double *FreeBurnFlux);

  /* For checking "unknown" keywords in chemkin-based mechanism input*/
  int(*KINCheckKeywordsFluentCantHandle) (int *iChemSetIndex, int *iCanNotReadNatively);
  int(*KINPTM_SolverInitialize)          (int *iChemSetIndex, int *nGasSpecies, int *nSurfSpecies, int *nMoments);
  int(*KINPTM_IntegratePTM_Decoupled)    (int *iChemSetIndex, int *nGasSpecies, int *nMoments, int *nSurfSpecies, double *dtime_step,
                                          double *dPressure,  double *dGasTemperature, double *pGasMassFractions,
                                          double *pMoments,   double *pSurfaceConc,    double *dParticleArea,
                                          double *pMoments_n, double *pSurfaceConc_n,  double *dParticleArea_n);
  int(*KINPTM_SetIntgMethod) (int *iMethod);

  int(*KINOppdif_CalculateFlame) (int *lout, int *iChemistrySet, double *dPressure, double *Xend);
  int(*KINOppdif_GetSolutionGridPoints) (int *FlameNp);
  int(*KINOppdif_GetSolution)  (int *FlameNp, int *nGasSpecies, double *FlameX, double *FlameT, double *FlameY);
  int(*KINOppdif_GetMixtureFraction) (int *FlameletNp, double *FlameZ);
  int(*KINOppdif_SetInlet) (char *param, int *nGasSpecies, double *Tinlet, double *Yinlet, double *Vinlet, double *isMassFlux);
  int(*KINOppdif_TurnOffContinuation) (void);
  int(*KINOppdif_SetParameter) (char *param, double *param_Val);
  int(*KINOppdif_SetOutputControl) (int *iwriteoutput);
  int(*KINOppdif_GetSolnSpeciesIntegratedROP) (int *num_spe, int *nflame, int *numROP, int *indexROP, double *speROP);
  /*int(*KINOppdif_TurnOffRestart) (void);*/
}
KIN_Functions;


FLUENT_EXPORT void KIN_Load_Library(Domain *, const char *, const char *);
FLUENT_EXPORT void KIN_Get_Procedures(void);
FLUENT_EXPORT void KIN_Preprocessor(Domain *, int, int, const char *, const char *, const char *, const char *);
FLUENT_EXPORT void KIN_Reinitialize(void);
FLUENT_EXPORT void KIN_Solve_Unsteady(Domain *);
FLUENT_EXPORT void KIN_Solve_Steady(Domain *);
FLUENT_EXPORT int  KIN_Get_Surface_RXN_Rate(cxindex CellID, int nspe, int nsite, int nsurf, Reaction_Mech *rm, double Volume,
                                            double dSurfaceArea, double dPressure, double dTemperature, double dSurfaceTemperature,
                                            double dCFDTimeStep, double *Mass_Diffusivity, double *y_i, double *yw_i, double *r_rate, double bl_delx);
FLUENT_EXPORT int KIN_Set_WashCoat_Factor(cxindex CellID, double dwashcoat);
FLUENT_EXPORT void KIN_Set_Parameters(void);
FLUENT_EXPORT void KIN_Finish(Domain *);
extern FLUENT_EXPORT int KIN_first_iter;
FLUENT_EXPORT cxboolean KIN_Library_P(void);
FLUENT_EXPORT cxboolean KIN_ChemkinFile_P(void);
FLUENT_EXPORT void KIN_Monitor_Cell(Domain *);
FLUENT_EXPORT void KIN_Get_MixtureThermalConductivity(double *, double *, double *);
FLUENT_EXPORT void KIN_Get_ThermalDiffusionCoeffs(double *, double *, double *, double *, double *);
FLUENT_EXPORT void KIN_Get_MixtureViscosity(double *, double *, double *);
FLUENT_EXPORT void KIN_Get_OrdinaryDiffusionCoeffs(double *, double *, double *, double *, double *);
FLUENT_EXPORT void KIN_Get_MixtureDiffusionCoeffs(double *, double *, double *, double *);
FLUENT_EXPORT void KIN_Get_DiffusionCoeffs(double *, double *, double *);
FLUENT_EXPORT void KIN_Get_Specific_Heat(double *, double *) ;
FLUENT_EXPORT void KIN_Get_Species_Enthalpy(double *, double *) ;
FLUENT_EXPORT void KIN_Get_Mixture_Enthalpy(double *, double *, double *) ;
FLUENT_EXPORT void KIN_Get_Chemistry_Sizes(void);
FLUENT_EXPORT void KIN_Get_Material_Sizes(void);
FLUENT_EXPORT int KIN_Reaction_Point_Step (cell_t c, Thread *t, int nspm, int *NumberFaces, real rho, real *hs,
                                           double dPressure, double dVolume,
                                           double *dCFDTimeStep, double *dTemperature, double *dGasEnthalpyProdRate,
                                           double *dTMultiplier, double *dEnthalpyFlowIn, double *dMassFlowIn,
                                           double dMassFractions[], double dSpeciesFlowIn[], double dYMultiplier[],
                                           double dGasSpeciesProdRate[]);
FLUENT_EXPORT void FluentImport_KINTransportData(int nspec, double *dEpsilon, double *dSigma,
                                                 double *dDipoleMoment, double *dPolarizability,
                                                 double *dzRotationalNumer, int *iNonlinearity);
FLUENT_EXPORT void FluentImport_KINMechanismSize(int *nelem, int *nspec, int *nreac);
FLUENT_EXPORT void FluentImport_KINElementData(int i, char *elem_name, double *atomic_wt);
FLUENT_EXPORT void FluentImport_KINSpeciesData(int i, char *spec_names, double *spec_wt,
                                               int *specelem_composition);
FLUENT_EXPORT void FluentImport_KINThermoData(int i, double *dTempRanges, double *dUpperTempCoeffs,
                                              double *dLowerTempCoeffs, double *dMiddleTempCoeffs,
                                              double (*dTempCoeff)[MAX_THERMO], int *nTemRange, int *iFormat);
FLUENT_EXPORT int  FluentImport_KINGetSurfThermoFits(int j, double *T_ranges, double *T_coeffs);
FLUENT_EXPORT int  FluentImport_KINSurfMaterialData(char **surfmech_name, int *nsitespe, int *nbulkspe);
FLUENT_EXPORT int  FluentImport_KINGetPhaseSizes(int j, int *inumphases, int *inumsitephases, int *inumbulkphases);
FLUENT_EXPORT int  FluentImport_KINGetPhaseNames(int j, char **sphase_names);
FLUENT_EXPORT int  FluentImport_KINGetPhaseSpeciesIndices(int j, int *num_phasespe, int *phase_firstspe, int *phase_lastspe);
FLUENT_EXPORT void FluentImport_KINMaterialSiteData(int j, int nsites, char **snames, double *site_mw );
FLUENT_EXPORT int  FluentImport_KINGetSpeciesOccupancy(int j, int *spe_occupancy);
FLUENT_EXPORT int  FluentImport_KINGetSiteDensity(int j, double *site_density);
FLUENT_EXPORT int  FluentImport_KINGetParticleBulkDensity(int j, double *particlebulk_density);
FLUENT_EXPORT void FluentImport_KINMaterialBulkData(int j, int nbulk, char **bnames, double *bulk_mw );
FLUENT_EXPORT int KIN_AllocImportData(cxboolean transport, cxboolean surface);
FLUENT_EXPORT void KIN_FreeImportData(cxboolean transport, cxboolean surface);
FLUENT_EXPORT int KIN_Get_Element_Matrix(int iflag, char **elem_names, int *elem_matrix);
FLUENT_EXPORT void KIN_Thermo_Data_From_File(double *elem_awt, double *spe_mw, double *T_ranges,
                                             double *thermo_coeffs, int *elem_comp);
FLUENT_EXPORT int KIN_Get_NumElements(void);
FLUENT_EXPORT int KIN_Get_NumGasSpecies(void);
FLUENT_EXPORT void KIN_Get_GasSpeciesNames(char **spe_names);
FLUENT_EXPORT int KIN_Get_NumGasReactions(void);
FLUENT_EXPORT int KIN_Apply_DCC(Domain *domain);
FLUENT_EXPORT int  KIN_LFS_Setup(Material *m, real yi_fuel[], real yi_oxid[]);
FLUENT_EXPORT real KIN_LFS_GetFlamespeed(int nsp, real Y[], real P, real T);
FLUENT_EXPORT void KIN_LFS_Finish(void);
FLUENT_EXPORT int KIN_Set_DCC_PhiControls(double DCC_MaxCluster, double DCC_MinCluster, double DCC_ReactLimit);
FLUENT_EXPORT int KIN_Get_MOM_Soot_Source(Domain *domain,
                                          double dGasTemperature, double dPressure, double *pGasMassFractions,
                                          double *pSootSpeciesFraction, int iSurfaceDataType,
                                          double *pMoments, double *pMomentsSourceTerms,
                                          double *pMoM_Nucl_api, double *pMoM_Coag_api, double *pMoM_Surf_api,
                                          double Coagolation_Cutoff, double Coagolation_EnhanceFactor,
                                          double *pGasSpeciesProductionRates, double *pSootSpeciesProductionRates,
                                          int iNumberMoments, double dParticleArea, double *dAreaGenerationRate,
                                          double *soot_site_density);
FLUENT_EXPORT int KIN_Get_SOOT_SITE_DENSITY(double *soot_site_density);
FLUENT_EXPORT int KIN_Get_SOOT_PARTICLEBULK_DENSITY(double *soot_particlebulk_density);
FLUENT_EXPORT void KIN_Check_NativeReaderCompatibility(int *iCanNotReadNatively);
FLUENT_EXPORT int KIN_Integrate_PTM(int nGasSpecies, int nMoments, int nSurfSpecies, double dtime_step,
                                    double dPressure,       double dGasTemperature, double *pGasMassFractions, double *pMoments, double *pSurfaceConc,
                                    double dParticleArea,  double *pMoments_n,     double *pSurfaceConc_n,    double *dParticleArea_n);
FLUENT_EXPORT int KIN_Init_PTM(int nGasSpecies, int nMoments, int nSurfSpecies);
#define FLCHEMDIR "fluentchemkinfiles"
#define CHEMXML "chem.xml"

/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_CHEMKIN_H
#define _FLUENT_CHEMKIN_H

#include "global.h"
#include "materials.h"
#include "mem.h"

#define speek(string)(*string)[0]

#define ADVANCE_STREAM(stream,n)(*stream=*stream+n)
#define REWIND_STREAM(stream,n)(*stream=*stream-n)
#define NULL_STREAM(stream)(strcpy(*stream,""))
#define CHEMKIN_LARGE 1.e20
#define CHEMKIN_SMALL 1.e-20

#define MAX_LINE_LENGTH 400
#define MAX_ELEM_PER_SPEC 9
#define MAX_WORD_LENGTH 46
#define MIN_THERMO_LINE_LENGTH 80

#define STRING_END '\0'

#define MAX_ELEMENTS   30
#define MAX_REACTANTS  50
#define MAX_PRODUCTS   50
#define MAX_THIRD      10
#define MAX_THERMO     9
#define MAX_TEM_RANGE 8

typedef char *STREAM;

typedef struct keyword_struct
{
  char *keyword;
  int section;
} Keyword;

typedef struct chem_element_struct
{
  char *name;     /* element name */
  double aweight; /* atomic weight */
} Chem_Element;

enum
{
  XMLGAS,
  XMLSURF,
  XMLREAC,
  STOIC,
  ARRHE,
  XMLTHIRD,
  AUXIL,
  COMMENT,
  ENDTAG,
  ENDSTOIC,
  ENDREAC,
  UNUSEDSPE,
  NOTAG
};

enum
{
  P_LINDEMANN,
  P_SRI,
  P_TROE,
  P_NONE
};

enum
{
  ELEM,
  SPEC,
  REAC,
  THERMO,
  NASA_THERMO,
  TRANSP,
  SITE,
  SITESDEN,
  SDEN,
  MATERIAL,
  BULK,
  EOS_SRK,
  END,
  ENDSTD
};

enum
{
  CALO = 0,
  JOUL,
  KELV,
  KCAL,
  EVOL,
  KJOUL,
  MAX_EUNIT
};

enum
{
  MOLE = 0,
  MOLC,
  MAX_AUNIT
};

enum
{
  LOW,
  HIGH,
  TROE,
  SRI,
  PLOG,
  REV,
  FORD,
  RORD,
  COV,
  DUP,
  THIRD,
  UNITS,
  STICK,
  MWOFF,
  MWON,
  ENDAUX
};

enum
{
  LT,
  RLT,
  JAN,
  FIT1,
  HV,
  EXCI,
  MOME,
  BOHM,
  ENRGDEP,
  TDEP,
  COLLEFF,
  CHEB,
  PCHEB,
  TCHEB,
  XSMI,
  DCOL,
  LANG,
  LHDE,
  LHNU,
  LHPR,
  NATIVE,
  NUCL,
  YIELD,
  CK_ATM,
  CK_BAR,
  CK_DYN,
  CK_PAS,
  CK_TOR,
  NONCON,
  USRPROG,
  XKEQ,
  TROEMX,
  TROESP,
  LOWMX,
  LOWSP,
  HIGHMX,
  HIGHSP,
  PLOGMX,
  PLOGSP,
  END_CKONLY
};

enum
{
  VOLUMETRIC,
  SURFACE
};

typedef struct species_struct
{
  char *name;
  double mw;
  int index;
  int is_site_species;
  int is_bulk_species;
  int is_thermo_data_present;
  double temperature[MAX_TEM_RANGE];
  int n_temperature_range;
  int thermo_format;
  double temperature_coeff[MAX_TEM_RANGE][MAX_THERMO];
  double upper_temperature_coeff[MAX_THERMO];
  double lower_temperature_coeff[MAX_THERMO];
  double mid_temperature_coeff[MAX_THERMO];

  int n_coeffs[POLYNOMIAL_MAX_RANGES];
  int max_poly_coeffts;
  int thermo_data_from_fluent_materials;
  int n_ranges;
  double **cp_coeffs;
  double **cp_ranges;

  double fent, feth;
  int phase;
  int transportindex;
  double carbon_fraction;
  double hydrogen_fraction;
  double nitrogen_fraction;
  double oxygen_fraction;
  double transport_coeffts[5];
  int reacting_p;
  cxboolean found_in_species_section_p;
  int site_occupancy;
} Species;

FLUENT_EXPORT void CONVERT_FROM_CHEMKIN(char *STRING);
FLUENT_EXPORT void CONVERT_TO_CHEMKIN(char *STRING);
FLUENT_EXPORT Pointer Read_Specie_Thermo_Data (char *, int, char **, int, FILE **, char **, cxboolean, cxboolean);
FLUENT_EXPORT Pointer Read_Chemkin_Files (const char *, FILE *fd, FILE *, FILE *, FILE *, cxboolean, FILE *);
FLUENT_EXPORT void Write_Chemkin_Files(const char *, Pointer);
FLUENT_EXPORT void read_mw (STREAM *, Species *, cxboolean, cxboolean, int *, int *);
FLUENT_EXPORT void read_mw_nasa_format (STREAM *, Species *, cxboolean, cxboolean, int *, int *);
FLUENT_EXPORT void Set_Condensed_Specie (Pointer);
FLUENT_EXPORT void Enable_Report_Each_line(cxboolean);
FLUENT_EXPORT void Read_Specie_Elemental_Fractions (char *matname, int specie_num,
                                                    char **specie_names,
                                                    FILE *file_ptrs,
                                                    char *file_names,
                                                    real *carbon_fractions,
                                                    real *hydrogen_fractions,
                                                    real *oxygen_fractions,
                                                    real *nitrogen_fractions);

FLUENT_EXPORT char *CFX_RIF_Specie_Name(char *str, char **species_names, int k, int index);
FLUENT_EXPORT void Get_Element_Matrix(Material *m, int *evt, int *elem_index, int *num_elem, char **elem_names);
FLUENT_EXPORT void Get_DR_Element_Matrix(Material *m, int *evt, int *global_elem_indx,
                                         int *num_elem, char **elem_names);
FLUENT_EXPORT void Get_Plain_Mechanism_Element_Matrix(Material *m, char *thermo_file, int *evt,
                                                      int *global_elem_indx, int *num_elem, char **elem_names);
FLUENT_EXPORT void Get_Encrypted_Mechanism_Element_Matrix(Material *m, int *evt, int *global_elem_indx,
                                                          int *num_elem, int ifound);
FLUENT_EXPORT Pointer Create_Red_Dim_Mixture(Domain *domain, Material *m, int num_rd_spe,
                                             int *fo_sp_indx, int *red_sp_indx);
FLUENT_EXPORT cxboolean is_mechanism_encrypted(FILE *fd);
FLUENT_EXPORT cxboolean reactiondata_apionly_p(void);
FLUENT_EXPORT cxboolean fluentmixture_matches_chemkin_p(Material *m);
#define EMP_FUEL_NAME "empirical-fuel"
#define EMP_SECONDARY_NAME "empirical-secondary"
#define SPECIES_IS_EMPIRICAL(name)(STREQ(name,EMP_FUEL_NAME)||STREQ(name,EMP_SECONDARY_NAME))

FLUENT_EXPORT char *CFX_RIF_Specie_Name(char *str, char **species_names, int k, int index);

FLUENT_EXPORT real element_weight(int elem_index);
FLUENT_EXPORT void element_name(int elem_index, char *ename);
#endif /* _FLUENT_CHEMKIN_H */
FLUENT_EXPORT void Register_Ckcfd_Encrypted_IO_Managers(void);
FLUENT_EXPORT void Deregister_Ckcfd_Encrypted_IO_Managers(void);
FLUENT_EXPORT void Register_Chem_Mech_File_HDF_IO_Manager(void);

/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#if ONE_D
#define WAVE 1
#define UDF_NAME_MAX_LEN 64

#define DEBUG_ONED 0

#define GT_Power 0

extern FLUENT_EXPORT void Open_GT_Library (void);
extern FLUENT_EXPORT void Close_GT_Library (void);
extern FLUENT_EXPORT void Create_GT_UDFs (void);

extern FLUENT_EXPORT int Start_GT_Power (const char *);
extern FLUENT_EXPORT void Get_GT_Ports (Domain *);
extern FLUENT_EXPORT void Get_GT_PortBCs (Thread *, Profile *);
extern FLUENT_EXPORT void Init_GT_Struct(void);
extern FLUENT_EXPORT void Get_GT_CellZone (Thread *, Profile *);
extern FLUENT_EXPORT void Update_GT_PortBCs (Domain *);
extern FLUENT_EXPORT void Update_GT_Solution (Domain *);
extern FLUENT_EXPORT void Create_Species_Association(Domain *);
extern FLUENT_EXPORT cxboolean gtstoppingfluent;

#if WAVE

extern FLUENT_EXPORT void Open_WAVE_Library(const char *);
extern FLUENT_EXPORT void Close_WAVE_Library(void);
extern FLUENT_EXPORT void Get_WAVE_Ports(Domain *);
extern FLUENT_EXPORT int  Start_WAVE(const char *);
extern FLUENT_EXPORT void Create_WAVE_UDFs(void);
extern FLUENT_EXPORT void Update_WAVE_PortBCs(Domain *);
extern FLUENT_EXPORT void Update_WAVE_Solution(Domain *);
extern FLUENT_EXPORT void Get_WAVE_PortBCs(Thread *, Profile *);


extern FLUENT_EXPORT int *link_ID;
extern FLUENT_EXPORT int *link_type;
extern FLUENT_EXPORT int n_links;
extern FLUENT_EXPORT int *link_number_phi;
extern FLUENT_EXPORT double *link_p;
extern FLUENT_EXPORT double *link_t;
extern FLUENT_EXPORT double *link_rho;
extern FLUENT_EXPORT double *link_massflux;
extern FLUENT_EXPORT double *link_F1;
extern FLUENT_EXPORT double *link_F2;
extern FLUENT_EXPORT double *link_F3;
extern FLUENT_EXPORT double *link_F4;
extern FLUENT_EXPORT double *link_F5;
extern FLUENT_EXPORT double *link_area;
extern FLUENT_EXPORT double *link_dx;

#endif



#if GRAPHICS
extern FLUENT_EXPORT void Draw_OneD_Cell (Thread *);
#endif
#endif

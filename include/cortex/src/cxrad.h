/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#define UPDATE_INTERVAL 20

typedef struct CX_Face_Nbr_Def
{
  CX_Face_Def *ref_face;
  CX_Cell_Id neigh_cell;
  cxboolean valid;
  struct CX_Face_Nbr_Def *next;
} CX_Face_Nbr_Def;


/*************************************************
 * TAG( CX_Rad_Group )
 *
 * This structure contains the definition for a group.
 * A group consists of a list of nodes.  Some criterion is used to
 * group cells together.
 */
typedef struct CX_Rad_Grp
{
  int   type;   /* iZone of elements in this group. */
  int   Id;
  CX_Face_Def *lastFace;  /* Linked list of faces */
  CX_Face_Def *firstFace;
  CX_Face_Nbr_Def *lastNbr; /* Linked list of nbr cells */
  CX_Face_Nbr_Def *firstNbr;
  int   nElements;
  int   nFaces; /* for S2S */
  struct CX_Rad_Grp *srf; /* List of surface groups for this volume
         * glob.
         */
  struct CX_Rad_Grp *lastSrf;
  struct CX_Rad_Grp *next;
  CX_Cell_Id  **cells;
  float min[3], max[3];
  int   nextDir;
  int   numAlloc;
} CX_Rad_Grp;


/*
 * The following are the globs (or groups).
 */

extern CX_Rad_Grp *curr_display_glob;
extern const int cxnodes_per_facet[NCELL_GEOM];
void radiation_trace(FILE *, int, int, int, int, int, int);
CX_Face_Def *get_center_face(CX_Rad_Grp *sGlob);












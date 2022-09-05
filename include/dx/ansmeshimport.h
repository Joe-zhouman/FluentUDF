/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _ANS_MESHIMPORT_H
#define _ANS_MESHIMPORT_H

#if RP_HOST_LIB || RP_NODE_LIB

#include "ansrpc.h"

#define CX_FREE(obj)  \
{                     \
  if (NNULLP(obj))    \
    CX_Free(obj);     \
  obj = NULL;         \
}

#define MIN_CHUNK_SIZE 524288 /* 4MB chunk for size_t */

#define FACE_ZONE(zone) (zone->type == (ND_ND-1))
#define CELL_ZONE(zone) (zone->type == ND_ND)
#if RP_3D
#define MIN_NODE_PER_CELL 4
#define MIN_NODE_PER_FACE 3
#else
#define MIN_NODE_PER_CELL 3
#define MIN_NODE_PER_FACE 2
#endif

/* Face struct */
typedef struct imeshface
{
  cxindex cell0;   /* cell 0 of the face */
  cxindex cell1;   /* cell 1 of the face */
  cxindex *nodes;  /* pointer to globalFaceNodeManager for this face */
  int numNodes;    /* number of nodes in the face */
  int zoneId;  /* cell zone for the face. Needed to associate a face thread id later on */
} IMeshFace;

/* Mesh Zone struct */
typedef struct imeshzone
{
  RpcInt16 type;        /* zone topology - point(0), line(1), surface(2), volume(3) */
  RpcInt64 id;          /* zone id */
  int elemType;         /* element type for the zone */
  RpcInt64 elemCount;   /* number of elements in the zone */
  RpcInt64 nodeCount;   /* number of unique nodes in the zone */
} IMeshZone;

extern Domain *domain;
extern cxindex vert_0, vert_1, vert_n, gvert_1, gvert_n;
extern cxindex cell_0, cell_1, cell_n, gcell_1, gcell_n;
extern cxindex face_0, face_1, face_n, gface_1, gface_n;
extern size_t ncell_per_chunk;
extern int nface_per_chunk, nvert_per_chunk;

int ImportAnsRpcMesh(char *hostName, int portNum, int timeOut);
int ConvertIMeshToFluentMesh();

#endif  /* RP_HOST_LIB || RP_NODE_LIB */
#endif  /* _ANS_MESHIMPORT_H */


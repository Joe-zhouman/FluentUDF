/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RANDOM_H
#define _FLUENT_RANDOM_H

#include "dll.h"

extern FLUENT_EXPORT long iseed;
extern FLUENT_EXPORT long iseed_wall_jet;
extern FLUENT_EXPORT long iseed_wall_film;
FLUENT_EXPORT float uniform_random(void);
FLUENT_EXPORT float uniform_random_mt(void **u);
FLUENT_EXPORT float wall_film_uniform_random(void);
FLUENT_EXPORT float gauss_random(void);
FLUENT_EXPORT void set_random_seed(long newseed);
FLUENT_EXPORT void reset_cheap_uniform_rand_seeds(void);
FLUENT_EXPORT real cheap_uniform_random(void);
FLUENT_EXPORT real cheap_gauss_random(void);
FLUENT_EXPORT void restore_random_seeds(void);
FLUENT_EXPORT void save_random_seeds(void);

typedef struct
{
  unsigned int var[3];
} uniform_random_seed;

typedef struct
{
  uniform_random_seed uniform;
  real next_gauss;
} gauss_random_seed;

FLUENT_EXPORT float wall_jet_uniform_random(uniform_random_seed *seed);
FLUENT_EXPORT void initUniformRandom(uniform_random_seed *seed, unsigned int init);
FLUENT_EXPORT unsigned int getUniformRandomInt(uniform_random_seed *seed);
FLUENT_EXPORT real getUniformRandom(uniform_random_seed *seed);
FLUENT_EXPORT void initGaussRandom(gauss_random_seed *seed, unsigned int init);
FLUENT_EXPORT real getGaussRandom(gauss_random_seed *seed);
FLUENT_EXPORT unsigned int getCrc32CharBuf(unsigned int crc, const unsigned char *buf, size_t len);
FLUENT_EXPORT unsigned int getCrc32Int(unsigned int crc, int ibuf);

#endif /* _FLUENT_RANDOM_H */

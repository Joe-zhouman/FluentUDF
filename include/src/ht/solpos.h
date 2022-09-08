/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_SOLPOS_H
#define _FLUENT_SOLPOS_H
#include "dll.h"
/*============================================================================
*
*    NAME:  solpos.h
*
*    Contains:
*        S_date       (computes the date from the day number)
*            INPUTS:     S_year, S_daynum
*            OUTPUTS:    S_year, S_month, S_day
*
*        S_solpos     (computes the solar position and intensity
*                      from time and place)
*            INPUTS:     S_month, S_day, S_latitude, S_longitude, S_timezone
*            OPTIONAL:
*                            S_year    DEFAULT 2001   (non-leap)
*                            S_hour    DEFAULT   12   (noon)
*                            S_minute  DEFAULT    0   ( "  )
*                            S_second  DEFAULT    0   ( "  )
*                            S_press   DEFAULT 1013.0 (standard pressure)
*                            S_temp    DEFAULT   10.0 (standard temperature)
*                            S_tilt    DEFAULT    0.0 (horizontal panel)
*                            S_aspect  DEFAULT  180.0 (South-facing panel)
*
*            OUTPUTS:    S_daynum, S_amass, S_ampress, S_azim, S_cosinc,
*                        S_elevref, S_etr, S_etrn, S_etrtilt, S_prime,
*                        S_sbcf, S_sunrise, S_sunset, S_unprime, S_zenref
*
*    Usage:
*         In calling program, along with other 'includes', insert:
*
*              #include "solpos.h"
*
*    Martin Rymes
*    National Renewable Energy Laboratory
*    25 March 1998
*----------------------------------------------------------------------------*/

/***** ALPHABETICAL LIST OF COMMON VARIABLES *****/
/* Each comment begins with a 1-column letter code:
   I:  INPUT variable
   O:  OUTPUT variable
   T:  TRANSITIONAL variable used in the algorithm,
       of interest only to the solar radiation
       modelers, and available to you because you
       may be one of them */
/***** INTEGERS *****/

extern int   S_day;        /* I/O:  Day of month (May 27 = 27, etc.)
                                      S_solpos needs this, but S_date will
                                      calculate it from S_daynum. */
extern int   S_daynum;     /* I/O:  Day number (day of year; Feb 1 = 32 )
                                      S_date needs this, but S_solpos will
                                      calculate it from S_month and S_day. */
extern int   S_hour;       /* I:    Hour of day, 0 - 23, DEFAULT = 12 */
extern int   S_minute;     /* I:    Minute of hour, 0 - 59, DEFAULT = 0 */
extern int   S_month;      /* I/O:  Month number (Jan = 1, Feb = 2, etc.)
                                      S_solpos needs this, but S_date will
                                      calculate it from S_daynum. */
extern int   S_second;     /* I:    Second of minute, 0 - 59, DEFAULT = 0 */
extern int   S_year;       /* I:    4-digit year (2-digit is assumed 19xx),
                                      DEFAULT = 2001 */

/***** FLOATS *****/

extern float S_amass;      /* O:  Relative optical airmass */
extern float S_ampress;    /* O:  Pressure-corrected airmass */
extern float S_aspect;     /* I:  Azimuth of panel surface (direction it
                                    faces) N=0, E=90, S=180, W=270,
                                    DEFAULT = 180 */
extern float S_azim;       /* O:  Solar azimuth angle:  N=0, E=90, S=180, W=270 */
extern float S_cosinc;     /* O:  Cosine of solar incidence angle on panel */
extern float S_dayang;     /* T:  Day angle (daynum*360/year-length) degrees */
extern float S_declin;     /* T:  Declination--zenith angle of solar noon
                                     at equator, degrees NORTH */
extern float S_eclong;     /* T:  Ecliptic longitude, degrees */
extern float S_ecobli;     /* T:  Obliquity of ecliptic */
extern float S_ectime;     /* T:  Time of ecliptic calculations */
extern float S_elevref;    /* O:  Solar elevation angle,
                                    deg. from horizon, refracted */
extern float S_eqntim;     /* T:  Equation of time (TST - LMT), minutes */
extern float S_erv;        /* T:  Earth radius vector
                                    (multiplied to solar constant) */
extern float S_etr;        /* O:  Extraterrestrial (top-of-atmosphere) W/sq m
                                    global horizontal solar irradiance */
extern float S_etrn;       /* O:  Extraterrestrial (top-of-atmosphere) W/sq m
                                    direct normal solar irradiance */
extern float S_etrtilt;    /* O:  Extraterrestrial (top-of-atmosphere) W/sq m
                                    global irradiance on a tilted surface */
extern float S_gmst;       /* T:  Greenwich mean sidereal time, hours */
extern float S_hrang;      /* T:  Hour angle--hour of sun from solar noon,
                                    degrees WEST */
extern float S_julday;     /* T:  Julian Day of 1 JAN 2000 minus 2,400,000 days
                                    (in order to regain single precision) */
extern float S_latitude;   /* I:  Latitude, degrees north (south negative) */
extern float S_longitude;  /* I:  Longitude, degrees east (west negative) */
extern float S_lmst;       /* T:  Local mean sidereal time, degrees */
extern float S_mnanom;     /* T:  Mean anomaly, degrees */
extern float S_mnlong;     /* T:  Mean longitude, degrees */
extern float S_rascen;     /* T:  Right ascension, degrees */
extern float S_press;      /* I:  Surface pressure, millibars, used for
                                    refraction correction and S_ampress */
extern float S_prime;      /* O:  Factor that normalizes Kt, Kn, etc. */
extern float S_sbcf;       /* O:  Shadow-band correction factor */
extern float S_solcon;     /* T:  Solar constant, 1367 W/sq m */
extern float S_ssha;       /* T:  Sunset(/rise) hour angle, degrees */
extern float S_sunrise;    /* O:  Sunrise time, minutes from midnight,
                                    local, no refraction */
extern float S_sunset;     /* O:  Sunset time, minutes from midnight,
                                    local, no refraction */
extern float S_temp;       /* I:  Ambient dry-bulb temperature, degrees C,
                                    used for refraction correction */
extern float S_tilt;       /* I:  Degrees tilt from horizontal of panel */
extern float S_timezone;   /* I:  Time zone, east (west negative).
                                    USA:  Mountain = -7, Central = -6, etc. */
extern float S_tst;        /* T:  True solar time, minutes from midnight */
extern float S_tstfix;     /* T:  True solar time - local standard time */
extern float S_unprime;    /* O:  Factor that denormalizes Kt', Kn', etc. */
extern float S_utime;      /* T:  Universal (Greenwich) standard time */
extern float S_zenetr;     /* T:  Solar zenith angle,
                                    no atmospheric correction (= ETR) */
extern float S_zenref;     /* O:  Solar zenith angle,
                                    deg. from zenith, refracted */

/*============================================================================
*    Integer function S_date, adapted from the NREL VAX solar libraries
*
*    This function calculates the month and day of month, given the
*    day number (number of day in year, sometimes confusingly called
*    the "Julian Day", but I know that you will never call it that).
*
*    Requires:
*        Year and day number:
*            S_year           NOTE:  2-digit year "xx" is assumed "19xx"
*                             DEFAULT S_year = 2001
*            S_daynum         RANGE: -1 to a large positive integer
*
*    Returns:
*        Year, month, day:
*            S_year
*            S_month
*            S_day
*----------------------------------------------------------------------------*/
extern int S_date (void);

/*============================================================================
*    Integer function S_solpos, adapted from the NREL VAX solar libraries
*
*    This function calculates the apparent solar position and intensity
*    (theoretical maximum solar energy) based on the date, time, and
*    location on Earth.
*
*    Requires:
*        Date and time:
*            S_year      DEFAULT 2001
*            S_month
*            S_day
*            S_hour      DEFAULT 12
*            S_minute    DEFAULT  0
*            S_second    DEFAULT  0
*        Location:
*            S_latitude
*            S_longitude
*        Location/time adjuster:
*            S_timezone
*        Atmospheric pressure and temperature:
*            S_press     DEFAULT 1013.0 mb
*            S_temp      DEFAULT 10.0 degrees C
*        Tilt of flat surface that receives solar energy:
*            S_aspect    DEFAULT 180 (South)
*            S_tilt      DEFAULT 0 (Horizontal)
*
*    Returns:
*        everything defined at the top of this listing.
*----------------------------------------------------------------------------*/
extern int S_solpos (void);
#endif /* _FLUENT_SOLPOS_H */

/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _FLUENT_RPM_H
#define _FLUENT_RPM_H


/**********************************************************************
 * rpm.h
 *
 * Provide the function "RPM_Solve()" which implements the Recursive
 * Projection Method (RPM) to stabilize and/or accelerate the
 * convergence of the algebraic multigrid solver.
 *
 * References:
 *      G. M. Shroff and H. B. Keller, "Stabilization of Unstable
 *  Procedures: The Recursive Projection Method", SIAM J. Numer.
 *  Anal., vol. 30, no. 4, pp. 1099-1120, 1993.
 *
 *  J. Moeller, "An Investigation of the Recursive Projection
 *  Method on a Scalar Linear and Non-Linear Partial Differential
 *  Equation", available at:
 *  www.nada.kth.se/~jmoller/Publications/TRITANA0118.pdf.
 **********************************************************************/
FLUENT_EXPORT int RPM_Solve(AMG_Controls amg, Level fine, real residual0[]);


#endif /* _FLUENT_RPM_H */

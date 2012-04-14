#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>

#include <omp.h>

#ifndef SIMD_H
#define SIMD_H

// SSE stands for Streaming SIMD Extensions

#define SSE_WIDTH	4

#ifdef MSVCPP
#define ALIGNED	__declspec(align(16))
#else
#define ALIGNED	__attribute__((aligned(16)))
#endif


void	SimdSet( float *, float  ,  int );

void	SimdAdd( float *, float *,  float *, int );
void	SimdAdd( float *, float  ,  float *, int );
void	SimdSub( float *, float *,  float *, int );
void	SimdSub( float *, float  ,  float *, int );
void	SimdMul( float *, float *,  float *, int );
void	SimdMul( float *, float  ,  float *, int );
void	SimdDiv( float *, float *,  float *, int );
void	SimdDiv( float *, float  ,  float *, int );

void	NonSimdAdd( float *, float *,  float *, int );
void	NonSimdAdd( float *, float  ,  float *, int );
void	NonSimdSub( float *, float *,  float *, int );
void	NonSimdSub( float *, float  ,  float *, int );
void	NonSimdMul( float *, float *,  float *, int );
void	NonSimdMul( float *, float  ,  float *, int );
void	NonSimdDiv( float *, float *,  float *, int );
void	NonSimdDiv( float *, float  ,  float *, int );

float	SimdMulAndSum(    float *, float *, int );
float	NonSimdMulAndSum( float *, float *, int );

double	Timer( );


#endif		// SIMD_H

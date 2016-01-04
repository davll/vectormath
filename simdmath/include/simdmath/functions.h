/*
The source file is part of simdmath

Copyright (c) 2015 David Lin <davll.xc@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once

#if defined(__GNUC__) || defined(__MINGW32__)
#  ifdef __cplusplus
#    define SIMDMATH_INLINE inline __attribute__((always_inline))
#  else
#    define SIMDMATH_INLINE static inline __attribute__((always_inline))
#  endif
#elif defined(_MSC_VER)
#  ifdef __cplusplus
#    define SIMDMATH_INLINE __forceinline
#  else
#    define SIMDMATH_INLINE static __forceinline
#  endif
#else
#  define SIMDMATH_INLINE static inline
#endif

// Arc Cosine Function
// acos(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_acosf4(vec_float4);
#endif

// Arc Sine Function
// asin(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_asinf4(vec_float4);
#endif

// Arc Tangent Function
// atan(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_atanf4(vec_float4);
#endif

// Arc Tangent Function (Two-variable version)
// atan2(x,y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_atan2f4(vec_float4, vec_float4);
#endif

// Component-wise Selection
#if defined(SIMDMATH_VEC_FLOAT4) && defined(SIMDMATH_VEC_INT4)
SIMDMATH_INLINE vec_float4 simdmath_blendf4(vec_float4, vec_float4, vec_int4);
#endif

// Cube-Root
// cbrt(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_cbrtf4(vec_float4);
#endif

// Ceil Function
// ceil(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_ceilf4(vec_float4);
#endif

// Copy Sign
// copysign(x, y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_copysignf4(vec_float4, vec_float4);
#endif

// Cosine Function
// cos(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_cosf4(vec_float4);
#endif

// cosh
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_coshf4(vec_float4);
#endif

// div
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_divf4(vec_float4, vec_float4);
#endif

// Base-e Exponential Function
// exp(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_expf4(vec_float4);
#endif

// Base-2 Exponential Function
// exp2(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_exp2f4(vec_float4);
#endif

// Base-e Exponential Function (for small |x|)
// expm1(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_expm1f4(vec_float4);
#endif

// Absolute Value
// fabs(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fabsf4(vec_float4);
#endif

// Positive Difference
// fdim(x, y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fdimf4(vec_float4, vec_float4);
#endif

// Floor Function
// floor(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_floorf4(vec_float4);
#endif

// fma
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fmaf4(vec_float4, vec_float4, vec_float4);
#endif

// Maximum Value
// fmax(x,y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fmaxf4(vec_float4, vec_float4);
#endif

// Minimum Value
// fmin(x,y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fminf4(vec_float4, vec_float4);
#endif

// Remainder Function
// fmod(x, y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_fmodf4(vec_float4, vec_float4);
#endif

// Fractional and Integral Extraction
// frexp(x, &e)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_frexpf4(vec_float4, vec_float4*);
#endif

// Euclidean Distance Function
// hypot(x, y)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_hypotf4(vec_float4, vec_float4);
#endif

// isnan(x)
#if defined(SIMDMATH_VEC_FLOAT4) && defined(SIMDMATH_VEC_INT4)
SIMDMATH_INLINE vec_int4 simdmath_isnanf4(vec_float4);
#endif

// isinf(x)
#if defined(SIMDMATH_VEC_FLOAT4) && defined(SIMDMATH_VEC_INT4)
SIMDMATH_INLINE vec_int4 simdmath_isinff4(vec_float4);
#endif

// isfinite(x)
#if defined(SIMDMATH_VEC_FLOAT4) && defined(SIMDMATH_VEC_INT4)
SIMDMATH_INLINE vec_int4 simdmath_isfinitef4(vec_float4);
#endif

// ldexp(x, e) = x * (2 ^ exp)
#if defined(SIMDMATH_VEC_FLOAT4) && defined(SIMDMATH_VEC_INT4)
SIMDMATH_INLINE vec_float4 simdmath_ldexpf4(vec_float4, vec_int4);
#endif

// log
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_logf4(vec_float4);
#endif

// log10
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_log10f4(vec_float4);
#endif

// log1p
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_log1pf4(vec_float4);
#endif

// log2
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_log2f4(vec_float4);
#endif

// logb
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_logbf4(vec_float4);
#endif

// modf
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_modff4(vec_float4, vec_float4*);
#endif

// Negation
// negate(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_negatef4(vec_float4);
#endif

// pow
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_powf4(vec_float4, vec_float4);
#endif

// Reciprocal Value
// recip(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_recipf4(vec_float4);
#endif

// remainder
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_remainderf4(vec_float4, vec_float4);
#endif

// Reciprocal Square-Root
// rsqrt(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_rsqrtf4(vec_float4);
#endif

// Set
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_setf4(float, float, float, float);
#endif

// Sine Function
// sin(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_sinf4(vec_float4);
#endif

// Sine and Cosine Function
// sincos(x,&s,&c)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE void simdmath_sincosf4(vec_float4, vec_float4* SIMDMATH_RESTRICT, vec_float4* SIMDMATH_RESTRICT);
#endif

// sinh
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_sinhf4(vec_float4);
#endif

// splat
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_splatf4(float);
#endif

// Square-Root
// sqrt(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_sqrtf4(vec_float4);
#endif

// Tangent Function
// tan(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_tanf4(vec_float4);
#endif

// tanh
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_tanhf4(vec_float4);
#endif

// Truncate to integer value
// trunc(x)
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_truncf4(vec_float4);
#endif

// Unaligned load
#ifdef SIMDMATH_VEC_FLOAT4
SIMDMATH_INLINE vec_float4 simdmath_uloadf4(const float*);
#endif

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

#if defined(__cplusplus) || (__STDC_VERSION__ < 199901L)
#  ifndef SIMDMATH_RESTRICT
#    if defined(__GNUC__)
#      define SIMDMATH_RESTRICT __restrict__
#    elif defined(_MSC_VER)
#      define SIMDMATH_RESTRICT __restrict
#    endif
#  endif
#endif

#if defined(__i386__)||defined(__x86_64__)||defined(_M_IX86)||defined(_M_X64)
#  include <xmmintrin.h>
#  include <emmintrin.h>
#  include <immintrin.h>
#  ifdef _MSC_VER
#    define __SSE__
#    define __SSE2__
#  endif
#  define SIMDMATH_VEC_FLOAT4
#  define SIMDMATH_VEC_DOUBLE2
#  define SIMDMATH_VEC_INT4
#  define SIMDMATH_VEC_LLONG2
   typedef __m128 vec_float4;
   typedef __m128d vec_double2;
   typedef __m128i vec_int4;
   typedef __m128i vec_llong2;
#  ifdef __AVX__
#    define SIMDMATH_VEC_FLOAT8
#    define SIMDMATH_VEC_DOUBLE4
#    define SIMDMATH_VEC_INT8
#    define SIMDMATH_VEC_LLONG4
     typedef __m256 vec_float8;
     typedef __m256d vec_double4;
     typedef __m256i vec_int8;
     typedef __m256i vec_llong4;
#  endif // __AVX__
#endif

#if defined(__arm__)||defined(__aarch64__)||defined(_M_ARM)
#  ifdef __ARM_NEON
#    include <arm_neon.h>
#    define SIMDMATH_VEC_FLOAT2
#    define SIMDMATH_VEC_FLOAT4
#    define SIMDMATH_VEC_INT2
#    define SIMDMATH_VEC_INT4
#    define SIMDMATH_VEC_LLONG2
     typedef float32x2_t vec_float2;
     typedef float32x4_t vec_float4;
     typedef int32x2_t vec_int2;
     typedef int32x4_t vec_int4;
     typedef int64x2_t vec_llong2;
#    ifdef __aarch64__
#      define SIMDMATH_VEC_DOUBLE2
       typedef float64x2_t vec_double2;
#    endif
#  endif
#endif

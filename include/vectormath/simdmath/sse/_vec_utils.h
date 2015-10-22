#pragma once

#include <xmmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <stdint.h>

#define _MM_COPYSIGNF_MASK 0x80000000
#define _MM_SIGNMASK_PS (_mm_castsi128_ps(_mm_set1_epi32(0x80000000)))

// bit-wise selection
static inline __m128
_selectf4(__m128 x, __m128 y, __m128 s)
{
  return _mm_or_ps(_mm_andnot_ps(s, x), _mm_and_ps(s, y));
}

// component-wise selection
static inline __m128
_blendf4(__m128 x, __m128 y, __m128 s)
{
#ifdef __SSE4_1__
  return _mm_blendv_ps(x, y, s);
#else
  return _selectf4(x, y, s);
#endif
}

static inline __m128
_maddf4 (__m128 x, __m128 y, __m128 z)
{
#ifdef __FMA__
  return _mm_fmadd_ps(x, y, z);
#else
  return _mm_add_ps(_mm_mul_ps(x, y), z);
#endif
}

static inline __m128
_nmsubf4 (__m128 x, __m128 y, __m128 z)
{
#ifdef __FMA__
  return _mm_fnmsub_ps(x, y, z);
#else
  return _mm_sub_ps(z, _mm_mul_ps(x, y));
#endif
}

static inline __m128
_unaligned_loadf4(const float* p)
{
#if defined(__SSE3__)
  return _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)((void*)p)));
#else
  return _mm_loadu_ps(p);
#endif
}

#ifndef __AVX__
#  ifdef _mm_permute_ps // workaround for GNU C Compilers
#  undef _mm_permute_ps
#  endif
#  define _mm_permute_ps(v,i) _mm_shuffle_ps((v), (v), (i))
#endif

#define _MM_SPLAT(e) _MM_SHUFFLE((e), (e), (e), (e))

#define _MM_ROR(i) _MM_SHUFFLE((i+3)%4, (i+2)%4, (i+1)%4, (i+0)%4)
#define _MM_ROL(i) _MM_SHUFFLE((7-i)%4, (6-i)%4, (5-i)%4, (4-i)%4)

#define _mm_ror_ps(v,i) (((i)%4) ? (_mm_permute_ps((v),_MM_ROR(i))) : (v))
#define _mm_rol_ps(v,i) (((i)%4) ? (_mm_permute_ps((v),_MM_ROL(i))) : (v))

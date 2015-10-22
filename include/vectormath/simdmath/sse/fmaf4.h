#pragma once

#include <immintrin.h>

static SIMD_INLINE __m128
_fmaf4 (__m128 x, __m128 y, __m128 z)
{
#ifdef __FMA__
  return _mm_fmadd_ps(x, y, z);
#else
  return _mm_add_ps(_mm_mul_ps(x, y), z);
#endif
}

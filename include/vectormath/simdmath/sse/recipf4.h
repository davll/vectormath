#pragma once

#include <xmmintrin.h>
#include <emmintrin.h>

static inline __m128
_recipf4 (__m128 x)
{
  // Reciprocal estimate and 1 Newton-Raphson iteration.
  // A constant of 1.0 + 1 ulp in the Newton-Raphson step results in exact
  // answers for powers of 2, and a slightly smaller relative error bound.

  const __m128 oneish = _mm_castsi128_ps(_mm_set1_epi32(0x3f800001));
  __m128 y0, tmp;

  y0 = _mm_rcp_ps( x );
  tmp = _mm_sub_ps( oneish, _mm_mul_ps( x, y0 ) );
  return _mm_add_ps( _mm_mul_ps( tmp, y0 ), y0 );
}

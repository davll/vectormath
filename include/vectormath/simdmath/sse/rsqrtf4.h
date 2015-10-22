#pragma once

#include <xmmintrin.h>

static inline __m128
_rsqrtf4 (__m128 x)
{
  // Newton-Raphson method
  const __m128 half = _mm_set1_ps(0.5f);
  const __m128 three = _mm_set1_ps(3.0f);

  __m128 approx = _mm_rsqrt_ps( x );
  __m128 muls = _mm_mul_ps( _mm_mul_ps(x, approx), approx );
  return _mm_mul_ps( _mm_mul_ps(half, approx), _mm_sub_ps(three, muls) );

  /*
  // Reciprocal square root estimate and 1 Newton-Raphson iteration.

  const __m128 zero = _mm_set1_ps(0.0f);
  const __m128 half = _mm_set1_ps(0.5f);
  const __m128 one = _mm_set1_ps(1.0f);
  __m128 y0, y0x, y0half, tmp;

  y0 = _mm_rsqrt_ps( x );
  y0x = _mm_add_ps( _mm_mul_ps( y0, x ), zero );
  y0half = _mm_add_ps( _mm_mul_ps( y0, half ), zero );
  tmp = _mm_sub_ps( one, _mm_mul_ps( y0, y0x ) );
  return _mm_add_ps( _mm_mul_ps( tmp, y0half ), y0 );
  */
}

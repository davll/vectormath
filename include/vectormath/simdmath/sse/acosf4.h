#pragma once

#include "_vec_utils.h"
#include "fabsf4.h"
#include "sqrtf4.h"

//
// Computes the inverse cosine of all four slots of x.
//
static inline __m128
_acosf4 (__m128 x)
{
  __m128 xabs = _fabsf4( x );
  __m128 select = _mm_cmplt_ps( x, _mm_setzero_ps() );
  __m128 t1 = _sqrtf4( _mm_sub_ps(_mm_set1_ps(1.0f), xabs) );

  /* Instruction counts can be reduced if the polynomial was
   * computed entirely from nested (dependent) fma's. However,
   * to reduce the number of pipeline stalls, the polygon is evaluated
   * in two halves (hi amd lo).
   */
  __m128 xabs2 = _mm_mul_ps(xabs,  xabs);
  __m128 xabs4 = _mm_mul_ps(xabs2, xabs2);
  __m128 hi, lo;

  hi = _mm_set1_ps(-0.0012624911f);
  hi = _maddf4(hi, xabs, _mm_set1_ps( 0.0066700901f));
  hi = _maddf4(hi, xabs, _mm_set1_ps(-0.0170881256f));
  hi = _maddf4(hi, xabs, _mm_set1_ps( 0.0308918810f));

  lo = _mm_set1_ps(-0.0501743046f);
  lo = _maddf4(lo, xabs, _mm_set1_ps( 0.0889789874f));
  lo = _maddf4(lo, xabs, _mm_set1_ps(-0.2145988016f));
  lo = _maddf4(lo, xabs, _mm_set1_ps( 1.5707963050f));

  __m128 result = _maddf4(hi, xabs4, lo);

  // Adjust the result if x is negactive.

  __m128 pos = _mm_mul_ps(t1, result);
  __m128 neg = _nmsubf4(t1, result, _mm_set1_ps(3.1415926535898f));

  return _blendf4(pos, neg, select);
}

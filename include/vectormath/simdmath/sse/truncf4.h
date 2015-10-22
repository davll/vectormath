#pragma once

#include "_vec_utils.h"
#include "fabsf4.h"

static inline __m128
_truncf4 (__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x3 );

#else /* SSE2 */

  const __m128 xa = _fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);

  const __m128i xi = _mm_cvttps_epi32(x);

  return _selectf4(x, _mm_cvtepi32_ps(xi), inrange);

#endif
}

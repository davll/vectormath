#pragma once

#include "_vec_utils.h"

static inline __m128
_copyxf4(__m128 a, __m128 b)
{
#ifdef __SSE4_1__
  return _mm_blend_ps(a, b, 0x1);
#else
  __m128 mask = _mm_castsi128_ps(_mm_setr_epi32(0xFFFFFFFF, 0, 0, 0));
  return _selectf4(a, b, mask);
#endif
}

#pragma once

#include "_vec_utils.h"

static inline __m128
_copyzf4(__m128 a, __m128 b)
{
#ifdef __SSE4_1__
  return _mm_blend_ps(a, b, 0x4);
#else
  __m128 mask = _mm_castsi128_ps(_mm_setr_epi32(0, 0, 0xFFFFFFFF, 0));
  return _selectf4(a, b, mask);
#endif
}

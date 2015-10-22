#pragma once

#include <xmmintrin.h>

static inline __m128
_fmaxf4(__m128 x, __m128 y)
{
  return _mm_max_ps(x, y);
}

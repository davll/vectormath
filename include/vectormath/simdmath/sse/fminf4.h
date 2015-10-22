#pragma once

#include <xmmintrin.h>

static inline __m128
_fminf4(__m128 x, __m128 y)
{
  return _mm_min_ps(x, y);
}

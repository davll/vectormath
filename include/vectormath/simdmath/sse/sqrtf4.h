#pragma once

#include <xmmintrin.h>

static inline __m128
_sqrtf4 (__m128 x)
{
  return _mm_sqrt_ps( x );
}

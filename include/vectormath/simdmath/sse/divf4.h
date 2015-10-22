#pragma once

#include "_vec_utils.h"

static inline __m128
_divf4 (__m128 numer, __m128 denom)
{
  return _mm_div_ps( numer, denom );
}

#pragma once

#include "_vec_utils.h"

static inline __m128
_negatef4(__m128 x)
{
  return _mm_xor_ps(_MM_SIGNMASK_PS, x);
}

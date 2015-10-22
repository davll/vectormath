#pragma once

#include "_vec_utils.h"

static inline __m128
_fabsf4(__m128 x)
{
  return _mm_andnot_ps(_MM_SIGNMASK_PS, x);
}

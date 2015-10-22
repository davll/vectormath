#pragma once

#include "_vec_utils.h"

static inline __m128
_copysignf4 (__m128 x, __m128 y)
{
  __m128 mask = _MM_SIGNMASK_PS;
  __m128 lhs = _mm_andnot_ps( mask, x );
  __m128 rhs = _mm_and_ps( mask, y );
  return _mm_or_ps( lhs, rhs );
}

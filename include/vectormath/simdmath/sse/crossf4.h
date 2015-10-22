#pragma once

#include "_vec_utils.h"

static inline __m128
_crossf4 (__m128 vec0, __m128 vec1)
{
  __m128 tmp0, tmp1, tmp2, tmp3;
  tmp0 = _mm_shuffle_ps(vec0, vec0, _MM_SHUFFLE(3,0,2,1));
  tmp1 = _mm_shuffle_ps(vec1, vec1, _MM_SHUFFLE(3,1,0,2));
  tmp2 = _mm_shuffle_ps(vec0, vec0, _MM_SHUFFLE(3,1,0,2));
  tmp3 = _mm_shuffle_ps(vec1, vec1, _MM_SHUFFLE(3,0,2,1));
  return _mm_sub_ps(_mm_mul_ps(tmp0, tmp1), _mm_mul_ps(tmp2, tmp3));
}

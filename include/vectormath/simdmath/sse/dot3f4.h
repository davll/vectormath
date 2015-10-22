#pragma once

#include "_vec_utils.h"

static inline __m128
_dot3f4 (__m128 x, __m128 y)
{
#if defined(__SSE4_1__)
  return _mm_dp_ps(x, y, 0x7f);
#elif defined(__SSE3__)
  __m128 t = _mm_mul_ps(x, y);
  __m128 t1 = _mm_hadd_ps(t, t);
  __m128 t2 = _mm_add_ps(t1, t);
  return _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(2,2,2,2));
#else
  __m128 t = _mm_mul_ps(x, y);
  __m128 tx = _mm_shuffle_ps(t, t, _MM_SHUFFLE(0,0,0,0));
  __m128 ty = _mm_shuffle_ps(t, t, _MM_SHUFFLE(1,1,1,1));
  __m128 tz = _mm_shuffle_ps(t, t, _MM_SHUFFLE(2,2,2,2));
  return _mm_add_ps(tx, _mm_add_ps(ty, tz));
#endif
}

#pragma once

#include "_vec_utils.h"

static inline __m128
_dot4f4 (__m128 x, __m128 y)
{
#if defined(__SSE4_1__)
  return _mm_dp_ps(x, y, 0xff);
#elif defined(__SSE3__)
  __m128 t = _mm_mul_ps(x, y);
  __m128 t1 = _mm_hadd_ps(t, t);
  return _mm_hadd_ps(t1, t1);
#else
  __m128 xyzw = _mm_mul_ps(x, y);
  __m128 wzyx = _mm_shuffle_ps(xyzw,xyzw, _MM_SHUFFLE(0,1,2,3));
  __m128 xw_yz = _mm_add_ps(xyzw, wzyx);
  __m128 yz_xw = _mm_shuffle_ps(xw_yz,xw_yz, _MM_SHUFFLE(2,3,0,1));
  __m128 result = _mm_add_ps(xw_yz, yz_xw);
  return result;
#endif
}

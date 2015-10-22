#pragma once

#include "_vec_utils.h"

static inline __m128
_combine3f4(__m128 xyz, __m128 w)
{
  //__m128 zzww = _mm_shuffle_ps(xyz_, w___, _MM_SHUFFLE(0,0,2,2));
  //__m128 xyzw = _mm_shuffle_ps(xyz_, zzww, _MM_SHUFFLE(2,0,1,0));
#ifdef __SSE4_1__
  return _mm_insert_ps(xyz, w, 0x30);
#else
  __m128 w_z, xyzw;
  w_z = _mm_shuffle_ps(w, xyz, _MM_SHUFFLE(0,2,1,0));
  xyzw = _mm_shuffle_ps(xyz, w_z, _MM_SHUFFLE(0,2,1,0));
  return xyzw;
#endif
}

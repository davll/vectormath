// -*- C++ -*-
#pragma once
#include <simdmath/simdmath.h>

#ifdef SIMDMATH_VEC_FLOAT4

template<int I>
inline float get_comp(vec_float4 x)
{
  static_assert(I >= 0 && I < 4, "");
#ifdef _MSC_VER
  return x.m128_f32[I];
#else
  return x[I];
#endif
}

#endif

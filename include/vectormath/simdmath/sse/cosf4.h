#pragma once

#include "sincosf4.h"

//
//     Computes the cosine of each of the four slots
//     by using a polynomial approximation.
//
static inline __m128
_cosf4 (__m128 x)
{
  __m128 s, c;
  _sincosf4(x, &s, &c);
  return c;
}

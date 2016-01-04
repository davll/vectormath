// -*- C++ -*-
/*
The source file is part of vectormath

Copyright (c) 2015 David Lin <davll.xc@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once
#include <simdmath/cxx>
#include <cfloat>
#include <cmath>
#ifdef __SSE__
#  include <xmmintrin.h>
#endif

namespace vectormath {

using std::fabs;
using std::fmax;
using std::fmin;
using std::sqrt;
using std::sin;
using std::cos;
using simdmath::fabs;
using simdmath::fmax;
using simdmath::fmin;
using simdmath::sqrt;
using simdmath::rsqrt;
using simdmath::recip;

inline float recip(float x)
{
  return 1.0f / x;
}

inline double recip(double x)
{
  return 1.0 / x;
}

inline float rsqrt(float x)
{
#ifdef __SSE__
  float approx = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
  return 0.5f * approx * (3.0f - x * approx * approx);
#else
  return recip(sqrt(x));
#endif
}

inline double rsqrt(double x)
{
  return recip(sqrt(x));
}

inline void sincos(float x, float* SIMDMATH_RESTRICT s, float* SIMDMATH_RESTRICT c)
{
#if defined(__APPLE__) && defined(__MACH__)
  __sincosf(x, s, c);
#else
  *s = sin(x);
  *c = cos(x);
#endif
}

inline void sincos(double x, double* SIMDMATH_RESTRICT s, double* SIMDMATH_RESTRICT c)
{
#if defined(__APPLE__) && defined(__MACH__)
  __sincos(x, s, c);
#else
  *s = sin(x);
  *c = cos(x);
#endif
}

}

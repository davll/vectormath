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

#if !defined(__i386) && !defined(__x86_64__) && !defined(_M_IX86) && !defined(_M_X64)
#  error Target CPU should be x86 family
#endif

#ifndef __SSE__
#  if (defined(_M_IX86_FP) && _M_IX86_FP >= 2) || defined(_M_X64)
#    define __SSE__
#    define __SSE2__
#  endif
#endif

#if !(defined(__SSE__) && defined(__SSE2__))
#  error Target CPU should support SSE and SSE2
#endif

#define VECTORMATH_SIMDF4_DEFINED

#include <xmmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>

namespace vectormath {

typedef __m128 simdf4;

inline simdf4 make_simdf4(float s0, float s1, float s2, float s3)
{
  return _mm_setr_ps(s0, s1, s2, s3);
}

template<>
struct Vec3<simdf4> {
  simdf4 x;
  simdf4 y;
  simdf4 z;

  static inline Vec3 splat(const Vec3<float>& v);
  static inline Vec3 load(const float* addr);
};

inline void store(float* addr, const Vec3<simdf4>& v);

template<>
struct Pos3<simdf4> {
  simdf4 x;
  simdf4 y;
  simdf4 z;

  static inline Pos3 splat(const Pos3<float>& v);
  static inline Pos3 load(const float* addr);
};

inline void store(float* addr, const Pos3<simdf4>& v);

template<>
struct Vec4<simdf4> {
  simdf4 x;
  simdf4 y;
  simdf4 z;
  simdf4 w;

  static inline Vec4 splat(const Vec4<float>& v);
  static inline Vec4 load(const float* addr);
};

inline void store(float* addr, const Vec4<simdf4>& v);

template<>
struct Quat<simdf4> {
  simdf4 w;
  simdf4 x;
  simdf4 y;
  simdf4 z;

  static inline Quat splat(const Quat<float>& v);
  static inline Quat load(const float* addr);
};

inline void store(float* addr, const Quat<simdf4>& q);

template<>
struct Mat3<simdf4> {
  Vec3<simdf4> c0;
  Vec3<simdf4> c1;
  Vec3<simdf4> c2;

  static inline Mat3 splat(const Mat3<float>& m);
};

template<>
struct Mat4<simdf4> {
  Vec4<simdf4> c0;
  Vec4<simdf4> c1;
  Vec4<simdf4> c2;
  Vec4<simdf4> c3;

  static inline Mat4 splat(const Mat4<float>& m);
};

template<>
struct Tfm3<simdf4> {
  Vec3<simdf4> c0;
  Vec3<simdf4> c1;
  Vec3<simdf4> c2;
  Vec3<simdf4> c3;

  static inline Tfm3 splat(const Tfm3<float>& m);
};

// Splat

inline Vec3<simdf4> Vec3<simdf4>::splat(const Vec3<float>& v)
{
  return Vec3<simdf4>{
    _mm_setr_ps( v.x, v.x, v.x, v.x ),
    _mm_setr_ps( v.y, v.y, v.y, v.y ),
    _mm_setr_ps( v.z, v.z, v.z, v.z )
  };
}

inline Pos3<simdf4> Pos3<simdf4>::splat(const Pos3<float>& v)
{
  return Pos3<simdf4>{
    _mm_setr_ps( v.x, v.x, v.x, v.x ),
    _mm_setr_ps( v.y, v.y, v.y, v.y ),
    _mm_setr_ps( v.z, v.z, v.z, v.z )
  };
}

inline Vec4<simdf4> Vec4<simdf4>::splat(const Vec4<float>& v)
{
  return Vec4<simdf4>{
    _mm_setr_ps( v.x, v.x, v.x, v.x ),
    _mm_setr_ps( v.y, v.y, v.y, v.y ),
    _mm_setr_ps( v.z, v.z, v.z, v.z ),
    _mm_setr_ps( v.w, v.w, v.w, v.w )
  };
}

inline Quat<simdf4> Quat<simdf4>::splat(const Quat<float>& v)
{
  return Quat<simdf4>{
    _mm_setr_ps( v.x, v.x, v.x, v.x ),
    _mm_setr_ps( v.y, v.y, v.y, v.y ),
    _mm_setr_ps( v.z, v.z, v.z, v.z ),
    _mm_setr_ps( v.w, v.w, v.w, v.w )
  };
}

inline Mat3<simdf4> Mat3<simdf4>::splat(const Mat3<float>& m)
{
  return Mat3<simdf4>{
    Vec3<simdf4>::splat(m.c0),
    Vec3<simdf4>::splat(m.c1),
    Vec3<simdf4>::splat(m.c2)
  };
}

inline Mat4<simdf4> Mat4<simdf4>::splat(const Mat4<float>& m)
{
  return Mat4<simdf4>{
    Vec4<simdf4>::splat(m.c0),
    Vec4<simdf4>::splat(m.c1),
    Vec4<simdf4>::splat(m.c2),
    Vec4<simdf4>::splat(m.c3)
  };
}

inline Tfm3<simdf4> Tfm3<simdf4>::splat(const Tfm3<float>& m)
{
  return Tfm3<simdf4>{
    Vec3<simdf4>::splat(m.c0),
    Vec3<simdf4>::splat(m.c1),
    Vec3<simdf4>::splat(m.c2),
    Vec3<simdf4>::splat(m.c3)
  };
}

// Load

inline Vec3<simdf4> Vec3<simdf4>::load(const float* addr)
{
  __m128 x0y0z0x1 = _mm_load_ps(addr);
  __m128 y1z1x2y2 = _mm_load_ps(addr+4);
  __m128 z2x3y3z3 = _mm_load_ps(addr+8);
  __m128 x2y2x3y3 = _mm_shuffle_ps(y1z1x2y2,z2x3y3z3,_MM_SHUFFLE(2,1,3,2));
  __m128 y0z0y1z1 = _mm_shuffle_ps(x0y0z0x1,y1z1x2y2,_MM_SHUFFLE(1,0,2,1));
  __m128 xxxx = _mm_shuffle_ps(x0y0z0x1,x2y2x3y3,_MM_SHUFFLE(2,0,3,0));
  __m128 yyyy = _mm_shuffle_ps(y0z0y1z1,x2y2x3y3,_MM_SHUFFLE(3,1,2,0));
  __m128 zzzz = _mm_shuffle_ps(y0z0y1z1,z2x3y3z3,_MM_SHUFFLE(3,0,3,1));
  return Vec3<simdf4>{ xxxx, yyyy, zzzz };
}

inline Pos3<simdf4> Pos3<simdf4>::load(const float* addr)
{
  Vec3<simdf4> v = Vec3<simdf4>::load(addr);
  return Pos3<simdf4>{ v.x, v.y, v.z };
}

inline Vec4<simdf4> Vec4<simdf4>::load(const float* addr)
{
  __m128 a0 = _mm_load_ps(addr);
  __m128 a1 = _mm_load_ps(addr+4);
  __m128 a2 = _mm_load_ps(addr+8);
  __m128 a3 = _mm_load_ps(addr+12);
  __m128 tmp0 = _mm_unpacklo_ps(a0, a2);
  __m128 tmp1 = _mm_unpacklo_ps(a1, a3);
  __m128 tmp2 = _mm_unpackhi_ps(a0, a2);
  __m128 tmp3 = _mm_unpackhi_ps(a1, a3);
  a0 = _mm_unpacklo_ps(tmp0, tmp1);
  a1 = _mm_unpackhi_ps(tmp0, tmp1);
  a2 = _mm_unpacklo_ps(tmp2, tmp3);
  a3 = _mm_unpackhi_ps(tmp2, tmp3);
  return Vec4<simdf4>{ a0, a1, a2, a3 };
}

inline Quat<simdf4> Quat<simdf4>::load(const float* addr)
{
  Vec4<simdf4> v = Vec4<simdf4>::load(addr);
  return Quat<simdf4>{ v.x, v.y, v.z, v.w };
}

// Store

inline void store(float* addr, const Vec3<simdf4>& v)
{
  __m128 xxxx = v.x, yyyy = v.y, zzzz = v.z;
  __m128 x0x2y0y2 = _mm_shuffle_ps(xxxx,yyyy, _MM_SHUFFLE(2,0,2,0));
  __m128 y1y3z1z3 = _mm_shuffle_ps(yyyy,zzzz, _MM_SHUFFLE(3,1,3,1));
  __m128 z0z2x1x3 = _mm_shuffle_ps(zzzz,xxxx, _MM_SHUFFLE(3,1,2,0));
  __m128 x0y0z0x1 = _mm_shuffle_ps(x0x2y0y2,z0z2x1x3, _MM_SHUFFLE(2,0,2,0));
  __m128 y1z1x2y2 = _mm_shuffle_ps(y1y3z1z3,x0x2y0y2, _MM_SHUFFLE(3,1,2,0));
  __m128 z2x3y3z3 = _mm_shuffle_ps(z0z2x1x3,y1y3z1z3, _MM_SHUFFLE(3,1,3,1));
  _mm_store_ps(addr  , x0y0z0x1);
  _mm_store_ps(addr+4, y1z1x2y2);
  _mm_store_ps(addr+8, z2x3y3z3);
}

inline void store(float* addr, const Pos3<simdf4>& p)
{
  store(addr, Vec3<simdf4>{ p.x, p.y, p.z });
}

inline void store(float* addr, const Vec4<simdf4>& v)
{
  __m128 a0 = v.x, a1 = v.y, a2 = v.z, a3 = v.w;
  __m128 tmp0 = _mm_unpacklo_ps(a0, a2);
  __m128 tmp1 = _mm_unpacklo_ps(a1, a3);
  __m128 tmp2 = _mm_unpackhi_ps(a0, a2);
  __m128 tmp3 = _mm_unpackhi_ps(a1, a3);
  a0 = _mm_unpacklo_ps(tmp0, tmp1);
  a1 = _mm_unpackhi_ps(tmp0, tmp1);
  a2 = _mm_unpacklo_ps(tmp2, tmp3);
  a3 = _mm_unpackhi_ps(tmp2, tmp3);
  _mm_store_ps(addr   , a0);
  _mm_store_ps(addr+ 4, a1);
  _mm_store_ps(addr+ 8, a2);
  _mm_store_ps(addr+12, a3);
}

inline void store(float* addr, const Quat<simdf4>& q)
{
  store(addr, Vec4<simdf4>{ q.w, q.x, q.y, q.z });
}

}

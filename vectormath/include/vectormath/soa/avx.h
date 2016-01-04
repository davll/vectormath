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

#if !defined(__i386) && !defined(__x86_64__) && !defined(_M_X86) && !defined(_M_X64)
#  error Target CPU should be x86 family
#endif

#if !(defined(__AVX__))
#  error Target CPU should support AVX
#endif

#define VECTORMATH_SIMDF8_DEFINED

#include <immintrin.h>

namespace vectormath {

typedef __m256 simdf8;

inline simdf8 make_simdf8(float s0, float s1, float s2, float s3, float s4, float s5, float s6, float s7)
{
  return _mm256_setr_ps(s0, s1, s2, s3, s4, s5, s6, s7);
}

template<>
struct Vec3<simdf8> {
  simdf8 x;
  simdf8 y;
  simdf8 z;

  static inline Vec3 splat(const Vec3<float>& v);
  static inline Vec3 load(const float* addr);
};

inline void store(float* addr, const Vec3<simdf8>& v);

template<>
struct Pos3<simdf8> {
  simdf8 x;
  simdf8 y;
  simdf8 z;

  static inline Pos3 splat(const Pos3<float>& v);
  static inline Pos3 load(const float* addr);
};

inline void store(float* addr, const Pos3<simdf8>& v);

template<>
struct Vec4<simdf8> {
  simdf8 x;
  simdf8 y;
  simdf8 z;
  simdf8 w;

  static inline Vec4 splat(const Vec4<float>& v);
  static inline Vec4 load(const float* addr);
};

inline void store(float* addr, const Vec4<simdf8>& v);

template<>
struct Quat<simdf8> {
  simdf8 w;
  simdf8 x;
  simdf8 y;
  simdf8 z;

  static inline Quat splat(const Quat<float>& v);
  static inline Quat load(const float* addr);
};

inline void store(float* addr, const Quat<simdf8>& q);

template<>
struct Mat3<simdf8> {
  Vec3<simdf8> c0;
  Vec3<simdf8> c1;
  Vec3<simdf8> c2;

  static inline Mat3 splat(const Mat3<float>& m);
};

template<>
struct Mat4<simdf8> {
  Vec4<simdf8> c0;
  Vec4<simdf8> c1;
  Vec4<simdf8> c2;
  Vec4<simdf8> c3;

  static inline Mat4 splat(const Mat4<float>& m);
};

template<>
struct Tfm3<simdf8> {
  Vec3<simdf8> c0;
  Vec3<simdf8> c1;
  Vec3<simdf8> c2;
  Vec3<simdf8> c3;

  static inline Tfm3 splat(const Tfm3<float>& m);
};

// Splat

inline Vec3<simdf8> Vec3<simdf8>::splat(const Vec3<float>& v)
{
  return Vec3<simdf8>{
    _mm256_setr_ps( v.x, v.x, v.x, v.x, v.x, v.x, v.x, v.x ),
    _mm256_setr_ps( v.y, v.y, v.y, v.y, v.y, v.y, v.y, v.y ),
    _mm256_setr_ps( v.z, v.z, v.z, v.z, v.z, v.z, v.z, v.z )
  };
}

inline Pos3<simdf8> Pos3<simdf8>::splat(const Pos3<float>& v)
{
  return Pos3<simdf8>{
    _mm256_setr_ps( v.x, v.x, v.x, v.x, v.x, v.x, v.x, v.x ),
    _mm256_setr_ps( v.y, v.y, v.y, v.y, v.y, v.y, v.y, v.y ),
    _mm256_setr_ps( v.z, v.z, v.z, v.z, v.z, v.z, v.z, v.z )
  };
}

inline Vec4<simdf8> Vec4<simdf8>::splat(const Vec4<float>& v)
{
  return Vec4<simdf8>{
    _mm256_setr_ps( v.x, v.x, v.x, v.x, v.x, v.x, v.x, v.x ),
    _mm256_setr_ps( v.y, v.y, v.y, v.y, v.y, v.y, v.y, v.y ),
    _mm256_setr_ps( v.z, v.z, v.z, v.z, v.z, v.z, v.z, v.z ),
    _mm256_setr_ps( v.w, v.w, v.w, v.w, v.w, v.w, v.w, v.w )
  };
}

inline Quat<simdf8> Quat<simdf8>::splat(const Quat<float>& v)
{
  return Quat<simdf8>{
    _mm256_setr_ps( v.x, v.x, v.x, v.x, v.x, v.x, v.x, v.x ),
    _mm256_setr_ps( v.y, v.y, v.y, v.y, v.y, v.y, v.y, v.y ),
    _mm256_setr_ps( v.z, v.z, v.z, v.z, v.z, v.z, v.z, v.z ),
    _mm256_setr_ps( v.w, v.w, v.w, v.w, v.w, v.w, v.w, v.w )
  };
}

inline Mat3<simdf8> Mat3<simdf8>::splat(const Mat3<float>& m)
{
  return Mat3<simdf8>{
    Vec3<simdf8>::splat(m.c0),
    Vec3<simdf8>::splat(m.c1),
    Vec3<simdf8>::splat(m.c2)
  };
}

inline Mat4<simdf8> Mat4<simdf8>::splat(const Mat4<float>& m)
{
  return Mat4<simdf8>{
    Vec4<simdf8>::splat(m.c0),
    Vec4<simdf8>::splat(m.c1),
    Vec4<simdf8>::splat(m.c2),
    Vec4<simdf8>::splat(m.c3)
  };
}

inline Tfm3<simdf8> Tfm3<simdf8>::splat(const Tfm3<float>& m)
{
  return Tfm3<simdf8>{
    Vec3<simdf8>::splat(m.c0),
    Vec3<simdf8>::splat(m.c1),
    Vec3<simdf8>::splat(m.c2),
    Vec3<simdf8>::splat(m.c3)
  };
}

// Load

inline Vec3<simdf8> Vec3<simdf8>::load(const float* addr)
{
  const __m128* m = (const __m128*) addr;
  __m256 m03, m14, m25, xy, yz;

  m03 = _mm256_castps128_ps256(m[0]); // load lower halves
  m14 = _mm256_castps128_ps256(m[1]);
  m25 = _mm256_castps128_ps256(m[2]);
  m03 = _mm256_insertf128_ps(m03,m[3],1); // load upper halves
  m14 = _mm256_insertf128_ps(m14,m[4],1);
  m25 = _mm256_insertf128_ps(m25,m[5],1);

  xy = _mm256_shuffle_ps(m14, m25, _MM_SHUFFLE(2,1,3,2)); // upper x's and y's
  yz = _mm256_shuffle_ps(m03, m14, _MM_SHUFFLE(1,0,2,1)); // lower y's and z's

  __m256 x = _mm256_shuffle_ps(m03, xy, _MM_SHUFFLE(2,0,3,0));
  __m256 y = _mm256_shuffle_ps(yz, xy, _MM_SHUFFLE(3,1,2,0));
  __m256 z = _mm256_shuffle_ps(yz, m25, _MM_SHUFFLE(3,0,3,1));
  return Vec3<simdf8>{ x, y, z };
}

inline Pos3<simdf8> Pos3<simdf8>::load(const float* addr)
{
  Vec3<simdf8> v = Vec3<simdf8>::load(addr);
  return Pos3<simdf8>{ v.x, v.y, v.z };
}

inline Vec4<simdf8> Vec4<simdf8>::load(const float* addr)
{
  const __m128* m = (const __m128*) addr;

  __m256 a0, a1, a2, a3;
  a0 = _mm256_castps128_ps256(m[0]);
  a1 = _mm256_castps128_ps256(m[1]);
  a2 = _mm256_castps128_ps256(m[2]);
  a3 = _mm256_castps128_ps256(m[3]);
  a0 = _mm256_insertf128_ps(a0,m[4],1);
  a1 = _mm256_insertf128_ps(a1,m[5],1);
  a2 = _mm256_insertf128_ps(a2,m[6],1);
  a3 = _mm256_insertf128_ps(a3,m[7],1);

  __m256 tmp0, tmp1, tmp2, tmp3;
  tmp0 = _mm256_unpacklo_ps(a0, a2);
  tmp1 = _mm256_unpacklo_ps(a1, a3);
  tmp2 = _mm256_unpackhi_ps(a0, a2);
  tmp3 = _mm256_unpackhi_ps(a1, a3);

  __m256 x = _mm256_unpacklo_ps(tmp0, tmp1);
  __m256 y = _mm256_unpackhi_ps(tmp0, tmp1);
  __m256 z = _mm256_unpacklo_ps(tmp2, tmp3);
  __m256 w = _mm256_unpackhi_ps(tmp2, tmp3);
  return Vec4<simdf8>{ x, y, z, w };
}

inline Quat<simdf8> Quat<simdf8>::load(const float* addr)
{
  Vec4<simdf8> v = Vec4<simdf8>::load(addr);
  return Quat<simdf8>{ v.x, v.y, v.z, v.w };
}

// Store

inline void store(float* addr, const Vec3<simdf8>& v)
{
  __m128* m = (__m128*) addr;
  __m256 x = v.x, y = v.y, z = v.z;

  __m256 rxy = _mm256_shuffle_ps(x,y, _MM_SHUFFLE(2,0,2,0));
  __m256 ryz = _mm256_shuffle_ps(y,z, _MM_SHUFFLE(3,1,3,1));
  __m256 rzx = _mm256_shuffle_ps(z,x, _MM_SHUFFLE(3,1,2,0));
  __m256 r03 = _mm256_shuffle_ps(rxy, rzx, _MM_SHUFFLE(2,0,2,0));
  __m256 r14 = _mm256_shuffle_ps(ryz, rxy, _MM_SHUFFLE(3,1,2,0));
  __m256 r25 = _mm256_shuffle_ps(rzx, ryz, _MM_SHUFFLE(3,1,3,1));

  m[0] = _mm256_castps256_ps128(r03);
  m[1] = _mm256_castps256_ps128(r14);
  m[2] = _mm256_castps256_ps128(r25);
  m[3] = _mm256_extractf128_ps(r03, 1);
  m[4] = _mm256_extractf128_ps(r14, 1);
  m[5] = _mm256_extractf128_ps(r25, 1);
}

inline void store(float* addr, const Pos3<simdf8>& p)
{
  store(addr, Vec3<simdf8>{ p.x, p.y, p.z });
}

inline void store(float* addr, const Vec4<simdf8>& v)
{
  __m128* m = (__m128*) addr;
  __m256 a0 = v.x;
  __m256 a1 = v.y;
  __m256 a2 = v.z;
  __m256 a3 = v.w;

  __m256 tmp0, tmp1, tmp2, tmp3;
  tmp0 = _mm256_unpacklo_ps(a0, a2);
  tmp1 = _mm256_unpacklo_ps(a1, a3);
  tmp2 = _mm256_unpackhi_ps(a0, a2);
  tmp3 = _mm256_unpackhi_ps(a1, a3);

  a0 = _mm256_unpacklo_ps(tmp0, tmp1);
  a1 = _mm256_unpackhi_ps(tmp0, tmp1);
  a2 = _mm256_unpacklo_ps(tmp2, tmp3);
  a3 = _mm256_unpackhi_ps(tmp2, tmp3);

  m[0] = _mm256_castps256_ps128(a0);
  m[1] = _mm256_castps256_ps128(a1);
  m[2] = _mm256_castps256_ps128(a2);
  m[3] = _mm256_castps256_ps128(a3);
  m[4] = _mm256_extractf128_ps(a0, 1);
  m[5] = _mm256_extractf128_ps(a1, 1);
  m[6] = _mm256_extractf128_ps(a2, 1);
  m[7] = _mm256_extractf128_ps(a3, 1);
}

inline void store(float* addr, const Quat<simdf8>& q)
{
  store(addr, Vec4<simdf8>{ q.w, q.x, q.y, q.z });
}

}

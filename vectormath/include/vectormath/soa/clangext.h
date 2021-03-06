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

#if !defined(__clang__) || !__has_extension(attribute_ext_vector_type)
#  error "The compiler does not support vector extension"
#endif

namespace vectormath {

typedef float simdf4 __attribute__((ext_vector_type(4)));
//typedef float simdf8 __attribute__((ext_vector_type(8)));

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

// Utility functions

inline simdf4 _unpacklo(simdf4 a, simdf4 b)
{
  return __builtin_shufflevector(a, b, 0, 4, 1, 5);
}

inline simdf4 _unpackhi(simdf4 a, simdf4 b)
{
  return __builtin_shufflevector(a, b, 2, 6, 3, 7);
}

inline void _transpose(simdf4& a0, simdf4& a1, simdf4& a2, simdf4& a3)
{
  simdf4 tmp0 = _unpacklo(a0, a2);
  simdf4 tmp1 = _unpacklo(a1, a3);
  simdf4 tmp2 = _unpackhi(a0, a2);
  simdf4 tmp3 = _unpackhi(a1, a3);
  a0 = _unpacklo(tmp0, tmp1);
  a1 = _unpackhi(tmp0, tmp1);
  a2 = _unpacklo(tmp2, tmp3);
  a3 = _unpackhi(tmp2, tmp3);
}

// Splat

inline Vec3<simdf4> Vec3<simdf4>::splat(const Vec3<float>& v)
{
  return Vec3<simdf4>{
    (simdf4){ v.x, v.x, v.x, v.x },
    (simdf4){ v.y, v.y, v.y, v.y },
    (simdf4){ v.z, v.z, v.z, v.z }
  };
}

inline Pos3<simdf4> Pos3<simdf4>::splat(const Pos3<float>& v)
{
  return Pos3<simdf4>{
    (simdf4){ v.x, v.x, v.x, v.x },
    (simdf4){ v.y, v.y, v.y, v.y },
    (simdf4){ v.z, v.z, v.z, v.z }
  };
}

inline Vec4<simdf4> Vec4<simdf4>::splat(const Vec4<float>& v)
{
  return Vec4<simdf4>{
    (simdf4){ v.x, v.x, v.x, v.x },
    (simdf4){ v.y, v.y, v.y, v.y },
    (simdf4){ v.z, v.z, v.z, v.z },
    (simdf4){ v.w, v.w, v.w, v.w }
  };
}

inline Quat<simdf4> Quat<simdf4>::splat(const Quat<float>& v)
{
  return Quat<simdf4>{
    (simdf4){ v.x, v.x, v.x, v.x },
    (simdf4){ v.y, v.y, v.y, v.y },
    (simdf4){ v.z, v.z, v.z, v.z },
    (simdf4){ v.w, v.w, v.w, v.w }
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
  simdf4 x0y0z0x1 = *(const simdf4*)(addr);
  simdf4 y1z1x2y2 = *(const simdf4*)(addr+4);
  simdf4 z2x3y3z3 = *(const simdf4*)(addr+8);
  simdf4 x2y2x3y3 = __builtin_shufflevector(y1z1x2y2,z2x3y3z3, 2,3,5,6);
  simdf4 y0z0y1z1 = __builtin_shufflevector(x0y0z0x1,y1z1x2y2, 1,2,4,5);
  simdf4 xxxx = __builtin_shufflevector(x0y0z0x1,x2y2x3y3, 0,3,4,6);
  simdf4 yyyy = __builtin_shufflevector(y0z0y1z1,x2y2x3y3, 0,2,5,7);
  simdf4 zzzz = __builtin_shufflevector(y0z0y1z1,z2x3y3z3, 1,3,4,7);
  return Vec3<simdf4>{ xxxx, yyyy, zzzz };
}

inline Pos3<simdf4> Pos3<simdf4>::load(const float* addr)
{
  Vec3<simdf4> v = Vec3<simdf4>::load(addr);
  return Pos3<simdf4>{ v.x, v.y, v.z };
}

inline Vec4<simdf4> Vec4<simdf4>::load(const float* addr)
{
  simdf4 a0 = *(const simdf4*)(addr);
  simdf4 a1 = *(const simdf4*)(addr+4);
  simdf4 a2 = *(const simdf4*)(addr+8);
  simdf4 a3 = *(const simdf4*)(addr+12);
  _transpose(a0, a1, a2, a3);
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
  simdf4 xxxx = v.x, yyyy = v.y, zzzz = v.z;
  simdf4 x0x2y0y2 = __builtin_shufflevector(xxxx,yyyy, 0,2,4,6);
  simdf4 y1y3z1z3 = __builtin_shufflevector(yyyy,zzzz, 1,3,5,7);
  simdf4 z0z2x1x3 = __builtin_shufflevector(zzzz,xxxx, 0,2,5,7);
  simdf4 x0y0z0x1 = __builtin_shufflevector(x0x2y0y2,z0z2x1x3, 0,2,4,6);
  simdf4 y1z1x2y2 = __builtin_shufflevector(y1y3z1z3,x0x2y0y2, 0,2,5,7);
  simdf4 z2x3y3z3 = __builtin_shufflevector(z0z2x1x3,y1y3z1z3, 1,3,5,7);
  *(simdf4*)(addr) = x0y0z0x1;
  *(simdf4*)(addr+4) = y1z1x2y2;
  *(simdf4*)(addr+8) = z2x3y3z3;
}

inline void store(float* addr, const Pos3<simdf4>& p)
{
  store(addr, Vec3<simdf4>{ p.x, p.y, p.z });
}

inline void store(float* addr, const Vec4<simdf4>& v)
{
  simdf4 a0 = v.x, a1 = v.y, a2 = v.z, a3 = v.w;
  _transpose(a0, a1, a2, a3);
  *(simdf4*)(addr) = a0;
  *(simdf4*)(addr+4) = a1;
  *(simdf4*)(addr+8) = a2;
  *(simdf4*)(addr+12) = a3;
}

inline void store(float* addr, const Quat<simdf4>& q)
{
  store(addr, Vec4<simdf4>{ q.w, q.x, q.y, q.z });
}

}

#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <cfloat>

namespace vectormath {

template<typename T> struct Vec3;
template<typename T> struct Pos3;
template<typename T> struct Vec4;
template<typename T> struct Mat3;
template<typename T> struct Mat4;
template<typename T> struct Quat;

// 3-component vector
template<typename T>
struct Vec3 {
  T x;
  T y;
  T z;

  inline Vec3() = default;
  inline Vec3(const Vec3&) = default;
  inline Vec3(const T& tx, const T& ty, const T& tz);
  explicit inline Vec3(const Vec4<T>& v);
  explicit inline Vec3(const Pos3<T>& p);
};

template<typename T> inline Vec3<T> operator-(const Vec3<T>& a);
template<typename T> inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> operator*(const Vec3<T>& a, const T& s);
template<typename T> inline Vec3<T> operator*(const T& s, const Vec3<T>& a);
template<typename T> inline T dot(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> abs(const Vec3<T>& a);
template<typename T> inline T length(const Vec3<T>& a);
template<typename T> inline Vec3<T> normalize(const Vec3<T>& a);

// 3-D position vector
template<typename T>
struct Pos3 {
  T x;
  T y;
  T z;

  inline Pos3() = default;
  inline Pos3(const Pos3&) = default;
  inline Pos3(const T& tx, const T& ty, const T& tz);
  explicit inline Pos3(const Vec3<T>& v);
  explicit inline Pos3(const Vec4<T>& v);
};

template<typename T> inline Pos3<T> operator-(const Pos3<T>& a);
template<typename T> inline Pos3<T> operator+(const Pos3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> operator-(const Pos3<T>& a, const Pos3<T>& b);
template<typename T> inline Pos3<T> operator-(const Pos3<T>& a, const Vec3<T>& b);
template<typename T> inline Pos3<T> operator*(const Pos3<T>& a, const T& s);
template<typename T> inline Pos3<T> operator*(const T& s, const Pos3<T>& a);
template<typename T> inline Pos3<T> min(const Pos3<T>& a, const Pos3<T>& b);
template<typename T> inline Pos3<T> max(const Pos3<T>& a, const Pos3<T>& b);
template<typename T> inline Pos3<T> abs(const Pos3<T>& a);

// 4-component vector
template<typename T>
struct Vec4 {
  T x;
  T y;
  T z;
  T w;

  inline Vec4() = default;
  inline Vec4(const Vec4&) = default;
  inline Vec4(const T& tx, const T& ty, const T& tz, const T& tw);
  explicit inline Vec4(const Vec3<T>& v, const T& tw = T(0));
  explicit inline Vec4(const Pos3<T>& p);
};

template<typename T> inline Vec4<T> operator-(const Vec4<T>& a);
template<typename T> inline Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b);
template<typename T> inline Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b);
template<typename T> inline Vec4<T> operator*(const Vec4<T>& a, const T& s);
template<typename T> inline Vec4<T> operator*(const T& s, const Vec4<T>& a);
template<typename T> inline T dot(const Vec4<T>& a, const Vec4<T>& b);

// Column-major 3x3 matrix
template<typename T>
struct Mat3 {
  Vec3<T> c0;
  Vec3<T> c1;
  Vec3<T> c2;

  inline Mat3() = default;
  inline Mat3(const Mat3&) = default;
  inline Mat3(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c);

  static inline Mat3 identity();
  static inline Mat3 rotation(const T& angle, const Vec3<T>& axis);
  static inline Mat3 rotation(const Quat<T>& unitquat);
  static inline Mat3 scale(const Vec3<T>& scalevec);
};

template<typename T> inline Mat3<T> operator+(const Mat3<T>& a, const Mat3<T>& b);
template<typename T> inline Mat3<T> operator*(const Mat3<T>& a, const T& s);
template<typename T> inline Vec3<T> operator*(const Mat3<T>& m, const Vec3<T>& v);
template<typename T> inline Mat3<T> operator*(const Mat3<T>& a, const Mat3<T>& b);
template<typename T> inline Mat3<T> transpose(const Mat3<T>& m);
template<typename T> inline Mat3<T> inverse(const Mat3<T>& m);

// Column-major 4x4 matrix
template<typename T>
struct Mat4 {
  Vec4<T> c0;
  Vec4<T> c1;
  Vec4<T> c2;
  Vec4<T> c3;

  inline Mat4() = default;
  inline Mat4(const Mat4&) = default;
  inline Mat4(const Vec4<T>& a, const Vec4<T>& b, const Vec4<T>& c, const Vec4<T>& d);
  explicit inline Mat4(const Mat3<T>& m, const Vec4<T>& v);

  static inline Mat4 identity();
};

template<typename T> inline Mat4<T> operator+(const Mat4<T>& a, const Mat4<T>& b);
template<typename T> inline Mat4<T> operator*(const Mat4<T>& a, const T& s);
template<typename T> inline Vec4<T> operator*(const Mat4<T>& m, const Vec3<T>& v);
template<typename T> inline Vec4<T> operator*(const Mat4<T>& m, const Pos3<T>& p);
template<typename T> inline Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v);
template<typename T> inline Mat4<T> operator*(const Mat4<T>& a, const Mat4<T>& b);
template<typename T> inline Mat4<T> transpose(const Mat4<T>& m);
template<typename T> inline Mat4<T> inverse(const Mat4<T>& m);
template<typename T> inline Mat3<T> upper3x3(const Mat4<T>& m);

// Column-major 4x3 matrix
template<typename T>
struct Tfm3 {
  Vec3<T> c0;
  Vec3<T> c1;
  Vec3<T> c2;
  Vec3<T> c3;

  inline Tfm3() = default;
  inline Tfm3(const Tfm3&) = default;
  inline Tfm3(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c, const Vec3<T>& d);
  explicit inline Tfm3(const Mat3<T>& m, const Vec3<T>& v);

  static inline Tfm3 identity();
};

template<typename T> inline Vec3<T> operator*(const Tfm3<T>& m, const Vec3<T>& v);
template<typename T> inline Pos3<T> operator*(const Tfm3<T>& m, const Pos3<T>& p);
template<typename T> inline Tfm3<T> operator*(const Tfm3<T>& a, const Tfm3<T>& b);
template<typename T> inline Tfm3<T> inverse(const Tfm3<T>& m);

// Quaternion
template<typename T>
struct Quat {
  T w;
  T x;
  T y;
  T z;

  inline Quat() = default;
  inline Quat(const Quat&) = default;
  inline Quat(const T& tw, const T& tx, const T& ty, const T& tz);

  static inline Quat identity();
  static inline Quat rotation(const T& angle, const Vec3<T>& axis);
  static inline Quat rotation(const Vec3<T>& v0, const Vec3<T>& v1);
};

template<typename T> inline Quat<T> operator-(const Quat<T>& a);
template<typename T> inline Quat<T> operator~(const Quat<T>& a);
template<typename T> inline Quat<T> operator+(const Quat<T>& a, const Quat<T>& b);
template<typename T> inline Quat<T> operator-(const Quat<T>& a, const Quat<T>& b);
template<typename T> inline Quat<T> operator*(const Quat<T>& a, const T& s);
template<typename T> inline Quat<T> operator*(const T& s, const Quat<T>& a);
template<typename T> inline Quat<T> operator*(const Quat<T>& a, const Quat<T>& b);
template<typename T> inline T dot(const Quat<T>& a, const Quat<T>& b);
template<typename T> inline Quat<T> normalize(const Quat<T>& a);
template<typename T> inline Vec3<T> transform(const Quat<T>& q, const Vec3<T>& v);

// Float utility functions

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
  return recip(std::sqrt(x));
}

inline double rsqrt(double x)
{
  return recip(std::sqrt(x));
}

// Vector Operations

template<typename T>
inline Vec3<T> operator-(const Vec3<T>& a)
{
  return Vec3<T>{ -a.x, -a.y, -a.z };
}

template<typename T>
inline Pos3<T> operator-(const Pos3<T>& a)
{
  return Pos3<T>{ -a.x, -a.y, -a.z };
}

template<typename T>
inline Vec4<T> operator-(const Vec4<T>& a)
{
  return Vec4<T>{ -a.x, -a.y, -a.z, -a.w };
}

template<typename T>
inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
  return Vec3<T>{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template<typename T>
inline Pos3<T> operator+(const Pos3<T>& a, const Vec3<T>& b)
{
  return Pos3<T>{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template<typename T>
inline Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b)
{
  return Vec4<T>{ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

template<typename T>
inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b)
{
  return Vec3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template<typename T>
inline Pos3<T> operator-(const Pos3<T>& a, const Vec3<T>& b)
{
  return Pos3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template<typename T>
inline Vec3<T> operator-(const Pos3<T>& a, const Pos3<T>& b)
{
  return Vec3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template<typename T>
inline Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b)
{
  return Vec4<T>{ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

template<typename T>
inline Vec3<T> operator*(const Vec3<T>& a, const T& s)
{
  return Vec3<T>{ a.x * s, a.y * s, a.z * s };
}

template<typename T>
inline Pos3<T> operator*(const Pos3<T>& a, const T& s)
{
  return Pos3<T>{ a.x * s, a.y * s, a.z * s };
}

template<typename T>
inline Vec4<T> operator*(const Vec4<T>& a, const T& s)
{
  return Vec4<T>{ a.x * s, a.y * s, a.z * s, a.w * s };
}

template<typename T>
inline Vec3<T> operator*(const T& s, const Vec3<T>& a)
{
  return Vec3<T>{ s * a.x, s * a.y, s * a.z };
}

template<typename T>
inline Pos3<T> operator*(const T& s, const Pos3<T>& a)
{
  return Pos3<T>{ s * a.x, s * a.y, s * a.z };
}

template<typename T>
inline Vec4<T> operator*(const T& s, const Vec4<T>& a)
{
  return Vec4<T>{ s * a.x, s * a.y, s * a.z, s * a.w };
}

template<typename T>
inline T dot(const Vec3<T>& a, const Vec3<T>& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
inline T dot(const Vec4<T>& a, const Vec4<T>& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template<typename T>
inline Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b)
{
  T tx = a.y * b.z - a.z * b.y;
  T ty = a.z * b.x - a.x * b.z;
  T tz = a.x * b.y - a.y * b.x;
  return Vec3<T>{ tx, ty, tz };
}

template<typename T>
inline Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b)
{
  using std::fmin;
  T x = fmin(a.x, b.x);
  T y = fmin(a.y, b.y);
  T z = fmin(a.z, b.z);
  return Vec3<T>{ x, y, z };
}

template<typename T>
inline Pos3<T> min(const Pos3<T>& a, const Pos3<T>& b)
{
  using std::fmin;
  T x = fmin(a.x, b.x);
  T y = fmin(a.y, b.y);
  T z = fmin(a.z, b.z);
  return Pos3<T>{ x, y, z };
}

template<typename T>
inline Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b)
{
  using std::fmax;
  T x = fmax(a.x, b.x);
  T y = fmax(a.y, b.y);
  T z = fmax(a.z, b.z);
  return Vec3<T>{ x, y, z };
}

template<typename T>
inline Pos3<T> max(const Pos3<T>& a, const Pos3<T>& b)
{
  using std::fmax;
  T x = fmax(a.x, b.x);
  T y = fmax(a.y, b.y);
  T z = fmax(a.z, b.z);
  return Pos3<T>{ x, y, z };
}

template<typename T>
inline Vec3<T> abs(const Vec3<T>& a)
{
  using std::fabs;
  return Vec3<T>{ fabs(a.x), fabs(a.y), fabs(a.z) };
}

template<typename T>
inline Pos3<T> abs(const Pos3<T>& a)
{
  using std::fabs;
  return Pos3<T>{ fabs(a.x), fabs(a.y), fabs(a.z) };
}

template<typename T>
inline T length(const Vec3<T>& a)
{
  using std::sqrt;
  T s = a.x * a.x + a.y * a.y + a.z * a.z;
  return sqrt(s);
}

template<typename T>
inline Vec3<T> normalize(const Vec3<T>& a)
{
  using std::sqrt;
  T s = a.x * a.x + a.y * a.y + a.z * a.z;
  s = rsqrt(s);
  return Vec3<T>{ (a.x * s), (a.y * s), (a.z * s) };
}

template<typename T>
inline Vec3<T>::Vec3(const T& tx, const T& ty, const T& tz)
: x(tx), y(ty), z(tz)
{
}

template<typename T>
inline Pos3<T>::Pos3(const T& tx, const T& ty, const T& tz)
: x(tx), y(ty), z(tz)
{
}

template<typename T>
inline Vec4<T>::Vec4(const T& tx, const T& ty, const T& tz, const T& tw)
: x(tx), y(ty), z(tz), w(tw)
{
}

template<typename T>
inline Vec3<T>::Vec3(const Pos3<T>& p)
: x(p.x), y(p.y), z(p.z)
{
}

template<typename T>
inline Vec3<T>::Vec3(const Vec4<T>& v)
: x(v.x), y(v.y), z(v.z)
{
}

template<typename T>
inline Vec4<T>::Vec4(const Vec3<T>& v, const T& tw)
: x(v.x), y(v.y), z(v.z), w(tw)
{
}

template<typename T>
inline Pos3<T>::Pos3(const Vec3<T>& v)
: x(v.x), y(v.y), z(v.z)
{
}

template<typename T>
inline Pos3<T>::Pos3(const Vec4<T>& v)
: x(v.x / v.w), y(v.y / v.w), z(v.z / v.w)
{
}

template<typename T>
inline Vec4<T>::Vec4(const Pos3<T>& p)
: x(p.x), y(p.y), z(p.z), w(T(1))
{
}

// Matrix Operations

template<typename T>
inline Mat3<T> operator+(const Mat3<T>& a, const Mat3<T>& b)
{
  return Mat3<T>{ a.c0 + b.c0, a.c1 + b.c1, a.c2 + b.c2 };
}

template<typename T>
inline Mat4<T> operator+(const Mat4<T>& a, const Mat4<T>& b)
{
  return Mat4<T>{ a.c0 + b.c0, a.c1 + b.c1, a.c2 + b.c2, a.c3 + b.c3 };
}

template<typename T>
inline Mat3<T> operator*(const Mat3<T>& a, const T& s)
{
  return Mat3<T>{ a.c0 * s, a.c1 * s, a.c2 * s };
}

template<typename T>
inline Mat4<T> operator*(const Mat4<T>& a, const T& s)
{
  return Mat4<T>{ a.c0 * s, a.c1 * s, a.c2 * s, a.c3 * s };
}

template<typename T>
inline Vec3<T> operator*(const Mat3<T>& m, const Vec3<T>& v)
{
  return m.c0 * v.x + m.c1 * v.y + m.c2 * v.z;
}

template<typename T>
inline Vec4<T> operator*(const Mat4<T>& m, const Vec3<T>& v)
{
  return m.c0 * v.x + m.c1 * v.y + m.c2 * v.z;
}

template<typename T>
inline Vec4<T> operator*(const Mat4<T>& m, const Pos3<T>& p)
{
  return m.c0 * p.x + m.c1 * p.y + m.c2 * p.z + m.c3;
}

template<typename T>
inline Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v)
{
  return m.c0 * v.x + m.c1 * v.y + m.c2 * v.z + m.c3 * v.w;
}

template<typename T>
inline Vec3<T> operator*(const Tfm3<T>& m, const Vec3<T>& v)
{
  return m.c0 * v.x + m.c1 * v.y + m.c2 * v.z;
}

template<typename T>
inline Pos3<T> operator*(const Tfm3<T>& m, const Pos3<T>& p)
{
  return Pos3<T>(m.c0 * p.x + m.c1 * p.y + m.c2 * p.z + m.c3);
}

template<typename T>
inline Mat3<T> operator*(const Mat3<T>& a, const Mat3<T>& b)
{
  return Mat3<T>{ a * b.c0, a * b.c1, a * b.c2 };
}

template<typename T>
inline Mat4<T> operator*(const Mat4<T>& a, const Mat4<T>& b)
{
  return Mat4<T>{ a * b.c0, a * b.c1, a * b.c2, a * b.c3 };
}

template<typename T>
inline Tfm3<T> operator*(const Tfm3<T>& a, const Tfm3<T>& b)
{
  return Tfm3<T>{ a * b.c0, a * b.c1, a * b.c2, a * b.c3 + a.c3 };
}

template<typename T>
inline Mat3<T> transpose(const Mat3<T>& m)
{
  return Mat3<T>{
    Vec3<T>{ m.c0.x, m.c1.x, m.c2.x },
    Vec3<T>{ m.c0.y, m.c1.y, m.c2.y },
    Vec3<T>{ m.c0.z, m.c1.z, m.c2.z }
  };
}

template<typename T>
inline Mat4<T> transpose(const Mat4<T>& m)
{
  return Mat4<T>{
    Vec4<T>{ m.c0.x, m.c1.x, m.c2.x, m.c3.x },
    Vec4<T>{ m.c0.y, m.c1.y, m.c2.y, m.c3.y },
    Vec4<T>{ m.c0.z, m.c1.z, m.c2.z, m.c3.z },
    Vec4<T>{ m.c0.w, m.c1.w, m.c2.w, m.c3.w }
  };
}

template<typename T>
inline Mat3<T> inverse(const Mat3<T>& m)
{
  Vec3<T> tmp0, tmp1, tmp2;
  tmp0 = cross(m.c1, m.c2);
  tmp1 = cross(m.c2, m.c0);
  tmp2 = cross(m.c0, m.c1);
  T detinv = recip(dot(m.c2, tmp2));
  return Mat3<T>{
    Vec3<T>{ (tmp0.x * detinv), (tmp1.x * detinv), (tmp2.x * detinv) },
    Vec3<T>{ (tmp0.y * detinv), (tmp1.y * detinv), (tmp2.y * detinv) },
    Vec3<T>{ (tmp0.z * detinv), (tmp1.z * detinv), (tmp2.z * detinv) }
  };
}

template<typename T>
inline Mat4<T> inverse(const Mat4<T>& m)
{
  Vec4<T> r0, r1, r2, r3;
  T tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, detinv;
  tmp0 = m.c2.z * m.c0.w - m.c0.z * m.c2.w;
  tmp1 = m.c3.z * m.c1.w - m.c1.z * m.c3.w;
  tmp2 = m.c0.y * m.c2.z - m.c2.y * m.c0.z;
  tmp3 = m.c1.y * m.c3.z - m.c3.y * m.c1.z;
  tmp4 = m.c2.y * m.c0.w - m.c0.y * m.c2.w;
  tmp5 = m.c3.y * m.c1.w - m.c1.y * m.c3.w;
  r0 = { m.c2.y * tmp1 - m.c2.w * tmp3 - m.c2.z * tmp5,
         m.c3.y * tmp0 - m.c3.w * tmp2 - m.c3.z * tmp4,
         m.c0.w * tmp3 + m.c0.z * tmp5 - m.c0.y * tmp1,
         m.c1.w * tmp2 + m.c1.z * tmp4 - m.c1.y * tmp0 };
  r1 = { m.c2.x * tmp1, m.c3.x * tmp0, m.c0.x * tmp1, m.c1.x * tmp0 };
  r3 = { m.c2.x * tmp3, m.c3.x * tmp2, m.c0.x * tmp3, m.c1.x * tmp2 };
  r2 = { m.c2.x * tmp5, m.c3.x * tmp4, m.c0.x * tmp5, m.c1.x * tmp4 };
  detinv = recip(dot(r0, {m.c0.x, m.c1.x, m.c2.x, m.c3.x}));
  tmp0 = m.c2.x * m.c0.y - m.c0.x * m.c2.y;
  tmp1 = m.c3.x * m.c1.y - m.c1.x * m.c3.y;
  tmp2 = m.c2.x * m.c0.w - m.c0.x * m.c2.w;
  tmp3 = m.c3.x * m.c1.w - m.c1.x * m.c3.w;
  tmp4 = m.c2.x * m.c0.z - m.c0.x * m.c2.z;
  tmp5 = m.c3.x * m.c1.z - m.c1.x * m.c3.z;
  r2 = { m.c2.w * tmp1 - m.c2.y * tmp3 + r2.x,
         m.c3.w * tmp0 - m.c3.y * tmp2 + r2.y,
         m.c0.y * tmp3 - m.c0.w * tmp1 - r2.z,
         m.c1.y * tmp2 - m.c1.w * tmp0 - r2.w };
  r3 = { m.c2.y * tmp5 - m.c2.z * tmp1 + r3.x,
         m.c3.y * tmp4 - m.c3.z * tmp0 + r3.y,
         m.c0.z * tmp1 - m.c0.y * tmp5 - r3.z,
         m.c1.z * tmp0 - m.c1.y * tmp4 - r3.w };
  r1 = { m.c2.z * tmp3 - m.c2.w * tmp5 - r1.x,
         m.c3.z * tmp2 - m.c3.w * tmp4 - r1.y,
         m.c0.w * tmp5 - m.c0.z * tmp3 + r1.z,
         m.c1.w * tmp4 - m.c1.z * tmp2 + r1.w };
  return Mat4<T>{ r0 * detinv, r1 * detinv, r2 * detinv, r3 * detinv };
}

template<typename T>
inline Tfm3<T> inverse(const Tfm3<T>& m)
{
  Mat3<T> r = inverse(Mat3<T>{ m.c0, m.c1, m.c2 });
  return Tfm3<T>{ r, -(r * m.c3) };
}

template<typename T>
inline Mat3<T> upper3x3(const Mat4<T>& m)
{
  return Mat3<T>{ Vec3<T>{m.c0}, Vec3<T>{m.c1}, Vec3<T>{m.c2} };
}

template<typename T>
inline Mat3<T>::Mat3(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c)
: c0(a), c1(b), c2(c)
{
}

template<typename T>
inline Mat4<T>::Mat4(const Vec4<T>& a, const Vec4<T>& b, const Vec4<T>& c, const Vec4<T>& d)
: c0(a), c1(b), c2(c), c3(d)
{
}

template<typename T>
inline Tfm3<T>::Tfm3(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c, const Vec3<T>& d)
: c0(a), c1(b), c2(c), c3(d)
{
}

template<typename T>
inline Mat4<T>::Mat4(const Mat3<T>& m, const Vec4<T>& v)
: c0(m.c0, T(0)), c1(m.c1, T(0)), c2(m.c2, T(0)), c3(v)
{
}

template<typename T>
inline Tfm3<T>::Tfm3(const Mat3<T>& m, const Vec3<T>& v)
: c0(m.c0), c1(m.c1), c2(m.c2), c3(v)
{
}

template<typename T>
inline Mat3<T> Mat3<T>::identity()
{
  return Mat3<T>{
    Vec3<T>{ T(1), T(0), T(0) },
    Vec3<T>{ T(0), T(1), T(0) },
    Vec3<T>{ T(0), T(0), T(1) }
  };
}

template<typename T>
inline Mat4<T> Mat4<T>::identity()
{
  return Mat4<T>{
    Vec4<T>{ T(1), T(0), T(0), T(0) },
    Vec4<T>{ T(0), T(1), T(0), T(0) },
    Vec4<T>{ T(0), T(0), T(1), T(0) },
    Vec4<T>{ T(0), T(0), T(0), T(1) }
  };
}

template<typename T>
inline Tfm3<T> Tfm3<T>::identity()
{
  return Tfm3<T>{
    Vec3<T>{ T(1), T(0), T(0) },
    Vec3<T>{ T(0), T(1), T(0) },
    Vec3<T>{ T(0), T(0), T(1) },
    Vec3<T>{ T(0), T(0), T(0) }
  };
}

template<typename T>
inline Mat3<T> Mat3<T>::rotation(const T& angle, const Vec3<T>& axis)
{
  using std::sin;
  using std::cos;
  T s = sin(angle);
  T c = cos(angle);
  T x = axis.x, y = axis.y, z = axis.z;
  T xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x;
  T omc = T(1) - c;
  return Mat3<T>{
    Vec3<T>{ xx * omc + c, xy * omc + z*s, zx * omc - y*s },
    Vec3<T>{ xy * omc - z*s, yy * omc + c, yz * omc + x*s },
    Vec3<T>{ zx * omc + y*s, yz * omc - x*s, zz * omc + c }
  };
}

template<typename T>
inline Mat3<T> Mat3<T>::scale(const Vec3<T>& scalevec)
{
  return Mat3<T>{
    Vec3<T>{ scalevec.x, T(0), T(0) },
    Vec3<T>{ T(0), scalevec.y, T(0) },
    Vec3<T>{ T(0), T(0), scalevec.z }
  };
}

// Quaternion Operations

template<typename T>
inline Quat<T> operator-(const Quat<T>& a)
{
  return Quat<T>{ -a.w, -a.x, -a.y, -a.z };
}

template<typename T>
inline Quat<T> operator~(const Quat<T>& a)
{
  return Quat<T>{ a.w, -a.x, -a.y, -a.z };
}

template<typename T>
inline Quat<T> operator+(const Quat<T>& a, const Quat<T>& b)
{
  return Quat<T>{ a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z };
}

template<typename T>
inline Quat<T> operator-(const Quat<T>& a, const Quat<T>& b)
{
  return Quat<T>{ a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z };
}

template<typename T>
inline Quat<T> operator*(const Quat<T>& a, const T& s)
{
  return Quat<T>{ a.w * s, a.x * s, a.y * s, a.z * s };
}

template<typename T>
inline Quat<T> operator*(const T& s, const Quat<T>& a)
{
  return Quat<T>{ s * a.w, s * a.x, s * a.y, s * a.z };
}

template<typename T>
inline Quat<T> operator*(const Quat<T>& a, const Quat<T>& b)
{
  // let w0 = a.w, v0 = a.xyz, w1 = b.w, v1 = b.xyz
  // result.w = w0 * w1 - dot(v0, v1)
  T tw = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
  // result.xyz = w0 * v1 + w1 * v0 + cross(v0, v1)
  T tx = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
  T ty = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
  T tz = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
  return Quat<T>{ tw, tx, ty, tz };
}

template<typename T>
inline T dot(const Quat<T>& a, const Quat<T>& b)
{
  return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
inline Quat<T> normalize(const Quat<T>& a)
{
  using std::sqrt;
  T s = a.w * a.w + a.x * a.x + a.y * a.y + a.z * a.z;
  s = rsqrt(s);
  return Quat<T>{ (a.w * s), (a.x * s), (a.y * s), (a.z * s) };
}

template<typename T>
inline Vec3<T> transform(const Quat<T>& q, const Vec3<T>& v)
{
  // let p = (xyz=v, w=0)
  // p' = q * p * inv(q)
  //    = q * p * ~q when q is unit
  // =>
  // tmpXYZ = q.w * v.xyz + cross(q.xyz, v.xyz)
  // tmpW = dot(q.xyz, v.xyz)
  // outXYZ = tmpW * q.xyz + tmpXYZ * q.w - cross(tmpXYZ, q.xyz)
  T tw = q.x * v.x + q.y * v.y + q.z * v.z;
  T tx = q.w * v.x + q.y * v.z - q.z * v.y;
  T ty = q.w * v.y + q.z * v.x - q.x * v.z;
  T tz = q.w * v.z + q.x * v.y - q.y * v.x;
  T rx = tw * q.x + q.w * tx - ty * q.z + tz * q.y;
  T ry = tw * q.y + q.w * ty - tz * q.x + tx * q.z;
  T rz = tw * q.z + q.w * tz - tx * q.y + ty * q.x;
  return Vec3<T>{ rx, ry, rz };
}

template<typename T>
inline Quat<T> Quat<T>::identity()
{
  return Quat<T>{T(1), T(0), T(0), T(0)};
}

template<typename T>
inline Quat<T> Quat<T>::rotation(const T& angle, const Vec3<T>& axis)
{
  using std::sin;
  using std::cos;
  T ha = angle / T(2);
  T s = sin(ha), c = cos(ha);
  return Quat<T>{ c, (axis.x * s), (axis.y * s), (axis.z * s) };
}

template<typename T>
inline Quat<T> Quat<T>::rotation(const Vec3<T>& v0, const Vec3<T>& v1)
{
  using std::sqrt;
  Vec3<T> sa = cross(v0, v1); // axis * sin(angle)
  T ca = dot(v0, v1); // cos(angle)
  // compute cos(angle/2) = sqrt((1+cos)/2)
  //         sin(angle/2) = sqrt((1-cos)/2)
  //      => sin(angle/2) / sin(angle) = 1/sqrt(2+2cos)
  T tmp0 = T(2) + ca + ca; // 2 + 2cos
  T tmp1 = T(1) / sqrt(tmp0); // sin(angle/2) / sin(angle)
  T tmp2 = tmp0 * tmp1 / T(2); // cos(angle/2)
  return Quat<T>{ tmp2, (sa.x * tmp1), (sa.y * tmp1), (sa.z * tmp1) };
}

template<typename T>
inline Mat3<T> Mat3<T>::rotation(const Quat<T>& q)
{
  T xx2 = q.x * q.x, xy2 = q.x * q.y, xz2 = q.x * q.z, xw2 = q.x * q.w,
    yy2 = q.y * q.y, yz2 = q.y * q.z, yw2 = q.y * q.w,
    zz2 = q.z * q.z, zw2 = q.z * q.w;
  xx2 += xx2, xy2 += xy2, xz2 += xz2, xw2 += xw2,
  yy2 += yy2, yz2 += yz2, yw2 += yw2,
  zz2 += zz2, zw2 += zw2;
  return Mat3<T>{
    Vec3<T>{ (T(1)-yy2-zz2), (xy2+zw2), (xz2-yw2) },
    Vec3<T>{ (xy2-zw2), (T(1)-xx2-zz2), (yz2+xw2) },
    Vec3<T>{ (xz2+yw2), (yz2-xw2), (T(1)-xx2-yy2) }
  };
}

template<typename T>
inline Quat<T>::Quat(const T& tw, const T& tx, const T& ty, const T& tz)
: w(tw), x(tx), y(ty), z(tz)
{
}

}

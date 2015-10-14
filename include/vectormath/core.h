#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <cfloat>

namespace vectormath {

template<typename T> struct Vec3;
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
};

template<typename T> inline Vec3<T> operator-(const Vec3<T>& a);
template<typename T> inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> operator*(const Vec3<T>& a, const T& s);
template<typename T> inline Vec3<T> operator*(const T& s, const Vec3<T>& a);
template<typename T> inline T dot(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> inline Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);

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
  static inline Mat3 rotation(const Quat<T>& unitquat);
};

template<typename T> inline Mat3<T> operator+(const Mat3<T>& a, const Mat3<T>& b);
template<typename T> inline Mat3<T> operator*(const Mat3<T>& a, const T& s);
template<typename T> inline Vec3<T> operator*(const Mat3<T>& m, const Vec3<T>& v);
template<typename T> inline Mat3<T> operator*(const Mat3<T>& a, const Mat3<T>& b);
template<typename T> inline Mat3<T> transpose(const Mat3<T>& m);

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

  static inline Mat4 identity();
};

template<typename T> inline Mat4<T> operator+(const Mat4<T>& a, const Mat4<T>& b);
template<typename T> inline Mat4<T> operator*(const Mat4<T>& a, const T& s);
template<typename T> inline Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v);
template<typename T> inline Mat4<T> operator*(const Mat4<T>& a, const Mat4<T>& b);
template<typename T> inline Mat4<T> transpose(const Mat4<T>& m);

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
template<typename T> inline Vec3<T> transform(const Quat<T>& q, const Vec3<T>& v);

// Vector Operations

template<typename T>
inline Vec3<T> operator-(const Vec3<T>& a)
{
  return Vec3<T>{ -a.x, -a.y, -a.z };
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
inline Vec3<T>::Vec3(const T& tx, const T& ty, const T& tz)
: x(tx), y(ty), z(tz)
{
}

template<typename T>
inline Vec4<T>::Vec4(const T& tx, const T& ty, const T& tz, const T& tw)
: x(tx), y(ty), z(tz), w(tw)
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
inline Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v)
{
  return m.c0 * v.x + m.c1 * v.y + m.c2 * v.z + m.c3 * v.w;
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
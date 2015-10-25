// -*- C++ -*-
#pragma once

namespace vectormath {

template<typename T> struct Plane;
template<typename T> struct BoundingBox;
template<typename T> struct Sphere;
template<typename T> struct Frustum;

template<typename T>
struct Plane {
  Vec4<T> equation;

  inline Plane() = default;
  inline Plane(const Plane&) = default;
  explicit inline Plane(const Vec4<T>& v);
  explicit inline Plane(const Vec3<T>& n, const T& d);
  explicit inline Plane(const Vec3<T>& n, const Pos3<T>& p);

  inline T operator[](const Pos3<T>& p) const;
};

template<typename T>
struct BoundingBox {
  Pos3<T> minpos;
  Pos3<T> maxpos;

  inline BoundingBox() = default;
  inline BoundingBox(const BoundingBox&) = default;
  explicit inline BoundingBox(const Pos3<T>& a, const Pos3<T>& b);

  inline void add(const Pos3<T>& p);
};

template<typename T>
struct Sphere {
  Pos3<T> center;
  T radius2; // squared radius

  inline Sphere() = default;
  inline Sphere(const Sphere&) = default;
  explicit inline Sphere(const Pos3<T>& c, const T& r2);

  inline T operator[](const Pos3<T>& p) const;
};

template<typename T>
struct Frustum {
  Plane<T> left;
  Plane<T> right;
  Plane<T> bottom;
  Plane<T> top;
  Plane<T> far;
  Plane<T> near;

  inline Frustum() = default;
  inline Frustum(const Frustum&) = default;
  explicit inline Frustum(const Mat4<T>& mat);
};

template<typename T>
inline Plane<T>::Plane(const Vec4<T>& v)
: equation(v)
{
}

template<typename T>
inline Plane<T>::Plane(const Vec3<T>& n, const T& d)
: equation(n, d)
{
}

template<typename T>
inline Plane<T>::Plane(const Vec3<T>& n, const Pos3<T>& p)
: equation(n, -dot(n, Vec3<T>(p)))
{
}

template<typename T>
inline T Plane<T>::operator[](const Pos3<T>& p) const
{
  return dot(equation, Vec4<T>(p));
}

template<typename T>
inline BoundingBox<T>::BoundingBox(const Pos3<T>& a, const Pos3<T>& b)
: minpos(min(a,b)), maxpos(max(a,b))
{
}

template<typename T>
inline void BoundingBox<T>::add(const Pos3<T>& p)
{
  minpos = min(minpos, p);
  maxpos = max(maxpos, p);
}

template<typename T>
inline Sphere<T>::Sphere(const Pos3<T>& c, const T& r2)
: center(c), radius2(r2)
{
}

template<typename T>
inline T Sphere<T>::operator[](const Pos3<T>& p) const
{
  return length_squared(p - center) - radius2;
}

template<typename T>
inline Frustum<T>::Frustum(const Mat4<T>& mat)
{
  Mat4<T> rowmat = transpose(mat);
  left   = Plane<T>{rowmat.c3 + rowmat.c0};
  right  = Plane<T>{rowmat.c3 - rowmat.c0};
  bottom = Plane<T>{rowmat.c3 + rowmat.c1};
  top    = Plane<T>{rowmat.c3 - rowmat.c1};
  near   = Plane<T>{rowmat.c3 + rowmat.c2};
  far    = Plane<T>{rowmat.c3 - rowmat.c2};
}

}

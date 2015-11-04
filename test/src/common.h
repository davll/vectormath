#pragma once

using Vec3f = vectormath::Vec3<float>;
using PVec3f = const vectormath::Vec3<float>&;
using Pos3f = vectormath::Pos3<float>;
using PPos3f = const vectormath::Pos3<float>&;
using Vec4f = vectormath::Vec4<float>;
using PVec4f = const vectormath::Vec4<float>&;
using Mat3f = vectormath::Mat3<float>;
using PMat3f = const vectormath::Mat3<float>&;
using Mat4f = vectormath::Mat4<float>;
using PMat4f = const vectormath::Mat4<float>&;
using Tfm3f = vectormath::Tfm3<float>;
using PTfm3f = const vectormath::Tfm3<float>&;
using Quatf = vectormath::Quat<float>;
using PQuatf = const vectormath::Quat<float>&;

#if defined(__GNUC__)
#  define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#  define NOINLINE __declspec(noinline)
#endif

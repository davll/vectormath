#pragma once

#include "common.h"

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#  if defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP > 0)
#    include <vectormath/soa/sse.h>
#  endif
#  if defined(__AVX__)
#    include <vectormath/soa/avx.h>
#  endif
#endif

#ifdef VECTORMATH_SIMDF2_DEFINED
using Vec3f2 = vectormath::Vec3<vectormath::simdf2>;
using Vec4f2 = vectormath::Vec4<vectormath::simdf2>;
using Pos3f2 = vectormath::Pos3<vectormath::simdf2>;
using Quatf2 = vectormath::Quat<vectormath::simdf2>;
using Mat3f2 = vectormath::Mat3<vectormath::simdf2>;
using Mat4f2 = vectormath::Mat4<vectormath::simdf2>;
using Tfm3f2 = vectormath::Tfm3<vectormath::simdf2>;
union SIMDF2_FLOAT {
	vectormath::simdf2 v;
	float f[2];
};
#endif

#ifdef VECTORMATH_SIMDF4_DEFINED
using vectormath::make_simdf4;
using Vec3f4 = vectormath::Vec3<vectormath::simdf4>;
using Vec4f4 = vectormath::Vec4<vectormath::simdf4>;
using Pos3f4 = vectormath::Pos3<vectormath::simdf4>;
using Quatf4 = vectormath::Quat<vectormath::simdf4>;
using Mat3f4 = vectormath::Mat3<vectormath::simdf4>;
using Mat4f4 = vectormath::Mat4<vectormath::simdf4>;
using Tfm3f4 = vectormath::Tfm3<vectormath::simdf4>;
union SIMDF4_FLOAT {
	vectormath::simdf4 v;
	float f[4];
};
#endif

#ifdef VECTORMATH_SIMDF8_DEFINED
using vectormath::make_simdf8;
using Vec3f8 = vectormath::Vec3<vectormath::simdf8>;
using Vec4f8 = vectormath::Vec4<vectormath::simdf8>;
using Pos3f8 = vectormath::Pos3<vectormath::simdf8>;
using Quatf8 = vectormath::Quat<vectormath::simdf8>;
using Mat3f8 = vectormath::Mat3<vectormath::simdf8>;
using Mat4f8 = vectormath::Mat4<vectormath::simdf8>;
using Tfm3f8 = vectormath::Tfm3<vectormath::simdf8>;
union SIMDF8_FLOAT {
	vectormath::simdf8 v;
	float f[8];
};
#endif

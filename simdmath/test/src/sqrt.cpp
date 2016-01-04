#include <simdmath/simdmath.h>
#include "common.h"
#include "catch.hpp"

#ifdef SIMDMATH_VEC_FLOAT4

TEST_CASE("vec_float4 sqrt", "[sqrtf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 2.0f, 4.0f, 0.25f);
  vec_float4 y = simdmath_sqrtf4(x);
  REQUIRE(get_comp<0>(y) == Approx(1.0f));
  REQUIRE(get_comp<1>(y) == Approx(1.41421f));
  REQUIRE(get_comp<2>(y) == Approx(2.0f));
  REQUIRE(get_comp<3>(y) == Approx(0.5f));
}

TEST_CASE("vec_float4 rsqrt", "[rsqrtf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 2.0f, 4.0f, 0.25f);
  vec_float4 y = simdmath_rsqrtf4(x);
  REQUIRE(get_comp<0>(y) == Approx(1.0f));
  REQUIRE(get_comp<1>(y) == Approx(0.70711f));
  REQUIRE(get_comp<2>(y) == Approx(0.5f));
  REQUIRE(get_comp<3>(y) == Approx(2.0f));
}

#endif

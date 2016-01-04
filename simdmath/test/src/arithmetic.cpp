#include <simdmath/simdmath.h>
#include "common.h"
#include "catch.hpp"

#ifdef SIMDMATH_VEC_FLOAT4

TEST_CASE("vec_float4 negate", "[negatef4]") {
  vec_float4 x = simdmath_setf4(1.0f, 0.5f, -2.5f, -3.0f);
  vec_float4 y = simdmath_negatef4(x);
  REQUIRE(get_comp<0>(y) == Approx(-1.0f));
  REQUIRE(get_comp<1>(y) == Approx(-0.5f));
  REQUIRE(get_comp<2>(y) == Approx(2.5f));
  REQUIRE(get_comp<3>(y) == Approx(3.0f));
}

TEST_CASE("vec_float4 div", "[divf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 0.5f, -2.5f, -3.0f);
  vec_float4 y = simdmath_setf4(2.0f, -2.0f, 5.0f, -1.0f);
  vec_float4 z = simdmath_divf4(x, y);
  REQUIRE(get_comp<0>(z) == Approx(0.5f));
  REQUIRE(get_comp<1>(z) == Approx(-0.25f));
  REQUIRE(get_comp<2>(z) == Approx(-0.5f));
  REQUIRE(get_comp<3>(z) == Approx(3.0f));
}

TEST_CASE("vec_float4 recip", "[recipf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 0.5f, -2.5f, -3.0f);
  vec_float4 y = simdmath_recipf4(x);
  REQUIRE(get_comp<0>(y) == Approx(1.0f));
  REQUIRE(get_comp<1>(y) == Approx(2.0f));
  REQUIRE(get_comp<2>(y) == Approx(-0.4f));
  REQUIRE(get_comp<3>(y) == Approx(-0.3333333333333f));
}

TEST_CASE("vec_float4 fabs", "[fabsf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 0.5f, -2.5f, -3.0f);
  vec_float4 y = simdmath_fabsf4(x);
  REQUIRE(get_comp<0>(y) == Approx(1.0f));
  REQUIRE(get_comp<1>(y) == Approx(0.5f));
  REQUIRE(get_comp<2>(y) == Approx(2.5f));
  REQUIRE(get_comp<3>(y) == Approx(3.0f));
}

TEST_CASE("vec_float4 fmod", "[fmodf4]") {
  vec_float4 x = simdmath_setf4(5.0f, 7.5f, -11.0f, 0.0f);
  vec_float4 y = simdmath_setf4(2.0f, 1.5f, 3.0f, 5.0f);
  vec_float4 z = simdmath_fmodf4(x, y);
  REQUIRE(get_comp<0>(z) == Approx(1.0f));
  REQUIRE(get_comp<1>(z) == Approx(0.0f));
  REQUIRE(get_comp<2>(z) == Approx(-2.0f));
  REQUIRE(get_comp<3>(z) == Approx(0.0f));
}

TEST_CASE("vec_float4 copysign", "[copysignf4]") {
  vec_float4 x = simdmath_setf4(1.0f, 0.5f, -2.5f, -3.0f);
  vec_float4 y = simdmath_setf4(2.0f, -2.0f, 5.0f, -1.0f);
  vec_float4 z = simdmath_copysignf4(x, y);
  REQUIRE(get_comp<0>(z) == Approx(1.0f));
  REQUIRE(get_comp<1>(z) == Approx(-0.5f));
  REQUIRE(get_comp<2>(z) == Approx(2.5f));
  REQUIRE(get_comp<3>(z) == Approx(-3.0f));
}

#endif

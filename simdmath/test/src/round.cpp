#include <simdmath/simdmath.h>
#include "common.h"
#include "catch.hpp"
#include <cmath>

static const float input_x[] = {
  -2.4f, -2.3f, -2.2f, -2.1f,
  -2.0f, -1.8f, -1.6f, -1.4f,
  -1.2f, -1.0f, -0.8f, -0.6f,
  -0.4f, -0.2f, 0.0f, 0.2f,
  0.4f, 0.6f, 0.8f, 1.0f,
  1.2f, 1.4f, 1.6f, 1.8f,
  2.0f, 2.1f, 2.2f, 2.3f,
  2.4f, 2.5f, 2.6f, 2.7f
};

static const float expected_floorx[] = {
  -3.0f, -3.0f, -3.0f, -3.0f,
  -2.0f, -2.0f, -2.0f, -2.0f,
  -2.0f, -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 1.0f, 1.0f,
  2.0f, 2.0f, 2.0f, 2.0f,
  2.0f, 2.0f, 2.0f, 2.0f
};

static const float expected_ceilx[] = {
  -2.0f, -2.0f, -2.0f, -2.0f,
  -2.0f, -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 1.0f, 1.0f,
  2.0f, 2.0f, 2.0f, 2.0f,
  2.0f, 3.0f, 3.0f, 3.0f,
  3.0f, 3.0f, 3.0f, 3.0f
};

static const float expected_truncx[] = {
  -2.0f, -2.0f, -2.0f, -2.0f,
  -2.0f, -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 1.0f, 1.0f,
  2.0f, 2.0f, 2.0f, 2.0f,
  2.0f, 2.0f, 2.0f, 2.0f
};

#ifdef SIMDMATH_VEC_FLOAT4

TEST_CASE("vec_float4 ceil", "[ceilf4]") {
  for (int i = 0; i < 32; i += 4) {
    vec_float4 x = simdmath_setf4(input_x[i], input_x[i+1], input_x[i+2], input_x[i+3]);
    vec_float4 y = simdmath_ceilf4(x);
    REQUIRE(get_comp<0>(y) == Approx(expected_ceilx[i+0]));
    REQUIRE(get_comp<1>(y) == Approx(expected_ceilx[i+1]));
    REQUIRE(get_comp<2>(y) == Approx(expected_ceilx[i+2]));
    REQUIRE(get_comp<3>(y) == Approx(expected_ceilx[i+3]));
  }
  {
    vec_float4 x = simdmath_setf4(-0.0f, 0.0f, NAN, INFINITY);
    vec_float4 y = simdmath_ceilf4(x);
    REQUIRE(get_comp<0>(y) == Approx(0.0f));
    REQUIRE(get_comp<1>(y) == Approx(0.0f));
    REQUIRE(std::isnan(get_comp<2>(y)));
    REQUIRE(std::isinf(get_comp<3>(y)));
  }
}

TEST_CASE("vec_float4 floor", "[floorf4]") {
  for (int i = 0; i < 32; i += 4) {
    vec_float4 x = simdmath_setf4(input_x[i], input_x[i+1], input_x[i+2], input_x[i+3]);
    vec_float4 y = simdmath_floorf4(x);
    REQUIRE(get_comp<0>(y) == Approx(expected_floorx[i+0]));
    REQUIRE(get_comp<1>(y) == Approx(expected_floorx[i+1]));
    REQUIRE(get_comp<2>(y) == Approx(expected_floorx[i+2]));
    REQUIRE(get_comp<3>(y) == Approx(expected_floorx[i+3]));
  }
  {
    vec_float4 x = simdmath_setf4(-0.0f, 0.0f, NAN, INFINITY);
    vec_float4 y = simdmath_floorf4(x);
    REQUIRE(get_comp<0>(y) == Approx(0.0f));
    REQUIRE(get_comp<1>(y) == Approx(0.0f));
    REQUIRE(std::isnan(get_comp<2>(y)));
    REQUIRE(std::isinf(get_comp<3>(y)));
  }
}

TEST_CASE("vec_float4 trunc", "[truncf4]") {
  for (int i = 0; i < 32; i += 4) {
    vec_float4 x = simdmath_setf4(input_x[i], input_x[i+1], input_x[i+2], input_x[i+3]);
    vec_float4 y = simdmath_truncf4(x);
    REQUIRE(get_comp<0>(y) == Approx(expected_truncx[i+0]));
    REQUIRE(get_comp<1>(y) == Approx(expected_truncx[i+1]));
    REQUIRE(get_comp<2>(y) == Approx(expected_truncx[i+2]));
    REQUIRE(get_comp<3>(y) == Approx(expected_truncx[i+3]));
  }
  {
    vec_float4 x = simdmath_setf4(-0.0f, 0.0f, NAN, INFINITY);
    vec_float4 y = simdmath_truncf4(x);
    REQUIRE(get_comp<0>(y) == Approx(0.0f));
    REQUIRE(get_comp<1>(y) == Approx(0.0f));
    REQUIRE(std::isnan(get_comp<2>(y)));
    REQUIRE(std::isinf(get_comp<3>(y)));
  }
}

#endif

#include <vectormath/core.h>
#include <vectormath/soa_ext.h>
#include <type_traits>
#include "catch.hpp"

using Vec4f4 = vectormath::Vec4<vectormath::simdf4>;
using PVec4f4 = const vectormath::Vec4<vectormath::simdf4>&;

TEST_CASE("vec4<simdf4>", "[vec3f4]") {
  REQUIRE(std::is_pod<Vec4f4>::value);

  SECTION("load") {
    float data[16] = {
      1.0f, 2.0f, 3.0f, 4.0f,
      5.0f, 6.0f, 7.0f, 8.0f,
      9.0f, 10.0f, 11.0f, 12.0f,
      13.0f, 14.0f, 15.0f, 16.0f
    };
    Vec4f4 v1 = Vec4f4::load(data);
    REQUIRE(v1.x[0] == 1.0f);
    REQUIRE(v1.x[1] == 5.0f);
    REQUIRE(v1.x[2] == 9.0f);
    REQUIRE(v1.x[3] == 13.0f);
    REQUIRE(v1.y[0] == 2.0f);
    REQUIRE(v1.y[1] == 6.0f);
    REQUIRE(v1.y[2] == 10.0f);
    REQUIRE(v1.y[3] == 14.0f);
    REQUIRE(v1.z[0] == 3.0f);
    REQUIRE(v1.z[1] == 7.0f);
    REQUIRE(v1.z[2] == 11.0f);
    REQUIRE(v1.z[3] == 15.0f);
    REQUIRE(v1.w[0] == 4.0f);
    REQUIRE(v1.w[1] == 8.0f);
    REQUIRE(v1.w[2] == 12.0f);
    REQUIRE(v1.w[3] == 16.0f);
  }

  SECTION("store") {
    Vec4f4 v1 = {
      {1.0f, 2.0f, 3.0f, 4.0f},
      {5.0f, 6.0f, 7.0f, 8.0f},
      {9.0f, 10.0f, 11.0f, 12.0f},
      {13.0f, 14.0f, 15.0f, 16.0f}
    };
    float data[16] = {0};
    store(data, v1);
    REQUIRE(data[0] == 1.0f);
    REQUIRE(data[1] == 5.0f);
    REQUIRE(data[2] == 9.0f);
    REQUIRE(data[3] == 13.0f);
    REQUIRE(data[4] == 2.0f);
    REQUIRE(data[5] == 6.0f);
    REQUIRE(data[6] == 10.0f);
    REQUIRE(data[7] == 14.0f);
    REQUIRE(data[8] == 3.0f);
    REQUIRE(data[9] == 7.0f);
    REQUIRE(data[10] == 11.0f);
    REQUIRE(data[11] == 15.0f);
    REQUIRE(data[12] == 4.0f);
    REQUIRE(data[13] == 8.0f);
    REQUIRE(data[14] == 12.0f);
    REQUIRE(data[15] == 16.0f);
  }
}

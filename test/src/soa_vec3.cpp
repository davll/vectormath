#include <vectormath/core.h>
#include <vectormath/soa_ext.h>
#include <type_traits>
#include "catch.hpp"

using Vec3f4 = vectormath::Vec3<vectormath::simdf4>;
using PVec3f4 = const vectormath::Vec3<vectormath::simdf4>&;

TEST_CASE("vec3<simdf4>", "[vec3f4]") {
  REQUIRE(std::is_pod<Vec3f4>::value);

  SECTION("load") {
    float data[12] = {
      1.0f, 2.0f, 3.0f,
      4.0f, 5.0f, 6.0f,
      7.0f, 8.0f, 9.0f,
      10.0f, 11.0f, 12.0f
    };
    Vec3f4 v1 = Vec3f4::load(data);
    REQUIRE(v1.x[0] == 1.0f);
    REQUIRE(v1.x[1] == 4.0f);
    REQUIRE(v1.x[2] == 7.0f);
    REQUIRE(v1.x[3] == 10.0f);
    REQUIRE(v1.y[0] == 2.0f);
    REQUIRE(v1.y[1] == 5.0f);
    REQUIRE(v1.y[2] == 8.0f);
    REQUIRE(v1.y[3] == 11.0f);
    REQUIRE(v1.z[0] == 3.0f);
    REQUIRE(v1.z[1] == 6.0f);
    REQUIRE(v1.z[2] == 9.0f);
    REQUIRE(v1.z[3] == 12.0f);
  }

  SECTION("store") {
    Vec3f4 v1 = {
      {1.0f, 2.0f, 3.0f, 4.0f},
      {5.0f, 6.0f, 7.0f, 8.0f},
      {9.0f, 10.0f, 11.0f, 12.0f}
    };
    float data[12] = {0};
    store(data, v1);
    REQUIRE(data[0] == 1.0f);
    REQUIRE(data[1] == 5.0f);
    REQUIRE(data[2] == 9.0f);
    REQUIRE(data[3] == 2.0f);
    REQUIRE(data[4] == 6.0f);
    REQUIRE(data[5] == 10.0f);
    REQUIRE(data[6] == 3.0f);
    REQUIRE(data[7] == 7.0f);
    REQUIRE(data[8] == 11.0f);
    REQUIRE(data[9] == 4.0f);
    REQUIRE(data[10] == 8.0f);
    REQUIRE(data[11] == 12.0f);
  }

  SECTION("arithmetic") {
    Vec3f4 v1 = {
      {1.0f, 2.0f, 3.0f, 4.0f},
      {5.0f, 6.0f, 7.0f, 8.0f},
      {9.0f, 10.0f, 11.0f, 12.0f}
    };
    Vec3f4 v2 = {
      {1.0f, -1.0f, 2.0f, -5.0f},
      {5.0f, 6.0f, 7.0f, 8.0f},
      {9.0f, 10.0f, 11.0f, 12.0f}
    };
    Vec3f4 v3 = v1 + v2;
    REQUIRE(v3.x[0] == 2.0f);
    // TODO
  }
}

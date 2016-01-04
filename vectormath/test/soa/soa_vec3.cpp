#include <type_traits>
#include "catch.hpp"
#include "common_soa.h"

TEST_CASE("vec3<simdf4>", "[vec3f4]") {
  REQUIRE(std::is_pod<Vec3f4>::value);
  REQUIRE((std::is_same<float, vectormath::simdf4>::value) == false);

  SECTION("load") {
	alignas(16) float data[12] = {
      1.0f, 2.0f, 3.0f,
      4.0f, 5.0f, 6.0f,
      7.0f, 8.0f, 9.0f,
      10.0f, 11.0f, 12.0f
    };
    Vec3f4 v1 = Vec3f4::load(data);
	SIMDF4_FLOAT x, y, z;
	x.v = v1.x;
	y.v = v1.y;
	z.v = v1.z;
    REQUIRE(x.f[0] == 1.0f);
    REQUIRE(x.f[1] == 4.0f);
    REQUIRE(x.f[2] == 7.0f);
    REQUIRE(x.f[3] == 10.0f);
    REQUIRE(y.f[0] == 2.0f);
    REQUIRE(y.f[1] == 5.0f);
    REQUIRE(y.f[2] == 8.0f);
    REQUIRE(y.f[3] == 11.0f);
    REQUIRE(z.f[0] == 3.0f);
    REQUIRE(z.f[1] == 6.0f);
    REQUIRE(z.f[2] == 9.0f);
    REQUIRE(z.f[3] == 12.0f);
  }

  SECTION("store") {
    Vec3f4 v1 = {
      make_simdf4(1.0f, 2.0f, 3.0f, 4.0f),
      make_simdf4(5.0f, 6.0f, 7.0f, 8.0f),
      make_simdf4(9.0f, 10.0f, 11.0f, 12.0f)
    };
	alignas(16) float data[12] = {0};
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

  /*
  SECTION("arithmetic") {
    Vec3f4 v1 = {
      make_simdf4(1.0f, 2.0f, 3.0f, 4.0f),
      make_simdf4(5.0f, 6.0f, 6.5f, 8.0f),
      make_simdf4(9.0f, 10.0f, 11.0f, 12.0f)
    };
    Vec3f4 v2 = {
      make_simdf4(1.0f, -1.0f, 2.0f, -5.0f),
      make_simdf4(-4.0f, 3.0f, -4.5f, -2.0f),
      make_simdf4(-9.0f, 10.0f, -1.0f, 0.0f)
    };
    Vec3f4 v3 = v1 + v2;
	SIMDF4_FLOAT x, y, z;
	x.v = v3.x;
	y.v = v3.y;
	z.v = v3.z;
    REQUIRE(x.f[0] == 2.0f);
    REQUIRE(x.f[1] == 1.0f);
    REQUIRE(x.f[2] == 5.0f);
    REQUIRE(x.f[3] == -1.0f);
    REQUIRE(y.f[0] == 1.0f);
    REQUIRE(y.f[1] == 9.0f);
    REQUIRE(y.f[2] == 2.0f);
    REQUIRE(y.f[3] == 6.0f);
    REQUIRE(z.f[0] == 0.0f);
    REQUIRE(z.f[1] == 20.0f);
    REQUIRE(z.f[2] == 10.0f);
    REQUIRE(z.f[3] == 12.0f);
  }
  */
}

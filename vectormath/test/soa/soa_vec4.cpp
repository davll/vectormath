#include <type_traits>
#include "catch.hpp"
#include "common_soa.h"

TEST_CASE("vec4<simdf4>", "[vec3f4]") {
  REQUIRE(std::is_pod<Vec4f4>::value);

  SECTION("load") {
	alignas(16) float data[16] = {
      1.0f, 2.0f, 3.0f, 4.0f,
      5.0f, 6.0f, 7.0f, 8.0f,
      9.0f, 10.0f, 11.0f, 12.0f,
      13.0f, 14.0f, 15.0f, 16.0f
    };
    Vec4f4 v1 = Vec4f4::load(data);
	SIMDF4_FLOAT x, y, z, w;
	x.v = v1.x;
	y.v = v1.y;
	z.v = v1.z;
	w.v = v1.w;
    REQUIRE(x.f[0] == 1.0f);
    REQUIRE(x.f[1] == 5.0f);
    REQUIRE(x.f[2] == 9.0f);
    REQUIRE(x.f[3] == 13.0f);
    REQUIRE(y.f[0] == 2.0f);
    REQUIRE(y.f[1] == 6.0f);
    REQUIRE(y.f[2] == 10.0f);
    REQUIRE(y.f[3] == 14.0f);
    REQUIRE(z.f[0] == 3.0f);
    REQUIRE(z.f[1] == 7.0f);
    REQUIRE(z.f[2] == 11.0f);
    REQUIRE(z.f[3] == 15.0f);
    REQUIRE(w.f[0] == 4.0f);
    REQUIRE(w.f[1] == 8.0f);
    REQUIRE(w.f[2] == 12.0f);
    REQUIRE(w.f[3] == 16.0f);
  }

  SECTION("store") {
    Vec4f4 v1 = {
      make_simdf4(1.0f, 2.0f, 3.0f, 4.0f),
      make_simdf4(5.0f, 6.0f, 7.0f, 8.0f),
      make_simdf4(9.0f, 10.0f, 11.0f, 12.0f),
      make_simdf4(13.0f, 14.0f, 15.0f, 16.0f)
    };
	alignas(16) float data[16] = {0};
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

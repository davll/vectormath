#include <type_traits>
#include "catch.hpp"
#include "common_soa.h"

TEST_CASE("pos3<simdf4>", "[pos3f4]") {
  REQUIRE(std::is_pod<Pos3f4>::value);

  SECTION("load") {
	alignas(16) float data[12] = {
      1.0f, 2.0f, 3.0f,
      4.0f, 5.0f, 6.0f,
      7.0f, 8.0f, 9.0f,
      10.0f, 11.0f, 12.0f
    };
    Pos3f4 v1 = Pos3f4::load(data);
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
    Pos3f4 v1 = {
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
}

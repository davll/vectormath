#include <type_traits>
#include "catch.hpp"
#include "common.h"

static NOINLINE Mat3f test_add(PMat3f a, PMat3f b);
static NOINLINE Mat3f test_mul1(PMat3f a, float s);
static NOINLINE Vec3f test_mul3(PMat3f a, PVec3f b);
static NOINLINE Mat3f test_mul4(PMat3f a, PMat3f b);
static NOINLINE Mat3f test_transpose(PMat3f a);
static NOINLINE Mat3f test_inv(PMat3f a);

TEST_CASE("mat3<float>", "[mat3f]") {
  REQUIRE(std::is_pod<Mat3f>::value);

  SECTION("addition") {
    Mat3f m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
    Mat3f m2 = { {9,8,7}, {6,5,4}, {3,2,1} };
    Mat3f m3 = test_add(m1, m2);
    REQUIRE(m3.c0.x == 10.0f);
    REQUIRE(m3.c0.y == 10.0f);
    REQUIRE(m3.c0.z == 10.0f);
    REQUIRE(m3.c1.x == 10.0f);
    REQUIRE(m3.c1.y == 10.0f);
    REQUIRE(m3.c1.z == 10.0f);
    REQUIRE(m3.c2.x == 10.0f);
    REQUIRE(m3.c2.y == 10.0f);
    REQUIRE(m3.c2.z == 10.0f);
  }

  SECTION("scaling") {
    Mat3f m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
    Mat3f m2 = test_mul1(m1, 0.5f);
    REQUIRE(m2.c0.x == 0.5f);
    REQUIRE(m2.c0.y == 1.0f);
    REQUIRE(m2.c0.z == 1.5f);
    REQUIRE(m2.c1.x == 2.0f);
    REQUIRE(m2.c1.y == 2.5f);
    REQUIRE(m2.c1.z == 3.0f);
    REQUIRE(m2.c2.x == 3.5f);
    REQUIRE(m2.c2.y == 4.0f);
    REQUIRE(m2.c2.z == 4.5f);
  }

  SECTION("transform vector") {
    Mat3f m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
    Vec3f v1 = { 1.0f, 2.0f, 3.0f };
    Vec3f v2 = test_mul3(m1, v1);
    REQUIRE(v2.x == 30.0f);
    REQUIRE(v2.y == 36.0f);
    REQUIRE(v2.z == 42.0f);
  }

  SECTION("matrix multiplication") {
    Mat3f m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
    Mat3f m2 = { {9,8,7}, {6,5,4}, {3,2,1} };
    Mat3f m3 = test_mul4(m1, m2);
    REQUIRE(m3.c0.x == 90.0f);
    REQUIRE(m3.c0.y == 114.0f);
    REQUIRE(m3.c0.z == 138.0f);
    REQUIRE(m3.c1.x == 54.0f);
    REQUIRE(m3.c1.y == 69.0f);
    REQUIRE(m3.c1.z == 84.0f);
    REQUIRE(m3.c2.x == 18.0f);
    REQUIRE(m3.c2.y == 24.0f);
    REQUIRE(m3.c2.z == 30.0f);
  }

  SECTION("matrix transposition") {
    Mat3f m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
    Mat3f m2 = test_transpose(m1);
    REQUIRE(m2.c0.x == 1.0f);
    REQUIRE(m2.c0.y == 4.0f);
    REQUIRE(m2.c0.z == 7.0f);
    REQUIRE(m2.c1.x == 2.0f);
    REQUIRE(m2.c1.y == 5.0f);
    REQUIRE(m2.c1.z == 8.0f);
    REQUIRE(m2.c2.x == 3.0f);
    REQUIRE(m2.c2.y == 6.0f);
    REQUIRE(m2.c2.z == 9.0f);
  }

  SECTION("matrix inversion") {
    Mat3f m1 = { {1,0,1}, {2,4,0}, {3,5,6} };
    Mat3f m2 = test_inv(m1);
    REQUIRE(m2.c0.x == Approx(12.0f / 11.0f));
    REQUIRE(m2.c0.y == Approx(5.0f / 22.0f));
    REQUIRE(m2.c0.z == Approx(-2.0f / 11.0f));
    REQUIRE(m2.c1.x == Approx(-6.0f / 11.0f));
    REQUIRE(m2.c1.y == Approx(3.0f / 22.0f));
    REQUIRE(m2.c1.z == Approx(1.0f / 11.0f));
    REQUIRE(m2.c2.x == Approx(-1.0f / 11.0f));
    REQUIRE(m2.c2.y == Approx(-5.0f / 22.0f));
    REQUIRE(m2.c2.z == Approx(2.0f / 11.0f));
  }

}

static Mat3f test_add(PMat3f a, PMat3f b)
{
  return a + b;
}

static Mat3f test_mul1(PMat3f a, float s)
{
  return a * s;
}

static Vec3f test_mul3(PMat3f a, PVec3f b)
{
  return a * b;
}

static Mat3f test_mul4(PMat3f a, PMat3f b)
{
  return a * b;
}

static Mat3f test_transpose(PMat3f a)
{
  return transpose(a);
}

static Mat3f test_inv(PMat3f a)
{
  return inverse(a);
}

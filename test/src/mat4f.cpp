#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"

using Vec4f = vectormath::Vec4<float>;
using PVec4f = const vectormath::Vec4<float>&;
using Mat4f = vectormath::Mat4<float>;
using PMat4f = const vectormath::Mat4<float>&;

static Mat4f test_add(PMat4f a, PMat4f b) __attribute__((noinline));
static Mat4f test_mul1(PMat4f a, float s) __attribute__((noinline));
static Vec4f test_mul3(PMat4f a, PVec4f b) __attribute__((noinline));
static Mat4f test_mul4(PMat4f a, PMat4f b) __attribute__((noinline));
static Mat4f test_transpose(PMat4f a) __attribute__((noinline));

TEST_CASE("mat4<float>", "[mat4f]") {
  REQUIRE(std::is_pod<Mat4f>::value);

  SECTION("addition") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Mat4f m2 = { {15,14,13,12}, {11,10,9,8}, {7,6,5,4}, {3,2,1,0} };
    Mat4f m3 = test_add(m1, m2);
    REQUIRE(m3.c0.x == 16.0f);
    REQUIRE(m3.c0.y == 16.0f);
    REQUIRE(m3.c0.z == 16.0f);
    REQUIRE(m3.c0.w == 16.0f);
    REQUIRE(m3.c1.x == 16.0f);
    REQUIRE(m3.c1.y == 16.0f);
    REQUIRE(m3.c1.z == 16.0f);
    REQUIRE(m3.c1.w == 16.0f);
    REQUIRE(m3.c2.x == 16.0f);
    REQUIRE(m3.c2.y == 16.0f);
    REQUIRE(m3.c2.z == 16.0f);
    REQUIRE(m3.c2.w == 16.0f);
    REQUIRE(m3.c3.x == 16.0f);
    REQUIRE(m3.c3.y == 16.0f);
    REQUIRE(m3.c3.z == 16.0f);
    REQUIRE(m3.c3.w == 16.0f);
  }

  SECTION("scaling") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Mat4f m2 = test_mul1(m1, 0.5f);
    REQUIRE(m2.c0.x == 0.5f);
    REQUIRE(m2.c0.y == 1.0f);
    REQUIRE(m2.c0.z == 1.5f);
    REQUIRE(m2.c0.w == 2.0f);
    REQUIRE(m2.c1.x == 2.5f);
    REQUIRE(m2.c1.y == 3.0f);
    REQUIRE(m2.c1.z == 3.5f);
    REQUIRE(m2.c1.w == 4.0f);
    REQUIRE(m2.c2.x == 4.5f);
    REQUIRE(m2.c2.y == 5.0f);
    REQUIRE(m2.c2.z == 5.5f);
    REQUIRE(m2.c2.w == 6.0f);
    REQUIRE(m2.c3.x == 6.5f);
    REQUIRE(m2.c3.y == 7.0f);
    REQUIRE(m2.c3.z == 7.5f);
    REQUIRE(m2.c3.w == 8.0f);
  }

  SECTION("transform vector") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Vec4f v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4f v2 = test_mul3(m1, v1);
    REQUIRE(v2.x == 90.0f);
    REQUIRE(v2.y == 100.0f);
    REQUIRE(v2.z == 110.0f);
    REQUIRE(v2.w == 120.0f);
  }

  SECTION("matrix multiplication") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Mat4f m2 = { {16,15,14,13}, {12,11,10,9}, {8,7,6,5}, {4,3,2,1} };
    Mat4f m3 = test_mul4(m1, m2);
    REQUIRE(m3.c0.x == 386.0f);
    REQUIRE(m3.c0.y == 444.0f);
    REQUIRE(m3.c0.z == 502.0f);
    REQUIRE(m3.c0.w == 560.0f);
    REQUIRE(m3.c1.x == 274.0f);
    REQUIRE(m3.c1.y == 316.0f);
    REQUIRE(m3.c1.z == 358.0f);
    REQUIRE(m3.c1.w == 400.0f);
    REQUIRE(m3.c2.x == 162.0f);
    REQUIRE(m3.c2.y == 188.0f);
    REQUIRE(m3.c2.z == 214.0f);
    REQUIRE(m3.c2.w == 240.0f);
    REQUIRE(m3.c3.x == 50.0f);
    REQUIRE(m3.c3.y == 60.0f);
    REQUIRE(m3.c3.z == 70.0f);
    REQUIRE(m3.c3.w == 80.0f);
  }

  SECTION("matrix transposition") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Mat4f m2 = test_transpose(m1);
    REQUIRE(m2.c0.x == 1.0f);
    REQUIRE(m2.c0.y == 5.0f);
    REQUIRE(m2.c0.z == 9.0f);
    REQUIRE(m2.c0.w == 13.0f);
    REQUIRE(m2.c1.x == 2.0f);
    REQUIRE(m2.c1.y == 6.0f);
    REQUIRE(m2.c1.z == 10.0f);
    REQUIRE(m2.c1.w == 14.0f);
    REQUIRE(m2.c2.x == 3.0f);
    REQUIRE(m2.c2.y == 7.0f);
    REQUIRE(m2.c2.z == 11.0f);
    REQUIRE(m2.c2.w == 15.0f);
    REQUIRE(m2.c3.x == 4.0f);
    REQUIRE(m2.c3.y == 8.0f);
    REQUIRE(m2.c3.z == 12.0f);
    REQUIRE(m2.c3.w == 16.0f);
  }

}

static Mat4f test_add(PMat4f a, PMat4f b)
{
  return a + b;
}

static Mat4f test_mul1(PMat4f a, float s)
{
  return a * s;
}

static Vec4f test_mul3(PMat4f a, PVec4f b)
{
  return a * b;
}

static Mat4f test_mul4(PMat4f a, PMat4f b)
{
  return a * b;
}

static Mat4f test_transpose(PMat4f a)
{
  return transpose(a);
}

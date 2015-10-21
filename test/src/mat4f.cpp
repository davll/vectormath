#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"

using Vec3f = vectormath::Vec3<float>;
using PVec3f = const vectormath::Vec3<float>&;
using Pos3f = vectormath::Pos3<float>;
using PPos3f = const vectormath::Pos3<float>&;
using Vec4f = vectormath::Vec4<float>;
using PVec4f = const vectormath::Vec4<float>&;
using Mat4f = vectormath::Mat4<float>;
using PMat4f = const vectormath::Mat4<float>&;

static Mat4f test_add(PMat4f a, PMat4f b) __attribute__((noinline));
static Mat4f test_mul1(PMat4f a, float s) __attribute__((noinline));
static Vec4f test_mul3(PMat4f a, PVec4f b) __attribute__((noinline));
static Mat4f test_mul4(PMat4f a, PMat4f b) __attribute__((noinline));
static Vec4f test_mul5(PMat4f a, PVec3f b) __attribute__((noinline));
static Vec4f test_mul6(PMat4f a, PPos3f b) __attribute__((noinline));
static Mat4f test_transpose(PMat4f a) __attribute__((noinline));
static Mat4f test_inv(PMat4f a) __attribute__((noinline));

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

  SECTION("transform vec4") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Vec4f v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4f v2 = test_mul3(m1, v1);
    REQUIRE(v2.x == 90.0f);
    REQUIRE(v2.y == 100.0f);
    REQUIRE(v2.z == 110.0f);
    REQUIRE(v2.w == 120.0f);
  }

  SECTION("transform vec3") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Vec3f v1 = { 1.0f, 2.0f, 3.0f };
    Vec4f v2 = test_mul5(m1, v1);
    REQUIRE(v2.x == 38.0f);
    REQUIRE(v2.y == 44.0f);
    REQUIRE(v2.z == 50.0f);
    REQUIRE(v2.w == 56.0f);
  }

  SECTION("transform pos3") {
    Mat4f m1 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    Pos3f v1 = { 10.0f, 20.0f, 30.0f };
    Vec4f v2 = test_mul6(m1, v1);
    REQUIRE(v2.x == 393.0f);
    REQUIRE(v2.y == 454.0f);
    REQUIRE(v2.z == 515.0f);
    REQUIRE(v2.w == 576.0f);
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

  SECTION("matrix inversion") {
    Mat4f m1 = { {2,10,0,5}, {1,-1,1,0}, {4,7,2,-1}, {5,4,3,3} };
    Mat4f m2 = test_inv(m1);
    REQUIRE(m2.c0.x == Approx(-34.0f / 32.0f));
    REQUIRE(m2.c0.y == Approx(-155.0f / 32.0f));
    REQUIRE(m2.c0.z == Approx(-5.0f / 32.0f));
    REQUIRE(m2.c0.w == Approx(55.0f / 32.0f));
    REQUIRE(m2.c1.x == Approx(8.0f / 32.0f));
    REQUIRE(m2.c1.y == Approx(28.0f / 32.0f));
    REQUIRE(m2.c1.z == Approx(4.0f / 32.0f));
    REQUIRE(m2.c1.w == Approx(-12.0f / 32.0f));
    REQUIRE(m2.c2.x == Approx(42.0f / 32.0f));
    REQUIRE(m2.c2.y == Approx(215.0f / 32.0f));
    REQUIRE(m2.c2.z == Approx(9.0f / 32.0f));
    REQUIRE(m2.c2.w == Approx(-67.0f / 32.0f));
    REQUIRE(m2.c3.x == Approx(4.0f / 32.0f));
    REQUIRE(m2.c3.y == Approx(6.0f / 32.0f));
    REQUIRE(m2.c3.z == Approx(-6.0f / 32.0f));
    REQUIRE(m2.c3.w == Approx(2.0f / 32.0f));
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

static Vec4f test_mul5(PMat4f a, PVec3f b)
{
  return a * b;
}

static Vec4f test_mul6(PMat4f a, PPos3f b)
{
  return a * b;
}

static Mat4f test_transpose(PMat4f a)
{
  return transpose(a);
}

static Mat4f test_inv(PMat4f a)
{
  return inverse(a);
}

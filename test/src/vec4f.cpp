#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"
#include "common.h"

static NOINLINE Vec4f test_neg(PVec4f a);
static NOINLINE Vec4f test_add(PVec4f a, PVec4f b);
static NOINLINE Vec4f test_sub(PVec4f a, PVec4f b);
static NOINLINE Vec4f test_mul1(PVec4f a, float s);
static NOINLINE Vec4f test_mul2(float s, PVec4f a);
static NOINLINE float test_dot(PVec4f a, PVec4f b);

TEST_CASE("vec4<float>", "[vec4f]") {
  REQUIRE(std::is_pod<Vec4f>::value);

  SECTION("negation") {
    Vec4f a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4f b = test_neg(a);
    REQUIRE(b.x == -1.0f);
    REQUIRE(b.y == -2.0f);
    REQUIRE(b.z == -3.0f);
    REQUIRE(b.w == -4.0f);
  }

  SECTION("addition") {
    Vec4f a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4f b = { 0.5f, -3.5f, 0.0f, -6.0f };
    Vec4f c = test_add(a, b);
    REQUIRE(c.x == 1.5f);
    REQUIRE(c.y == -1.5f);
    REQUIRE(c.z == 3.0f);
    REQUIRE(c.w == -2.0f);
  }

  SECTION("subtraction") {
    Vec4f a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4f b = { 0.5f, -3.5f, 0.0f, 5.0f };
    Vec4f c = test_sub(a, b);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == 5.5f);
    REQUIRE(c.z == 3.0f);
    REQUIRE(c.w == -1.0f);
  }

  SECTION("scaling") {
    Vec4f a = { 1.0f, -2.0f, 3.5f, -0.5f };
    Vec4f b = test_mul1(a, 2.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == -4.0f);
    REQUIRE(b.z == 7.0f);
    REQUIRE(b.w == -1.0f);

    Vec4f c = test_mul2(0.5f, a);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == -1.0f);
    REQUIRE(c.z == 1.75f);
    REQUIRE(c.w == -0.25f);
  }

  SECTION("dot product") {
    Vec4f a = { 1.0f, 0.5f, -1.5f, 100.0f };
    Vec4f b = { 2.0f, -2.0f, 1.0f, 0.0f };
    float x = test_dot(a, b);
    REQUIRE(x == -0.5f);
  }

}

static Vec4f test_neg(PVec4f a)
{
  return -a;
}

static Vec4f test_add(PVec4f a, PVec4f b)
{
  return a + b;
}

static Vec4f test_sub(PVec4f a, PVec4f b)
{
  return a - b;
}

static Vec4f test_mul1(PVec4f a, float s)
{
  return a * s;
}

static Vec4f test_mul2(float s, PVec4f a)
{
  return s * a;
}

static float test_dot(PVec4f a, PVec4f b)
{
  return dot(a, b);
}

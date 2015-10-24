#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"

using Vec3f = vectormath::Vec3<float>;
using PVec3f = const vectormath::Vec3<float>&;

static Vec3f test_neg(PVec3f a) __attribute__((noinline));
static Vec3f test_add(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_sub(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_mul1(PVec3f a, float s) __attribute__((noinline));
static Vec3f test_mul2(float s, PVec3f a) __attribute__((noinline));
static float test_dot(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_cross(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_min(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_max(PVec3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_abs(PVec3f a) __attribute__((noinline));
static float test_len(PVec3f a) __attribute__((noinline));
static float test_lensqr(PVec3f a) __attribute__((noinline));
static Vec3f test_normalize(PVec3f a) __attribute__((noinline));

TEST_CASE("vec3<float>", "[vec3f]") {
  REQUIRE(std::is_pod<Vec3f>::value);

  SECTION("negation") {
    Vec3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = test_neg(a);
    REQUIRE(b.x == -1.0f);
    REQUIRE(b.y == -2.0f);
    REQUIRE(b.z == -3.0f);
  }

  SECTION("addition") {
    Vec3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = { 0.5f, -3.5f, 0.0f };
    Vec3f c = test_add(a, b);
    REQUIRE(c.x == 1.5f);
    REQUIRE(c.y == -1.5f);
    REQUIRE(c.z == 3.0f);
  }

  SECTION("subtraction") {
    Vec3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = { 0.5f, -3.5f, 0.0f };
    Vec3f c = test_sub(a, b);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == 5.5f);
    REQUIRE(c.z == 3.0f);
  }

  SECTION("scaling") {
    Vec3f a = { 1.0f, -2.0f, 3.5f };
    Vec3f b = test_mul1(a, 2.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == -4.0f);
    REQUIRE(b.z == 7.0f);

    Vec3f c = test_mul2(0.5f, a);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == -1.0f);
    REQUIRE(c.z == 1.75f);
  }

  SECTION("dot product") {
    Vec3f a = { 1.0f, 0.5f, -1.5f };
    Vec3f b = { 2.0f, -2.0f, 1.0f };
    float x = test_dot(a, b);
    REQUIRE(x == -0.5f);
  }

  SECTION("cross product") {
    Vec3f a = { 1.0f, 1.0f, -1.0f };
    Vec3f b = { -1.0f, 1.0f, 1.0f };
    Vec3f c = test_cross(a, b);
    REQUIRE(c.x == 2.0f);
    REQUIRE(c.y == 0.0f);
    REQUIRE(c.z == 2.0f);
  }

  SECTION("min/max per element") {
    Vec3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = { 0.5f, 4.0f, -1.0f };
    Vec3f c = test_min(a, b);
    Vec3f d = test_max(a, b);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == 2.0f);
    REQUIRE(c.z == -1.0f);
    REQUIRE(d.x == 1.0f);
    REQUIRE(d.y == 4.0f);
    REQUIRE(d.z == 3.0f);
  }

  SECTION("abs") {
    Vec3f a = { 0.5f, 0.0f, -1.0f };
    Vec3f b = test_abs(a);
    REQUIRE(b.x == 0.5f);
    REQUIRE(b.y == 0.0f);
    REQUIRE(b.z == 1.0f);
  }

  SECTION("length") {
    Vec3f a = { 2.0f, 1.0f, -2.0f };
    REQUIRE(test_len(a) == Approx(3.0f));
  }

  SECTION("length squared") {
    Vec3f a = { 2.0f, 1.0f, -2.0f };
    REQUIRE(test_lensqr(a) == Approx(9.0f));
  }

  SECTION("normalize") {
    Vec3f a = { 2.0f, -1.0f, 2.0f };
    Vec3f b = test_normalize(a);
    REQUIRE(b.x == Approx(2.0f / 3.0f));
    REQUIRE(b.y == Approx(-1.0f / 3.0f));
    REQUIRE(b.z == Approx(2.0f / 3.0f));
  }

}

static Vec3f test_neg(PVec3f a)
{
  return -a;
}

static Vec3f test_add(PVec3f a, PVec3f b)
{
  return a + b;
}

static Vec3f test_sub(PVec3f a, PVec3f b)
{
  return a - b;
}

static Vec3f test_mul1(PVec3f a, float s)
{
  return a * s;
}

static Vec3f test_mul2(float s, PVec3f a)
{
  return s * a;
}

static float test_dot(PVec3f a, PVec3f b)
{
  return dot(a, b);
}

static Vec3f test_cross(PVec3f a, PVec3f b)
{
  return cross(a, b);
}

static Vec3f test_min(PVec3f a, PVec3f b)
{
  return min(a, b);
}

static Vec3f test_max(PVec3f a, PVec3f b)
{
  return max(a, b);
}

static Vec3f test_abs(PVec3f a)
{
  return abs(a);
}

static float test_len(PVec3f a)
{
  return length(a);
}

static float test_lensqr(PVec3f a)
{
  return length_squared(a);
}

static Vec3f test_normalize(PVec3f a)
{
  return normalize(a);
}

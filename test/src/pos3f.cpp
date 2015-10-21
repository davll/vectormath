#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"

using Vec3f = vectormath::Vec3<float>;
using Vec4f = vectormath::Vec4<float>;
using Pos3f = vectormath::Pos3<float>;
using PVec3f = const vectormath::Vec3<float>&;
using PPos3f = const vectormath::Pos3<float>&;

static Pos3f test_neg(PPos3f a) __attribute__((noinline));
static Pos3f test_add(PPos3f a, PVec3f b) __attribute__((noinline));
static Pos3f test_sub1(PPos3f a, PVec3f b) __attribute__((noinline));
static Vec3f test_sub2(PPos3f a, PPos3f b) __attribute__((noinline));
static Pos3f test_mul1(PPos3f a, float s) __attribute__((noinline));
static Pos3f test_mul2(float s, PPos3f a) __attribute__((noinline));

TEST_CASE("pos3<float>", "[pos3f]") {
  REQUIRE(std::is_pod<Pos3f>::value);

  SECTION("from/to vec3") {
    Pos3f a = Pos3f(Vec3f{ 1.0f, 2.0f, 3.0f });
    Vec3f b = Vec3f(Pos3f{ 4.0f, 5.0f, 6.0f });
    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
    REQUIRE(b.x == 4.0f);
    REQUIRE(b.y == 5.0f);
    REQUIRE(b.z == 6.0f);
  }

  SECTION("from/to vec4") {
    Vec4f a = Vec4f(Pos3f{ 10.0f, 20.0f, 30.0f });
    Pos3f b = Pos3f(Vec4f{ 4.0f, 5.0f, 6.0f, 2.0f });
    REQUIRE(a.x == 10.0f);
    REQUIRE(a.y == 20.0f);
    REQUIRE(a.z == 30.0f);
    REQUIRE(a.w == 1.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == 2.5f);
    REQUIRE(b.z == 3.0f);
  }

  SECTION("negation") {
    Pos3f a = { 1.0f, 2.0f, 3.0f };
    Pos3f b = test_neg(a);
    REQUIRE(b.x == -1.0f);
    REQUIRE(b.y == -2.0f);
    REQUIRE(b.z == -3.0f);
  }

  SECTION("addition/subtraction by vec3") {
    Pos3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = { 0.5f, -3.5f, 0.0f };
    Pos3f c = test_add(a, b);
    REQUIRE(c.x == 1.5f);
    REQUIRE(c.y == -1.5f);
    REQUIRE(c.z == 3.0f);
    c = test_sub1(a, b);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == 5.5f);
    REQUIRE(c.z == 3.0f);
  }

  SECTION("difference with other pos3") {
    Pos3f a = { 1.0f, 2.0f, 3.0f };
    Pos3f b = { 0.5f, -3.5f, 0.0f };
    Vec3f c = test_sub2(a, b);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == 5.5f);
    REQUIRE(c.z == 3.0f);
  }

  SECTION("scaling") {
    Pos3f a = { 1.0f, -2.0f, 3.5f };
    Pos3f b = test_mul1(a, 2.0f);
    REQUIRE(b.x == 2.0f);
    REQUIRE(b.y == -4.0f);
    REQUIRE(b.z == 7.0f);

    Pos3f c = test_mul2(0.5f, a);
    REQUIRE(c.x == 0.5f);
    REQUIRE(c.y == -1.0f);
    REQUIRE(c.z == 1.75f);
  }
}

static Pos3f test_neg(PPos3f a)
{
  return -a;
}

static Pos3f test_add(PPos3f a, PVec3f b)
{
  return a + b;
}

static Pos3f test_sub1(PPos3f a, PVec3f b)
{
  return a - b;
}

static Vec3f test_sub2(PPos3f a, PPos3f b)
{
  return a - b;
}

static Pos3f test_mul1(PPos3f a, float s)
{
  return a * s;
}

static Pos3f test_mul2(float s, PPos3f a)
{
  return s * a;
}

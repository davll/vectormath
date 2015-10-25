#include <vectormath/core.h>
#include <type_traits>
#include "catch.hpp"

using Vec3f = vectormath::Vec3<float>;
using PVec3f = const vectormath::Vec3<float>&;
using Pos3f = vectormath::Pos3<float>;
using PPos3f = const vectormath::Pos3<float>&;
using Mat3f = vectormath::Mat3<float>;
using Tfm3f = vectormath::Tfm3<float>;
using PTfm3f = const vectormath::Tfm3<float>&;

static Vec3f test_mul1(PTfm3f a, PVec3f b) __attribute__((noinline));
static Pos3f test_mul2(PTfm3f a, PPos3f b) __attribute__((noinline));
static Tfm3f test_mul3(PTfm3f a, PTfm3f b) __attribute__((noinline));
static Tfm3f test_inv(PTfm3f a) __attribute__((noinline));

TEST_CASE("tfm3<float>", "[tfm3f]") {
  REQUIRE(std::is_pod<Tfm3f>::value);

  SECTION("transform vec3") {
    Tfm3f m = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    Vec3f v = {1,2,3};
    Vec3f c = test_mul1(m, v);
    REQUIRE(c.x == 30.0f);
    REQUIRE(c.y == 36.0f);
    REQUIRE(c.z == 42.0f);
  }

  SECTION("transform pos3") {
    Tfm3f m = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    Pos3f v = {1,2,3};
    Pos3f c = test_mul2(m, v);
    REQUIRE(c.x == 40.0f);
    REQUIRE(c.y == 47.0f);
    REQUIRE(c.z == 54.0f);
  }

  SECTION("matrix composition") {
    Tfm3f m1 = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    Tfm3f m2 = {{-1,3,4}, {10,-5,1}, {3,0,7}, {0,1,4}};
    Tfm3f m3 = test_mul3(m1, m2);
    REQUIRE(m3.c0.x == 39.0f);
    REQUIRE(m3.c0.y == 45.0f);
    REQUIRE(m3.c0.z == 51.0f);
    REQUIRE(m3.c1.x == -3.0f);
    REQUIRE(m3.c1.y == 3.0f);
    REQUIRE(m3.c1.z == 9.0f);
    REQUIRE(m3.c2.x == 52.0f);
    REQUIRE(m3.c2.y == 62.0f);
    REQUIRE(m3.c2.z == 72.0f);
    REQUIRE(m3.c3.x == 42.0f);
    REQUIRE(m3.c3.y == 48.0f);
    REQUIRE(m3.c3.z == 54.0f);
  }

  SECTION("inversion") {
    Tfm3f a = {{1,2,3}, {40,5,6}, {7,9,9}, {10,11,12}};
    Tfm3f b = test_inv(a);
    REQUIRE(b.c0.x == Approx(-0.02727f));
    REQUIRE(b.c0.y == Approx( 0.02727f));
    REQUIRE(b.c0.z == Approx(-0.00909f));
    REQUIRE(b.c1.x == Approx(-0.96364f));
    REQUIRE(b.c1.y == Approx(-0.03636f));
    REQUIRE(b.c1.z == Approx( 0.34545f));
    REQUIRE(b.c2.x == Approx( 0.98485f));
    REQUIRE(b.c2.y == Approx( 0.01515f));
    REQUIRE(b.c2.z == Approx(-0.22727f));
    REQUIRE(b.c3.x == Approx(-0.94545f));
    REQUIRE(b.c3.y == Approx(-0.05455f));
    REQUIRE(b.c3.z == Approx(-0.98182f));
  }

  SECTION("make camera transformation") {
    Pos3f eye = { -1.0f, 0.0f, 1.0f };
    Mat3f rot = Mat3f::rotation(0.5235988f, Vec3f{ 0.0f, 1.0f, 0.0f });
    Pos3f target = eye + rot * Vec3f{0,0,-1} * 5.0f;
    Vec3f up = { 0.0f, 1.0f, 0.0f };
    Tfm3f m = Tfm3f::make_camera(eye, target, up);
    REQUIRE(m.c0.x == Approx(rot.c0.x));
    REQUIRE(m.c0.y == Approx(rot.c0.y));
    REQUIRE(m.c0.z == Approx(rot.c0.z));
    REQUIRE(m.c1.x == Approx(rot.c1.x));
    REQUIRE(m.c1.y == Approx(rot.c1.y));
    REQUIRE(m.c1.z == Approx(rot.c1.z));
    REQUIRE(m.c2.x == Approx(rot.c2.x));
    REQUIRE(m.c2.y == Approx(rot.c2.y));
    REQUIRE(m.c2.z == Approx(rot.c2.z));
    REQUIRE(m.c3.x == eye.x);
    REQUIRE(m.c3.y == eye.y);
    REQUIRE(m.c3.z == eye.z);
  }
}

static Vec3f test_mul1(PTfm3f a, PVec3f b)
{
  return a * b;
}

static Pos3f test_mul2(PTfm3f a, PPos3f b)
{
  return a * b;
}

static Tfm3f test_mul3(PTfm3f a, PTfm3f b)
{
  return a * b;
}

static Tfm3f test_inv(PTfm3f a)
{
  return inverse(a);
}

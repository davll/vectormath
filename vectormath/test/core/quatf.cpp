#include <type_traits>
#include "catch.hpp"
#include "common.h"

static NOINLINE Quatf test_neg(PQuatf a);
static NOINLINE Quatf test_conj(PQuatf a);
static NOINLINE Quatf test_add(PQuatf a, PQuatf b);
static NOINLINE Quatf test_sub(PQuatf a, PQuatf b);
static NOINLINE Quatf test_mul1(PQuatf a, float s);
static NOINLINE Quatf test_mul2(float s, PQuatf a);
static NOINLINE Quatf test_mul3(PQuatf a, PQuatf b);
static NOINLINE float test_dot(PQuatf a, PQuatf b);
static NOINLINE Quatf test_normalize(PQuatf a);
static NOINLINE Vec3f test_tfm(PQuatf q, PVec3f v);
//static Mat3f test_cvtmat(PQuatf q);

TEST_CASE("quat<float>", "[quatf]") {
  REQUIRE(std::is_pod<Quatf>::value);

  SECTION("negation") {
    Quatf a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Quatf b = test_neg(a);
    REQUIRE(b.w == -1.0f);
    REQUIRE(b.x == -2.0f);
    REQUIRE(b.y == -3.0f);
    REQUIRE(b.z == -4.0f);
  }

  SECTION("conjugate") {
    Quatf a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Quatf b = test_conj(a);
    REQUIRE(b.w == 1.0f);
    REQUIRE(b.x == -2.0f);
    REQUIRE(b.y == -3.0f);
    REQUIRE(b.z == -4.0f);
  }

  SECTION("addition") {
    Quatf a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Quatf b = { 0.5f, -3.5f, 0.0f, -6.0f };
    Quatf c = test_add(a, b);
    REQUIRE(c.w == 1.5f);
    REQUIRE(c.x == -1.5f);
    REQUIRE(c.y == 3.0f);
    REQUIRE(c.z == -2.0f);
  }

  SECTION("subtraction") {
    Quatf a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Quatf b = { 0.5f, -3.5f, 0.0f, 5.0f };
    Quatf c = test_sub(a, b);
    REQUIRE(c.w == 0.5f);
    REQUIRE(c.x == 5.5f);
    REQUIRE(c.y == 3.0f);
    REQUIRE(c.z == -1.0f);
  }

  SECTION("scaling") {
    Quatf a = { 1.0f, -2.0f, 3.5f, -0.5f };
    Quatf b = test_mul1(a, 2.0f);
    REQUIRE(b.w == 2.0f);
    REQUIRE(b.x == -4.0f);
    REQUIRE(b.y == 7.0f);
    REQUIRE(b.z == -1.0f);

    Quatf c = test_mul2(0.5f, a);
    REQUIRE(c.w == 0.5f);
    REQUIRE(c.x == -1.0f);
    REQUIRE(c.y == 1.75f);
    REQUIRE(c.z == -0.25f);
  }

  SECTION("quaternion multiplication") {
    Quatf a = { 1.0f, 0.0f, 1.0f, 0.0f };
    Quatf b = { 1.0f, 0.5f, 0.5f, 0.75f };
    Quatf c = test_mul3(a, b);
    REQUIRE(c.w == 0.50f);
    REQUIRE(c.x == 1.25f);
    REQUIRE(c.y == 1.50f);
    REQUIRE(c.z == 0.25f);
  }

  SECTION("dot product") {
    Quatf a = { 1.0f, 0.5f, -1.5f, 100.0f };
    Quatf b = { 2.0f, -2.0f, 1.0f, 0.0f };
    float x = test_dot(a, b);
    REQUIRE(x == -0.5f);
  }

  SECTION("normalize") {
    Quatf a = { -1.0f, 1.0f, -1.0f, 1.0f };
    Quatf b = test_normalize(a);
    REQUIRE(b.w == Approx(-0.5f));
    REQUIRE(b.x == Approx(0.5f));
    REQUIRE(b.y == Approx(-0.5f));
    REQUIRE(b.z == Approx(0.5f));
  }

  SECTION("transform vector") {
    float c45 = 0.7071067811865476f;
    Quatf q = { c45, 0.0f, 0.0f, c45 };
    Vec3f v1 = { 1.0f, 2.0f, 3.0f };
    Vec3f v2 = test_tfm(q, v1);
    REQUIRE(v2.x == Approx(-2.0f));
    REQUIRE(v2.y == Approx(1.0f));
    REQUIRE(v2.z == Approx(3.0f));
  }

  SECTION("convert to/from 3x3 matrix") {
    float pi = 3.141592653589793f;
    Quatf q = Quatf::rotation(pi / 3.0f, Vec3f{0.0f, 0.0f, 1.0f});
    Mat3f m = Mat3f::rotation(q);
    REQUIRE(m.c0.x == Approx(0.5f));
    REQUIRE(m.c0.y == Approx(0.8660254037844386f));
    REQUIRE(m.c0.z == Approx(0.0f));
    REQUIRE(m.c1.x == Approx(-0.8660254037844386f));
    REQUIRE(m.c1.y == Approx(0.5f));
    REQUIRE(m.c1.z == Approx(0.0f));
    REQUIRE(m.c2.x == Approx(0.0f));
    REQUIRE(m.c2.y == Approx(0.0f));
    REQUIRE(m.c2.z == Approx(1.0f));
    Quatf q2 = Quatf::rotation(m);
    REQUIRE(q2.w == Approx(q.w));
    REQUIRE(q2.x == Approx(q.x));
    REQUIRE(q2.y == Approx(q.y));
    REQUIRE(q2.z == Approx(q.z));
  }
}

static Quatf test_neg(PQuatf a)
{
  return -a;
}

static Quatf test_conj(PQuatf a)
{
  return ~a;
}

static Quatf test_add(PQuatf a, PQuatf b)
{
  return a + b;
}

static Quatf test_sub(PQuatf a, PQuatf b)
{
  return a - b;
}

static Quatf test_mul1(PQuatf a, float s)
{
  return a * s;
}

static Quatf test_mul2(float s, PQuatf a)
{
  return s * a;
}

static Quatf test_mul3(PQuatf a, PQuatf b)
{
  return a * b;
}

static float test_dot(PQuatf a, PQuatf b)
{
  return dot(a, b);
}

static Quatf test_normalize(PQuatf a)
{
  return normalize(a);
}

static Vec3f test_tfm(PQuatf q, PVec3f v)
{
  return transform(q, v);
}

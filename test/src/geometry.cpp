#include <vectormath/core.h>
#include <vectormath/geometry.h>
#include "catch.hpp"
#include "common.h"

using Planef = vectormath::Plane<float>;
using BBoxf = vectormath::BoundingBox<float>;
using Spheref = vectormath::Sphere<float>;
using Frustumf = vectormath::Frustum<float>;

TEST_CASE("Plane<float>", "planef") {
  Planef plane = Planef{ Vec3f(1.0f, 2.0f, 3.0f), -6.0f };
  Pos3f x = {1.0f, 1.0f, 1.0f};
  REQUIRE(plane[x] == 0.0f);
  x = {0.0f, 0.0f, 2.0f};
  REQUIRE(plane[x] == 0.0f);
  x = {0.0f, 3.0f, 0.0f};
  REQUIRE(plane[x] == 0.0f);
}

TEST_CASE("BoundingBox<float>", "boundingboxf") {
  BBoxf box = BBoxf{ Pos3f{1.0f, -3.0f, 4.0f}, Pos3f{0.0f, 2.0f, 0.5f} };
  REQUIRE(box.minpos.x == 0.0f);
  REQUIRE(box.minpos.y == -3.0f);
  REQUIRE(box.minpos.z == 0.5f);
  REQUIRE(box.maxpos.x == 1.0f);
  REQUIRE(box.maxpos.y == 2.0f);
  REQUIRE(box.maxpos.z == 4.0f);
  box.add(Pos3f{ 2.0f, 0.5f, -1.0f });
  REQUIRE(box.minpos.x == 0.0f);
  REQUIRE(box.minpos.y == -3.0f);
  REQUIRE(box.minpos.z == -1.0f);
  REQUIRE(box.maxpos.x == 2.0f);
  REQUIRE(box.maxpos.y == 2.0f);
  REQUIRE(box.maxpos.z == 4.0f);
}

TEST_CASE("Sphere<float>", "spheref") {
  Spheref sphere = Spheref{ Pos3f{0.0f, -1.0f, 1.0f}, 9.0f };
  float d2 = sphere[Pos3f{ 1.0f, 2.0f, 3.0f }];
  REQUIRE(d2 == 5.0f);
  d2 = sphere[Pos3f{ 0.0f, 0.0f, 0.0f }];
  REQUIRE(d2 == -7.0f);
  d2 = sphere[Pos3f{ 3.0f, -1.0f, 1.0f }];
  REQUIRE(d2 == 0.0f);
}

TEST_CASE("Frustum<float>", "frustumf") {
  Mat4f m = {
    {1,0,0,0}, {0,1,0,0}, {0,0,-1,0}, {0,0,0,1}
  }; // glOrtho(-1, 1, -1, 1, -1, 1)
  Frustumf fru = Frustumf{ m };
  REQUIRE(fru.left.equation.x == 1.0f);
  REQUIRE(fru.left.equation.y == 0.0f);
  REQUIRE(fru.left.equation.z == 0.0f);
  REQUIRE(fru.left.equation.w == 1.0f);
  REQUIRE(fru.right.equation.x == -1.0f);
  REQUIRE(fru.right.equation.y == 0.0f);
  REQUIRE(fru.right.equation.z == 0.0f);
  REQUIRE(fru.right.equation.w == 1.0f);
  REQUIRE(fru.bottom.equation.x == 0.0f);
  REQUIRE(fru.bottom.equation.y == 1.0f);
  REQUIRE(fru.bottom.equation.z == 0.0f);
  REQUIRE(fru.bottom.equation.w == 1.0f);
  REQUIRE(fru.top.equation.x == 0.0f);
  REQUIRE(fru.top.equation.y == -1.0f);
  REQUIRE(fru.top.equation.z == 0.0f);
  REQUIRE(fru.top.equation.w == 1.0f);
  REQUIRE(fru.near.equation.x == 0.0f);
  REQUIRE(fru.near.equation.y == 0.0f);
  REQUIRE(fru.near.equation.z == -1.0f);
  REQUIRE(fru.near.equation.w == 1.0f);
  REQUIRE(fru.far.equation.x == 0.0f);
  REQUIRE(fru.far.equation.y == 0.0f);
  REQUIRE(fru.far.equation.z == 1.0f);
  REQUIRE(fru.far.equation.w == 1.0f);
}

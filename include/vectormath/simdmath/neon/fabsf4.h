#pragma once

#include <arm_neon.h>

static inline float32x4_t
_fabsf4(float32x4_t x)
{
  return vabsq_f32(x);
}

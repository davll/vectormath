#pragma once

#ifdef __SSE__
#  include "sse/fabsf4.h"
#endif

#ifdef __ARM_NEON
#  include "neon/fabsf4.h"
#endif

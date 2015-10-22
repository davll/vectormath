#pragma once

#include "_vec_utils.h"
#include "fabsf4.h"

static inline __m128
_floorf4 (__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x1 );

#else /* SSE2 */

  const __m128 xa = _fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);

  const __m128i xi = _mm_cvttps_epi32(x);
  const __m128i xi1 = _mm_sub_epi32(xi, _mm_set1_epi32(1));

  const __m128 truncated0 = _selectf4(x, _mm_cvtepi32_ps(xi), inrange);
  const __m128 truncated1 = _selectf4(x, _mm_cvtepi32_ps(xi1), inrange);

  /* If truncated value is greater than input, subtract one. */

  return _selectf4(truncated0, truncated1, _mm_cmpgt_ps(truncated0, x));

#endif
}

/*
 .const
 .align 4
 mone:	.long	0xbf800000
 absmask:.long	0x7fffffff

 .text
 .align 4
 .globl _floorf
 _floorf:
 movd		%xmm0,			%ecx
 andl		$0x7fffffff,	%ecx	// |x|
 subl		$1,				%ecx	// subtract 1. This forces |+-0| to -0
 cmpl		$0x4afffffe,	%ecx	// values >= 0x4b000000 - 1 are either integers, NaN or Inf
 ja			1f						// unsigned compare adds 0 to the list

 cvttps2dq   %xmm0,			%xmm2
 cvtdq2ps    %xmm2,			%xmm2
 cmpltss		%xmm2,			%xmm0
 andps		mone(%rip),		%xmm0
 addss		%xmm2,			%xmm0
 1:	ret

 // fast path using SSE 4.1
 roundss		$0x1,	%xmm0,	%xmm0
 movss		%xmm0,		  4(%esp)
 flds	  4(%esp)
 ret

 */

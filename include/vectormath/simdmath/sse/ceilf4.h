#pragma once

#include "_vec_utils.h"
#include "fabsf4.h"

static inline __m128
_ceilf4 (__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x2 );

#else /* SSE2 */

  const __m128 xa = _fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);

  const __m128i xi = _mm_cvttps_epi32(x);
  const __m128i xi1 = _mm_add_epi32(xi, _mm_set1_epi32(1));

  const __m128 truncated0 = _selectf4(x, _mm_cvtepi32_ps(xi), inrange);
  const __m128 truncated1 = _selectf4(x, _mm_cvtepi32_ps(xi1), inrange);

  /* If truncated value is greater than input, subtract one. */

  return _selectf4(truncated0, truncated1, _mm_cmpgt_ps(x, truncated0));

#endif
}

/*
 .const
 .align 4
 one:	.long	0x3f800000
 absmask:.long	0x7fffffff

 .text
 .align 4
 .globl _ceilf
 _ceilf:
 movd		%xmm0,			%eax
 andl		absmask(%rip),	%eax
 movd		absmask(%rip),	%xmm1
 cmpl		$0x4b000000,	%eax
 andnps		%xmm0,			%xmm1
 jae			1f

 cvttps2dq	%xmm0,			%xmm2
 movdqa		%xmm0,			%xmm3
 psrad		$31,			%xmm0	// (x < 0) ? -1 : 0
 cvtdq2ps	%xmm2,			%xmm2
 pcmpgtd		%xmm2,			%xmm3	// (x >i trunc(x)) ? -1 : 0
 andnps		%xmm3,			%xmm0	// (x > trunc(x)) ? -1 : 0
 andps		one(%rip),		%xmm0	// (x > trunc(x)) ? 1.0 : 0.0
 addss		%xmm2,			%xmm0	// (x > trunc(x)) ? trunc(x) + 1.0 : trunc(x)
 orps		%xmm1,			%xmm0	// ceil(x)
 1:	ret

 // fast path using SSE 4.1
 roundss		$0x2,	%xmm0,	%xmm0
 movss		%xmm0,		  4(%esp)
 flds	  4(%esp)
 ret

 */

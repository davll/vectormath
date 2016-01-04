/*
The source file is part of simdmath

Copyright (c) 2015 David Lin <davll.xc@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once

#include "_sincos.h"

SIMDMATH_INLINE __m128 simdmath_sse_selectf4(__m128 x, __m128 y, __m128 s)
{
  return _mm_or_ps(_mm_andnot_ps(s, x), _mm_and_ps(s, y));
}

SIMDMATH_INLINE __m128 simdmath_sse_blendf4(__m128 x, __m128 y, __m128 s)
{
#ifdef __SSE4_1__
  return _mm_blendv_ps(x, y, s);
#else
  return _mm_or_ps(_mm_andnot_ps(s, x), _mm_and_ps(s, y));
#endif
}

SIMDMATH_INLINE __m128 simdmath_acosf4(__m128 x)
{
  __m128 xabs = simdmath_fabsf4( x );
  __m128 select = _mm_cmplt_ps( x, _mm_setzero_ps() );
  __m128 t1 = _mm_sqrt_ps( _mm_sub_ps(_mm_set1_ps(1.0f), xabs) );

  /* Instruction counts can be reduced if the polynomial was
   * computed entirely from nested (dependent) fma's. However,
   * to reduce the number of pipeline stalls, the polygon is evaluated
   * in two halves (hi amd lo).
   */
  __m128 xabs2 = _mm_mul_ps(xabs,  xabs);
  __m128 xabs4 = _mm_mul_ps(xabs2, xabs2);
  __m128 hi, lo;

  hi = _mm_set1_ps(-0.0012624911f);
  hi = _mm_add_ps(_mm_mul_ps(hi, xabs), _mm_set1_ps( 0.0066700901f));
  hi = _mm_add_ps(_mm_mul_ps(hi, xabs), _mm_set1_ps(-0.0170881256f));
  hi = _mm_add_ps(_mm_mul_ps(hi, xabs), _mm_set1_ps( 0.0308918810f));

  lo = _mm_set1_ps(-0.0501743046f);
  lo = _mm_add_ps(_mm_mul_ps(lo, xabs), _mm_set1_ps( 0.0889789874f));
  lo = _mm_add_ps(_mm_mul_ps(lo, xabs), _mm_set1_ps(-0.2145988016f));
  lo = _mm_add_ps(_mm_mul_ps(lo, xabs), _mm_set1_ps( 1.5707963050f));

  __m128 result = _mm_add_ps(_mm_mul_ps(hi, xabs4), lo);

  // Adjust the result if x is negactive.

  __m128 pos = _mm_mul_ps(t1, result);
  __m128 neg = _mm_sub_ps(_mm_set1_ps(3.1415926535898f), _mm_mul_ps(t1, result));

  return simdmath_sse_blendf4(pos, neg, select);
}

SIMDMATH_INLINE __m128 simdmath_blendf4(__m128 x, __m128 y, __m128i s)
{
  return simdmath_sse_blendf4(x, y, _mm_castsi128_ps(s));
}

SIMDMATH_INLINE __m128 simdmath_ceilf4(__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x2 );

#else /* SSE2 */

  const __m128 xa = simdmath_fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);
  const __m128i xi = _mm_cvttps_epi32(x);
  const __m128i xi1 = _mm_add_epi32(xi, _mm_set1_epi32(1));
  const __m128 truncated0 = simdmath_sse_blendf4(x, _mm_cvtepi32_ps(xi), inrange);
  const __m128 truncated1 = simdmath_sse_blendf4(x, _mm_cvtepi32_ps(xi1), inrange);
  /* If truncated value is greater than input, subtract one. */
  return simdmath_sse_blendf4(truncated0, truncated1, _mm_cmpgt_ps(x, truncated0));

#endif
}

SIMDMATH_INLINE __m128 simdmath_copysignf4(__m128 x, __m128 y)
{
  __m128 mask = _mm_castsi128_ps( _mm_set1_epi32(0x80000000) );
  return _mm_or_ps( _mm_andnot_ps(mask, x), _mm_and_ps(mask, y) );
}

SIMDMATH_INLINE __m128 simdmath_divf4(__m128 x, __m128 y)
{
  return _mm_div_ps(x, y);
}

SIMDMATH_INLINE __m128 simdmath_fabsf4(__m128 x)
{
  return _mm_andnot_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), x);
}

SIMDMATH_INLINE __m128 simdmath_fdimf4(__m128 x, __m128 y)
{
  __m128 diff = _mm_sub_ps(x, y);
  __m128 res = _mm_max_ps(_mm_setzero_ps(), diff);
  return simdmath_sse_blendf4(diff, res, _mm_cmpeq_ps(diff, diff));
}

SIMDMATH_INLINE __m128 simdmath_floorf4(__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x1 );

#else /* SSE2 */

  const __m128 xa = simdmath_fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);
  const __m128i xi = _mm_cvttps_epi32(x);
  const __m128i xi1 = _mm_sub_epi32(xi, _mm_set1_epi32(1));
  const __m128 truncated0 = simdmath_sse_blendf4(x, _mm_cvtepi32_ps(xi), inrange);
  const __m128 truncated1 = simdmath_sse_blendf4(x, _mm_cvtepi32_ps(xi1), inrange);
  /* If truncated value is greater than input, subtract one. */
  return simdmath_sse_blendf4(truncated0, truncated1, _mm_cmpgt_ps(truncated0, x));

#endif
}

SIMDMATH_INLINE __m128 simdmath_fmaf4(__m128 x, __m128 y, __m128 z)
{
#ifdef __FMA__
  return _mm_fmadd_ps(x, y, z);
#else
  return _mm_add_ps(_mm_mul_ps(x, y), z);
#endif
}

SIMDMATH_INLINE __m128 simdmath_fmaxf4(__m128 x, __m128 y)
{
  return _mm_max_ps( x, y );
}

SIMDMATH_INLINE __m128 simdmath_fminf4(__m128 x, __m128 y)
{
  return _mm_min_ps( x, y );
}

SIMDMATH_INLINE __m128 simdmath_fmodf4(__m128 x, __m128 y)
{
  // Find i = truncated_integer(|x/y|)
	//   If |divf4(x,y)| < 2^20, the quotient is at most off by 1.0.
	//   Thus i is either the truncated quotient, one less, or one greater.
  __m128 q = _mm_div_ps( x, y );
	__m128 xabs = simdmath_fabsf4( x );
	__m128 yabs = simdmath_fabsf4( y );
	__m128 qabs = simdmath_fabsf4( q );
	__m128 xabs2 = _mm_add_ps( xabs, xabs );
	__m128 infx = _mm_castsi128_ps(_mm_cmpeq_epi32( _mm_castps_si128(xabs), _mm_set1_epi32(0x7F800000) ));
	__m128 zerox = _mm_cmpeq_ps( x, _mm_setzero_ps() );
	__m128 zeroy = _mm_cmpeq_ps( y, _mm_setzero_ps() );
	__m128 nanx = _mm_cmpeq_ps( x, x );
	__m128 nany = _mm_cmpeq_ps( y, y );

  __m128 inrange = _mm_cmpgt_ps( _mm_castsi128_ps(_mm_set1_epi32(0x49800000)), qabs );
  inrange = _mm_and_ps( inrange, _mm_cmpgt_ps( _mm_castsi128_ps(_mm_set1_epi32(0x7f800000)), xabs ));

  __m128i qi1 = _mm_cvttps_epi32(qabs);
  __m128i qi0 = _mm_sub_epi32(qi1, _mm_set1_epi32(1));
  __m128i qi2 = _mm_add_epi32(qi1, _mm_set1_epi32(1));

  __m128 i0 = _mm_cvtepi32_ps(qi0);
  __m128 i1 = _mm_cvtepi32_ps(qi1);
  __m128 i2 = _mm_cvtepi32_ps(qi2);

  // Correct i will be the largest one such that |x| - i*|y| >= 0.  Can test instead as
	// 2*|x| - i*|y| >= |x|:
	//
	// With exact inputs, the negative-multiply-subtract gives the exact result rounded towards zero.
	// Thus |x| - i*|y| may be < 0 but still round to zero.  However, if 2*|x| - i*|y| < |x|, the computed
	// answer will be rounded down to < |x|.  2*|x| can be represented exactly provided |x| < 2^128.
  //
  __m128 r1 = _mm_sub_ps( xabs2, _mm_mul_ps(i1, yabs) );
	__m128 r2 = _mm_sub_ps( xabs2, _mm_mul_ps(i2, yabs) );

	__m128 i = i0;
	i = simdmath_sse_blendf4( i1, i, _mm_cmpgt_ps( xabs, r1 ) );
	i = simdmath_sse_blendf4( i2, i, _mm_cmpgt_ps( xabs, r2 ) );

	i = simdmath_copysignf4( i, q );
	i = _mm_and_ps( _mm_sub_ps( x, _mm_mul_ps(i, y) ), inrange );
	i = simdmath_sse_blendf4( i, x, zerox );
	i = _mm_or_ps( i, _mm_or_ps( infx, zeroy ) );
	i = simdmath_sse_blendf4( x, i, nanx );
	i = simdmath_sse_blendf4( y, i, nany );
	return i;
}

SIMDMATH_INLINE __m128 simdmath_negatef4(__m128 x)
{
  return _mm_xor_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), x);
}

SIMDMATH_INLINE __m128 simdmath_recipf4(__m128 x)
{
  // Reciprocal estimate and 1 Newton-Raphson iteration.
  // A constant of 1.0 + 1 ulp in the Newton-Raphson step results in exact
  // answers for powers of 2, and a slightly smaller relative error bound.
  const __m128 oneish = _mm_castsi128_ps(_mm_set1_epi32(0x3f800001));
  __m128 y0 = _mm_rcp_ps(x);
  __m128 tmp = _mm_sub_ps(oneish, _mm_mul_ps(x, y0));
  return _mm_add_ps(_mm_mul_ps(tmp, y0), y0);
}

SIMDMATH_INLINE __m128 simdmath_rsqrtf4(__m128 x)
{
  // Newton-Raphson method
  const __m128 half = _mm_set1_ps(0.5f);
  const __m128 three = _mm_set1_ps(3.0f);
  __m128 approx = _mm_rsqrt_ps(x);
  __m128 muls = _mm_mul_ps(_mm_mul_ps(x, approx), approx);
  return _mm_mul_ps(_mm_mul_ps(half, approx), _mm_sub_ps(three, muls));
}

SIMDMATH_INLINE __m128 simdmath_setf4(float a0, float a1, float a2, float a3)
{
  return _mm_setr_ps(a0, a1, a2, a3);
}

SIMDMATH_INLINE void simdmath_sincosf4(__m128 x, __m128* SIMDMATH_RESTRICT s, __m128* SIMDMATH_RESTRICT c)
{
  __m128 xl, xl2, xl3, ts, tc;
  __m128i q, offsetSin, offsetCos;

  // Range reduction using : xl = angle * TwoOverPi;
  //
  xl = _mm_mul_ps(x, _mm_set1_ps(0.63661977236f));

  // Find the quadrant the angle falls in
  // using:  q = (int) (ceil(abs(xl))*sign(xl))
  //
  xl = _mm_add_ps(xl, simdmath_copysignf4(_mm_set1_ps(0.5f), xl));
  q = _mm_cvttps_epi32(xl);

  // Compute the offset based on the quadrant that the angle falls in.
  // Add 1 to the offset for the cosine.
  //
  offsetSin = _mm_and_si128(q, _mm_set1_epi32(0x3));
  offsetCos = _mm_add_epi32(offsetSin, _mm_set1_epi32(1));

  // Remainder in range [-pi/4..pi/4]
  //
  __m128 qf = _mm_cvtepi32_ps(q);
  __m128 p1 = _mm_sub_ps(x, _mm_mul_ps(qf, _mm_set1_ps(__SINCOSF_KC1)));
  xl = _mm_sub_ps(p1, _mm_mul_ps(qf, _mm_set1_ps(__SINCOSF_KC2)));

  // Compute x^2 and x^3
  //
  xl2 = _mm_mul_ps(xl, xl);
  xl3 = _mm_mul_ps(xl2, xl);

  // Compute both the sin and cos of the angles
  // using a polynomial expression:
  //   cx = 1.0f + xl2 * ((C0 * xl2 + C1) * xl2 + C2), and
  //   sx = xl + xl3 * ((S0 * xl2 + S1) * xl2 + S2)
  //
  __m128 cx, sx;

  cx = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(__SINCOSF_CC0), xl2), _mm_set1_ps(__SINCOSF_CC1));
  sx = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(__SINCOSF_SC0), xl2), _mm_set1_ps(__SINCOSF_SC1));

  cx = _mm_add_ps(_mm_mul_ps(cx, xl2), _mm_set1_ps(__SINCOSF_CC2));
  sx = _mm_add_ps(_mm_mul_ps(sx, xl2), _mm_set1_ps(__SINCOSF_SC2));

  cx = _mm_add_ps(_mm_mul_ps(cx, xl2), _mm_set1_ps(1.0f));
  sx = _mm_add_ps(_mm_mul_ps(sx, xl3), xl);

  // Use the cosine when the offset is odd and the sin
  // when the offset is even
  //
  __m128i sinMask, cosMask;

  sinMask = _mm_and_si128(offsetSin, _mm_set1_epi32(0x1));
  sinMask = _mm_cmpeq_epi32(sinMask, _mm_setzero_si128());

  cosMask = _mm_and_si128(offsetCos, _mm_set1_epi32(0x1));
  cosMask = _mm_cmpeq_epi32(cosMask, _mm_setzero_si128());

  ts = simdmath_sse_blendf4(cx, sx, _mm_castsi128_ps(sinMask));
  tc = simdmath_sse_blendf4(cx, sx, _mm_castsi128_ps(cosMask));

  // Flip the sign of the result when (offset mod 4) = 1 or 2
  //
  sinMask = _mm_and_si128(offsetSin, _mm_set1_epi32(0x2));
  sinMask = _mm_cmpeq_epi32(sinMask, _mm_setzero_si128());

  cosMask = _mm_and_si128(offsetCos, _mm_set1_epi32(0x2));
  cosMask = _mm_cmpeq_epi32(cosMask, _mm_setzero_si128());

  ts = simdmath_sse_blendf4(simdmath_negatef4(ts), ts, _mm_castsi128_ps(sinMask));
  tc = simdmath_sse_blendf4(simdmath_negatef4(tc), tc, _mm_castsi128_ps(cosMask));

  *s = ts;
  *c = tc;
}

SIMDMATH_INLINE __m128 simdmath_splatf4(float x)
{
  return _mm_set1_ps(x);
}

SIMDMATH_INLINE __m128 simdmath_sqrtf4(__m128 x)
{
  return _mm_sqrt_ps(x);
}

SIMDMATH_INLINE __m128 simdmath_tanf4(__m128 x)
{
  __m128 xl, xl2, xl3;
  __m128i q;

  /* range reduction using : xl = angle * 2 / pi */
  xl = _mm_mul_ps(x, _mm_set1_ps(0.63661977236f));

  /* find the quadrant the angle falls in */
  /* using : q = (int) ( ceil( abs(xl) ) * sign(xl) ) */
  xl = _mm_add_ps(xl, simdmath_copysignf4(_mm_set1_ps(0.5f), xl));
  q = _mm_cvttps_epi32(xl);

  /* remainder in range [-pi/4 .. pi/4] */
  __m128 qf, p1;
  qf = _mm_cvtepi32_ps(q);
  p1 = _mm_sub_ps(x, _mm_mul_ps(qf, _mm_set1_ps(__SINCOSF_KC1)));
  xl = _mm_sub_ps(p1, _mm_mul_ps(qf, _mm_set1_ps(__SINCOSF_KC2)));

  /* compute x^2 and x^3 */
  xl2 = _mm_mul_ps(xl, xl);
  xl3 = _mm_mul_ps(xl2, xl);

  /* compute both the sin and cos of the angles */
  /* using a polynomial expression: */
  /*   cx = 1 + xl2 * ( C0 * xl2 + C1 ) */
  /*   sx = xl + xl3 * S0 */
  __m128 ct2, cx, sx;
  ct2 = _mm_set1_ps(-0.4291161787f);
  ct2 = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(0.0097099364f), xl2), ct2);
  cx = _mm_add_ps(_mm_mul_ps(ct2, xl2), _mm_set1_ps(1.0f));
  sx = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(-0.0957822992f), xl3), xl);

  /* compute both cx/sx and sx/cx */
  __m128 cxosx = _mm_div_ps(cx, sx);
  __m128 sxocx = _mm_div_ps(sx, cx);
  __m128 ncxosx = simdmath_negatef4(cxosx);

  /* for odd numbered quadrants return -cx/sx; sx/cx otherwise */
  q = _mm_and_si128(_mm_set1_epi32(0x1), q);
  __m128i mask = _mm_cmpeq_epi32(q, _mm_setzero_si128());
  return simdmath_sse_blendf4(ncxosx, sxocx, _mm_castsi128_ps(mask));
}

SIMDMATH_INLINE __m128 simdmath_truncf4(__m128 x)
{
#ifdef __SSE4_1__ /* SSE 4.1 */

  return _mm_round_ps( x, 0x3 );

#else /* SSE2 */

  const __m128 xa = simdmath_fabsf4(x);
  const __m128 inrange = _mm_cmpgt_ps(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)), xa);
  const __m128i xi = _mm_cvttps_epi32(x);
  return simdmath_sse_blendf4(x, _mm_cvtepi32_ps(xi), inrange);

#endif
}

SIMDMATH_INLINE __m128 simdmath_uloadf4(const float* p)
{
#if defined(__SSE3__)
  return _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)((void*)p)));
#else
  return _mm_loadu_ps(p);
#endif
}

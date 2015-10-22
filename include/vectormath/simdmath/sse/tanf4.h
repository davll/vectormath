#pragma once

#include "_vec_utils.h"
#include "../_sincos.h"
#include "divf4.h"
#include "copysignf4.h"
#include "negatef4.h"

//
// Computes the tangent of all four slots of x by using a polynomia approximation.
//
static inline __m128
_tanf4 (__m128 x)
{
  __m128 xl, xl2, xl3, res;
  __m128i q;

  /* range reduction using : xl = angle * 2 / pi */

  xl = _mm_mul_ps(x, _mm_set1_ps(0.63661977236f));

  /* find the quadrant the angle falls in */
  /* using : q = (int) ( ceil( abs(xl) ) * sign(xl) ) */

  xl = _mm_add_ps(xl, _copysignf4(_mm_set1_ps(0.5f), xl));
  q = _mm_cvttps_epi32(xl);

  /* remainder in range [-pi/4 .. pi/4] */

  __m128 qf, p1;

  qf = _mm_cvtepi32_ps(q);
  p1 = _nmsubf4( qf, _mm_set1_ps(__SINCOSF_KC1), x );
  xl = _nmsubf4( qf, _mm_set1_ps(__SINCOSF_KC2), p1 );

  /* compute x^2 and x^3 */
  xl2 = _mm_mul_ps(xl, xl);
  xl3 = _mm_mul_ps(xl2, xl);

  /* compute both the sin and cos of the angles */
  /* using a polynomial expression: */
  /*   cx = 1 + xl2 * ( C0 * xl2 + C1 ) */
  /*   sx = xl + xl3 * S0 */

  __m128 ct2, cx, sx;

  ct2 = _mm_set1_ps(-0.4291161787f);
  ct2 = _maddf4(_mm_set1_ps(0.0097099364f), xl2, ct2);
  cx = _maddf4(ct2, xl2, _mm_set1_ps(1.0f));
  sx = _maddf4(_mm_set1_ps(-0.0957822992f), xl3, xl);

  /* compute both cx/sx and sx/cx */

  __m128 cxosx = _mm_div_ps(cx, sx);
  __m128 sxocx = _mm_div_ps(sx, cx);
  __m128 ncxosx = _negatef4(cxosx);

  /* for odd numbered quadrants return -cx/sx; sx/cx otherwise */

  q = _mm_and_si128(_mm_set1_epi32(0x1), q);
  __m128i mask = _mm_cmpeq_epi32(q, _mm_setzero_si128());

  return _blendf4(ncxosx, sxocx, _mm_castsi128_ps(mask));
}

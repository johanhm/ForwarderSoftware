/*
 * File: funcpinv.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 11-May-2015 18:50:04
 */

/* Include files */
#include "funcpinv.h"

/* Function Declarations */
static void b_eml_xaxpy(int n, double a, const double x[18], int ix0, double y[6],
  int iy0);
static double b_eml_xdotc(int n, const double x[9], int ix0, const double y[9],
  int iy0);
static double b_eml_xnrm2(int n, const double x[3], int ix0);
static void b_eml_xrot(double x[18], int ix0, int iy0, double c, double s);
static void b_eml_xscal(int n, double a, double x[3], int ix0);
static void b_eml_xswap(double x[18], int ix0, int iy0);
static void c_eml_xaxpy(int n, double a, const double x[6], int ix0, double y[18],
  int iy0);
static void c_eml_xscal(double a, double x[18], int ix0);
static void d_eml_xaxpy(int n, double a, int ix0, double y[9], int iy0);
static void d_eml_xscal(double a, double x[9], int ix0);
static double eml_div(double x, double y);
static void eml_xaxpy(int n, double a, int ix0, double y[18], int iy0);
static double eml_xdotc(int n, const double x[18], int ix0, const double y[18],
  int iy0);
static void eml_xgesvd(const double A[18], double U[18], double S[3], double V[9]);
static double eml_xnrm2(int n, const double x[18], int ix0);
static void eml_xrot(double x[9], int ix0, int iy0, double c, double s);
static void eml_xrotg(double *a, double *b, double *c, double *s);
static void eml_xscal(int n, double a, double x[18], int ix0);
static void eml_xswap(double x[9], int ix0, int iy0);

/* Function Definitions */

/*
 * Arguments    : int n
 *                double a
 *                const double x[18]
 *                int ix0
 *                double y[6]
 *                int iy0
 * Return Type  : void
 */
static void b_eml_xaxpy(int n, double a, const double x[18], int ix0, double y[6],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[9]
 *                int ix0
 *                const double y[9]
 *                int iy0
 * Return Type  : double
 */
static double b_eml_xdotc(int n, const double x[9], int ix0, const double y[9],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : int n
 *                const double x[3]
 *                int ix0
 * Return Type  : double
 */
static double b_eml_xnrm2(int n, const double x[3], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : double x[18]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
static void b_eml_xrot(double x[18], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 6; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

/*
 * Arguments    : int n
 *                double a
 *                double x[3]
 *                int ix0
 * Return Type  : void
 */
static void b_eml_xscal(int n, double a, double x[3], int ix0)
{
  int i2;
  int k;
  i2 = (ix0 + n) - 1;
  for (k = ix0; k <= i2; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double x[18]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
static void b_eml_xswap(double x[18], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 6; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * Arguments    : int n
 *                double a
 *                const double x[6]
 *                int ix0
 *                double y[18]
 *                int iy0
 * Return Type  : void
 */
static void c_eml_xaxpy(int n, double a, const double x[6], int ix0, double y[18],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : double a
 *                double x[18]
 *                int ix0
 * Return Type  : void
 */
static void c_eml_xscal(double a, double x[18], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 5; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : int n
 *                double a
 *                int ix0
 *                double y[9]
 *                int iy0
 * Return Type  : void
 */
static void d_eml_xaxpy(int n, double a, int ix0, double y[9], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : double a
 *                double x[9]
 *                int ix0
 * Return Type  : void
 */
static void d_eml_xscal(double a, double x[9], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 2; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double x
 *                double y
 * Return Type  : double
 */
static double eml_div(double x, double y)
{
  return x / y;
}

/*
 * Arguments    : int n
 *                double a
 *                int ix0
 *                double y[18]
 *                int iy0
 * Return Type  : void
 */
static void eml_xaxpy(int n, double a, int ix0, double y[18], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[18]
 *                int ix0
 *                const double y[18]
 *                int iy0
 * Return Type  : double
 */
static double eml_xdotc(int n, const double x[18], int ix0, const double y[18],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : const double A[18]
 *                double U[18]
 *                double S[3]
 *                double V[9]
 * Return Type  : void
 */
static void eml_xgesvd(const double A[18], double U[18], double S[3], double V[9])
{
  double b_A[18];
  double s[3];
  double e[3];
  int i;
  double work[6];
  double Vf[9];
  int q;
  int qs;
  double ztest0;
  int ii;
  int m;
  double rt;
  double ztest;
  int iter;
  double tiny;
  double snorm;
  int32_T exitg2;
  boolean_T exitg1;
  double f;
  double varargin_1[5];
  double mtmp;
  double sqds;
  memcpy(&b_A[0], &A[0], 18U * sizeof(double));
  for (i = 0; i < 3; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    work[i] = 0.0;
  }

  memset(&U[0], 0, 18U * sizeof(double));
  memset(&Vf[0], 0, 9U * sizeof(double));
  for (q = 0; q < 3; q++) {
    qs = q + 6 * q;
    ztest0 = eml_xnrm2(6 - q, b_A, qs + 1);
    if (ztest0 > 0.0) {
      if (b_A[qs] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      eml_xscal(6 - q, eml_div(1.0, s[q]), b_A, qs + 1);
      b_A[qs]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (ii = q + 1; ii + 1 < 4; ii++) {
      i = q + 6 * ii;
      if (s[q] != 0.0) {
        eml_xaxpy(6 - q, -eml_div(eml_xdotc(6 - q, b_A, qs + 1, b_A, i + 1),
                   b_A[q + 6 * q]), qs + 1, b_A, i + 1);
      }

      e[ii] = b_A[i];
    }

    for (ii = q; ii + 1 < 7; ii++) {
      U[ii + 6 * q] = b_A[ii + 6 * q];
    }

    if (q + 1 <= 1) {
      ztest0 = b_eml_xnrm2(2, e, 2);
      if (ztest0 == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          e[0] = -ztest0;
        } else {
          e[0] = ztest0;
        }

        b_eml_xscal(2, eml_div(1.0, e[0]), e, 2);
        e[1]++;
      }

      e[0] = -e[0];
      if (e[0] != 0.0) {
        for (ii = 2; ii < 7; ii++) {
          work[ii - 1] = 0.0;
        }

        for (ii = 1; ii + 1 < 4; ii++) {
          b_eml_xaxpy(5, e[ii], b_A, 2 + 6 * ii, work, 2);
        }

        for (ii = 1; ii + 1 < 4; ii++) {
          c_eml_xaxpy(5, eml_div(-e[ii], e[1]), work, 2, b_A, 2 + 6 * ii);
        }
      }

      for (ii = 1; ii + 1 < 4; ii++) {
        Vf[ii] = e[ii];
      }
    }
  }

  m = 1;
  e[1] = b_A[13];
  e[2] = 0.0;
  for (q = 2; q > -1; q += -1) {
    qs = q + 6 * q;
    if (s[q] != 0.0) {
      for (ii = q + 1; ii + 1 < 4; ii++) {
        i = (q + 6 * ii) + 1;
        eml_xaxpy(6 - q, -eml_div(eml_xdotc(6 - q, U, qs + 1, U, i), U[qs]), qs
                  + 1, U, i);
      }

      for (ii = q; ii + 1 < 7; ii++) {
        U[ii + 6 * q] = -U[ii + 6 * q];
      }

      U[qs]++;
      for (ii = 1; ii <= q; ii++) {
        U[(ii + 6 * q) - 1] = 0.0;
      }
    } else {
      for (ii = 0; ii < 6; ii++) {
        U[ii + 6 * q] = 0.0;
      }

      U[qs] = 1.0;
    }
  }

  for (q = 2; q > -1; q += -1) {
    if ((q + 1 <= 1) && (e[0] != 0.0)) {
      for (ii = 2; ii < 4; ii++) {
        i = 2 + 3 * (ii - 1);
        d_eml_xaxpy(2, -eml_div(b_eml_xdotc(2, Vf, 2, Vf, i), Vf[1]), 2, Vf, i);
      }
    }

    for (ii = 0; ii < 3; ii++) {
      Vf[ii + 3 * q] = 0.0;
    }

    Vf[q + 3 * q] = 1.0;
  }

  for (q = 0; q < 3; q++) {
    ztest0 = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = eml_div(s[q], rt);
      s[q] = rt;
      if (q + 1 < 3) {
        ztest0 = eml_div(e[q], ztest);
      }

      c_eml_xscal(ztest, U, 6 * q + 1);
    }

    if ((q + 1 < 3) && (ztest0 != 0.0)) {
      rt = fabs(ztest0);
      ztest = eml_div(rt, ztest0);
      ztest0 = rt;
      s[q + 1] *= ztest;
      d_eml_xscal(ztest, Vf, 3 * (q + 1) + 1);
    }

    e[q] = ztest0;
  }

  iter = 0;
  tiny = eml_div(2.2250738585072014E-308, 2.2204460492503131E-16);
  snorm = 0.0;
  for (ii = 0; ii < 3; ii++) {
    ztest0 = fabs(s[ii]);
    ztest = fabs(e[ii]);
    if (ztest0 >= ztest) {
    } else {
      ztest0 = ztest;
    }

    if (snorm >= ztest0) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    ii = m;
    do {
      exitg2 = 0;
      q = ii + 1;
      if (ii + 1 == 0) {
        exitg2 = 1;
      } else {
        ztest0 = fabs(e[ii]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[ii]) + fabs(s[ii + 1])))
            || (ztest0 <= tiny) || ((iter > 20) && (ztest0 <=
              2.2204460492503131E-16 * snorm))) {
          e[ii] = 0.0;
          exitg2 = 1;
        } else {
          ii--;
        }
      }
    } while (exitg2 == 0);

    if (ii + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      i = m + 2;
      exitg1 = false;
      while ((!exitg1) && (i >= ii + 1)) {
        qs = i;
        if (i == ii + 1) {
          exitg1 = true;
        } else {
          ztest0 = 0.0;
          if (i < m + 2) {
            ztest0 = fabs(e[i - 1]);
          }

          if (i > ii + 2) {
            ztest0 += fabs(e[i - 2]);
          }

          ztest = fabs(s[i - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <= tiny)) {
            s[i - 1] = 0.0;
            exitg1 = true;
          } else {
            i--;
          }
        }
      }

      if (qs == ii + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (ii = m; ii + 1 >= q + 1; ii--) {
        ztest0 = s[ii];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[ii] = ztest0;
        if (ii + 1 > q + 1) {
          f = -rt * e[0];
          e[0] *= ztest;
        }

        eml_xrot(Vf, 3 * ii + 1, 3 * (m + 1) + 1, ztest, rt);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (ii = q; ii + 1 <= m + 2; ii++) {
        eml_xrotg(&s[ii], &f, &ztest, &rt);
        f = -rt * e[ii];
        e[ii] *= ztest;
        b_eml_xrot(U, 6 * ii + 1, 6 * (q - 1) + 1, ztest, rt);
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      mtmp = varargin_1[0];
      for (i = 0; i < 4; i++) {
        if (varargin_1[i + 1] > mtmp) {
          mtmp = varargin_1[i + 1];
        }
      }

      f = eml_div(s[m + 1], mtmp);
      ztest0 = eml_div(s[m], mtmp);
      ztest = eml_div(e[m], mtmp);
      sqds = eml_div(s[q], mtmp);
      rt = eml_div((ztest0 + f) * (ztest0 - f) + ztest * ztest, 2.0);
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      ztest = 0.0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = eml_div(ztest0, rt + ztest);
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * eml_div(e[q], mtmp);
      for (ii = q + 1; ii <= m + 1; ii++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (ii > q + 1) {
          e[0] = f;
        }

        f = ztest * s[ii - 1] + rt * e[ii - 1];
        e[ii - 1] = ztest * e[ii - 1] - rt * s[ii - 1];
        ztest0 = rt * s[ii];
        s[ii] *= ztest;
        eml_xrot(Vf, 3 * (ii - 1) + 1, 3 * ii + 1, ztest, rt);
        s[ii - 1] = f;
        eml_xrotg(&s[ii - 1], &ztest0, &ztest, &rt);
        f = ztest * e[ii - 1] + rt * s[ii];
        s[ii] = -rt * e[ii - 1] + ztest * s[ii];
        ztest0 = rt * e[ii];
        e[ii] *= ztest;
        b_eml_xrot(U, 6 * (ii - 1) + 1, 6 * ii + 1, ztest, rt);
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        d_eml_xscal(-1.0, Vf, 3 * q + 1);
      }

      i = q + 1;
      while ((q + 1 < 3) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        eml_xswap(Vf, 3 * q + 1, 3 * (q + 1) + 1);
        b_eml_xswap(U, 6 * q + 1, 6 * (q + 1) + 1);
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (ii = 0; ii < 3; ii++) {
    S[ii] = s[ii];
    for (i = 0; i < 3; i++) {
      V[i + 3 * ii] = Vf[i + 3 * ii];
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[18]
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const double x[18], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : double x[9]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
static void eml_xrot(double x[9], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 3; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

/*
 * Arguments    : double *a
 *                double *b
 *                double *c
 *                double *s
 * Return Type  : void
 */
static void eml_xrotg(double *a, double *b, double *c, double *s)
{
  double roe;
  double absa;
  double absb;
  double scale;
  double ads;
  double bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    ads = 0.0;
    scale = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    ads = scale * sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      ads = -ads;
    }

    *c = *a / ads;
    *s = *b / ads;
    if (absa > absb) {
      scale = *s;
    } else if (*c != 0.0) {
      scale = 1.0 / *c;
    } else {
      scale = 1.0;
    }
  }

  *a = ads;
  *b = scale;
}

/*
 * Arguments    : int n
 *                double a
 *                double x[18]
 *                int ix0
 * Return Type  : void
 */
static void eml_xscal(int n, double a, double x[18], int ix0)
{
  int i1;
  int k;
  i1 = (ix0 + n) - 1;
  for (k = ix0; k <= i1; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double x[9]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
static void eml_xswap(double x[9], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 3; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * Arguments    : const double a[18]
 *                double b[18]
 * Return Type  : void
 */
void funcpinv(const double a[18], double b[18])
{
  double V[9];
  double s[3];
  double U[18];
  double S[9];
  int k;
  double tol;
  int r;
  int vcol;
  int ar;
  int ic;
  int i0;
  int ib;
  int ia;
  memset(&b[0], 0, 18U * sizeof(double));
  eml_xgesvd(a, U, s, V);
  memset(&S[0], 0, 9U * sizeof(double));
  for (k = 0; k < 3; k++) {
    S[k + 3 * k] = s[k];
  }

  tol = 6.0 * S[0] * 2.2204460492503131E-16;
  r = 0;
  k = 0;
  while ((k + 1 < 4) && (S[k + 3 * k] > tol)) {
    r++;
    k++;
  }

  if (r > 0) {
    vcol = 0;
    for (ar = 0; ar + 1 <= r; ar++) {
      tol = 1.0 / S[ar + 3 * ar];
      for (k = vcol; k + 1 <= vcol + 3; k++) {
        V[k] *= tol;
      }

      vcol += 3;
    }

    for (k = 0; k < 17; k += 3) {
      for (ic = k; ic + 1 <= k + 3; ic++) {
        b[ic] = 0.0;
      }
    }

    vcol = -1;
    for (k = 0; k < 17; k += 3) {
      ar = 0;
      vcol++;
      i0 = (vcol + 6 * (r - 1)) + 1;
      for (ib = vcol; ib + 1 <= i0; ib += 6) {
        if (U[ib] != 0.0) {
          ia = ar;
          for (ic = k; ic + 1 <= k + 3; ic++) {
            ia++;
            b[ic] += U[ib] * V[ia - 1];
          }
        }

        ar += 3;
      }
    }
  }
}

/*
 * File trailer for funcpinv.c
 *
 * [EOF]
 */

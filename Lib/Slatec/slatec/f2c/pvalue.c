/* pvalue.f -- translated by f2c (version 20060506).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__8 = 8;
static integer c__2 = 2;
static integer c__5 = 5;

/* DECK PVALUE */
/* Subroutine */ int pvalue_(integer *l, integer *nder, real *x, real *yfit, 
	real *yp, real *a)
{
    /* System generated locals */
    address a__1[5];
    integer i__1, i__2, i__3[5];
    char ch__1[150];

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    ;
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    static integer i__, n, k1, k2, k3, k4;
    static real cc;
    static integer ic, kc, in, k1i, lm1, lp1;
    static real dif;
    static integer k3p1, k4p1, ndo;
    static real val;
    static integer ilo, iup, ndp1, inp1, k3pn, k4pn, nord;
    static char xern1[8], xern2[8];
    static integer maxord;
    extern /* Subroutine */ int xermsg_(char *, char *, char *, integer *, 
	    integer *, ftnlen, ftnlen, ftnlen);

    /* Fortran I/O blocks */
    static icilist io___28 = { 0, xern1, 0, "(I8)", 8, 1 };
    static icilist io___30 = { 0, xern2, 0, "(I8)", 8, 1 };


/* ***BEGIN PROLOGUE  PVALUE */
/* ***PURPOSE  Use the coefficients generated by POLFIT to evaluate the */
/*            polynomial fit of degree L, along with the first NDER of */
/*            its derivatives, at a specified point. */
/* ***LIBRARY   SLATEC */
/* ***CATEGORY  K6 */
/* ***TYPE      SINGLE PRECISION (PVALUE-S, DP1VLU-D) */
/* ***KEYWORDS  CURVE FITTING, LEAST SQUARES, POLYNOMIAL APPROXIMATION */
/* ***AUTHOR  Shampine, L. F., (SNLA) */
/*           Davenport, S. M., (SNLA) */
/* ***DESCRIPTION */

/*     Written by L. F. Shampine and S. M. Davenport. */

/*     Abstract */

/*     The subroutine  PVALUE  uses the coefficients generated by  POLFIT */
/*     to evaluate the polynomial fit of degree  L , along with the first */
/*     NDER  of its derivatives, at a specified point.  Computationally */
/*     stable recurrence relations are used to perform this task. */

/*     The parameters for  PVALUE  are */

/*     Input -- */
/*         L -      the degree of polynomial to be evaluated.  L  may be */
/*                  any non-negative integer which is less than or equal */
/*                  to  NDEG , the highest degree polynomial provided */
/*                  by  POLFIT . */
/*         NDER -   the number of derivatives to be evaluated.  NDER */
/*                  may be 0 or any positive value.  If NDER is less */
/*                  than 0, it will be treated as 0. */
/*         X -      the argument at which the polynomial and its */
/*                  derivatives are to be evaluated. */
/*         A -      work and output array containing values from last */
/*                  call to  POLFIT . */

/*     Output -- */
/*         YFIT -   value of the fitting polynomial of degree  L  at  X */
/*         YP -     array containing the first through  NDER  derivatives */
/*                  of the polynomial of degree  L .  YP  must be */
/*                  dimensioned at least  NDER  in the calling program. */

/* ***REFERENCES  L. F. Shampine, S. M. Davenport and R. E. Huddleston, */
/*                 Curve fitting by polynomials in one variable, Report */
/*                 SLA-74-0270, Sandia Laboratories, June 1974. */
/* ***ROUTINES CALLED  XERMSG */
/* ***REVISION HISTORY  (YYMMDD) */
/*   740601  DATE WRITTEN */
/*   890531  Changed all specific intrinsics to generic.  (WRB) */
/*   890531  REVISION DATE from Version 3.2 */
/*   891214  Prologue converted to Version 4.0 format.  (BAB) */
/*   900315  CALLs to XERROR changed to CALLs to XERMSG.  (THJ) */
/*   900510  Convert XERRWV calls to XERMSG calls.  (RWC) */
/*   920501  Reformatted the REFERENCES section.  (WRB) */
/* ***END PROLOGUE  PVALUE */
/* ***FIRST EXECUTABLE STATEMENT  PVALUE */
    /* Parameter adjustments */
    --a;
    --yp;

    /* Function Body */
    if (*l < 0) {
	goto L12;
    }
    ndo = max(*nder,0);
    ndo = min(ndo,*l);
    maxord = a[1] + .5f;
    k1 = maxord + 1;
    k2 = k1 + maxord;
    k3 = k2 + maxord + 2;
    nord = a[k3] + .5f;
    if (*l > nord) {
	goto L11;
    }
    k4 = k3 + *l + 1;
    if (*nder < 1) {
	goto L2;
    }
    i__1 = *nder;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1: */
	yp[i__] = 0.f;
    }
L2:
    if (*l >= 2) {
	goto L4;
    }
    if (*l == 1) {
	goto L3;
    }

/* L IS 0 */

    val = a[k2 + 1];
    goto L10;

/* L IS 1 */

L3:
    cc = a[k2 + 2];
    val = a[k2 + 1] + (*x - a[2]) * cc;
    if (*nder >= 1) {
	yp[1] = cc;
    }
    goto L10;

/* L IS GREATER THAN 1 */

L4:
    ndp1 = ndo + 1;
    k3p1 = k3 + 1;
    k4p1 = k4 + 1;
    lp1 = *l + 1;
    lm1 = *l - 1;
    ilo = k3 + 3;
    iup = k4 + ndp1;
    i__1 = iup;
    for (i__ = ilo; i__ <= i__1; ++i__) {
/* L5: */
	a[i__] = 0.f;
    }
    dif = *x - a[lp1];
    kc = k2 + lp1;
    a[k4p1] = a[kc];
    a[k3p1] = a[kc - 1] + dif * a[k4p1];
    a[k3 + 2] = a[k4p1];

/* EVALUATE RECURRENCE RELATIONS FOR FUNCTION VALUE AND DERIVATIVES */

    i__1 = lm1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	in = *l - i__;
	inp1 = in + 1;
	k1i = k1 + inp1;
	ic = k2 + in;
	dif = *x - a[inp1];
	val = a[ic] + dif * a[k3p1] - a[k1i] * a[k4p1];
	if (ndo <= 0) {
	    goto L8;
	}
	i__2 = ndo;
	for (n = 1; n <= i__2; ++n) {
	    k3pn = k3p1 + n;
	    k4pn = k4p1 + n;
/* L6: */
	    yp[n] = dif * a[k3pn] + n * a[k3pn - 1] - a[k1i] * a[k4pn];
	}

/* SAVE VALUES NEEDED FOR NEXT EVALUATION OF RECURRENCE RELATIONS */

	i__2 = ndo;
	for (n = 1; n <= i__2; ++n) {
	    k3pn = k3p1 + n;
	    k4pn = k4p1 + n;
	    a[k4pn] = a[k3pn];
/* L7: */
	    a[k3pn] = yp[n];
	}
L8:
	a[k4p1] = a[k3p1];
/* L9: */
	a[k3p1] = val;
    }

/* NORMAL RETURN OR ABORT DUE TO ERROR */

L10:
    *yfit = val;
    return 0;

L11:
    s_wsfi(&io___28);
    do_fio(&c__1, (char *)&(*l), (ftnlen)sizeof(integer));
    e_wsfi();
    s_wsfi(&io___30);
    do_fio(&c__1, (char *)&nord, (ftnlen)sizeof(integer));
    e_wsfi();
/* Writing concatenation */
    i__3[0] = 40, a__1[0] = "THE ORDER OF POLYNOMIAL EVALUATION, L = ";
    i__3[1] = 8, a__1[1] = xern1;
    i__3[2] = 49, a__1[2] = " REQUESTED EXCEEDS THE HIGHEST ORDER FIT, NORD "
	    "= ";
    i__3[3] = 8, a__1[3] = xern2;
    i__3[4] = 45, a__1[4] = ", COMPUTED BY POLFIT -- EXECUTION TERMINATED.";
    s_cat(ch__1, a__1, i__3, &c__5, (ftnlen)150);
    xermsg_("SLATEC", "PVALUE", ch__1, &c__8, &c__2, (ftnlen)6, (ftnlen)6, (
	    ftnlen)150);
    return 0;

L12:
    xermsg_("SLATEC", "PVALUE", "INVALID INPUT PARAMETER.  ORDER OF POLYNOMI"
	    "AL EVALUATION REQUESTED IS NEGATIVE -- EXECUTION TERMINATED.", &
	    c__2, &c__2, (ftnlen)6, (ftnlen)6, (ftnlen)103);
    return 0;
} /* pvalue_ */

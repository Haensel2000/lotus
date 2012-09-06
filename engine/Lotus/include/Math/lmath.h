/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LMATH_H
#define _HDR_LMATH_H

#include <system\lsystem.h>
#include <system\lplatforms.h>

namespace Lotus
{
	template <class T> T max(T a, T b);
	template <class T> T max(T a, T b, T c);

	const int MAX_UNSIGNED_SHORT = 256*256;
	
	/* class Math:
	 * Provides basic mathematical functions both for double and single 
	 * precision, by introducing a template parameter R that is either
	 * float or double. They clamp the input argument to [-1,1] to avoid
	 * NaN handling, resulting from rounding errors. */
	template <class R> class Math
	{
	public:
		static R ACos (R value);
		static R ASin (R value);
		static R ATan (R value);
		static R ATan2 (R x, R y);
		static R Ceil (R value);
		static R Cos (R value);
		static R Exp (R value);
		static R FAbs (R value);
		static R Floor (R value);
		static R FMod (R x, R y);
		static R InvSqrt (R value);
		static R Log (R value);
		static R Pow (R base, R exponent);
		static R Sin (R value);
		static R Sqr (R value);
		static R Sqrt (R value);
		static R Tan (R value);

		// Return -1 if the input is negative, 0 if the input is zero, and +1
		// if the input is positive.
		static int Sign (int iValue);
		static R Sign (R fValue);

		// Generate a random number in [0,1).  The random number generator may
		// be seeded by a first call to UnitRandom with a positive seed.
		static R UnitRandom (unsigned int seed = 0);

		// Generate a random number in [-1,1).  The random number generator may
		// be seeded by a first call to SymmetricRandom with a positive seed.
		static R SymmetricRandom (unsigned int seed = 0);

		// Generate a random number in [min,max).  The random number generator may
		// be seeded by a first call to IntervalRandom with a positive seed.
		static R IntervalRandom (R fMin, R fMax, unsigned int seed = 0);

		// Fast evaluation of trigonometric and inverse trigonometric functions
		// using polynomial approximations.  The speed ups were measured on an
		// AMD 2800 (2.08 GHz) processor using Visual Studio .NET 2003 with a
		// release build.

		// The input must be in [0,pi/2].
		// max error sin0 = 1.7e-04, speed up = 4.0
		// max error sin1 = 1.9e-08, speed up = 2.8
		static R FastSin0 (R angle);
		static R FastSin1 (R angle);

		// The input must be in [0,pi/2]
		// max error cos0 = 1.2e-03, speed up = 4.5
		// max error cos1 = 6.5e-09, speed up = 2.8
		static R FastCos0 (R angle);
		static R FastCos1 (R angle);

		// The input must be in [0,pi/4].
		// max error tan0 = 8.1e-04, speed up = 5.6
		// max error tan1 = 1.9e-08, speed up = 3.4
		static R FastTan0 (R angle);
		static R FastTan1 (R angle);

		// The input must be in [0,1].
		// max error invsin0 = 6.8e-05, speed up = 7.5
		// max error invsin1 = 1.4e-07, speed up = 5.5
		static R FastInvSin0 (R value);
		static R FastInvSin1 (R value);

		// The input must be in [0,1].
		// max error invcos0 = 6.8e-05, speed up = 7.5
		// max error invcos1 = 1.4e-07, speed up = 5.7
		static R FastInvCos0 (R value);
		static R FastInvCos1 (R value);

		// The input must be in [-1,1]. 
		// max error invtan0 = 1.2e-05, speed up = 2.8
		// max error invtan1 = 2.3e-08, speed up = 1.8
		static R FastInvTan0 (R value);
		static R FastInvTan1 (R value);

		// A fast approximation to 1/sqrt.
		static R FastInvSqrt (R value);

		// common constants
		DLL_ITEM static const R EPSILON;
		DLL_ITEM static const R ZERO_TOLERANCE;
		DLL_ITEM static const R MAX_REAL;
		DLL_ITEM static const R PI;
		DLL_ITEM static const R TWO_PI;
		DLL_ITEM static const R HALF_PI;
		DLL_ITEM static const R INV_PI;
		DLL_ITEM static const R INV_TWO_PI;
		DLL_ITEM static const R DEG_TO_RAD;
		DLL_ITEM static const R RAD_TO_DEG;
	};
	
#include "lmath.inl"
}



#endif
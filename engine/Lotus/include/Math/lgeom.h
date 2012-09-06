/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LGEOM_H
#define _HDR_LGEOM_H

#include "math\lvector.h"

namespace Lotus
{
	template <class R> class TLine3
	{
	public:
		TVector3<R> origin, direction; // direction has to be unitLength

		TLine3(const TVector3<R>& origin, const TVector3<R>& direction);
		R distanceTo(const TVector3<R>& v) const;
	};

	template <class R> class TPlane3
	{
	public:
		TVector3<R> normal;
		R constant;

		TPlane3();
		TPlane3(const TVector3<R>& normal, R constant);
		TPlane3(const TVector3<R>& normal, const TVector3<R>& point);
		TPlane3(const TVector3<R>& a, const TVector3<R>& b, const TVector3<R>& c);

		int whichSide(const TVector3<R>& point) const;
		R distanceTo(const TVector3<R>&  point) const; // signed distance
	};

#include "lgeom.inl"

	typedef TPlane3<float> Plane3f;
	typedef Plane3f Plane3;
	typedef TPlane3<double> Plane3d;

	typedef TLine3<float> Line3f;
	typedef Line3f Line3;
	typedef TLine3<double> Line3d;
}

#endif
/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class TLine3:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TLine3<R>::TLine3(const TVector3<R>& origin, const TVector3<R>& direction)
: origin(origin), direction(direction)
{
}
/* ------------------------------------------------------- */
template <class R> R TLine3<R>::distanceTo(const TVector3<R>& v) const
{
	return TVector3<R>::Length(direction.cross(v - origin));
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TPlane3:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TPlane3<R>::TPlane3()
: normal(), constant()
{
}
/* ------------------------------------------------------- */
template <class R> TPlane3<R>::TPlane3(const TVector3<R>& normal, R constant) 
: normal(normal), constant(constant)
{
}
/* ------------------------------------------------------- */
template <class R> TPlane3<R>::TPlane3(const TVector3<R>& normal, const TVector3<R>& point) 
: normal(normal)
{
	constant = normal.dot(point);
}
/* ------------------------------------------------------- */
template <class R> TPlane3<R>::TPlane3(const TVector3<R>& a, const TVector3<R>& b, const TVector3<R>& c)
{
	normal = (b-a).cross(c-a);
	normal.normalize();
	constant = normal.dot(a);
}
/* ------------------------------------------------------- */
template <class R> int TPlane3<R>::whichSide(const TVector3<R>& point) const
{
	R dist = distanceTo(point);
	if (dist > ((R)0.0))
	{
		return 1;
	}
	else if (dist < ((R)0.0))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
/* ------------------------------------------------------- */
template <class R> R TPlane3<R>::distanceTo(const TVector3<R>&  point) const
{
	return normal.dot(point) - constant;
}
/* ------------------------------------------------------- */
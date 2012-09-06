/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* Operators:                                              */
/*                                                         */
/* ------------------------------------------------------- */
template <class R> TVector2<R> operator*(R scalar, const TVector2<R>& vector)
{
	return vector * scalar;
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> operator*(R scalar, const TVector3<R>& vector)
{
	return vector * scalar;
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> operator*(R scalar, const TVector4<R>& vector)
{
	return vector * scalar;
}
/* ------------------------------------------------------- */
/* class TVector2:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TVector2<R>::TVector2(R x, R y)
{
	m_tuple[0] = x;
	m_tuple[1] = y;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>::TVector2(const R* tuple)
{
	m_tuple[0] = tuple[0];
	m_tuple[1] = tuple[1];
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>::TVector2(const TVector2<R>& vector)
{
	m_tuple[0] = vector.m_tuple[0];
	m_tuple[1] = vector.m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> void TVector2<R>::operator=(const TVector2& vector)
{
	m_tuple[0] = vector.m_tuple[0];
	m_tuple[1] = vector.m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>::operator const R* () const
{
	return &m_tuple;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>::operator R*()
{
	return &m_tuple;
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::operator[] (int i) const
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> R& TVector2<R>::operator[] (int i)
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::X() const
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R& TVector2<R>::X()
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::Y() const
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R& TVector2<R>::Y()
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator==(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator!=(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator<(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator<=(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator>(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TVector2<R>::operator>=(const TVector2<R>& vector) const
{
	return (memcmp(m_tuple, vector.m_tuple, 2*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::operator+(const TVector2<R>& vector) const
{
	return TVector2<R>(m_tuple[0] + vector.m_tuple[0], m_tuple[1] + vector.m_tuple[1]);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::operator-(const TVector2<R>& vector) const
{
	return TVector2<R>(m_tuple[0] - vector.m_tuple[0], m_tuple[1] - vector.m_tuple[1]);	
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::operator*(R scalar) const
{
	return TVector2<R>(m_tuple[0] * scalar, m_tuple[1] * scalar);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::operator/(R scalar) const
{
	float invScalar = ((R)1.0)/scalar;
	return TVector2<R>(m_tuple[0] * invScalar, m_tuple[1] * invScalar);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::operator-() const
{
	return TVector2<R>(-m_tuple[0], -m_tuple[1]);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>& TVector2<R>::operator+=(const TVector2<R>& vector)
{
	m_tuple[0] += vector.m_tuple[0];
	m_tuple[1] += vector.m_tuple[1];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>& TVector2<R>::operator-=(const TVector2<R>& vector)
{
	m_tuple[0] -= vector.m_tuple[0];
	m_tuple[1] -= vector.m_tuple[1];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>& TVector2<R>::operator*=(R scalar)
{
	m_tuple[0] *= scalar;
	m_tuple[1] *= scalar;
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R>& TVector2<R>::operator/=(R scalar)
{
	float invScalar = ((R)1.0)/scalar;
	m_tuple[0] *= invScalar;
	m_tuple[1] *= invScalar;
	return *this;
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::length() const
{
	return Math<R>::Sqrt(m_tuple[0]*m_tuple[0] + m_tuple[1]*m_tuple[1]);
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::squaredLength() const
{
	return m_tuple[0]*m_tuple[0] + m_tuple[1]*m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::dot(const TVector2<R>& vector) const
{
	return m_tuple[0]*vector.m_tuple[0] + m_tuple[1]*vector.m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::normalize()
{
	R len = length();
	if (len > Math<R>::ZERO_TOLERANCE)
	{
		R invLen = ((R)1.0)/len;
		m_tuple[0] *= invLen;
		m_tuple[1] *= invLen;
	}
	else
	{
		len = (R)0.0;
		m_tuple[0] *= (R)0.0;
		m_tuple[1] *= (R)0.0;
	}
	
	return len;
}
/* ------------------------------------------------------- */
template <class R>  R TVector2<R>::Length(const TVector2<R>& v)
{
	return v.length();
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::perp() const 
{
	return TVector2<R>(m_tuple[1], -m_tuple[0]);
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TVector2<R>::unitPerp() const 
{
	TVector2<R> tmp(m_tuple[1], -m_tuple[0]);
	tmp.normalize();
	return tmp;
}
/* ------------------------------------------------------- */
template <class R> R TVector2<R>::dotPerp(const TVector2<R>& vector) const 
{
	return m_tuple[0]*vector.m_tuple[1] - m_tuple[1]*vector.m_tuple[0];
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
template <class R>  void TVector2<R>::Orthonormalize(TVector2<R>& u, TVector2<R>& v) 
{
	// Gram-Schmidt orthonormalization
	u.normalize();
	v -= u.dot(v)*u;
	v.normalize();
}
/* ------------------------------------------------------- */
template <class R>  void TVector2<R>::GenerateOrthonormalBasis(TVector2<R>& u,
	TVector2<R>& v, bool unitLength) 
{
	if (!unitLength)
		u.normalize();
	v = u.perp();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TTuple3 :                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TTuple3<R>::TTuple3(R x, R y, R z)
{
	m_tuple[0] = x;
	m_tuple[1] = y;
	m_tuple[2] = z;
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>::TTuple3(const R* tuple)
{
	m_tuple[0] = tuple[0];
	m_tuple[1] = tuple[1];
	m_tuple[2] = tuple[2];
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>::TTuple3(const TTuple3<R>& tuple)
{
	m_tuple[0] = tuple.m_tuple[0];
	m_tuple[1] = tuple.m_tuple[1];
	m_tuple[2] = tuple.m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> void TTuple3<R>::operator=(const TTuple3& tuple)
{
	m_tuple[0] = tuple.m_tuple[0];
	m_tuple[1] = tuple.m_tuple[1];
	m_tuple[2] = tuple.m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>::operator const R* () const
{
	return m_tuple;
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>::operator R*()
{
	return m_tuple;
}
/* ------------------------------------------------------- */
template <class R> R TTuple3<R>::operator[] (int i) const
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> R& TTuple3<R>::operator[] (int i)
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator==(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator!=(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator<(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator<=(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator>(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple3<R>::operator>=(const TTuple3<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 3*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R> TTuple3<R>::operator+(const TTuple3<R>& tuple) const
{
	return TTuple3<R>(	m_tuple[0] + tuple.m_tuple[0],
						m_tuple[1] + tuple.m_tuple[1],
						m_tuple[2] + tuple.m_tuple[2]);
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R> TTuple3<R>::operator-(const TTuple3<R>& tuple) const
{
	return TTuple3<R>(	m_tuple[0] - tuple.m_tuple[0],
						m_tuple[1] - tuple.m_tuple[1],
						m_tuple[2] - tuple.m_tuple[2]);	
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R> TTuple3<R>::operator*(R scalar) const
{
	return TTuple3<R>(	m_tuple[0] * scalar,
						m_tuple[1] * scalar,
						m_tuple[2] * scalar);
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R> TTuple3<R>::operator/(R scalar) const
{
	register float invScalar = ((R)1.0)/scalar;
	return TTuple3<R>(	m_tuple[0] * invScalar,
						m_tuple[1] * invScalar,
						m_tuple[2] * invScalar);
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R> TTuple3<R>::operator-() const
{
	return TTuple3<R>(-m_tuple[0], -m_tuple[1], -m_tuple[2]);
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>& TTuple3<R>::operator+=(const TTuple3<R>& tuple)
{
	m_tuple[0] += tuple.m_tuple[0];
	m_tuple[1] += tuple.m_tuple[1];
	m_tuple[2] += tuple.m_tuple[2];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>& TTuple3<R>::operator-=(const TTuple3<R>& tuple)
{
	m_tuple[0] -= tuple.m_tuple[0];
	m_tuple[1] -= tuple.m_tuple[1];
	m_tuple[2] -= tuple.m_tuple[2];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>& TTuple3<R>::operator*=(R scalar)
{
	m_tuple[0] *= scalar;
	m_tuple[1] *= scalar;
	m_tuple[2] *= scalar;
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple3<R>& TTuple3<R>::operator/=(R scalar)
{
	register float invScalar = ((R)1.0)/scalar;
	m_tuple[0] *= invScalar;
	m_tuple[1] *= invScalar;
	m_tuple[2] *= invScalar;
	return *this;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TVector3:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TVector3<R>::TVector3(R x, R y, R z) 
: TTuple3<R>(x,y,z)
{
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>::TVector3(const R* tuple)
: TTuple3<R>(tuple)
{
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>::TVector3(const TVector3<R>& vector)
: TTuple3<R>(vector)
{
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::X() const
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R& TVector3<R>::X()
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::Y() const
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R& TVector3<R>::Y()
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::Z() const
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R& TVector3<R>::Z()
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::length() const
{
	return Math<R>::Sqrt(	m_tuple[0]*m_tuple[0] + 
							m_tuple[1]*m_tuple[1] +
							m_tuple[2]*m_tuple[2] );
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::squaredLength() const
{
	return	m_tuple[0]*m_tuple[0] + 
			m_tuple[1]*m_tuple[1] + 
			m_tuple[2]*m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::dot(const TVector3<R>& vector) const
{
	return	m_tuple[0]*vector.m_tuple[0] +
			m_tuple[1]*vector.m_tuple[1] +
			m_tuple[2]*vector.m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R TVector3<R>::normalize()
{
	R len = length();
	if (len > Math<R>::ZERO_TOLERANCE)
	{
		R invLen = ((R)1.0)/len;
		m_tuple[0] *= invLen;
		m_tuple[1] *= invLen;
		m_tuple[2] *= invLen;
	}
	else
	{
		len = (R)0.0;
		m_tuple[0] *= (R)0.0;
		m_tuple[1] *= (R)0.0;
		m_tuple[2] *= (R)0.0;
	}
	
	return len;
}
/* ------------------------------------------------------- */
template <class R>  R TVector3<R>::Length(const TVector3<R>& v)
{
	return v.length();
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::cross(const TVector3<R>& vector) const
{
	return TVector3(
		m_tuple[1]*vector.m_tuple[2] - m_tuple[2]*vector.m_tuple[1],
		m_tuple[2]*vector.m_tuple[0] - m_tuple[0]*vector.m_tuple[2],
		m_tuple[0]*vector.m_tuple[1] - m_tuple[1]*vector.m_tuple[0] );
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::unitCross(const TVector3<R>& vector) const
{
	TVector3 tmp = cross(vector);
	tmp.normalize();
	return tmp;
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::operator+(const TVector3& tuple) const
{
	return (TVector3<R>)TTuple3<R>::operator+(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::operator-(const TVector3& tuple) const
{
	return (TVector3<R>)TTuple3<R>::operator-(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::operator*(R scalar) const
{
	return (TVector3<R>)TTuple3<R>::operator*(scalar);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::operator/(R scalar) const
{
	return (TVector3<R>)TTuple3<R>::operator/(scalar);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TVector3<R>::operator-() const
{
	return (TVector3<R>)TTuple3<R>::operator-();
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>& TVector3<R>::operator+=(const TVector3& tuple)
{
	return (TVector3<R>&)TTuple3<R>::operator+=(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>& TVector3<R>::operator-=(const TVector3& tuple)
{
	return (TVector3<R>&)TTuple3<R>::operator-=(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>& TVector3<R>::operator*=(R scalar)
{
	return (TVector3<R>&)TTuple3<R>::operator*=(scalar);
}
/* ------------------------------------------------------- */
template <class R> TVector3<R>& TVector3<R>::operator/=(R scalar)
{
	return (TVector3<R>&)TTuple3<R>::operator/=(scalar);
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
template <class R>  
void TVector3<R>::Orthonormalize(TVector3<R>& u, TVector3<R>& v, TVector3<R>& w) 
{
	// Gram-Schmidt orthonormalization
	u.normalize();
	v -= u.dot(v)*u;
	v.normalize();
	w -= u.dot(w)*u + v.dot(w)*v;
	w.normalize();
}
/* ------------------------------------------------------- */
template <class R>  
void TVector3<R>::Orthonormalize(ArrayPtr<TVector3> vectors) 
{
	assert(vectors.size() >= 3);
	Orthonormalize(vectors[0], vectors[1], vectors[2]);
}
/* ------------------------------------------------------- */
template <class R>  
void TVector3<R>::GenerateOrthonormalBasis(TVector3<R>& u, TVector3<R>& v,
		TVector3<R>& w, bool unitLength) 
{
	if (!unitLength)
		u.normalize();
	if (u.m_tuple[0] >= u.m_tuple[1])	// generate a normal vector by swapping
	{									// two components and setting the third to
		v.m_tuple[0] = -u.m_tuple[2];	// zero. for reasons of numerical
		v.m_tuple[1] = 0;				// robustness the smaller component is set
		v.m_tuple[2] = u.m_tuple[0];	// to zero
	}
	else
	{
		v.m_tuple[0] = 0;
		v.m_tuple[1] = u.m_tuple[2];				
		v.m_tuple[2] = -u.m_tuple[1];
	}
	v.normalize();
	w = u.cross(v);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TTuple4:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TTuple4<R>::TTuple4(R x, R y, R z, R w)
{
	m_tuple[0] = x;
	m_tuple[1] = y;
	m_tuple[2] = z;
	m_tuple[3] = w;
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>::TTuple4(const R* tuple)
{
	m_tuple[0] = tuple[0];
	m_tuple[1] = tuple[1];
	m_tuple[2] = tuple[2];
	m_tuple[3] = tuple[3];
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>::TTuple4(const TTuple4<R>& tuple)
{
	m_tuple[0] = tuple.m_tuple[0];
	m_tuple[1] = tuple.m_tuple[1];
	m_tuple[2] = tuple.m_tuple[2];
	m_tuple[3] = tuple.m_tuple[3];
}
/* ------------------------------------------------------- */
template <class R> void TTuple4<R>::operator=(const TTuple4& tuple)
{
	m_tuple[0] = tuple.m_tuple[0];
	m_tuple[1] = tuple.m_tuple[1];
	m_tuple[2] = tuple.m_tuple[2];
	m_tuple[3] = tuple.m_tuple[3];
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>::operator const R* () const
{
	return &m_tuple;
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>::operator R*()
{
	return &m_tuple;
}
/* ------------------------------------------------------- */
template <class R> R TTuple4<R>::operator[] (int i) const
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> R& TTuple4<R>::operator[] (int i)
{
	return m_tuple[i];
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator==(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator!=(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator<(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator<=(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator>(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TTuple4<R>::operator>=(const TTuple4<R>& tuple) const
{
	return (memcmp(m_tuple, tuple.m_tuple, 4*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R> TTuple4<R>::operator+(const TTuple4<R>& tuple) const
{
	return TTuple4<R>(	m_tuple[0] + tuple.m_tuple[0],
						m_tuple[1] + tuple.m_tuple[1],
						m_tuple[2] + tuple.m_tuple[2],
						m_tuple[3] + tuple.m_tuple[3]);
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R> TTuple4<R>::operator-(const TTuple4<R>& tuple) const
{
	return TTuple4<R>(	m_tuple[0] - tuple.m_tuple[0],
						m_tuple[1] - tuple.m_tuple[1],
						m_tuple[2] - tuple.m_tuple[2],
						m_tuple[3] - tuple.m_tuple[3]);	
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R> TTuple4<R>::operator*(R scalar) const
{
	return TTuple4<R>(	m_tuple[0] * scalar,
						m_tuple[1] * scalar,
						m_tuple[2] * scalar,
						m_tuple[3] * scalar);
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R> TTuple4<R>::operator/(R scalar) const
{
	register float invScalar = ((R)1.0)/scalar;
	return TTuple4<R>(	m_tuple[0] * invScalar,
						m_tuple[1] * invScalar,
						m_tuple[2] * invScalar,
						m_tuple[3] * invScalar);
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R> TTuple4<R>::operator-() const
{
	return TTuple4<R>(-m_tuple[0], -m_tuple[1], -m_tuple[2], -m_tuple[3]);
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>& TTuple4<R>::operator+=(const TTuple4<R>& tuple)
{
	m_tuple[0] += tuple.m_tuple[0];
	m_tuple[1] += tuple.m_tuple[1];
	m_tuple[2] += tuple.m_tuple[2];
	m_tuple[3] += tuple.m_tuple[3];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>& TTuple4<R>::operator-=(const TTuple4<R>& tuple)
{
	m_tuple[0] -= tuple.m_tuple[0];
	m_tuple[1] -= tuple.m_tuple[1];
	m_tuple[2] -= tuple.m_tuple[2];
	m_tuple[3] -= tuple.m_tuple[3];
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>& TTuple4<R>::operator*=(R scalar)
{
	m_tuple[0] *= scalar;
	m_tuple[1] *= scalar;
	m_tuple[2] *= scalar;
	m_tuple[3] *= scalar;
	return *this;
}
/* ------------------------------------------------------- */
template <class R> TTuple4<R>& TTuple4<R>::operator/=(R scalar)
{
	register float invScalar = ((R)1.0)/scalar;
	m_tuple[0] *= invScalar;
	m_tuple[1] *= invScalar;
	m_tuple[2] *= invScalar;
	m_tuple[3] *= invScalar;
	return *this;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TVector4:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TVector4<R>::TVector4(R x, R y, R z, R w)
: TTuple4<R>(x,y,z,w)
{
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>::TVector4(const R* tuple)
: TTuple4<R>(tuple)
{
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>::TVector4(const TVector4<R>& vector)
: TTuple4<R>(vector) 
{
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::X() const
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R& TVector4<R>::X()
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::Y() const
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R& TVector4<R>::Y()
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::Z() const
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R& TVector4<R>::Z()
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::W() const
{
	return m_tuple[3];
}
/* ------------------------------------------------------- */
template <class R> R& TVector4<R>::W()
{
	return m_tuple[3];
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::length() const
{
	return Math<R>::Sqrt(	m_tuple[0]*m_tuple[0] + 
							m_tuple[1]*m_tuple[1] +
							m_tuple[2]*m_tuple[2] +
							m_tuple[3]*m_tuple[3] );
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::squaredLength() const
{
	return	m_tuple[0]*m_tuple[0] + 
			m_tuple[1]*m_tuple[1] + 
			m_tuple[2]*m_tuple[2] +
			m_tuple[3]*m_tuple[3] ;
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::dot(const TVector4<R>& vector) const
{
	return	m_tuple[0]*vector.m_tuple[0] +
			m_tuple[1]*vector.m_tuple[1] +
			m_tuple[2]*vector.m_tuple[2] +
			m_tuple[3]*vector.m_tuple[3] ;
}
/* ------------------------------------------------------- */
template <class R> R TVector4<R>::normalize()
{
	R len = length();
	if (len > Math<R>::ZERO_TOLERANCE)
	{
		R invLen = ((R)1.0)/len;
		m_tuple[0] *= invLen;
		m_tuple[1] *= invLen;
		m_tuple[2] *= invLen;
		m_tuple[3] *= invLen;
	}
	else
	{
		len = (R)0.0;
		m_tuple[0] *= (R)0.0;
		m_tuple[1] *= (R)0.0;
		m_tuple[2] *= (R)0.0;
		m_tuple[3] *= (R)0.0;
	}
	
	return len;
}
/* ------------------------------------------------------- */
template <class R>  R TVector4<R>::Length(const TVector4<R>& v)
{
	return v.length();
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TVector4<R>::operator+(const TVector4& tuple) const
{
	return (TVector4<R>)TTuple4<R>::operator+(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TVector4<R>::operator-(const TVector4& tuple) const
{
	return (TVector4<R>)TTuple4<R>::operator-(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TVector4<R>::operator*(R scalar) const
{
	return (TVector4<R>)TTuple4<R>::operator*(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TVector4<R>::operator/(R scalar) const
{
	return (TVector4<R>)TTuple4<R>::operator/(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TVector4<R>::operator-() const
{
	return (TVector4<R>)TTuple4<R>::operator-(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>& TVector4<R>::operator+=(const TVector4& tuple)
{
	return (TVector4<R>&)TTuple4<R>::operator+=(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>& TVector4<R>::operator-=(const TVector4& tuple)
{
	return (TVector4<R>&)TTuple4<R>::operator-=(tuple);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>& TVector4<R>::operator*=(R scalar)
{
	return (TVector4<R>&)TTuple4<R>::operator*=(scalar);
}
/* ------------------------------------------------------- */
template <class R> TVector4<R>& TVector4<R>::operator/=(R scalar)
{
	return (TVector4<R>&)TTuple4<R>::operator/=(scalar);
}
/* ------------------------------------------------------- */
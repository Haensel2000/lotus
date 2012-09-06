/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LVECTOR_H
#define _HDR_LVECTOR_H

#include <system\lplatforms.h>
#include <system\lpointer.h>

namespace Lotus
{
	/* class TVector2
	 * Implements a 2D-Vector with a lot of useful functionality, like
	 * comparison, arithmetic, conversion and other mathematical alogrithms.
	 * The accuracy can be specified through the template parameter.
	 * Constraints on R: has to be either double or float */
	template <class R> class TVector2
	{
	private:
		R m_tuple[2];
	public:
		// constructors
		TVector2(R x = 0, R y = 0);
		TVector2(const R* tuple);
		TVector2(const TVector2& vector);

		void operator=(const TVector2& vector);

		// member access
		operator const R* () const;
		operator R*();
		R operator[] (int i) const;
		R& operator[] (int i);
		R X() const;
		R& X();
		R Y() const;
		R& Y();

		//comparison operators
		bool operator==(const TVector2& vector) const;
		bool operator!=(const TVector2& vector) const;
		bool operator<(const TVector2& vector) const;
		bool operator<=(const TVector2& vector) const;
		bool operator>(const TVector2& vector) const;
		bool operator>=(const TVector2& vector) const;

		//algebraic operations
		TVector2 operator+(const TVector2& vector) const;
		TVector2 operator-(const TVector2& vector) const;
		TVector2 operator*(R scalar) const;
		TVector2 operator/(R scalar) const;
		TVector2 operator-() const;
		TVector2& operator+=(const TVector2& vector);
		TVector2& operator-=(const TVector2& vector);
		TVector2& operator*=(R scalar);
		TVector2& operator/=(R scalar);

		// geometric operations
		R length() const;
		R squaredLength() const;
		R dot(const TVector2& vector) const;
		R normalize(); // returns the length of the vector
		static R Length(const TVector2& v);

		// specific geomteric operations
		TVector2 perp() const;
		TVector2 unitPerp() const;
		R dotPerp(const TVector2& vector) const;
		
		static void Orthonormalize(TVector2& u, TVector2& v);
		static void GenerateOrthonormalBasis(TVector2& u, TVector2& v,
			bool unitLength); // only u is given, v is computed

		DLL_ITEM static const TVector2 ZERO;
		DLL_ITEM static const TVector2 UNIT_X;
		DLL_ITEM static const TVector2 UNIT_Y;

	};

	/* class TTuple3
	 * Implements a collection of three floating point values. This class can be used as 
	 * a baseclass for colors, vectors and other classes that rely on a tuple of 3 values.
	 * Constraints on R: has to be either double or float */
	template <class R> class TTuple3
	{
	protected:
		R m_tuple[3];
	public:
		// constructors
		TTuple3(R x, R y, R z);
		TTuple3(const R* tuple);
		TTuple3(const TTuple3& tuple);
		void operator=(const TTuple3& tuple);

		// member access
		operator const R* () const;
		operator R*();
		R operator[] (int i) const;
		R& operator[] (int i);

		//comparison operators
		bool operator==(const TTuple3& tuple) const;
		bool operator!=(const TTuple3& tuple) const;
		bool operator<(const TTuple3& tuple) const;
		bool operator<=(const TTuple3& tuple) const;
		bool operator>(const TTuple3& tuple) const;
		bool operator>=(const TTuple3& tuple) const;

		//algebraic operations
		TTuple3 operator+(const TTuple3& tuple) const;
		TTuple3 operator-(const TTuple3& tuple) const;
		TTuple3 operator*(R scalar) const;
		TTuple3 operator/(R scalar) const;
		TTuple3 operator-() const;
		TTuple3& operator+=(const TTuple3& tuple);
		TTuple3& operator-=(const TTuple3& tuple);
		TTuple3& operator*=(R scalar);
		TTuple3& operator/=(R scalar);
	};

	/* class TVector3
	 * Implements a 3D-Vector with a lot of useful functionality, like
	 * comparison, arithmetic, conversion and other mathematical alogrithms.
	 * The accuracy can be specified through the template parameter.
	 * Constraints on R: has to be either double or float */
	template <class R> class TVector3 : public TTuple3<R>
	{
	public:
		// constructors
		TVector3(R x = 0, R y = 0, R z = 0);
		TVector3(const R* tuple);
		TVector3(const TVector3& vector);

		// member access
		R X() const;
		R& X();
		R Y() const;
		R& Y();
		R Z() const;
		R& Z();

		// geometric operations
		R length() const;
		R squaredLength() const;
		R dot(const TVector3& vector) const;
		R normalize(); // returns the length of the vector
		static R Length(const TVector3& v);
		
		// specific geomteric operations
		TVector3 cross(const TVector3& vector) const;
		TVector3 unitCross(const TVector3& vector) const;
		
		static void Orthonormalize(TVector3& u, TVector3& v, TVector3& w);
		static void Orthonormalize(ArrayPtr<TVector3> vectors);
		static void GenerateOrthonormalBasis(TVector3& u, TVector3& v, TVector3& w,
			bool unitLength); // only u is given. v and w are filled with data

		//algebraic operations are delegated to tuple
		TVector3 operator+(const TVector3& tuple) const;
		TVector3 operator-(const TVector3& tuple) const;
		TVector3 operator*(R scalar) const;
		TVector3 operator/(R scalar) const;
		TVector3 operator-() const;
		TVector3& operator+=(const TVector3& tuple);
		TVector3& operator-=(const TVector3& tuple);
		TVector3& operator*=(R scalar);
		TVector3& operator/=(R scalar);

		DLL_ITEM static const TVector3 ZERO;
		DLL_ITEM static const TVector3 UNIT_X;
		DLL_ITEM static const TVector3 UNIT_Y;
		DLL_ITEM static const TVector3 UNIT_Z;
	};

	/* class TTuple3
	 * Implements a collection of three floating point values. This class can be used as 
	 * a baseclass for colors, tuples and other classes that rely on a tuple of 3 values.
	 * Constraints on R: has to be either double or float */
	template <class R> class TTuple4
	{
	protected:
		R m_tuple[4];
	public:
		// constructors
		TTuple4(R x = 0, R y = 0, R z = 0, R w = 0);
		TTuple4(const R* tuple);
		TTuple4(const TTuple4& tuple);

		void operator=(const TTuple4& tuple);

		// member access
		operator const R* () const;
		operator R*();
		R operator[] (int i) const;
		R& operator[] (int i);

		//comparison operators
		bool operator==(const TTuple4& tuple) const;
		bool operator!=(const TTuple4& tuple) const;
		bool operator<(const TTuple4& tuple) const;
		bool operator<=(const TTuple4& tuple) const;
		bool operator>(const TTuple4& tuple) const;
		bool operator>=(const TTuple4& tuple) const;

		//algebraic operations
		TTuple4 operator+(const TTuple4& tuple) const;
		TTuple4 operator-(const TTuple4& tuple) const;
		TTuple4 operator*(R scalar) const;
		TTuple4 operator/(R scalar) const;
		TTuple4 operator-() const;
		TTuple4& operator+=(const TTuple4& tuple);
		TTuple4& operator-=(const TTuple4& tuple);
		TTuple4& operator*=(R scalar);
		TTuple4& operator/=(R scalar);
	};


	/* class TVector4
	 * Implements a 3D-Vector with a lot of useful functionality, like
	 * comparison, arithmetic, conversion and other mathematical alogrithms.
	 * The accuracy can be specified through the template parameter.
	 * Constraints on R: has to be either double or float */
	template <class R> class TVector4 : public TTuple4<R>
	{
	public:
		// constructors
		TVector4(R x = 0, R y = 0, R z = 0, R w = 0);
		TVector4(const R* tuple);
		TVector4(const TVector4& vector);

		R X() const;
		R& X();
		R Y() const;
		R& Y();
		R Z() const;
		R& Z();
		R W() const;
		R& W();

		// geometric operations
		R length() const;
		R squaredLength() const;
		R dot(const TVector4& vector) const;
		R normalize(); // returns the length of the vector
		static R Length(const TVector4& v);

		//algebraic operations are delegated to tuple
		TVector4 operator+(const TVector4& tuple) const;
		TVector4 operator-(const TVector4& tuple) const;
		TVector4 operator*(R scalar) const;
		TVector4 operator/(R scalar) const;
		TVector4 operator-() const;
		TVector4& operator+=(const TVector4& tuple);
		TVector4& operator-=(const TVector4& tuple);
		TVector4& operator*=(R scalar);
		TVector4& operator/=(R scalar);

		DLL_ITEM static const TVector4 ZERO;
		DLL_ITEM static const TVector4 UNIT_X;
		DLL_ITEM static const TVector4 UNIT_Y;
		DLL_ITEM static const TVector4 UNIT_Z;
		DLL_ITEM static const TVector4 UNIT_W;
	};

	template <class R> TVector2<R> operator*(R scalar, const TVector2<R>& vector);
	template <class R> TVector3<R> operator*(R scalar, const TVector3<R>& vector);
	template <class R> TVector4<R> operator*(R scalar, const TVector4<R>& vector);

#include "lvector.inl"

	typedef TVector2<float> Vector2f;
	typedef Vector2f Vector2;
	typedef TVector2<double> Vector2d;
	typedef TVector3<float> Vector3f;
	typedef Vector3f Vector3;
	typedef TVector3<double> Vector3d;
	typedef TVector4<float> Vector4f;
	typedef Vector4f Vector4;
	typedef TVector4<double> Vector4d;
}


#endif
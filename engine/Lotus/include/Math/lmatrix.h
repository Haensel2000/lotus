/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LMATRIX_H
#define _HDR_LMATRIX_H

#include <math\lvector.h>
#include <math\lmath.h>

#define _MATRIX2_DIM 2
#define _MATRIX2_SQR_DIM 4
#define _MATRIX3_DIM 3
#define _MATRIX3_2DIM 6
#define _MATRIX3_SQR_DIM 9
#define _MATRIX4_DIM 4
#define _MATRIX4_2DIM 8
#define _MATRIX4_3DIM 12
#define _MATRIX4_SQR_DIM 16

namespace Lotus
{
	/* class TMatrix2
	 * Implements a 2x2 Matrix, that stores its values in a 1D-Array ordering
	 * the values in row major ordering.
	 * Constraints on R: has to be either double or float */
	template <class R> class TMatrix2
	{
	private:
		R m_val[_MATRIX2_SQR_DIM];
		int getRowIndex(int row) const;		
	public:
		// construction
		TMatrix2();
		TMatrix2(const TMatrix2& matrix);
		TMatrix2(bool zero);
		TMatrix2(R m_00, R m_01, R m_10, R m_11);
		TMatrix2(const R values[_MATRIX2_SQR_DIM], bool rowMajor = true);

		void toZero();
		void toIdentity();
		void toDiagonal(R x, R y);

		// assignment
		TMatrix2& operator=(const TMatrix2& matrix);

		// member access
		operator const R*() const;
		operator R*();
		const R* operator[] (int row) const;
		R* operator[] (int row);
		R operator() (int row, int col) const;
		R& operator() (int row, int col);
		void setRow(int row, const TVector2<R>& vector);
		TVector2<R> getRow(int row) const;
		void setColumn(int column, const TVector2<R>& vector);
		TVector2<R> getColumn(int column) const;
		void getColumnMajor(ArrayPtr<R> arr) const;

		// comparison operators
		bool operator==(const TMatrix2& matrix) const;
		bool operator!=(const TMatrix2& matrix) const;
		bool operator<(const TMatrix2& matrix) const;
		bool operator<=(const TMatrix2& matrix) const;
		bool operator>(const TMatrix2& matrix) const;
		bool operator>=(const TMatrix2& matrix) const;

		// arithmetic operations
		TMatrix2 operator+(const TMatrix2& matrix) const;
		TMatrix2 operator-(const TMatrix2& matrix) const;
		TMatrix2 operator*(const TMatrix2& matrix) const;
		TMatrix2 operator*(R scalar) const;
		TMatrix2 operator/(R scalar) const;
		TMatrix2 operator-() const;
		TMatrix2& operator+=(const TMatrix2& matrix);
		TMatrix2& operator-=(const TMatrix2& matrix);
		TMatrix2& operator*=(R scalar);
		TMatrix2& operator/=(R scalar);
		TVector2<R> operator*(const TVector2<R>& vector) const;

		// other operations
		TMatrix2 transpose() const;
		TMatrix2 transposeTimes(const TMatrix2& matrix) const;
		TMatrix2 timesTranspose(const TMatrix2& matrix) const;
		TMatrix2 timesDiagonal(const TVector2<R>& vector) const;
		TMatrix2 inverse() const;
		TMatrix2 adjoint() const;
		R determinant() const;
		R qForm(const TVector2<R>& u, const TVector2<R>& v) const;

		// dimension specific operations
		R getAngle() const;
		void orthonormalize();
		void eigenDecomposition(TMatrix2& rot, TMatrix2& diag) const;

		DLL_ITEM static const TMatrix2 ZERO;
		DLL_ITEM static const TMatrix2 IDENTITY;
	};

	/* class TMatrix3
	 * Implements a 3x3 Matrix, that stores its values in a 1D-Array ordering
	 * the values in row major ordering.
	 * Constraints on R: has to be either double or float */
	template <class R> class TMatrix3
	{
	private:
		R m_val[_MATRIX3_SQR_DIM];
		int getRowIndex(int row) const;
	public:
		// construction
		TMatrix3();
		TMatrix3(const TMatrix3& matrix);
		TMatrix3(bool zero);
		TMatrix3(R m_00, R m_01, R m_02, R m_10, R m_11, R m_12, R m_20, R m_21, R m_22);
		TMatrix3(const R values[_MATRIX3_SQR_DIM], bool rowMajor = true);

		void toZero();
		void toIdentity();
		void toDiagonal(R x, R y, R z);

		// assignment
		TMatrix3& operator=(const TMatrix3& matrix);

		// member access
		operator const R*() const;
		operator R*();
		const R* operator[] (int row) const;
		R* operator[] (int row);
		R operator() (int row, int col) const;
		R& operator() (int row, int col);
		void setRow(int row, const TVector3<R>& vector);
		TVector3<R> getRow(int row) const;
		void setColumn(int column, const TVector3<R>& vector);
		TVector3<R> getColumn(int column) const;
		void getColumnMajor(ArrayPtr<R> arr) const;

		// comparison operators
		bool operator==(const TMatrix3& matrix) const;
		bool operator!=(const TMatrix3& matrix) const;
		bool operator<(const TMatrix3& matrix) const;
		bool operator<=(const TMatrix3& matrix) const;
		bool operator>(const TMatrix3& matrix) const;
		bool operator>=(const TMatrix3& matrix) const;

		// arithmetic operations
		TMatrix3 operator+(const TMatrix3& matrix) const;
		TMatrix3 operator-(const TMatrix3& matrix) const;
		TMatrix3 operator*(const TMatrix3& matrix) const;
		TMatrix3 operator*(R scalar) const;
		TMatrix3 operator/(R scalar) const;
		TMatrix3 operator-() const;
		TMatrix3& operator+=(const TMatrix3& matrix);
		TMatrix3& operator-=(const TMatrix3& matrix);
		TMatrix3& operator*=(R scalar);
		TMatrix3& operator/=(R scalar);
		TVector3<R> operator*(const TVector3<R>& vector) const;

		// other operations
		TMatrix3 transpose() const;
		TMatrix3 transposeTimes(const TMatrix3& matrix) const;
		TMatrix3 timesTranspose(const TMatrix3& matrix) const;
		TMatrix3 timesDiagonal(const TVector3<R>& vector) const;
		TMatrix3 inverse() const;
		TMatrix3 adjoint() const;
		R determinant() const;
		R qForm(const TVector3<R>& u, const TVector3<R>& v) const;
		void decompose(TMatrix3& rotation, TVector3<R>& scale); 

		void eigenDecomposition (TMatrix3& rkRot, TMatrix3& rkDiag) const;
		bool Tridiagonalize (R afDiag[3], R afSubd[2]);
		bool QLAlgorithm (R afDiag[3], R afSubd[2]);
		TMatrix3& MakeDiagonal (R fM00, R fM11, R fM22);

		// dimension specific operations
		void getAxisAngle(TVector3<R>& vref, R& angle) const;
		void fromAxisAngle(const TVector3<R>& axis, R angle);
		void orthonormalize();

		static TMatrix3 Slerp(R t, const TMatrix3& begin, const TMatrix3& end);

		DLL_ITEM static const TMatrix3 ZERO;
		DLL_ITEM static const TMatrix3 IDENTITY;
	};

	/* class TMatrix4
	 * Implements a 4x4 Matrix, that stores its values in a 1D-Array ordering
	 * the values in row major ordering.
	 * Constraints on R: has to be either double or float */
	template <class R> class TMatrix4
	{
	private:
		R m_val[_MATRIX4_SQR_DIM];
		int getRowIndex(int row) const;
	public:
		// construction
		TMatrix4();
		TMatrix4(const TMatrix4& matrix);
		TMatrix4(bool zero);
		TMatrix4(R m_00, R m_01, R m_02, R m_03,
			     R m_10, R m_11, R m_12, R m_13,
				 R m_20, R m_21, R m_22, R m_23,
				 R m_30, R m_31, R m_32, R m_33);
		TMatrix4(const R values[_MATRIX4_SQR_DIM], bool rowMajor = true);

		void toZero();
		void toIdentity();
		void toDiagonal(R x, R y, R z, R w);

		// assignment
		TMatrix4& operator=(const TMatrix4& matrix);

		// member access
		operator const R*() const;
		operator R*();
		const R* operator[] (int row) const;
		R* operator[] (int row);
		R operator() (int row, int col) const;
		R& operator() (int row, int col);
		void setRow(int row, const TVector4<R>& vector);
		TVector4<R> getRow(int row) const;
		void setColumn(int column, const TVector4<R>& vector);
		TVector4<R> getColumn(int column) const;
		void getColumnMajor(ArrayPtr<R> arr) const;

		// comparison operators
		bool operator==(const TMatrix4& matrix) const;
		bool operator!=(const TMatrix4& matrix) const;
		bool operator<(const TMatrix4& matrix) const;
		bool operator<=(const TMatrix4& matrix) const;
		bool operator>(const TMatrix4& matrix) const;
		bool operator>=(const TMatrix4& matrix) const;

		// arithmetic operations
		TMatrix4 operator+(const TMatrix4& matrix) const;
		TMatrix4 operator-(const TMatrix4& matrix) const;
		TMatrix4 operator*(const TMatrix4& matrix) const;
		TMatrix4 operator*(R scalar) const;
		TMatrix4 operator/(R scalar) const;
		TMatrix4 operator-() const;
		TMatrix4& operator+=(const TMatrix4& matrix);
		TMatrix4& operator-=(const TMatrix4& matrix);
		TMatrix4& operator*=(R scalar);
		TMatrix4& operator/=(R scalar);
		TVector4<R> operator*(const TVector4<R>& vector) const;

		// other operations
		TMatrix4 transpose() const;
		TMatrix4 transposeTimes(const TMatrix4& matrix) const;
		TMatrix4 timesTranspose(const TMatrix4& matrix) const;
		TMatrix4 timesDiagonal(const TVector4<R>& matrix) const;
		TMatrix4 inverse() const;
		TMatrix4 adjoint() const;
		R determinant() const;
		R qForm(const TVector4<R>& u, const TVector4<R>& v) const;

		// dimension specific operations
		void toObliqueProjection (const TVector3<R>& normal, const TVector3<R>& point,
			const TVector3<R>& direction);
		void toPerspectiveProjection (const TVector3<R>& normal, const TVector3<R>& point,
			const TVector3<R>& eye);
		void toReflection (const TVector3<R>& normal, const TVector3<R>& point);

		DLL_ITEM static const TMatrix4 ZERO;
		DLL_ITEM static const TMatrix4 IDENTITY;

	};

	template <class R> TMatrix2<R> operator*(R scalar, 
		const TMatrix2<R>& matrix);
	template <class R> TVector2<R> operator*(const TVector2<R>& vector,
		const TMatrix2<R>& matrix);
	template <class R> TMatrix3<R> operator*(R scalar, 
		const TMatrix3<R>& matrix);
	template <class R> TVector3<R> operator*(const TVector3<R>& vector,
		const TMatrix3<R>& matrix);
	template <class R> TMatrix4<R> operator*(R scalar, 
		const TMatrix4<R>& matrix);
	template <class R> TVector4<R> operator*(const TVector4<R>& vector,
		const TMatrix4<R>& matrix);

	typedef TMatrix2<float> Matrix2f;
	typedef Matrix2f Matrix2;
	typedef TMatrix2<double> Matrix2d;
	typedef TMatrix3<float> Matrix3f;
	typedef Matrix3f Matrix3;
	typedef TMatrix3<double> Matrix3d;
	typedef TMatrix4<float> Matrix4f;
	typedef Matrix4f Matrix4;
	typedef TMatrix4<double> Matrix4d;

#include "lmatrix.inl"
}

#endif
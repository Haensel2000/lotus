/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* Operators:                                              */
/*                                                         */
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> operator*(R scalar, 
	const TMatrix2<R>& matrix)
{
	return matrix * scalar;
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> operator*(const TVector2<R>& v,
	const TMatrix2<R>& m)
{
	return TVector2<R>(v[0]*m[0][0] + v[1]*m[1][0],
					   v[0]*m[0][1] + v[1]*m[1][1]);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> operator*(R scalar, 
	const TMatrix3<R>& matrix)
{
	return matrix * scalar;
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> operator*(const TVector3<R>& v,
	const TMatrix3<R>& m)
{
	return TVector3<R>(
		v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0],
		v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1],
		v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> operator*(R scalar, 
	const TMatrix4<R>& matrix)
{
	return matrix * scalar;
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> operator*(const TVector4<R>& v,
	const TMatrix4<R>& m)
{
	return TVector4<R>(
		v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0] + v[3]*m[3][0],
		v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1] + v[3]*m[3][1],
		v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] + v[3]*m[3][2],
		v[0]*m[0][3] + v[1]*m[1][3] + v[2]*m[2][3] + v[3]*m[3][3] );
}
/* ------------------------------------------------------- */
/* class TMatrix2:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::TMatrix2()
{
	memset(&m_val, 0, _MATRIX2_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::TMatrix2(const TMatrix2<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::TMatrix2(bool zero)
{
	if (zero) 
	{
		memset(&m_val, 0, _MATRIX2_SQR_DIM*sizeof(R));
	}
	else
	{
		toIdentity();
	}
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::TMatrix2(R m_00, R m_01, R m_10, R m_11)
{
	m_val[0] = m_00; m_val[1] = m_01;
	m_val[2] = m_10; m_val[3] = m_11;
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::TMatrix2(const R values[4], bool rowMajor)
{
	if (rowMajor)
	{
		memcpy(&m_val, &values, _MATRIX2_SQR_DIM*sizeof(R));
	}
	else
	{
		m_val[0] = values[0]; m_val[1] = values[2];		
		m_val[2] = values[1]; m_val[3] = values[3];
		
	}
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::toZero()
{
	memset(&m_val, 0, _MATRIX2_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::toIdentity()
{
	toDiagonal(1, 1);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::toDiagonal(R x, R y)
{
	m_val[0] = x; m_val[1] = 0;
	m_val[2] = 0; m_val[2] = y; 
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>& TMatrix2<R>::operator=(const TMatrix2<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R));
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::operator const R*() const
{
	return &m_val[0];
} 
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>::operator R*()
{
	return &m_val[0];
}
/* ------------------------------------------------------- */
template <class R> const R* TMatrix2<R>::operator[] (int row) const
{
	assert(row < _MATRIX2_DIM && row >= 0);
	return &m_tuple[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R* TMatrix2<R>::operator[] (int row)
{
	assert(row < _MATRIX2_DIM && row >= 0);
	return &m_tuple[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R TMatrix2<R>::operator() (int row, int col) const
{
	assert(row < _MATRIX2_DIM && col < _MATRIX2_DIM && row >= 0 && col >= 0);
	return m_val[col + getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R& TMatrix2<R>::operator() (int row, int col)
{
	assert(row < _MATRIX2_DIM && col < _MATRIX2_DIM && row >= 0 && col >= 0);
	return m_val[col + getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::setRow(int row, const TVector2<R>& vector)
{
	assert(row < _MATRIX2_DIM && row >= 0);
	int pos = getRowIndex(row);
	m_val[pos] = vector[0];
	m_val[pos+1] = vector[1];
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TMatrix2<R>::getRow(int row) const
{
	assert(row < _MATRIX2_DIM && row >= 0);
	int pos = getRowIndex(row);
	return TVector2<R>(m_val[pos], m_val[pos+1]);
}
/* ------------------------------------------------------- */
template <class R> 
void TMatrix2<R>::setColumn(int column, 
							const TVector2<R>& vector)
{
	assert(column < _MATRIX2_DIM && column >= 0);
	m_val[column] = vector[0];
	m_val[column + _MATRIX2_DIM] = vector[1]; 
}
/* ------------------------------------------------------- */
template <class R> TVector2<R> TMatrix2<R>::getColumn(int column) const
{
	assert(column < 2 && column >= 0);
	return TVector2<R>(m_val[column], m_val[column + _MATRIX2_DIM]);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::getColumnMajor(ArrayPtr<R> arr) const
{
	assert(arr.size() == _MATRIX2_SQR_DIM);
	arr[0] = m_val[0]; arr[2] = m_val[1];
	arr[1] = m_val[2]; arr[3] = m_val[3];
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator==(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator!=(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator<(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator<=(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator>(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix2<R>::operator>=(const TMatrix2<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX2_SQR_DIM*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix2<R> TMatrix2<R>::operator+(const TMatrix2<R>& matrix) const
{
	return TMatrix2( m_val[0] + matrix.m_val[0],
					 m_val[1] + matrix.m_val[1],
					 m_val[2] + matrix.m_val[2],
					 m_val[3] + matrix.m_val[3]);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix2<R> TMatrix2<R>::operator-(const TMatrix2<R>& matrix) const
{
	return TMatrix2( m_val[0] - matrix.m_val[0],
					 m_val[1] - matrix.m_val[1],
					 m_val[2] - matrix.m_val[2],
					 m_val[3] - matrix.m_val[3]);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix2<R> TMatrix2<R>::operator*(const TMatrix2<R>& m) const
{
	return TMatrix2( m_val[0]*m.m_val[0] + m_val[1]*m.m_val[2],
					 m_val[0]*m.m_val[1] + m_val[1]*m.m_val[3],
					 m_val[2]*m.m_val[0] + m_val[3]*m.m_val[2],
					 m_val[2]*m.m_val[1] + m_val[3]*m.m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::operator*(R scalar) const
{
	return TMatrix2( m_val[0]*scalar, m_val[1]*scalar,
					 m_val[2]*scalar, m_val[3]*scalar );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::operator/(R scalar) const
{
	R invScalar = ((R)1.0)/scalar;
	return operator*(invScalar);
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::operator-() const
{
	return TMatrix2( -m_val[0], -m_val[1],
					 -m_val[2], -m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix2<R>& TMatrix2<R>::operator+=(const TMatrix2<R>& matrix)
{
	m_val[0] += matrix.m_val[0]; m_val[1] += matrix.m_val[1];
	m_val[2] += matrix.m_val[2]; m_val[3] += matrix.m_val[3];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix2<R>& TMatrix2<R>::operator-=(const TMatrix2<R>& matrix)
{
	m_val[0] -= matrix.m_val[0]; m_val[1] -= matrix.m_val[1];
	m_val[2] -= matrix.m_val[2]; m_val[3] -= matrix.m_val[3];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>& TMatrix2<R>::operator*=(R scalar)
{
	m_val[0] *= scalar; m_val[1] *= scalar;
	m_val[2] *= scalar; m_val[3] *= scalar;	
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R>& TMatrix2<R>::operator/=(R scalar)
{
	R invScalar = ((R)1.0)/scalar;
	operator*=(invScalar);
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TVector2<R> TMatrix2<R>::operator*(const TVector2<R>& v) const
{
	return TVector2<R>(	m_val[0]*v[0] + m_val[1]*v[1],
						m_val[2]*v[0] + m_val[3]*v[1] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::transpose() const
{
	return TMatrix2( m_val[0], m_val[2],
					 m_val[1], m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::transposeTimes(const TMatrix2<R>& m) const
{
	return TMatrix2( m_val[0]*m.m_val[0] + m_val[2]*m.m_val[2],
					 m_val[0]*m.m_val[1] + m_val[2]*m.m_val[3],
					 m_val[1]*m.m_val[0] + m_val[3]*m.m_val[2],
					 m_val[1]*m.m_val[1] + m_val[3]*m.m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::timesTranspose(const TMatrix2<R>& m) const
{
	return TMatrix2( m_val[0]*m.m_val[0] + m_val[1]*m.m_val[1],
					 m_val[0]*m.m_val[2] + m_val[1]*m.m_val[3],
					 m_val[2]*m.m_val[0] + m_val[3]*m.m_val[1],
					 m_val[2]*m.m_val[2] + m_val[3]*m.m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::timesDiagonal(const TVector2<R>& v) const
{
	return TMatrix2<R>( m_val[0]*v[0], m_val[1]*v[1],
						m_val[2]*v[0], m_val[3]*v[1] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::inverse() const
{
	TMatrix2 inv = adjoint();
    R det = determinant();
    if ( Math<R>::FAbs(det) > Math<R>::ZERO_TOLERANCE )
    {
        inv /= det;
    }
    else
    {
		inv.toZero();
    }

    return inv;
}
/* ------------------------------------------------------- */
template <class R> TMatrix2<R> TMatrix2<R>::adjoint() const
{
	return TMatrix2(  m_val[3], -m_val[1],
					 -m_val[2],  m_val[0] );
}
/* ------------------------------------------------------- */
template <class R> R TMatrix2<R>::determinant() const
{
	return m_val[0]*m_val[3] - m_val[1]*m_val[2];
}
/* ------------------------------------------------------- */
template <class R> R TMatrix2<R>::qForm(const TVector2<R>& u, const TVector2<R>& v) const
{
	return u.dot(operator*(v));
}
/* ------------------------------------------------------- */
template <class R> R TMatrix2<R>::getAngle() const
{
	return Math<R>::ATan2(m_val[2], m_val[0]);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::orthonormalize()
{
	TVector2<R> u = getColumn(0);
	TVector2<R> v = getColumn(1);
	TVector2<R>::Orthonormalize(u, v);
	setColumn(0, u);
	setColumn(1, v);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix2<R>::eigenDecomposition(TMatrix2& rot, TMatrix2& diag) const
{
	R trace = m_val[0] + m_val[3];
    R diff = m_val[0] - m_val[3];
    R discr = Math<R>::Sqrt(diff*diff + ((R)4.0)*m_val[1]*m_val[1]);
    R eval0 = ((R)0.5) * (trace-discr);
    R eval1 = ((R)0.5) * (trace+discr);
    diag.toDiagonal(eval0, eval1);

    R lcos, lsin;
    if ( diff >= (R)0.0 )
    {
        lcos = m_val[1];
        lsin = eval0 - m_val[0];
    }
    else
    {
        lcos = eval0 - m_val[3];
        lsin = m_val[1];
    }
    R tmp = Math<R>::InvSqrt(lcos*lcos + lsin*lsin);
    lcos *= tmp;
    lsin *= tmp;

    rot.m_val[0] = lcos;
    rot.m_val[1] = -lsin;
    rot.m_val[2] = lsin;
    rot.m_val[3] = lcos;
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
template <class R> int TMatrix2<R>::getRowIndex(int row) const
{
	return row<<1;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TMatrix3:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::TMatrix3()
{
	memset(&m_val, 0, _MATRIX3_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::TMatrix3(const TMatrix3<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::TMatrix3(bool zero)
{
	if (zero) 
	{
		memset(&m_val, 0, _MATRIX3_SQR_DIM*sizeof(R));
	}
	else
	{
		toIdentity();
	}
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R>::TMatrix3(R m_00, R m_01, R m_02, R m_10, R m_11, R m_12, R m_20, R m_21, R m_22)
{
	m_val[0] = m_00; m_val[1] = m_01; m_val[2] = m_02;
	m_val[3] = m_10; m_val[4] = m_11; m_val[5] = m_12;
	m_val[6] = m_20; m_val[7] = m_21; m_val[8] = m_22;
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::TMatrix3(const R values[9], bool rowMajor)
{
	if (rowMajor)
	{
		memcpy(&m_val, &values, _MATRIX3_SQR_DIM*sizeof(R));
	}
	else
	{
		m_val[0] = values[0]; m_val[1] = values[3]; m_val[2] = values[6];
		m_val[3] = values[1]; m_val[4] = values[4]; m_val[5] = values[7];
		m_val[6] = values[2]; m_val[7] = values[5]; m_val[8] = values[8];		
	}
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::toZero()
{
	memset(&m_val, 0, _MATRIX3_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::toIdentity()
{
	toDiagonal(1, 1, 1);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::toDiagonal(R x, R y, R z)
{
	m_val[0] = x; m_val[1] = 0; m_val[2] = 0;
	m_val[3] = 0; m_val[4] = y; m_val[5] = 0;
	m_val[6] = 0; m_val[7] = 0; m_val[8] = z;	 
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>& TMatrix3<R>::operator=(const TMatrix3<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R));
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::operator const R*() const
{
	return &m_val[0];
} 
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>::operator R*()
{
	return &m_val[0];
}
/* ------------------------------------------------------- */
template <class R> const R* TMatrix3<R>::operator[] (int row) const
{
	assert(row < _MATRIX3_DIM && row >= 0);
	return &m_val[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R* TMatrix3<R>::operator[] (int row)
{
	assert(row < _MATRIX3_DIM && row >= 0);
	return &m_val[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R TMatrix3<R>::operator() (int row, int col) const
{
	assert(row < _MATRIX3_DIM && col < _MATRIX3_DIM && row >= 0 && col >= 0);
	return m_val[col + (getRowIndex(row))];
}
/* ------------------------------------------------------- */
template <class R> R& TMatrix3<R>::operator() (int row, int col)
{
	assert(row < _MATRIX3_DIM && col < _MATRIX3_DIM && row >= 0 && col >= 0);
	return m_val[col + (getRowIndex(row))];
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::setRow(int row, const TVector3<R>& vector)
{
	assert(row < _MATRIX3_DIM && row >= 0);
	int pos = getRowIndex(row);
	m_val[pos] = vector[0];
	m_val[pos+1] = vector[1];
	m_val[pos+2] = vector[2];
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TMatrix3<R>::getRow(int row) const
{
	assert(row < _MATRIX3_DIM && row >= 0);
	int pos = getRowIndex(row);
	return TVector3<R>(m_val[pos], m_val[pos+1], m_val[pos+2]);
}
/* ------------------------------------------------------- */
template <class R> 
void TMatrix3<R>::setColumn(int column, 
							const TVector3<R>& vector)
{
	assert(column < _MATRIX3_DIM && column >= 0);
	m_val[column] = vector[0];
	m_val[column + _MATRIX3_DIM] = vector[1]; 
	m_val[column + _MATRIX3_2DIM] = vector[2]; 
}
/* ------------------------------------------------------- */
template <class R> TVector3<R> TMatrix3<R>::getColumn(int column) const
{
	assert(column < _MATRIX3_DIM && column >= 0);
	return TVector3<R>(m_val[column], m_val[column + _MATRIX3_DIM],
		m_val[column + _MATRIX3_2DIM]);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::getColumnMajor(ArrayPtr<R> arr) const
{
	assert(arr.size() == _MATRIX3_SQR_DIM);
	arr[0] = m_val[0]; arr[1] = m_val[3]; arr[2] = m_val[6];
	arr[3] = m_val[1]; arr[4] = m_val[4]; arr[5] = m_val[7];
	arr[6] = m_val[2]; arr[7] = m_val[5]; arr[8] = m_val[8];
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator==(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator!=(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator<(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator<=(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator>(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::operator>=(const TMatrix3<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX3_SQR_DIM*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R> TMatrix3<R>::operator+(const TMatrix3<R>& matrix) const
{
	return TMatrix3( m_val[0] + matrix.m_val[0],
					 m_val[1] + matrix.m_val[1],
					 m_val[2] + matrix.m_val[2],
					 m_val[3] + matrix.m_val[3],
					 m_val[4] + matrix.m_val[4],
					 m_val[5] + matrix.m_val[5],
					 m_val[6] + matrix.m_val[6],
					 m_val[7] + matrix.m_val[7],
					 m_val[8] + matrix.m_val[8]);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R> TMatrix3<R>::operator-(const TMatrix3<R>& matrix) const
{
	return TMatrix3( m_val[0] - matrix.m_val[0],
					 m_val[1] - matrix.m_val[1],
					 m_val[2] - matrix.m_val[2],
					 m_val[3] - matrix.m_val[3],
					 m_val[4] - matrix.m_val[4],
					 m_val[5] - matrix.m_val[5],
					 m_val[6] - matrix.m_val[6],
					 m_val[7] - matrix.m_val[7],
					 m_val[8] - matrix.m_val[8]);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R> TMatrix3<R>::operator*(const TMatrix3<R>& m) const
{
	return TMatrix3( 
		 m_val[0]*m.m_val[0] + m_val[1]*m.m_val[3] + m_val[2]*m.m_val[6],
		 m_val[0]*m.m_val[1] + m_val[1]*m.m_val[4] + m_val[2]*m.m_val[7],
		 m_val[0]*m.m_val[2] + m_val[1]*m.m_val[5] + m_val[2]*m.m_val[8],
		 m_val[3]*m.m_val[0] + m_val[4]*m.m_val[3] + m_val[5]*m.m_val[6],
		 m_val[3]*m.m_val[1] + m_val[4]*m.m_val[4] + m_val[5]*m.m_val[7],
		 m_val[3]*m.m_val[2] + m_val[4]*m.m_val[5] + m_val[5]*m.m_val[8],
		 m_val[6]*m.m_val[0] + m_val[7]*m.m_val[3] + m_val[8]*m.m_val[6],
		 m_val[6]*m.m_val[1] + m_val[7]*m.m_val[4] + m_val[8]*m.m_val[7],
		 m_val[6]*m.m_val[2] + m_val[7]*m.m_val[5] + m_val[8]*m.m_val[8]);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::operator*(R scalar) const
{
	return TMatrix3( m_val[0]*scalar, m_val[1]*scalar, m_val[2]*scalar,
					 m_val[3]*scalar, m_val[4]*scalar, m_val[5]*scalar,
					 m_val[6]*scalar, m_val[7]*scalar, m_val[8]*scalar );
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::operator/(R scalar) const
{
	R invScalar = ((R)1.0)/scalar;
	return operator*(invScalar);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::operator-() const
{
	return TMatrix3( -m_val[0], -m_val[1], -m_val[2],
					 -m_val[3], -m_val[4], -m_val[5],
					 -m_val[6], -m_val[7], -m_val[8] );
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R>& TMatrix3<R>::operator+=(const TMatrix3<R>& m)
{
	m_val[0] += m.m_val[0]; m_val[1] += m.m_val[1]; m_val[2] += m.m_val[2];
	m_val[3] += m.m_val[3]; m_val[4] += m.m_val[4]; m_val[5] += m.m_val[5];
	m_val[6] += m.m_val[6]; m_val[7] += m.m_val[7]; m_val[8] += m.m_val[8];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R>& TMatrix3<R>::operator-=(const TMatrix3<R>& matrix)
{
	m_val[0] -= m.m_val[0]; m_val[1] -= m.m_val[1]; m_val[2] -= m.m_val[2];
	m_val[3] -= m.m_val[3]; m_val[4] -= m.m_val[4]; m_val[5] -= m.m_val[5];
	m_val[6] -= m.m_val[6]; m_val[7] -= m.m_val[7]; m_val[8] -= m.m_val[8];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>& TMatrix3<R>::operator*=(R scalar)
{
	m_val[0] *= scalar; m_val[1] *= scalar; m_val[2] *= scalar;
	m_val[3] *= scalar; m_val[4] *= scalar; m_val[5] *= scalar;
	m_val[6] *= scalar; m_val[7] *= scalar; m_val[8] *= scalar;
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R>& TMatrix3<R>::operator/=(R scalar)
{
	R invScalar = ((R)1.0)/scalar;
	operator*=(invScalar);
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TVector3<R> TMatrix3<R>::operator*(const TVector3<R>& v) const
{
	return TVector3<R>(	m_val[0]*v[0] + m_val[1]*v[1] + m_val[2]*v[2],
						m_val[3]*v[0] + m_val[4]*v[1] + m_val[5]*v[2],
						m_val[6]*v[0] + m_val[7]*v[1] + m_val[8]*v[2] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::transpose() const
{
	return TMatrix3( m_val[0], m_val[3], m_val[6],
					 m_val[1], m_val[4], m_val[7],
					 m_val[2], m_val[5], m_val[8] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::transposeTimes(const TMatrix3<R>& matrix) const
{
	// The result of this operation is a symmetric matrix:
	R v1 = m_val[0]*m.m_val[1] + m_val[3]*m.m_val[4] + m_val[6]*m.m_val[7];
	R v2 = m_val[0]*m.m_val[2] + m_val[3]*m.m_val[5] + m_val[6]*m.m_val[8];
	R v5 = m_val[1]*m.m_val[2] + m_val[4]*m.m_val[5] + m_val[7]*m.m_val[8];
	R d1 = m_val[0]*m.m_val[0] + m_val[3]*m.m_val[3] + m_val[6]*m.m_val[6];
	R d2 = m_val[1]*m.m_val[1] + m_val[4]*m.m_val[4] + m_val[7]*m.m_val[7];
	R d3 = m_val[2]*m.m_val[2] + m_val[5]*m.m_val[5] + m_val[8]*m.m_val[8];
	return TMatrix3( d1, v1, v2,
					 v1, d2, v5,
					 v2, v5, d3 );
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::timesTranspose(const TMatrix3<R>& matrix) const
{
	// The result of this operation is a symmetric matrix:
	R v1 = m_val[0]*m.m_val[3] + m_val[1]*m.m_val[4] + m_val[2]*m.m_val[5];
	R v2 = m_val[0]*m.m_val[6] + m_val[1]*m.m_val[7] + m_val[2]*m.m_val[8];
	R v5 = m_val[3]*m.m_val[6] + m_val[4]*m.m_val[7] + m_val[5]*m.m_val[8];
	R d1 = m_val[0]*m.m_val[0] + m_val[1]*m.m_val[1] + m_val[2]*m.m_val[2];
	R d2 = m_val[3]*m.m_val[3] + m_val[4]*m.m_val[4] + m_val[5]*m.m_val[5];
	R d3 = m_val[6]*m.m_val[6] + m_val[7]*m.m_val[7] + m_val[8]*m.m_val[8];
	return TMatrix3( d1, v1, v2,
					 v1, d2, v5,
					 v2, v5, d3 );
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::timesDiagonal(const TVector3<R>& v) const
{
	return TMatrix3<R>( m_val[0]*v[0], m_val[1]*v[1], m_val[2]*v[2],
						m_val[3]*v[0], m_val[4]*v[1], m_val[5]*v[2],
						m_val[6]*v[0], m_val[7]*v[1], m_val[8]*v[2]);
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::inverse() const
{
	TMatrix3 inv = adjoint();
    R det = m_val[0]*inv.m_val[0] + 
			m_val[1]*inv.m_val[3] +
			m_val[2]*inv.m_val[6];
    if ( Math<R>::FAbs(det) > Math<R>::ZERO_TOLERANCE )
    {
        inv /= det;
    }
    else
    {
		inv.toZero();
    }

    return inv;
}
/* ------------------------------------------------------- */
template <class R> TMatrix3<R> TMatrix3<R>::adjoint() const
{
    return TMatrix3( m_val[4]*m_val[8] - m_val[5]*m_val[7],
					 m_val[2]*m_val[7] - m_val[1]*m_val[8],
					 m_val[1]*m_val[5] - m_val[2]*m_val[4],
					 m_val[5]*m_val[6] - m_val[3]*m_val[8],
					 m_val[0]*m_val[8] - m_val[2]*m_val[6],
					 m_val[2]*m_val[3] - m_val[0]*m_val[5],
					 m_val[3]*m_val[7] - m_val[4]*m_val[6],
					 m_val[1]*m_val[6] - m_val[0]*m_val[7],
					 m_val[0]*m_val[4] - m_val[1]*m_val[3] );
}
/* ------------------------------------------------------- */
template <class R> R TMatrix3<R>::determinant() const
{
	R cof_00 = m_val[4]*m_val[8] - m_val[5]*m_val[7];
    R cof_10 = m_val[5]*m_val[6] - m_val[3]*m_val[8];
    R cof_20 = m_val[3]*m_val[7] - m_val[4]*m_val[6];
    return m_val[0]*cof_00 + m_val[1]*cof_10 + m_val[2]*cof_20;
}
/* ------------------------------------------------------- */
template <class R> R TMatrix3<R>::qForm(const TVector3<R>& u, const TVector3<R>& v) const
{
	return u.dot(operator*(v));
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::decompose(TMatrix3& rotation, TVector3<R>& scale)
{
	R invCol[3];
	scale[0] = getColumn(0).length();
	scale[1] = getColumn(1).length();
	scale[2] = getColumn(2).length();

	invCol[0] = ((R)1.0)/scale[0];
	invCol[1] = ((R)1.0)/scale[1];
	invCol[2] = ((R)1.0)/scale[2];

	rotation = *this;
	rotation.m_val[0] *= invCol[0]; rotation.m_val[1] *= invCol[1]; rotation.m_val[2] *= invCol[2];
	rotation.m_val[3] *= invCol[0]; rotation.m_val[4] *= invCol[1]; rotation.m_val[5] *= invCol[2];
	rotation.m_val[6] *= invCol[0]; rotation.m_val[7] *= invCol[1]; rotation.m_val[8] *= invCol[2];

	//if (determinant() < (R)0.0)
	//	scale[0] = -scale[0];
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::eigenDecomposition (TMatrix3<R>& rkRot, TMatrix3<R>& rkDiag) const
{
    // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    R afDiag[3], afSubd[2];
    rkRot = *this;
    bool bReflection = rkRot.Tridiagonalize(afDiag,afSubd);
    bool bConverged = rkRot.QLAlgorithm(afDiag,afSubd);
    assert( bConverged );

    // (insertion) sort eigenvalues in increasing order, d0 <= d1 <= d2
    int i;
    R fSave;

    if ( afDiag[1] < afDiag[0] )
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
        bReflection = !bReflection;
    }

    if ( afDiag[2] < afDiag[1] )
    {
        // swap d1 and d2
        fSave = afDiag[1];
        afDiag[1] = afDiag[2];
        afDiag[2] = fSave;

        // swap V1 and V2
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][1];
            rkRot[i][1] = rkRot[i][2];
            rkRot[i][2] = fSave;
        }
        bReflection = !bReflection;
    }

    if ( afDiag[1] < afDiag[0] )
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
        bReflection = !bReflection;
    }

    rkDiag.MakeDiagonal(afDiag[0],afDiag[1],afDiag[2]);

    if ( bReflection )
    {
        // The orthogonal transformation that diagonalizes M is a reflection.
        // Make the eigenvectors a right--handed system by changing sign on
        // the last column.
        rkRot[0][2] = -rkRot[0][2];
        rkRot[1][2] = -rkRot[1][2];
        rkRot[2][2] = -rkRot[2][2];
    }
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix3<R>::Tridiagonalize (R afDiag[3], R afSubd[2])
{
    // Householder reduction T = Q^t M Q
    //   Input:   
    //     mat, symmetric 3x3 matrix M
    //   Output:  
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    R fM00 = m_val[0];
    R fM01 = m_val[1];
    R fM02 = m_val[2];
    R fM11 = m_val[4];
    R fM12 = m_val[5];
    R fM22 = m_val[8];

    afDiag[0] = fM00;
    if ( Math<R>::FAbs(fM02) >= Math<R>::ZERO_TOLERANCE )
    {
        afSubd[0] = Math<R>::Sqrt(fM01*fM01+fM02*fM02);
        R fInvLength = ((R)1.0)/afSubd[0];
        fM01 *= fInvLength;
        fM02 *= fInvLength;
        R fTmp = ((R)2.0)*fM01*fM12+fM02*(fM22-fM11);
        afDiag[1] = fM11+fM02*fTmp;
        afDiag[2] = fM22-fM02*fTmp;
        afSubd[1] = fM12-fM01*fTmp;

        m_val[0] = (R)1.0;
        m_val[1] = (R)0.0;
        m_val[2] = (R)0.0;
        m_val[3] = (R)0.0;
        m_val[4] = fM01;
        m_val[5] = fM02;
        m_val[6] = (R)0.0;
        m_val[7] = fM02;
        m_val[8] = -fM01;
        return true;
    }
    else
    {
        afDiag[1] = fM11;
        afDiag[2] = fM22;
        afSubd[0] = fM01;
        afSubd[1] = fM12;

        m_val[0] = (R)1.0;
        m_val[1] = (R)0.0;
        m_val[2] = (R)0.0;
        m_val[3] = (R)0.0;
        m_val[4] = (R)1.0;
        m_val[5] = (R)0.0;
        m_val[6] = (R)0.0;
        m_val[7] = (R)0.0;
        m_val[8] = (R)1.0;
        return false;
    }
}
//----------------------------------------------------------------------------
template <class R> bool TMatrix3<R>::QLAlgorithm (R afDiag[3], R afSubd[2])
{
    // This is an implementation of the symmetric QR algorithm from the book
    // "Matrix Computations" by Gene H. Golub and Charles F. Van Loan, second
    // edition.  The algorithm is 8.2.3.  The implementation has a slight
    // variation to actually make it a QL algorithm, and it traps the case
    // when either of the subdiagonal terms s0 or s1 is zero and reduces the
    // 2-by-2 subblock directly.

    const int iMax = 32;
    for (int i = 0; i < iMax; i++)
    {
        R fSum, fDiff, fDiscr, fEValue0, fEValue1, fCos, fSin, fTmp;
        int iRow;

        fSum = Math<R>::FAbs(afDiag[0]) + Math<R>::FAbs(afDiag[1]);
        if ( Math<R>::FAbs(afSubd[0]) + fSum == fSum )
        {
            // The matrix is effectively
            //       +-        -+
            //   M = | d0  0  0 |
            //       | 0  d1 s1 |
            //       | 0  s1 d2 |
            //       +-        -+

            // Compute the eigenvalues as roots of a quadratic equation.
            fSum = afDiag[1] + afDiag[2];
            fDiff = afDiag[1] - afDiag[2];
            fDiscr = Math<R>::Sqrt(fDiff*fDiff +
                ((R)4.0)*afSubd[1]*afSubd[1]);
            fEValue0 = ((R)0.5)*(fSum - fDiscr);
            fEValue1 = ((R)0.5)*(fSum + fDiscr);

            // Compute the Givens rotation.
            if ( fDiff >= (R)0.0 )
            {
                fCos = afSubd[1];
                fSin = afDiag[1] - fEValue0;
            }
            else
            {
                fCos = afDiag[2] - fEValue0;
                fSin = afSubd[1];
            }
            fTmp = Math<R>::InvSqrt(fCos*fCos + fSin*fSin);
            fCos *= fTmp;
            fSin *= fTmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (iRow = 0; iRow < 3; iRow++)
            {
                fTmp = m_val[getRowIndex(iRow) + 2];
                m_val[getRowIndex(iRow) + 2] = fSin*m_val[getRowIndex(iRow) + 1] + fCos*fTmp;
                m_val[getRowIndex(iRow) + 1] = fCos*m_val[getRowIndex(iRow) + 1] - fSin*fTmp;
            }

            // Update the tridiagonal matrix.
            afDiag[1] = fEValue0;
            afDiag[2] = fEValue1;
            afSubd[0] = (R)0.0;
            afSubd[1] = (R)0.0;
            return true;
        }

        fSum = Math<R>::FAbs(afDiag[1]) + Math<R>::FAbs(afDiag[2]);
        if ( Math<R>::FAbs(afSubd[1]) + fSum == fSum )
        {
            // The matrix is effectively
            //       +-         -+
            //   M = | d0  s0  0 |
            //       | s0  d1  0 |
            //       | 0   0  d2 |
            //       +-         -+

            // Compute the eigenvalues as roots of a quadratic equation.
            fSum = afDiag[0] + afDiag[1];
            fDiff = afDiag[0] - afDiag[1];
            fDiscr = Math<R>::Sqrt(fDiff*fDiff +
                ((R)4.0)*afSubd[0]*afSubd[0]);
            fEValue0 = ((R)0.5)*(fSum - fDiscr);
            fEValue1 = ((R)0.5)*(fSum + fDiscr);

            // Compute the Givens rotation.
            if ( fDiff >= (R)0.0 )
            {
                fCos = afSubd[0];
                fSin = afDiag[0] - fEValue0;
            }
            else
            {
                fCos = afDiag[1] - fEValue0;
                fSin = afSubd[0];
            }
            fTmp = Math<R>::InvSqrt(fCos*fCos + fSin*fSin);
            fCos *= fTmp;
            fSin *= fTmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (iRow = 0; iRow < 3; iRow++)
            {
                fTmp = m_val[getRowIndex(iRow) + 1];
                m_val[getRowIndex(iRow) + 1] = fSin*m_val[getRowIndex(iRow)] + fCos*fTmp;
                m_val[getRowIndex(iRow)] = fCos*m_val[getRowIndex(iRow)] - fSin*fTmp;
            }

            // Update the tridiagonal matrix.
            afDiag[0] = fEValue0;
            afDiag[1] = fEValue1;
            afSubd[0] = (R)0.0;
            afSubd[1] = (R)0.0;
            return true;
        }

        // The matrix is
        //       +-        -+
        //   M = | d0 s0  0 |
        //       | s0 d1 s1 |
        //       | 0  s1 d2 |
        //       +-        -+

        // Set up the parameters for the first pass of the QL step.  The
        // value for A is the difference between diagonal term D[2] and the
        // implicit shift suggested by Wilkinson.
        R fRatio = (afDiag[1]-afDiag[0])/(((R)2.0f)*afSubd[0]);
        R fRoot = Math<R>::Sqrt((R)1.0 + fRatio*fRatio);
        R fB = afSubd[1];
        R fA = afDiag[2] - afDiag[0];
        if ( fRatio >= (R)0.0 )
            fA += afSubd[0]/(fRatio + fRoot);
        else
            fA += afSubd[0]/(fRatio - fRoot);

        // Compute the Givens rotation for the first pass.
        if ( Math<R>::FAbs(fB) >= Math<R>::FAbs(fA) )
        {
            fRatio = fA/fB;
            fSin = Math<R>::InvSqrt((R)1.0 + fRatio*fRatio);
            fCos = fRatio*fSin;
        }
        else
        {
            fRatio = fB/fA;
            fCos = Math<R>::InvSqrt((R)1.0 + fRatio*fRatio);
            fSin = fRatio*fCos;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (iRow = 0; iRow < 3; iRow++)
        {
            fTmp = m_val[getRowIndex(iRow) + 2];
            m_val[getRowIndex(iRow) + 2] = fSin*m_val[getRowIndex(iRow) + 1]+fCos*fTmp;
            m_val[getRowIndex(iRow) + 1] = fCos*m_val[getRowIndex(iRow) + 1]-fSin*fTmp;
        }

        // Set up the parameters for the second pass of the QL step.  The
        // values tmp0 and tmp1 are required to fully update the tridiagonal
        // matrix at the end of the second pass.
        R fTmp0 = (afDiag[1] - afDiag[2])*fSin +
            ((R)2.0)*afSubd[1]*fCos;
        R fTmp1 = fCos*afSubd[0];
        fB = fSin*afSubd[0];
        fA = fCos*fTmp0 - afSubd[1];
        fTmp0 *= fSin;

        // Compute the Givens rotation for the second pass.  The subdiagonal
        // term S[1] in the tridiagonal matrix is updated at this time.
        if ( Math<R>::FAbs(fB) >= Math<R>::FAbs(fA) )
        {
            fRatio = fA/fB;
            fRoot = Math<R>::Sqrt((R)1.0 + fRatio*fRatio);
            afSubd[1] = fB*fRoot;
            fSin = ((R)1.0)/fRoot;
            fCos = fRatio*fSin;
        }
        else
        {
            fRatio = fB/fA;
            fRoot = Math<R>::Sqrt((R)1.0 + fRatio*fRatio);
            afSubd[1] = fA*fRoot;
            fCos = ((R)1.0)/fRoot;
            fSin = fRatio*fCos;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (iRow = 0; iRow < 3; iRow++)
        {
            fTmp = m_val[getRowIndex(iRow) + 1];
            m_val[getRowIndex(iRow) + 1] = fSin*m_val[getRowIndex(iRow)]+fCos*fTmp;
            m_val[getRowIndex(iRow)] = fCos*m_val[getRowIndex(iRow)]-fSin*fTmp;
        }

        // Complete the update of the tridiagonal matrix.
        R fTmp2 = afDiag[1] - fTmp0;
        afDiag[2] += fTmp0;
        fTmp0 = (afDiag[0] - fTmp2)*fSin + ((R)2.0)*fTmp1*fCos;
        afSubd[0] = fCos*fTmp0 - fTmp1;
        fTmp0 *= fSin;
        afDiag[1] = fTmp2 + fTmp0;
        afDiag[0] -= fTmp0;
    }
    return false;
}
//----------------------------------------------------------------------------
template <class R>TMatrix3<R>&TMatrix3<R>::MakeDiagonal (R fM00, R fM11, R fM22)
{
    m_val[0] = fM00;
    m_val[1] = (R)0.0;
    m_val[2] = (R)0.0;
    m_val[3] = (R)0.0;
    m_val[4] = fM11;
    m_val[5] = (R)0.0;
    m_val[6] = (R)0.0;
    m_val[7] = (R)0.0;
    m_val[8] = fM22;
    return *this;
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::getAxisAngle(TVector3<R>& axis, R& angle) const
{
	// Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    R trace = m_val[0] + m_val[4] + m_val[8];
    R lcos = ((R)0.5)*(trace - (R)1.0);
    angle = Math<R>::ACos(lcos);  // in [0,PI]

    if ( angle > (R)0.0 )
    {
        if ( angle < Math<R>::PI )
        {
            axis[0] = m_val[7]-m_val[5];
            axis[1] = m_val[2]-m_val[6];
            axis[2] = m_val[3]-m_val[1];
            axis.normalize();
        }
        else
        {
            // angle is PI
            R halfInverse;
            if ( m_val[0] >= m_val[4] )
            {
                // r00 >= r11
                if ( m_val[0] >= m_val[8] )
                {
                    // r00 is maximum diagonal term
                    axis[0] = ((R)0.5)*Math<R>::Sqrt(m_val[0] -
                        m_val[4] - m_val[8] + (R)1.0);
                    halfInverse = ((R)0.5)/axis[0];
                    axis[1] = halfInverse*m_val[1];
                    axis[2] = halfInverse*m_val[2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = ((R)0.5)*Math<R>::Sqrt(m_val[8] -
                        m_val[0] - m_val[4] + (R)1.0);
                    halfInverse = ((R)0.5)/axis[2];
                    axis[0] = halfInverse*m_val[2];
                    axis[1] = halfInverse*m_val[5];
                }
            }
            else
            {
                // r11 > r00
                if ( m_val[4] >= m_val[8] )
                {
                    // r11 is maximum diagonal term
                    axis[1] = ((R)0.5)*Math<R>::Sqrt(m_val[4] -
                        m_val[0] - m_val[8] + (R)1.0);
                    halfInverse  = ((R)0.5)/axis[1];
                    axis[0] = halfInverse*m_val[1];
                    axis[2] = halfInverse*m_val[5];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = ((R)0.5)*Math<R>::Sqrt(m_val[8] -
                        m_val[0] - m_val[4] + (R)1.0);
                    halfInverse = ((R)0.5)/axis[2];
                    axis[0] = halfInverse*m_val[2];
                    axis[1] = halfInverse*m_val[5];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        axis[0] = (R)1.0;
        axis[1] = (R)0.0;
        axis[2] = (R)0.0;
    }
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::fromAxisAngle(const TVector3<R>& axis, R angle)
{
	R lcos = Math<R>::Cos(angle);
    R lsin = Math<R>::Sin(angle);
    R oneMinusCos = ((R)1.0) - lcos;
    R xsqr = axis[0]*axis[0];
    R ysqr = axis[1]*axis[1];
    R zsqr = axis[2]*axis[2];
    R xym = axis[0]*axis[1]*oneMinusCos;
    R xzm = axis[0]*axis[2]*oneMinusCos;
    R yzm = axis[1]*axis[2]*oneMinusCos;
    R xSin = axis[0]*lsin;
    R ySin = axis[1]*lsin;
    R zSin = axis[2]*lsin;
    
    m_val[0] = xsqr*oneMinusCos+lcos;
    m_val[1] = xym-zSin;
    m_val[2] = xzm+ySin;
    m_val[3] = xym+zSin;
    m_val[4] = ysqr*oneMinusCos+lcos;
    m_val[5] = yzm-xSin;
    m_val[6] = xzm-ySin;
    m_val[7] = yzm+xSin;
    m_val[8] = zsqr*oneMinusCos+lcos;
}
/* ------------------------------------------------------- */
template <class R> void TMatrix3<R>::orthonormalize()
{
	TVector3<R> u = getColumn(0);
	TVector3<R> v = getColumn(1);
	TVector3<R> w = getColumn(2);
	TVector3<R>::Orthonormalize(u, v, w);
	setColumn(0, u);
	setColumn(1, v);
	setColumn(2, w);
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
template <class R> int TMatrix3<R>::getRowIndex(int row) const
{
	return (row<<2) - row;
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
template <class R> 
TMatrix3<R> TMatrix3<R>::Slerp(R t, const TMatrix3& begin, const TMatrix3& end)
{
	TVector3<R> axis;
    R angle;
    TMatrix3 prod = begin.transposeTimes(end);
    prod.getAxisAngle(axis, angle);
    return TMatrix3(axis, t*angle);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TMatrix4:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::TMatrix4()
{
	memset(&m_val, 0, _MATRIX4_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::TMatrix4(const TMatrix4<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::TMatrix4(bool zero)
{
	if (zero) 
	{
		memset(&m_val, 0, _MATRIX4_SQR_DIM*sizeof(R));
	}
	else
	{
		toIdentity();
	}
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R>::TMatrix4(R m_00, R m_01, R m_02, R m_03,
					  R m_10, R m_11, R m_12, R m_13,
					  R m_20, R m_21, R m_22, R m_23,
					  R m_30, R m_31, R m_32, R m_33)
{
	m_val[0]  = m_00; m_val[1]  = m_01; m_val[2]  = m_02; m_val[3]  = m_03;
	m_val[4]  = m_10; m_val[5]  = m_11; m_val[6]  = m_12; m_val[7]  = m_13;
	m_val[8]  = m_20; m_val[9]  = m_21; m_val[10] = m_22; m_val[11] = m_23;
	m_val[12] = m_30; m_val[13] = m_31; m_val[14] = m_32; m_val[15] = m_33;
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::TMatrix4(const R v[_MATRIX4_SQR_DIM], bool rowMajor)
{
	if (rowMajor)
	{
		memcpy(&m_val, &v, _MATRIX4_SQR_DIM*sizeof(R));
	}
	else
	{
		m_val[0]  = v[0]; m_val[1]  = v[4]; m_val[2]  =  v[8]; m_val[3]  = v[12];
		m_val[4]  = v[1]; m_val[5]  = v[5]; m_val[6]  =  v[9]; m_val[7]  = v[13];
		m_val[8]  = v[2]; m_val[9]  = v[6]; m_val[10] = v[10]; m_val[11] = v[14];
		m_val[12] = v[3]; m_val[13] = v[7]; m_val[14] = v[11]; m_val[15] = v[15];		
	}
}
/* ------------------------------------------------------- */
template <class R> void TMatrix4<R>::toZero()
{
	memset(&m_val, 0, _MATRIX4_SQR_DIM*sizeof(R));
}
/* ------------------------------------------------------- */
template <class R> void TMatrix4<R>::toIdentity()
{
	toDiagonal(1, 1, 1, 1);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix4<R>::toDiagonal(R x, R y, R z, R w)
{
	m_val[0]  = x; m_val[1]  = 0; m_val[2]  = 0; m_val[3]  = 0;
	m_val[4]  = 0; m_val[5]  = y; m_val[6]  = 0; m_val[7]  = 0;
	m_val[8]  = 0; m_val[9]  = 0; m_val[10] = z; m_val[11] = 0;
	m_val[12] = 0; m_val[13] = 0; m_val[14] = 0; m_val[15] = w;
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>& TMatrix4<R>::operator=(const TMatrix4<R>& matrix)
{
	memcpy(&m_val, &matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R));
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::operator const R*() const
{
	return &m_val[0];
} 
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>::operator R*()
{
	return &m_val[0];
}
/* ------------------------------------------------------- */
template <class R> const R* TMatrix4<R>::operator[] (int row) const
{
	assert(row < _MATRIX4_DIM && row >= 0);
	return &m_val[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R* TMatrix4<R>::operator[] (int row)
{
	assert(row < _MATRIX4_DIM && row >= 0);
	return &m_val[getRowIndex(row)];
}
/* ------------------------------------------------------- */
template <class R> R TMatrix4<R>::operator() (int row, int col) const
{
	assert(row < _MATRIX4_DIM && col < _MATRIX4_DIM && row >= 0 && col >= 0);
	return m_val[col + (getRowIndex(row))];
}
/* ------------------------------------------------------- */
template <class R> R& TMatrix4<R>::operator() (int row, int col)
{
	assert(row < _MATRIX4_DIM && col < _MATRIX4_DIM && row >= 0 && col >= 0);
	return m_val[col + (getRowIndex(row))];
}
/* ------------------------------------------------------- */
template <class R> void TMatrix4<R>::setRow(int row, const TVector4<R>& vector)
{
	assert(row < _MATRIX4_DIM && row >= 0);
	int pos = getRowIndex(row);
	m_val[pos] = vector[0];
	m_val[pos+1] = vector[1];
	m_val[pos+2] = vector[2];
	m_val[pos+3] = vector[3];
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TMatrix4<R>::getRow(int row) const
{
	assert(row < _MATRIX4_DIM && row >= 0);
	int pos = getRowIndex(row);
	return TVector4<R>(m_val[pos], m_val[pos+1], m_val[pos+2], m_val[pos+3]);
}
/* ------------------------------------------------------- */
template <class R> 
void TMatrix4<R>::setColumn(int column, 
							const TVector4<R>& vector)
{
	assert(column < _MATRIX4_DIM && column >= 0);
	m_val[column] = vector[0];
	m_val[column + _MATRIX4_DIM] = vector[1]; 
	m_val[column + _MATRIX4_2DIM] = vector[2];
	m_val[column + _MATRIX4_3DIM] = vector[3]; 
}
/* ------------------------------------------------------- */
template <class R> TVector4<R> TMatrix4<R>::getColumn(int column) const
{
	assert(column < _MATRIX4_DIM && column >= 0);
	return TVector4<R>(m_val[column],  m_val[column + _MATRIX4_DIM],
		m_val[column + _MATRIX4_2DIM], m_val[column + _MATRIX4_3DIM]);
}
/* ------------------------------------------------------- */
template <class R> void TMatrix4<R>::getColumnMajor(ArrayPtr<R> a) const
{
	assert(arr.size() == _MATRIX4_SQR_DIM);
	a[0]  = m_val[0]; a[1]  = m_val[4]; a[2]  =  m_val[8]; a[3]  = m_val[12];
	a[4]  = m_val[1]; a[5]  = m_val[5]; a[6]  =  m_val[9]; a[7]  = m_val[13];
	a[8]  = m_val[2]; a[9]  = m_val[6]; a[10] = m_val[10]; a[11] = m_val[14];
	a[12] = m_val[3]; a[13] = m_val[7]; a[14] = m_val[11]; a[15] = m_val[15];
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator==(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) == 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator!=(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) != 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator<(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) < 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator<=(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) <= 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator>(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) > 0);
}
/* ------------------------------------------------------- */
template <class R> bool TMatrix4<R>::operator>=(const TMatrix4<R>& matrix) const
{
	return (memcmp(m_val, matrix.m_val, _MATRIX4_SQR_DIM*sizeof(R)) >= 0);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R> TMatrix4<R>::operator+(const TMatrix4<R>& matrix) const
{
	return TMatrix4( m_val[0]  + matrix.m_val[0],
					 m_val[1]  + matrix.m_val[1],
					 m_val[2]  + matrix.m_val[2],
					 m_val[3]  + matrix.m_val[3],
					 m_val[4]  + matrix.m_val[4],
					 m_val[5]  + matrix.m_val[5],
					 m_val[6]  + matrix.m_val[6],
					 m_val[7]  + matrix.m_val[7],
					 m_val[8]  + matrix.m_val[8],
					 m_val[9]  + matrix.m_val[9],
					 m_val[10] + matrix.m_val[10],
					 m_val[11] + matrix.m_val[11],
					 m_val[12] + matrix.m_val[12],
					 m_val[13] + matrix.m_val[13],
					 m_val[14] + matrix.m_val[14],
					 m_val[15] + matrix.m_val[15] );
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R> TMatrix4<R>::operator-(const TMatrix4<R>& matrix) const
{
	return TMatrix4( m_val[0]  - matrix.m_val[0],
					 m_val[1]  - matrix.m_val[1],
					 m_val[2]  - matrix.m_val[2],
					 m_val[3]  - matrix.m_val[3],
					 m_val[4]  - matrix.m_val[4],
					 m_val[5]  - matrix.m_val[5],
					 m_val[6]  - matrix.m_val[6],
					 m_val[7]  - matrix.m_val[7],
					 m_val[8]  - matrix.m_val[8],
					 m_val[9]  - matrix.m_val[9],
					 m_val[10] - matrix.m_val[10],
					 m_val[11] - matrix.m_val[11],
					 m_val[12] - matrix.m_val[12],
					 m_val[13] - matrix.m_val[13],
					 m_val[14] - matrix.m_val[14],
					 m_val[15] - matrix.m_val[15] );
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R> TMatrix4<R>::operator*(const TMatrix4<R>& m) const
{
	return TMatrix4( 
		 m_val[0] *m.m_val[0] + m_val[1] *m.m_val[4] + m_val[2]*m.m_val[8]   + m_val[3]*m.m_val[12],
		 m_val[0] *m.m_val[1] + m_val[1] *m.m_val[5] + m_val[2]*m.m_val[9]   + m_val[3]*m.m_val[13],
		 m_val[0] *m.m_val[2] + m_val[1] *m.m_val[6] + m_val[2]*m.m_val[10]  + m_val[3]*m.m_val[14],
		 m_val[0] *m.m_val[3] + m_val[1] *m.m_val[7] + m_val[2]*m.m_val[11]  + m_val[3]*m.m_val[15],
		 m_val[4] *m.m_val[0] + m_val[5] *m.m_val[4] + m_val[6]*m.m_val[8]   + m_val[7]*m.m_val[12],
		 m_val[4] *m.m_val[1] + m_val[5] *m.m_val[5] + m_val[6]*m.m_val[9]   + m_val[7]*m.m_val[13],
		 m_val[4] *m.m_val[2] + m_val[5] *m.m_val[6] + m_val[6]*m.m_val[10]  + m_val[7]*m.m_val[14],
		 m_val[4] *m.m_val[3] + m_val[5] *m.m_val[7] + m_val[6]*m.m_val[11]  + m_val[7]*m.m_val[15],
		 m_val[8] *m.m_val[0] + m_val[9] *m.m_val[4] + m_val[10]*m.m_val[8]  + m_val[11]*m.m_val[12],
		 m_val[8] *m.m_val[1] + m_val[9] *m.m_val[5] + m_val[10]*m.m_val[9]  + m_val[11]*m.m_val[13],
		 m_val[8] *m.m_val[2] + m_val[9] *m.m_val[6] + m_val[10]*m.m_val[10] + m_val[11]*m.m_val[14],
		 m_val[8] *m.m_val[3] + m_val[9] *m.m_val[7] + m_val[10]*m.m_val[11] + m_val[11]*m.m_val[15],
		 m_val[12]*m.m_val[0] + m_val[13]*m.m_val[4] + m_val[14]*m.m_val[8]  + m_val[15]*m.m_val[12],
		 m_val[12]*m.m_val[1] + m_val[13]*m.m_val[5] + m_val[14]*m.m_val[9]  + m_val[15]*m.m_val[13],
		 m_val[12]*m.m_val[2] + m_val[13]*m.m_val[6] + m_val[14]*m.m_val[10] + m_val[15]*m.m_val[14],
		 m_val[12]*m.m_val[3] + m_val[13]*m.m_val[7] + m_val[14]*m.m_val[11] + m_val[15]*m.m_val[15] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::operator*(R scalar) const
{
	return TMatrix4( m_val[0] *scalar, m_val[1] *scalar, m_val[2] *scalar, m_val[3] *scalar,
					 m_val[4] *scalar, m_val[5] *scalar, m_val[6] *scalar, m_val[7] *scalar,
					 m_val[8] *scalar, m_val[9] *scalar, m_val[10]*scalar, m_val[11]*scalar,
					 m_val[12]*scalar, m_val[13]*scalar, m_val[14]*scalar, m_val[15]*scalar );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::operator/(R scalar) const
{
	R invScalar = ((R)1.0)/scalar;
	return operator*(invScalar);
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::operator-() const
{
	return TMatrix4( -m_val[0] , -m_val[1] , -m_val[2] , -m_val[3] ,
					 -m_val[4] , -m_val[5] , -m_val[6] , -m_val[7] ,
					 -m_val[8] , -m_val[9] , -m_val[10], -m_val[11],
					 -m_val[12], -m_val[13], -m_val[14], -m_val[15] );
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R>& TMatrix4<R>::operator+=(const TMatrix4<R>& m)
{
	m_val[0]  += m.m_val[0];  m_val[1]  += m.m_val[1];  m_val[2]  += m.m_val[2];  m_val[3]  += m.m_val[3];
	m_val[4]  += m.m_val[4];  m_val[5]  += m.m_val[5];  m_val[6]  += m.m_val[6];  m_val[7]  += m.m_val[7];
	m_val[8]  += m.m_val[8];  m_val[9]  += m.m_val[9];  m_val[10] += m.m_val[10]; m_val[11] += m.m_val[11];
	m_val[12] += m.m_val[12]; m_val[13] += m.m_val[13]; m_val[14] += m.m_val[14]; m_val[15] += m.m_val[15];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TMatrix4<R>& TMatrix4<R>::operator-=(const TMatrix4<R>& matrix)
{
	m_val[0]  -= m.m_val[0];  m_val[1]  -= m.m_val[1];  m_val[2]  -= m.m_val[2];  m_val[3]  -= m.m_val[3];
	m_val[4]  -= m.m_val[4];  m_val[5]  -= m.m_val[5];  m_val[6]  -= m.m_val[6];  m_val[7]  -= m.m_val[7];
	m_val[8]  -= m.m_val[8];  m_val[9]  -= m.m_val[9];  m_val[10] -= m.m_val[10]; m_val[11] -= m.m_val[11];
	m_val[12] -= m.m_val[12]; m_val[13] -= m.m_val[13]; m_val[14] -= m.m_val[14]; m_val[15] -= m.m_val[15];
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>& TMatrix4<R>::operator*=(R s)
{
	m_val[0]  *= s; m_val[1]  *= s; m_val[2]  *= s; m_val[3]  *= s;
	m_val[4]  *= s; m_val[5]  *= s; m_val[6]  *= s; m_val[7]  *= s;
	m_val[8]  *= s; m_val[9]  *= s; m_val[10] *= s; m_val[11] *= s;
	m_val[12] *= s; m_val[13] *= s; m_val[14] *= s; m_val[15] *= s;
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R>& TMatrix4<R>::operator/=(R scalar)
{
	R invScalar = ((R)1.0)/scalar;
	operator*=(invScalar);
	return (*this);
}
/* ------------------------------------------------------- */
template <class R> 
TVector4<R> TMatrix4<R>::operator*(const TVector4<R>& v) const
{
	return TVector4<R>(	m_val[0] *v[0] + m_val[1] *v[1] + m_val[2] *v[2] + m_val[3] *v[3],
						m_val[4] *v[0] + m_val[5] *v[1] + m_val[6] *v[2] + m_val[7] *v[3],
						m_val[8] *v[0] + m_val[9] *v[1] + m_val[10]*v[2] + m_val[11]*v[3],
						m_val[12]*v[0] + m_val[13]*v[1] + m_val[14]*v[2] + m_val[15]*v[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::transpose() const
{
	return TMatrix4( m_val[0], m_val[4], m_val[8],  m_val[12],
					 m_val[1], m_val[5], m_val[9],  m_val[13],
					 m_val[2], m_val[6], m_val[10], m_val[14],
					 m_val[3], m_val[7], m_val[11], m_val[15] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::transposeTimes(const TMatrix4<R>& matrix) const
{
	// The result of this operation is a symmetric matrix:
	R v1 =  m_val[0]*m.m_val[1] + m_val[4]*m.m_val[5] + m_val[8]*m.m_val[9]   + m_val[12]*m.m_val[13];
	R v2 =  m_val[0]*m.m_val[2] + m_val[4]*m.m_val[6] + m_val[8]*m.m_val[10]  + m_val[12]*m.m_val[14];
	R v3 =  m_val[0]*m.m_val[3] + m_val[4]*m.m_val[7] + m_val[8]*m.m_val[11]  + m_val[12]*m.m_val[15];
	R v6 =  m_val[1]*m.m_val[2] + m_val[5]*m.m_val[6] + m_val[9]*m.m_val[10]  + m_val[13]*m.m_val[14];
	R v7 =  m_val[1]*m.m_val[3] + m_val[5]*m.m_val[7] + m_val[9]*m.m_val[11]  + m_val[13]*m.m_val[15];
	R v11 = m_val[2]*m.m_val[3] + m_val[6]*m.m_val[7] + m_val[10]*m.m_val[11] + m_val[14]*m.m_val[15];

	R d1 = m_val[0]*m.m_val[0] + m_val[4]*m.m_val[4] + m_val[8]*m.m_val[8]   + m_val[12]*m.m_val[12];
	R d2 = m_val[1]*m.m_val[1] + m_val[5]*m.m_val[5] + m_val[9]*m.m_val[9]   + m_val[13]*m.m_val[13];
	R d3 = m_val[2]*m.m_val[2] + m_val[6]*m.m_val[6] + m_val[10]*m.m_val[10] + m_val[14]*m.m_val[14];
	R d4 = m_val[3]*m.m_val[3] + m_val[7]*m.m_val[7] + m_val[11]*m.m_val[11] + m_val[15]*m.m_val[15];
	return TMatrix4( d1, v1, v2 , v3,
					 v1, d2, v6 , v7,
					 v2, v3, d3 , v11,
					 v6, v7, v11, d4 );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::timesTranspose(const TMatrix4<R>& matrix) const
{
	// The result of this operation is a symmetric matrix:
	R v1 =  m_val[0]*m.m_val[4]  + m_val[1] *m.m_val[5]  + m_val[2] *m.m_val[6]   + m_val[3] *m.m_val[7];
	R v2 =  m_val[0]*m.m_val[8]  + m_val[1] *m.m_val[9]  + m_val[2] *m.m_val[10]  + m_val[3] *m.m_val[11];
	R v3 =  m_val[0]*m.m_val[12] + m_val[1] *m.m_val[13] + m_val[2] *m.m_val[14]  + m_val[3] *m.m_val[15];
	R v6 =  m_val[4]*m.m_val[8]  + m_val[5] *m.m_val[9]  + m_val[6] *m.m_val[10]  + m_val[7] *m.m_val[11];
	R v7 =  m_val[4]*m.m_val[12] + m_val[5] *m.m_val[13] + m_val[6] *m.m_val[14]  + m_val[7] *m.m_val[15];
	R v11 = m_val[8]*m.m_val[12] + m_val[10]*m.m_val[13] + m_val[11]*m.m_val[14]  + m_val[14]*m.m_val[15];

	R d1 = m_val[0] *m.m_val[0] +  m_val[1] *m.m_val[1]  + m_val[2]*m.m_val[2]   + m_val[3] *m.m_val[3];
	R d2 = m_val[4] *m.m_val[4]  + m_val[5] *m.m_val[5]  + m_val[6]*m.m_val[6]   + m_val[7] *m.m_val[7];
	R d3 = m_val[8] *m.m_val[8]  + m_val[9] *m.m_val[9]  + m_val[10]*m.m_val[10] + m_val[11]*m.m_val[11];
	R d4 = m_val[12]*m.m_val[12] + m_val[13]*m.m_val[13] + m_val[14]*m.m_val[14] + m_val[15]*m.m_val[15];
	return TMatrix4( d1, v1, v2 , v3,
					 v1, d2, v6 , v7,
					 v2, v3, d3 , v11,
					 v6, v7, v11, d4 );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::timesDiagonal(const TVector4<R>& matrix) const
{
	return TMatrix4<R>( m_val[0]* v[0], m_val[1]*v[1],  m_val[2]* v[2],  m_val[3]* v[3],
						m_val[4]* v[0], m_val[5]*v[1],  m_val[6]* v[2],  m_val[7]* v[3],
						m_val[8]* v[0], m_val[9]*v[1],  m_val[10]*v[2],  m_val[11]*v[3],
						m_val[12]*v[0], m_val[13]*v[1], m_val[14]*v[2],  m_val[15]*v[3] );
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::inverse() const
{
	R a0 = m_val[0] *m_val[5]  - m_val[1] *m_val[4];
    R a1 = m_val[0] *m_val[6]  - m_val[2] *m_val[4];
    R a2 = m_val[0] *m_val[7]  - m_val[3] *m_val[4];
    R a3 = m_val[1] *m_val[6]  - m_val[2] *m_val[5];
    R a4 = m_val[1] *m_val[7]  - m_val[3] *m_val[5];
    R a5 = m_val[2] *m_val[7]  - m_val[3] *m_val[6];
    R b0 = m_val[8] *m_val[13] - m_val[9] *m_val[12];
    R b1 = m_val[8] *m_val[14] - m_val[10]*m_val[12];
    R b2 = m_val[8] *m_val[15] - m_val[11]*m_val[12];
    R b3 = m_val[9] *m_val[14] - m_val[10]*m_val[13];
    R b4 = m_val[9] *m_val[15] - m_val[11]*m_val[13];
    R b5 = m_val[10]*m_val[15] - m_val[11]*m_val[14];

    R det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    if ( Math<R>::FAbs(det) <= Math<R>::ZERO_TOLERANCE )
        return TMatrix4<R>::ZERO;

    TMatrix4 inv(
		+ m_val[5] *b5 - m_val[6] *b4 + m_val[7] *b3,
		- m_val[4] *b5 + m_val[6] *b2 - m_val[7] *b1,
		+ m_val[4] *b4 - m_val[5] *b2 + m_val[7] *b0,
		- m_val[4] *b3 + m_val[5] *b1 - m_val[6] *b0,
		- m_val[1] *b5 + m_val[2] *b4 - m_val[3] *b3,
		+ m_val[0] *b5 - m_val[2] *b2 + m_val[3] *b1,
		- m_val[0] *b4 + m_val[1] *b2 - m_val[3] *b0,
		+ m_val[0] *b3 - m_val[1] *b1 + m_val[2] *b0,
		+ m_val[13]*a5 - m_val[14]*a4 + m_val[15]*a3,
		- m_val[12]*a5 + m_val[14]*a2 - m_val[15]*a1,
		+ m_val[12]*a4 - m_val[13]*a2 + m_val[15]*a0,
		- m_val[12]*a3 + m_val[13]*a1 - m_val[14]*a0,
		- m_val[9] *a5 + m_val[10]*a4 - m_val[11]*a3,
		+ m_val[8] *a5 - m_val[10]*a2 + m_val[11]*a1,
		- m_val[8] *a4 + m_val[9] *a2 - m_val[11]*a0,
		+ m_val[8] *a3 - m_val[9] *a1 + m_val[10]*a0 );

	inv /= det;
    return inv;
}
/* ------------------------------------------------------- */
template <class R> TMatrix4<R> TMatrix4<R>::adjoint() const
{
    R a0 = m_val[0] *m_val[5]  - m_val[1] *m_val[4];
    R a1 = m_val[0] *m_val[6]  - m_val[2] *m_val[4];
    R a2 = m_val[0] *m_val[7]  - m_val[3] *m_val[4];
    R a3 = m_val[1] *m_val[6]  - m_val[2] *m_val[5];
    R a4 = m_val[1] *m_val[7]  - m_val[3] *m_val[5];
    R a5 = m_val[2] *m_val[7]  - m_val[3] *m_val[6];
    R b0 = m_val[8] *m_val[13] - m_val[9] *m_val[12];
    R b1 = m_val[8] *m_val[14] - m_val[10]*m_val[12];
    R b2 = m_val[8] *m_val[15] - m_val[11]*m_val[12];
    R b3 = m_val[9] *m_val[14] - m_val[10]*m_val[13];
    R b4 = m_val[9] *m_val[15] - m_val[11]*m_val[13];
    R b5 = m_val[10]*m_val[15] - m_val[11]*m_val[14];

    return TMatrix4(
		+ m_val[5] *b5 - m_val[6] *b4 + m_val[7] *b3,
		- m_val[4] *b5 + m_val[6] *b2 - m_val[7] *b1,
		+ m_val[4] *b4 - m_val[5] *b2 + m_val[7] *b0,
		- m_val[4] *b3 + m_val[5] *b1 - m_val[6] *b0,
		- m_val[1] *b5 + m_val[2] *b4 - m_val[3] *b3,
		+ m_val[0] *b5 - m_val[2] *b2 + m_val[3] *b1,
		- m_val[0] *b4 + m_val[1] *b2 - m_val[3] *b0,
		+ m_val[0] *b3 - m_val[1] *b1 + m_val[2] *b0,
		+ m_val[13]*a5 - m_val[14]*a4 + m_val[15]*a3,
		- m_val[12]*a5 + m_val[14]*a2 - m_val[15]*a1,
		+ m_val[12]*a4 - m_val[13]*a2 + m_val[15]*a0,
		- m_val[12]*a3 + m_val[13]*a1 - m_val[14]*a0,
		- m_val[9] *a5 + m_val[10]*a4 - m_val[11]*a3,
		+ m_val[8] *a5 - m_val[10]*a2 + m_val[11]*a1,
		- m_val[8] *a4 + m_val[9] *a2 - m_val[11]*a0,
		+ m_val[8] *a3 - m_val[9] *a1 + m_val[10]*a0 );
}
/* ------------------------------------------------------- */
template <class R> R TMatrix4<R>::determinant() const
{
	R a0 = m_val[0] *m_val[5]  - m_val[1] *m_val[4];
    R a1 = m_val[0] *m_val[6]  - m_val[2] *m_val[4];
    R a2 = m_val[0] *m_val[7]  - m_val[3] *m_val[4];
    R a3 = m_val[1] *m_val[6]  - m_val[2] *m_val[5];
    R a4 = m_val[1] *m_val[7]  - m_val[3] *m_val[5];
    R a5 = m_val[2] *m_val[7]  - m_val[3] *m_val[6];
    R b0 = m_val[8] *m_val[13] - m_val[9] *m_val[12];
    R b1 = m_val[8] *m_val[14] - m_val[10]*m_val[12];
    R b2 = m_val[8] *m_val[15] - m_val[11]*m_val[12];
    R b3 = m_val[9] *m_val[14] - m_val[10]*m_val[13];
    R b4 = m_val[9] *m_val[15] - m_val[11]*m_val[13];
    R b5 = m_val[10]*m_val[15] - m_val[11]*m_val[14];
    return a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
}
/* ------------------------------------------------------- */
template <class R> R TMatrix4<R>::qForm(const TVector4<R>& u, const TVector4<R>& v) const
{
	return u.dot(operator*(v));
}
/* ------------------------------------------------------- */
template <class R>
void TMatrix4<R>::toObliqueProjection (const TVector3<R>& normal,
    const TVector3<R>& point, const TVector3<R>& direction)
{
    // The projection plane is Dot(N,X-P) = 0 where N is a 3-by-1 unit-length
    // normal vector and P is a 3-by-1 point on the plane.  The projection
    // is oblique to the plane, in the direction of the 3-by-1 vector D.
    // Necessarily Dot(N,D) is not zero for this projection to make sense.
    // Given a 3-by-1 point U, compute the intersection of the line U+t*D
    // with the plane to obtain t = -Dot(N,U-P)/Dot(N,D).  Then
    //
    //   projection(U) = P + [I - D*N^T/Dot(N,D)]*(U-P)
    //
    // A 4-by-4 homogeneous transformation representing the projection is
    //
    //       +-                               -+
    //   M = | D*N^T - Dot(N,D)*I   -Dot(N,P)D |
    //       |          0^T          -Dot(N,D) |
    //       +-                               -+
    //
    // where M applies to [U^T 1]^T by M*[U^T 1]^T.  The matrix is chosen so
    // that M[3][3] > 0 whenever Dot(N,D) < 0 (projection is onto the
    // "positive side" of the plane).

    R ndd = normal.Dot(direction);
    R ndp = normal.Dot(point);
    m_val[0]  = direction[0]*normal[0] - ndd;
    m_val[1]  = direction[0]*normal[1];
    m_val[2]  = direction[0]*normal[2];
    m_val[3]  = -ndp*direction[0];
    m_val[4]  = direction[1]*normal[0];
    m_val[5]  = direction[1]*normal[1] - ndd;
    m_val[6]  = direction[1]*normal[2];
    m_val[7]  = -ndp*direction[1];
    m_val[8]  = direction[2]*normal[0];
    m_val[9]  = direction[2]*normal[1];
    m_val[10] = direction[2]*normal[2] - ndd;
    m_val[11] = -ndp*direction[2];
    m_val[12] = 0.0f;
    m_val[13] = 0.0f;
    m_val[14] = 0.0f;
    m_val[15] = -ndd;
}
/* ------------------------------------------------------- */
template <class R>
void TMatrix4<R>::toPerspectiveProjection (const TVector3<R>& normal,
    const TVector3<R>& point, const TVector3<R>& eye)
{
    //     +-                                                 -+
    // M = | Dot(N,E-P)*I - E*N^T    -(Dot(N,E-P)*I - E*N^T)*E |
    //     |        -N^t                      Dot(N,E)         |
    //     +-                                                 -+
    //
    // where E is the eye point, P is a point on the plane, and N is a
    // unit-length plane normal.

    R ndemp = normal.Dot(eye-point);

    m_val[0]  = ndemp - eye[0]*normal[0];
    m_val[1]  = -eye[0]*normal[1];
    m_val[2]  = -eye[0]*normal[2];
    m_val[3]  = -(m_val[0]*eye[0] + m_val[1]*eye[1] + m_val[2]*eye[2]);
    m_val[4]  = -eye[1]*normal[0];
    m_val[5]  = ndemp - eye[1]*normal[1];
    m_val[6]  = -eye[1]*normal[2];
    m_val[7]  = -(m_val[4]*eye[0] + m_val[5]*eye[1] + m_val[6]*eye[2]);
    m_val[8]  = -eye[2]*normal[0];
    m_val[9]  = -eye[2]*normal[1];
    m_val[10] = ndemp- eye[2]*normal[2];
    m_val[11] = -(m_val[8]*eye[0] + m_val[9]*eye[1] + m_val[10]*eye[2]);
    m_val[12] = -normal[0];
    m_val[13] = -normal[1];
    m_val[14] = -normal[2];
    m_val[15] = normal.Dot(eye);
}
/* ------------------------------------------------------- */
template <class R>
void TMatrix4<R>::toReflection (const TVector3<R>& normal,
    const TVector3<R>& point)
{
    //     +-                         -+
    // M = | I-2*N*N^T    2*Dot(N,P)*N |
    //     |     0^T            1      |
    //     +-                         -+
    //
    // where P is a point on the plane and N is a unit-length plane normal.

    R twoNdP = ((R)2.0)*(normal.Dot(point));

    m_val[0]  = (R)1.0 - ((R)2.0)*normal[0]*normal[0];
    m_val[1]  = -((R)2.0)*normal[0]*normal[1];
    m_val[2]  = -((R)2.0)*normal[0]*normal[2];
    m_val[3]  = twoNdP*normal[0];
    m_val[4]  = -((R)2.0)*normal[1]*normal[0];
    m_val[5]  = (R)1.0 - ((R)2.0)*normal[1]*normal[1];
    m_val[6]  = -((R)2.0)*normal[1]*normal[2];
    m_val[7]  = twoNdP*normal[1];
    m_val[8]  = -((R)2.0)*normal[2]*normal[0];
    m_val[9]  = -((R)2.0)*normal[2]*normal[1];
    m_val[10] = (R)1.0 - ((R)2.0)*normal[2]*normal[2];
    m_val[11] = twoNdP*normal[2];
    m_val[12] = (R)0.0;
    m_val[13] = (R)0.0;
    m_val[14] = (R)0.0;
    m_val[15] = (R)1.0;
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
template <class R> int TMatrix4<R>::getRowIndex(int row) const
{
	return (row<<2);
}
/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "..\..\include\math\lmatrix.h"

using namespace Lotus;

template<> const TMatrix2<float> TMatrix2<float>::ZERO(
    0.0f,0.0f,
    0.0f,0.0f);
template<> const TMatrix2<float> TMatrix2<float>::IDENTITY(
    1.0f,0.0f,
    0.0f,1.0f);

template<> const TMatrix2<double> TMatrix2<double>::ZERO(
    0.0,0.0,
    0.0,0.0);
template<> const TMatrix2<double> TMatrix2<double>::IDENTITY(
    1.0,0.0,
    0.0,1.0);

template<> const TMatrix3<float> TMatrix3<float>::ZERO(
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f);
template<> const TMatrix3<float> TMatrix3<float>::IDENTITY(
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f);

template<> const TMatrix3<double> TMatrix3<double>::ZERO(
    0.0,0.0,0.0,
    0.0,0.0,0.0,
	0.0,0.0,0.0);
template<> const TMatrix3<double> TMatrix3<double>::IDENTITY(
    1.0,0.0,0.0,
    0.0,1.0,0.0,
	0.0,0.0,1.0);

template<> const TMatrix4<float> TMatrix4<float>::ZERO(
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f);
template<> const TMatrix4<float> TMatrix4<float>::IDENTITY(
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f);

template<> const TMatrix4<double> TMatrix4<double>::ZERO(
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0);
template<> const TMatrix4<double> TMatrix4<double>::IDENTITY(
    1.0,0.0,0.0,0.0,
    0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0);
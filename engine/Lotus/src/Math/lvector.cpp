/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "..\..\include\math\lvector.h"

using namespace Lotus;

template<> const TVector2<float> TVector2<float>::ZERO(0.0f,0.0f);
template<> const TVector2<float> TVector2<float>::UNIT_X(1.0f,0.0f);
template<> const TVector2<float> TVector2<float>::UNIT_Y(0.0f,1.0f);

template<> const TVector2<double> TVector2<double>::ZERO(0.0,0.0);
template<> const TVector2<double> TVector2<double>::UNIT_X(1.0,0.0);
template<> const TVector2<double> TVector2<double>::UNIT_Y(0.0,1.0);

template<> const TVector3<float> TVector3<float>::ZERO(0.0f,0.0f,0.0f);
template<> const TVector3<float> TVector3<float>::UNIT_X(1.0f,0.0f,0.0f);
template<> const TVector3<float> TVector3<float>::UNIT_Y(0.0f,1.0f,0.0f);
template<> const TVector3<float> TVector3<float>::UNIT_Z(0.0f,0.0f,1.0f);

template<> const TVector3<double> TVector3<double>::ZERO(0.0,0.0,0.0);
template<> const TVector3<double> TVector3<double>::UNIT_X(1.0,0.0,0.0);
template<> const TVector3<double> TVector3<double>::UNIT_Y(0.0,1.0,0.0);
template<> const TVector3<double> TVector3<double>::UNIT_Z(0.0,0.0,1.0);

template<> const TVector4<float> TVector4<float>::ZERO(0.0f,0.0f,0.0f,0.0f);
template<> const TVector4<float> TVector4<float>::UNIT_X(1.0f,0.0f,0.0f,0.0f);
template<> const TVector4<float> TVector4<float>::UNIT_Y(0.0f,1.0f,0.0f,0.0f);
template<> const TVector4<float> TVector4<float>::UNIT_Z(0.0f,0.0f,1.0f,0.0f);
template<> const TVector4<float> TVector4<float>::UNIT_W(0.0f,0.0f,0.0f,1.0f);

template<> const TVector4<double> TVector4<double>::ZERO(0.0,0.0,0.0,0.0);
template<> const TVector4<double> TVector4<double>::UNIT_X(1.0,0.0,0.0,0.0);
template<> const TVector4<double> TVector4<double>::UNIT_Y(0.0,1.0,0.0,0.0);
template<> const TVector4<double> TVector4<double>::UNIT_Z(0.0,0.0,1.0,0.0);
template<> const TVector4<double> TVector4<double>::UNIT_W(0.0,0.0,0.0,0.0);
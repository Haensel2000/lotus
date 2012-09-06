/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "..\..\include\math\lcolor.h"

using namespace Lotus;

template<> const TColor3<float> TColor3<float>::BLACK(0.0f,0.0f,0.0f);
template<> const TColor3<float> TColor3<float>::WHITE(1.0f,1.0f,1.0f);
template<> const TColor3<float> TColor3<float>::RED(1.0f,0.0f,0.0f);
template<> const TColor3<float> TColor3<float>::GREEN(0.0f,1.0f,0.0f);
template<> const TColor3<float> TColor3<float>::BLUE(0.0f,0.0f,1.0f);

template<> const TColor3<double> TColor3<double>::BLACK(0.0,0.0,0.0);
template<> const TColor3<double> TColor3<double>::WHITE(1.0,1.0,1.0);
template<> const TColor3<double> TColor3<double>::RED(1.0,0.0,0.0);
template<> const TColor3<double> TColor3<double>::GREEN(0.0,1.0,0.0);
template<> const TColor3<double> TColor3<double>::BLUE(0.0,0.0,1.0);

template<> const TColor4<float> TColor4<float>::BLACK(0.0f,0.0f,0.0f,1.0f);
template<> const TColor4<float> TColor4<float>::WHITE(1.0f,1.0f,1.0f,1.0f);
template<> const TColor4<float> TColor4<float>::RED(1.0f,0.0f,0.0f,1.0f);
template<> const TColor4<float> TColor4<float>::GREEN(0.0f,1.0f,0.0f,1.0f);
template<> const TColor4<float> TColor4<float>::BLUE(0.0f,0.0f,1.0f,1.0f);

template<> const TColor4<double> TColor4<double>::BLACK(0.0,0.0,0.0,1.0);
template<> const TColor4<double> TColor4<double>::WHITE(1.0,1.0,1.0,1.0);
template<> const TColor4<double> TColor4<double>::RED(1.0,0.0,0.0,1.0);
template<> const TColor4<double> TColor4<double>::GREEN(0.0,1.0,0.0,1.0);
template<> const TColor4<double> TColor4<double>::BLUE(0.0,0.0,1.0,1.0);
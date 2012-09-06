/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXCONVERT_H
#define _HDR_DXCONVERT_H 

#include <math\lmatrix.h>
#include <math\lvector.h>
#include <math\lcolor.h>
#include <resource\lffeffects.h>
#include "dxdecl.h"

using Lotus::Vector3;
using Lotus::Matrix4;
using Lotus::TextureArgument;
using Lotus::Color4;

namespace DX
{
	
	D3D_Vector Convert(const Vector3& v);
	D3D_Matrix Convert(const Matrix4& m);

	unsigned int Convert(TextureArgument targ);
	unsigned int ConvertUInt(const Color4& color);
	D3DCOLORVALUE Convert(const Color4& color);

}

#endif
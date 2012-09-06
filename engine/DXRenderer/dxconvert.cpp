/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxconvert.h"

using namespace DX;

/* ------------------------------------------------------- */
D3D_Vector DX::Convert(const Vector3& v)
{
	return D3D_Vector(v);
}
/* ------------------------------------------------------- */
D3D_Matrix DX::Convert(const Matrix4& m)
{
	return D3D_Matrix(m);
}
/* ------------------------------------------------------- */
unsigned int DX::Convert(TextureArgument targ)
{
	switch (targ)
	{
	case Lotus::TA_CONSTANT: return D3DTA_CONSTANT; break;
	case Lotus::TA_CURRENT: return D3DTA_CURRENT; break;
	case Lotus::TA_DIFFUSE: return D3DTA_DIFFUSE; break;
	case Lotus::TA_SPECULAR: return D3DTA_SPECULAR; break;
	case Lotus::TA_TEMP: return D3DTA_TEMP; break;
	case Lotus::TA_TEXTURE: return D3DTA_TEXTURE; break;
	case Lotus::TA_TFACTOR: return D3DTA_TFACTOR; break;
	default: return D3DTA_CURRENT;
	}
}
/* ------------------------------------------------------- */
unsigned int DX::ConvertUInt(const Color4& color)
{
	return D3DCOLOR_ARGB(int(color.A()*255.0f), int(color.R()*255.0f), int(color.G()*255.0f), int(color.B()*255.0f));
}
/* ------------------------------------------------------- */
D3DCOLORVALUE DX::Convert(const Color4& color)
{
	D3DCOLORVALUE result;
	result.a = color.A();
	result.r = color.R();
	result.g = color.G();
	result.b = color.B();
	return result;
}
/* ------------------------------------------------------- */
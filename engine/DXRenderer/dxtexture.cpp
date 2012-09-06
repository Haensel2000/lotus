/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxtexture.h"

using namespace DX;

/* ------------------------------------------------------- */
/* class DXTexture:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
DXTexture::DXTexture(D3D_Texture* texture, ArrayPtr<unsigned int>& data)
: Texture(data), m_texture(texture)
{
}
/* ------------------------------------------------------- */
DXTexture::~DXTexture()
{
	if (m_texture)
		m_texture->Release();
}
/* ------------------------------------------------------- */
D3D_Texture* DXTexture::toInternal()
{
	return m_texture;
}
/* ------------------------------------------------------- */
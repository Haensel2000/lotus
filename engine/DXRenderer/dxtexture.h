/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXTEXTURE_H
#define _HDR_DXTEXTURE_H 

#include <resource\ltexture.h>
#include "dxdecl.h"

using Lotus::Texture;
using Lotus::ArrayPtr;

namespace DX
{
	class DXTexture : public Texture
	{
	private:
		D3D_Texture* m_texture;
	public:
		DXTexture(D3D_Texture* texture, ArrayPtr<unsigned int>& data);
		~DXTexture();

		D3D_Texture* toInternal();
	};
}

#endif
#pragma once

#include "dxbasic.h"
#include "dxinclude.h"

namespace DX
{
	class Texture
	{
		private:
			TEXTURE texture;
		public:
			Texture(TEXTURE internalTex) : texture(internalTex) 
			{
			}
			TEXTURE toInternal() { return texture; }
	};
}
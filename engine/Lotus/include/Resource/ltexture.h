/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LTEXTURE_H
#define _HDR_LTEXTURE_H

#include <math\lcolor.h>
#include <scenegraph\lsgbase.h>
#include <system\lpointer.h>


namespace Lotus
{
	

	/* class Texture
	 * This class provides an interface for a texture ressource. Handling of texture ressources
	 * depends on the graphic api. A certain renderer has to subclass Texture and implement 
	 * handling of the texture ressource and streaming of texture data. */
	class Texture : public Object
	{
	protected:
		ArrayPtr<unsigned int> m_data;
	public:
		Texture();
		Texture(ArrayPtr<unsigned int>& data);
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		virtual String getType() const;


	};
}

#endif
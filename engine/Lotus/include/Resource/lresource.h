/***************************************** 
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LRESOURCE_H
#define _HDR_LRESOURCE_H

#include <scenegraph\lsgbase.h>

namespace Lotus
{
	class Resource : public Serializable
	{
	private:
	public:
		virtual Array<Serializable*> getAttached() const = 0;
		virtual void release() = 0;	
	};
}

#endif
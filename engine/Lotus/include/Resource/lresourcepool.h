/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LRESOURCEPOOL_H
#define _HDR_LRESOURCEPOOL_H

#include <resource\lresource.h>
#include <system\larray.h>

#include <map>
#include <string>

using std::map;
using std::string;

namespace Lotus
{
	/* class ResourcePool
	 * This class handles the memory management of resources (textures, vertexdata, effects,
	 * geometrydata). Resources are shared objects that are referenced through resource 
	 * handles. Each resource handle stores the resource type and a unique index within these
	 * type. This index is used for the building of the render tree as well. */
	class ResourcePool
	{
	private:
		

		static ResourcePool s_resourcePool;
		
		map<string, Array<Resource>> m_pool;
	public:
		ResourcePool();
		~ResourcePool();

		void loadResourceFile(const string& filename);

		static ResourcePool* GetInstance();
	};
}

#endif
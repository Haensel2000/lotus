/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lresourcepool.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class ResourcePool:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
ResourcePool::ResourcePool()
{
}
/* ------------------------------------------------------- */
ResourcePool::~ResourcePool()
{
}
/* ------------------------------------------------------- */
void loadResourceFile(const string& filename)
{
	
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
ResourcePool* ResourcePool::GetInstance()
{
	return &s_resourcePool;
}

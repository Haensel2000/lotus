/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lresourcestream.h>
#include <resource\lresource.h>
#include <scenegraph\lsgbase.h>
#include <scenegraph\lspatial.h>
#include <scenegraph\lgroup.h>
#include <scenegraph\lgeometry.h>

using namespace Lotus;

//"class Lotus::" \
//	#clazz

#define STREAM_REGISTER(clazz) s_factory.insert(String(typeid(clazz).name()), &Serializable::Factory<clazz>)

/* ------------------------------------------------------- */
/* class Stream :                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
/* If a class that derived from object should be serializable in the streaming system
 * the corresponding class has to implement a static method Factory and member functions
 * save and read. Finally the application programer has to register his class  here
 * just by calling the macro STREAM_REGISTER(classname); */
void ResourceStream::RegisterClasses()
{
	STREAM_REGISTER( Controllable );
	STREAM_REGISTER( SphereVolume );
	STREAM_REGISTER( Group );
	STREAM_REGISTER( Geometry );
	STREAM_REGISTER( GeometryData );
	STREAM_REGISTER( VertexData );
}
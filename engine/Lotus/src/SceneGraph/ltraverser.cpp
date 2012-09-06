/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\ltraverser.h>
#include <scenegraph\lsgbase.h>
#include <scenegraph\lspatial.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Collector:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Collector::Collector(int hashSize)
: m_objects(hashSize), m_ordered(new Array<Object*>(hashSize, hashSize-1))
{
}
/* ------------------------------------------------------- */
bool Collector::operator()(Object* obj)
{
	// register the object:
	if (m_objects.insert(obj))
	{
		m_ordered->append(obj);
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
Ptr< Array<Object*> > Collector::getCollection()
{
	return m_ordered;
}
/* ------------------------------------------------------- */
bool Collector::all()
{
	return true;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Seeker:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Seeker::Seeker(const String& targetName)
: m_targetName(targetName), m_target(0)
{
}
/* ------------------------------------------------------- */
bool Seeker::operator()(Object* obj)
{
	if (obj->getName() == m_targetName)
	{
		m_target = obj;
		return false;
	}
	return true;
}
/* ------------------------------------------------------- */
Object* Seeker::getTarget()
{
	return m_target;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class SpatialUpdater:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
SpatialUpdater::SpatialUpdater(double time)
: m_time(time), m_transformChanged(0), m_boundChanged(0), m_parentBoundChange(0)
{
}
/* ------------------------------------------------------- */
bool SpatialUpdater::pre(Spatial* obj)
{
	if (obj->isStatic())
		return false;
	else
	{
		obj->updateControllers(m_time);
		if (obj->transformChanged() && !m_transformChanged)
		{
			m_transformChanged = obj;
			m_boundChanged = obj;
			m_parentBoundChange = obj->getParent();
		}
		else if (obj->boundChanged() && !m_boundChanged && !m_transformChanged)
		{
			m_boundChanged = obj;
			m_parentBoundChange = obj->getParent();
		}
		if (m_transformChanged)
		{
			obj->updateTransform();
		}
		return true;
	}
}
/* ------------------------------------------------------- */
bool SpatialUpdater::post(Spatial* obj)
{
	if (!obj->isStatic())
	{
		if (m_boundChanged)
		{
			obj->updateBound();
		}
		else if (obj == m_parentBoundChange)
		{
			obj->updateBound();
			m_parentBoundChange = obj->getParent();
		}
		if (obj == m_boundChanged)
		{
			m_transformChanged = 0;
			m_boundChanged = 0;
		}
	}
	obj->resetFlags();
	return true;
}
/* ------------------------------------------------------- */





/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lgeometry.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Geometry:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Geometry::Geometry()
: m_modelBound(0), m_isRegistered(false)
{
}
/* ------------------------------------------------------- */
Geometry::Geometry(const Geometry& g)
: Spatial(g), m_modelBound(g.m_modelBound->copy()), m_geometryData(g.m_geometryData), m_isRegistered(false)
{
}
/* ------------------------------------------------------- */
Geometry::Geometry(Ptr<GeometryData>& gdata, Renderer* renderer)
: m_geometryData(gdata), m_isRegistered(false)
{
	m_modelBound = newBoundingVolume();
	m_modelBound->computeFromData(gdata->getVertexData());

	if (!m_geometryData->isRegistered() && renderer)
	{
		registerData(renderer);
	}
}
/* ------------------------------------------------------- */
Geometry::~Geometry()
{
	unregisterInstance();
	if (m_modelBound)
		delete m_modelBound;
}
/* ------------------------------------------------------- */
Spatial* Geometry::copy()
{
	Geometry* result = new Geometry(*this);
	result->registerInstance();
	return result;
}
/* ------------------------------------------------------- */
void Geometry::load(Stream& stream)
{
	Spatial::load(stream);

	stream.read(m_modelBound);
	stream.read(m_geometryData);
}
/* ------------------------------------------------------- */
void Geometry::link(PtrLinker& linker)
{
	Spatial::link(linker);

	linker.link(m_modelBound);
	linker.link(m_geometryData);
}
/* ------------------------------------------------------- */
void Geometry::save(Stream& stream) const
{
	Spatial::save(stream);

	stream.write(m_modelBound);
	stream.write(m_geometryData);
}
/* ------------------------------------------------------- */
int Geometry::getDiskUsed() const
{
	return Spatial::getDiskUsed() + sizeof(BoundingVolume*) + sizeof(GeometryData*);
}
/* ------------------------------------------------------- */
bool Geometry::fowardAll(Fowarder& c)
{
	if (Spatial::fowardAll(c))
	{
		m_modelBound->fowardAll(c);
		m_geometryData->fowardAll(c);
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
void Geometry::addEffect(Ptr<Effect> effect)
{
	if (!m_geometryData->getEffects().contains(effect))
	{
		if (m_geometryData->getRefCount() > 1)
		{
			m_geometryData->removeRef();
			m_geometryData = m_geometryData->copy();
			m_geometryData->addRef();
			m_geometryData->addEffect(effect);
			registerData();
		}
		else
		{
			m_geometryData->addEffect(effect); // TODO resort in rendertree
		}	
	}
}
/* ------------------------------------------------------- */
void Geometry::removeEffect(Ptr<Effect> effect)
{
	if (m_geometryData->getEffects().contains(effect))
	{
		if (m_geometryData->getRefCount() > 1)
		{
			m_geometryData->removeRef();
			m_geometryData = m_geometryData->copy();
			m_geometryData->addRef();
			m_geometryData->removeEffect(effect);
			registerData();
		}
		else
		{
			m_geometryData->removeEffect(effect); // TODO resort in rendertree
		}	
	}
}
/* ------------------------------------------------------- */
void Geometry::addRenderPass(Ptr<RenderPass>& renderPass)
{
	Spatial::addRenderPass(renderPass);
	if (!m_geometryData->isRegistered())
		renderPass->getRenderer()->add(m_geometryData);
	m_geometryData->addInstance(this, renderPass);
}
/* ------------------------------------------------------- */
void Geometry::removeRenderPass(Ptr<RenderPass>& renderPass)
{
	Spatial::removeRenderPass(renderPass);
	m_geometryData->removeInstance(this, renderPass);
}
/* ------------------------------------------------------- */
const BoundingVolume* Geometry::getModelBound() const
{
	return m_modelBound;
}
/* ------------------------------------------------------- */
BoundingVolume* Geometry::changeModelBound()
{
	m_boundChanged = true;
	if (!m_modelBound)
		m_modelBound = newBoundingVolume();
	return m_modelBound;
}
/* ------------------------------------------------------- */
Ptr<VertexData>& Geometry::getVertexData()
{
	return m_geometryData->getVertexData();
}
/* ------------------------------------------------------- */
Ptr<GeometryData>& Geometry::getGeometryData()
{
	return m_geometryData;
}
/* ------------------------------------------------------- */
void Geometry::registerInstance()
{
	for (List< Ptr<RenderPass> >::Iterator i = m_renderPasses.begin(); i != false; i++)
	{
		m_geometryData->addInstance(this, *i);
	}
}
/* ------------------------------------------------------- */
void Geometry::unregisterInstance()
{
	for (List< Ptr<RenderPass> >::Iterator i = m_renderPasses.begin(); i != false; i++)
	{
		m_geometryData->addInstance(this, *i);
	}
}
/* ------------------------------------------------------- */
void Geometry::updateBound()
{
	if (!m_worldBound)
		m_worldBound = newBoundingVolume();
	(*m_worldBound) = (*m_modelBound);
	m_worldBound->transform(m_world);
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
void Geometry::registerData(Renderer* renderer)
{
	Ptr<GeometryData>& newg = (renderer) ?
		renderer->add(m_geometryData) :
		m_geometryData->getRenderer()->add(m_geometryData);
	if (newg != m_geometryData) // This geometryData objecta already exists -> merge
	{
		m_geometryData->removeRef();
		m_geometryData = newg;
		m_geometryData->addRef();
	}
}

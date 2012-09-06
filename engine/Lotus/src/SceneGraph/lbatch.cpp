/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lbatch.h>
#include <scenegraph\lrenderer.h>

using namespace Lotus;


/* ------------------------------------------------------- */
/* class RenderPass:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
RenderPass::RenderPass(Renderer* renderer)
: m_renderer(renderer)
{}
/* ------------------------------------------------------- */
void RenderPass::load(Stream& stream)
{
	Object::load(stream);
	stream.read(m_globalEffects);
}
/* ------------------------------------------------------- */
void RenderPass::link(PtrLinker& linker)
{
	Object::link(linker);
	linker.link(m_globalEffects);
	//m_renderer = stream.getRenderer();
}
/* ------------------------------------------------------- */
void RenderPass::save(Stream& stream) const
{
	Object::save(stream);
	stream.write(m_globalEffects);
}
/* ------------------------------------------------------- */
int RenderPass::getDiskUsed() const
{
	return Object::getDiskUsed() + m_globalEffects.getDiskUsed();
}
/* ------------------------------------------------------- */
bool RenderPass::fowardAll(Fowarder& c)
{
	if (Object::fowardAll(c))
	{
		for (List< Ptr<Effect> >::Iterator i = m_globalEffects.begin(); i != false; i++)
		{
			(*i)->fowardAll(c);
		}
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
void RenderPass::addEffect(Ptr<Effect> effect)
{
	m_globalEffects.insertFront(effect);
}
/* ------------------------------------------------------- */
void RenderPass::removeEffect(Ptr<Effect> effect)
{
	m_globalEffects.remove(effect);
}
/* ------------------------------------------------------- */
void RenderPass::begin(Renderer* renderer)
{
	for (List< Ptr<Effect> >::Iterator i = m_globalEffects.begin(); i != false; i++)
	{
		(*i)->begin(renderer);
	}
}
/* ------------------------------------------------------- */
void RenderPass::end(Renderer* renderer)
{
	for (List< Ptr<Effect> >::Iterator i = m_globalEffects.begin(); i != false; i++)
	{
		(*i)->end(renderer);
	}
}
/* ------------------------------------------------------- */
Renderer* RenderPass::getRenderer()
{
	return m_renderer;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class InstanceGroup:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
InstanceGroup::InstanceGroup()
: instances(GeometryBatch::ARRAY_SIZE, GeometryBatch::ARRAY_GROW)
{
}
/* ------------------------------------------------------- */
InstanceGroup::InstanceGroup(const InstanceGroup& igroup)
: instances(igroup.instances), renderPass(igroup.renderPass)
{
}
/* ------------------------------------------------------- */
/* class GeometryData:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
GeometryData::GeometryData()
: m_vertexData(0), m_batch(0), m_refCount(0)
{
}
/* ------------------------------------------------------- */
GeometryData::GeometryData(BatchType batchType)
: m_batchType(batchType), m_vertexData(0), m_batch(0), m_refCount(0)
{
}
/* ------------------------------------------------------- */
GeometryData::GeometryData(const GeometryData& g)
: m_vertexData(g.m_vertexData), m_effects(g.m_effects), m_batchType(g.m_batchType), m_batch(0), m_refCount(0)
{
}
/* ------------------------------------------------------- */
GeometryData::GeometryData(Ptr<VertexData>& vdata, const List< Ptr<Effect> >& effects, BatchType batchType)
: m_vertexData(vdata), m_effects(effects), m_batchType(batchType), m_batch(0), m_refCount(0)
{
}
/* ------------------------------------------------------- */
void GeometryData::load(Stream& stream)
{
	Object::load(stream);
	stream.read(m_effects);
	stream.read(m_vertexData);
	stream.read(m_batchType);
}
/* ------------------------------------------------------- */
void GeometryData::link(PtrLinker& linker)
{
	Object::link(linker);
	linker.link(m_effects);
	linker.link(m_vertexData);
}
/* ------------------------------------------------------- */
void GeometryData::save(Stream& stream) const
{
	Object::save(stream);
	stream.write(m_effects);
	stream.write(m_vertexData);
	stream.write(m_batchType);
}
/* ------------------------------------------------------- */
int GeometryData::getDiskUsed() const
{
	return Object::getDiskUsed() + m_effects.getDiskUsed() + sizeof(VertexData*) + sizeof(BatchType);
}
/* ------------------------------------------------------- */
bool GeometryData::fowardAll(Fowarder& c)
{
	if (Object::fowardAll(c))
	{
		for (List< Ptr<Effect> >::Iterator i = m_effects.begin(); i != false; i++)
		{
			(*i)->fowardAll(c);
		}
		m_vertexData->fowardAll(c);
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
Ptr<GeometryData> GeometryData::copy()
{
	return Ptr<GeometryData>(new GeometryData(*this));
}
/* ------------------------------------------------------- */
void GeometryData::addEffect(Ptr<Effect> effect)
{
	m_effects.insertOrdered(effect, EffectPtrComparator());
}
/* ------------------------------------------------------- */
void GeometryData::removeEffect(Ptr<Effect> effect)
{
	m_effects.remove(effect);
}
/* ------------------------------------------------------- */
Ptr<VertexData>& GeometryData::getVertexData()
{
	return m_vertexData;
}
/* ------------------------------------------------------- */
ArrayPtr<GeometryVertex>& GeometryData::changeGeometryVertexData()
{
	if (isRegistered())
		throw VertexDataImmutableException("GeometryData::changeGeometryVertexData(): VertexData is already registered.");
	return m_vertexData->m_gdata;
}
/* ------------------------------------------------------- */
const List< Ptr<Effect> >& GeometryData::getEffects()
{
	return m_effects;
}
/* ------------------------------------------------------- */
BatchType GeometryData::getBatchType() const
{
	return m_batchType;
}
/* ------------------------------------------------------- */
Renderer* GeometryData::getRenderer() const
{
	return m_batch->getRenderer();
}
/* ------------------------------------------------------- */
bool GeometryData::isRegistered() const
{
	return (m_batch != 0);
}
/* ------------------------------------------------------- */
void GeometryData::addInstance(Geometry* instance, Ptr<RenderPass>& renderPass)
{
	m_batch->addInstance(instance, renderPass);
}
/* ------------------------------------------------------- */
void GeometryData::removeInstance(Geometry* instance, Ptr<RenderPass>& renderPass)
{
	if (m_batch)
		m_batch->removeInstance(instance, renderPass);
}
/* ------------------------------------------------------- */
void GeometryData::addRef()
{
	m_refCount++;
}
/* ------------------------------------------------------- */
void GeometryData::removeRef()
{
	m_refCount--;
}
/* ------------------------------------------------------- */
unsigned int GeometryData::getRefCount() const
{
	return m_refCount;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class GeometryBatch:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
GeometryBatch::GeometryBatch(Renderer* renderer)
: m_renderer(renderer), m_instancesChanged(false)
{
}
/* ------------------------------------------------------- */
GeometryBatch::~GeometryBatch()
{
}
/* ------------------------------------------------------- */
void GeometryBatch::removeAllInstances()
{
	m_instanceGroups.removeAll();
	m_instancesChanged = true;
}
/* ------------------------------------------------------- */
Ptr<GeometryData>& GeometryBatch::registerData(Ptr<GeometryData>& data)
{
	assert(data);
	if ((!uniqueOnly() || m_registered.size() == 0))
	{
		bool found;
		VertexDataEquality condition;
		condition.vertexData = data->getVertexData();
		Ptr<GeometryData>& cont = m_registered.find(found, condition);
		if (!found)
		{
			m_registered.insertFront(data);
			data->m_batch = this;
			return data;
		}
		else
		{
			return cont;
		}
	}
	return Ptr<GeometryData>(0);
}
/* ------------------------------------------------------- */
const Ptr<GeometryData>& GeometryBatch::uniqueData() const
{
	if (uniqueOnly() && m_registered.size() > 0)
		return m_registered.front();
	else
		return 0;
}
/* ------------------------------------------------------- */
Renderer* GeometryBatch::getRenderer() const
{
	return m_renderer;
}
/* ------------------------------------------------------- */
void GeometryBatch::update()
{
	if (m_instancesChanged)
	{
		commit();
		m_instancesChanged = false;
	}
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
void GeometryBatch::addInstance(Geometry* instance, Ptr<RenderPass>& renderPass)
{
	for (List<InstanceGroup>::Iterator i = m_instanceGroups.begin(); i != false; i++)
	{
		if (i->renderPass == renderPass)
		{
			i->instances.append(instance);
		}
	}
	// renderPass isn't registered:
	InstanceGroup ig;
	ig.renderPass = renderPass;
	ig.instances.append(instance);
	m_instanceGroups.append(ig);
	m_instancesChanged = true;
}
/* ------------------------------------------------------- */
void GeometryBatch::removeInstance(Geometry* instance, Ptr<RenderPass>& renderPass)
{
	for (List<InstanceGroup>::Iterator i = m_instanceGroups.begin(); i != false; i++)
	{
		if (i->renderPass == renderPass)
		{
			i->instances.removeObject(instance);
			m_instancesChanged = true;
		}
	}
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
bool GeometryBatch::VertexDataEquality::operator() (Ptr<GeometryData>& data)
{
	return (vertexData == data->getVertexData());
}

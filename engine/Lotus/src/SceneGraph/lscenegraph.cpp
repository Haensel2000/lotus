/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lscenegraph.h>
#include <scenegraph\lgeometry.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class SceneGraph:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
SceneGraph::SceneGraph(Renderer* renderer)
: m_roots(0), m_renderer(renderer)
{
	assignRenderer();
}
/* ------------------------------------------------------- */
SceneGraph::SceneGraph(Renderer* renderer, int hashSize)
: m_renderer(renderer)
{
	m_roots = new HashTable<String, Spatial*>(hashSize);
	assignRenderer();
}
/* ------------------------------------------------------- */
SceneGraph::SceneGraph(Renderer* renderer, Set<Serializable*>&  roots)
: m_roots(0), m_renderer(renderer)
{
	fillHash(roots);
	assignRenderer();
}
/* ------------------------------------------------------- */
SceneGraph::~SceneGraph()
{
	if (m_roots)
	{
		for (HashTable<String, Spatial*>::Iterator i = m_roots->begin(); i != false; i++)
		{
			delete (*i);
		}
		delete m_roots;
	}
}
/* ------------------------------------------------------- */
void SceneGraph::load(const char* filename, int bufferSize)
{
	//Stream s(m_renderer, bufferSize);
	//s.load(filename);
	//fillHash(s.getObjects());
}
/* ------------------------------------------------------- */
void SceneGraph::save(const char* filename, int bufferSize)
{
	/*Stream s(m_renderer, bufferSize);

	for (HashTable<String, Spatial*>::Iterator i = m_roots->begin(); i != false; i++)
	{
		s.add(*i);
	}

	s.save(filename);*/
}
/* ------------------------------------------------------- */
Object* SceneGraph::get(const String& root)
{
	return m_roots->get(root);
}
/* ------------------------------------------------------- */
Object* SceneGraph::get(const String& root, const String& name)
{
	Spatial* s = m_roots->get(root);
	if (!s)
		throw new Exception("root object not found in scene graph");
	return s->getObject(name);
}
/* ------------------------------------------------------- */
bool SceneGraph::add(Spatial* root)
{
	return m_roots->insert(root->getName(), root);
}
/* ------------------------------------------------------- */
bool SceneGraph::remove(Spatial* root)
{
	return m_roots->remove(root->getName());
}
/* ------------------------------------------------------- */
void SceneGraph::update(double time)
{
	SpatialUpdater s(time);
	TreeTraverser<SpatialUpdater> ts(s);
	apply(ts);
	//TreeTraverser<Culler> tc(Culler(
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
void SceneGraph::fillHash(Set<Serializable*>& roots)
{
	if (m_roots)
		delete m_roots;

	m_roots = new HashTable<String, Spatial*>(int(roots.size()*1.3));
	for (Array<Serializable*>::Iterator i = roots.begin(); i != false; i++)
	{
		Spatial* tmpSpatial = dynamic_cast<Spatial*>(*i);
		if (tmpSpatial)
			m_roots->insert(tmpSpatial->getName(), tmpSpatial);
	}
}
/* ------------------------------------------------------- */
void SceneGraph::assignRenderer()
{
	//assert(m_renderer);
	if (m_renderer)
		m_renderer->setSceneGraph(this);
}
/* ------------------------------------------------------- */
/* class Deleter:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
bool Deleter::operator()(Object* object)
{
	delete object;
	return true;
}
/* ------------------------------------------------------- */
/* class Instancer:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
bool Instancer::operator()(Spatial* object)
{
	Geometry* g = dynamic_cast<Geometry*>(object);
	if (g)
	{
		g->registerInstance();
	}
	return true;
}
/* ------------------------------------------------------- */
/* class UnInstancer:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
bool UnInstancer::operator()(Spatial* object)
{
	Geometry* g = dynamic_cast<Geometry*>(object);
	if (g)
	{
		g->unregisterInstance();
	}
	return true;
}

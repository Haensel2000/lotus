/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lrenderer.h>
#include <scenegraph\lcamera.h>
#include <scenegraph\ltraverser.h>
#include <scenegraph\lgeometry.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class RenderTree:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
RenderTree::RenderTree(Renderer* renderer)
: m_renderer(renderer)
{
	m_root = new RenderTreeNode;
	m_root->effect = 0;
	m_root->parent = 0;
}
/* ------------------------------------------------------- */
RenderTree::~RenderTree()
{
	recDelete(m_root);
}
/* ------------------------------------------------------- */
Ptr<GeometryData>& RenderTree::add(Ptr<GeometryData>& data)
{
	RenderTreeNode* current = m_root;
	EffectEquality condition;
	bool found;
	for (const List< Ptr<Effect> >::Iterator i = data->getEffects().begin(); i != false; i++)
	{
		condition.effect = *i;
		RenderTreeNode* tmp = current->children.find(found, condition);
		if (!found) // node was not found - create it
		{
			RenderTreeNode* node = new RenderTreeNode;
			node->effect = *i;
			node->parent = current;
			current->children.insertFront(node);
			current = node;
		}
		else
		{
			current = tmp;
		}
	}
	for (List<RenderTreeNode*>::Iterator j = current->children.begin(); j != false; j++)
	{
		if (!(*j)->effect)
		{
			return registerObject(data, (RenderTreeLeaf*)(*j)); 
		}
	}
	RenderTreeLeaf* leaf = new RenderTreeLeaf;
	leaf->parent = current;
	leaf->effect = 0;
	current->children.insertFront(leaf);
	return registerObject(data, leaf);
}
/* ------------------------------------------------------- */
void RenderTree::render()
{
	for (List<RenderTreeNode*>::Iterator i = m_root->children.begin(); i != false; i++)
	{
		recDraw(*i);
	}
}
/* ------------------------------------------------------- */
void RenderTree::commit()
{
	recCommit(m_root);
}
/* ------------------------------------------------------- */
void RenderTree::update()
{
	recCommit(m_root);
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
Ptr<GeometryData>& RenderTree::registerObject(Ptr<GeometryData>& data, RenderTreeLeaf* leaf)
{
	for (List<GeometryBatch*>::Iterator i = leaf->batches.begin(); i != false; i++)
	{
		if	((*i)->getType() == data->getBatchType() || 
			((*i)->getType() == BT_INSTANCE && data->getBatchType() == BT_TRANSFORM))
		{
			Ptr<GeometryData>& gd = (*i)->registerData(data);
			if (gd)
				return gd;
		}
	}
	leaf->batches.insertFront(m_renderer->createGeometryBatch(data->getBatchType()));
	return leaf->batches.front()->registerData(data);
}
/* ------------------------------------------------------- */
void RenderTree::recDraw(RenderTreeNode* node)
{
	if (node->effect)
	{
		node->effect->begin(m_renderer);
		for (List<RenderTreeNode*>::Iterator i = node->children.begin(); i != false; i++)
		{
			recDraw(*i);
		}
		node->effect->end(m_renderer);
	}
	else
	{
		RenderTreeLeaf* l = (RenderTreeLeaf*)node;
		for (List<GeometryBatch*>::Iterator i = l->batches.begin(); i != false; i++)
		{
			(*i)->update();
			(*i)->draw();
		}
	}
}
/* ------------------------------------------------------- */
void RenderTree::recDelete(RenderTreeNode* node)
{
	if (node->effect || node->parent == 0)
	{
		for (List<RenderTreeNode*>::Iterator i = node->children.begin(); i != false; i++)
		{
			recDelete(*i);		
		}
		delete node;
	}
	else
	{
		RenderTreeLeaf* l = (RenderTreeLeaf*)node;
		for (List<GeometryBatch*>::Iterator i = l->batches.begin(); i != false; i++)
		{
			delete (*i);
		}
		delete l;
	}
}
/* ------------------------------------------------------- */
void RenderTree::recCommit(RenderTreeNode* node)
{
	if (node->effect || node->parent == 0)
	{
		for (List<RenderTreeNode*>::Iterator i = node->children.begin(); i != false; i++)
		{
			recCommit(*i);
		}
	}
	else
	{
		RenderTreeLeaf* l = (RenderTreeLeaf*)node;
		for (List<GeometryBatch*>::Iterator i = l->batches.begin(); i != false; i++)
		{
			(*i)->commit();
		}
	}
}
/* ------------------------------------------------------- */
void RenderTree::recUpdate(RenderTreeNode* node)
{
	if (node->effect || node->parent == 0)
	{
		for (List<RenderTreeNode*>::Iterator i = node->children.begin(); i != false; i++)
		{
			recUpdate(*i);
		}
	}
	else
	{
		RenderTreeLeaf* l = (RenderTreeLeaf*)node;
		for (List<GeometryBatch*>::Iterator i = l->batches.begin(); i != false; i++)
		{
			(*i)->update();
		}
	}
}
/* ------------------------------------------------------- */
/* class Renderer:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Renderer::Renderer()
: m_currentFont(-1), m_maxLights(0), m_maxTextures(0), m_renderTree(0)
{
}
/* ------------------------------------------------------- */
Renderer::~Renderer()
{
	if (m_renderTree)
		delete m_renderTree;
}
/* ------------------------------------------------------- */
void Renderer::initialize()
{
	m_renderTree = new RenderTree(this);
}
/* ------------------------------------------------------- */
void Renderer::setSceneGraph(SceneGraph* sgraph)
{
	m_sceneGraph = sgraph;
}
/* ------------------------------------------------------- */
int Renderer::getWidth() const
{
	return m_width;
}
/* ------------------------------------------------------- */
int Renderer::getHeight() const
{
	return m_height;
}
/* ------------------------------------------------------- */
void Renderer::setCamera(Ptr<Camera>& camera)
{
	if (m_camera)
		m_camera->setRenderer(0);
	m_camera = camera;
	camera->setRenderer(this);
}
/* ------------------------------------------------------- */
Ptr<Camera>& Renderer::getCamera()
{
	return m_camera;
}
/* ------------------------------------------------------- */
void Renderer::setBackgroundColor(const Color3& color)
{
	m_backgroundColor = color;
}
/* ------------------------------------------------------- */
const Color3& Renderer::getBackgroundColor() const
{
	return m_backgroundColor;
}
/* ------------------------------------------------------- */
int Renderer::getMaxLights() const
{
	return m_maxLights;
}
/* ------------------------------------------------------- */
int Renderer::getMaxTextures() const
{
	return m_maxTextures;
}
/* ------------------------------------------------------- */
bool Renderer::beginScene()
{
	return true;
}
/* ------------------------------------------------------- */
void Renderer::endScene()
{
}
/* ------------------------------------------------------- */
Ptr<GeometryData>& Renderer::add(Ptr<GeometryData>& data)
{
	assert(m_renderTree);
	return m_renderTree->add(data);
}
/* ------------------------------------------------------- */
inline void Renderer::commit()
{
	assert(m_renderTree);
	m_renderTree->commit();
}
/* ------------------------------------------------------- */
inline void Renderer::update()
{
	assert(m_renderTree);
	m_renderTree->update();
}
/* ------------------------------------------------------- */
void Renderer::drawScene(double time)
{
	m_sceneGraph->update(time);
	clearBuffers();
	beginScene();
	m_renderTree->render();
	endScene();
	displayBackBuffer();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class EffectEquality:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
bool RenderTree::EffectEquality::operator() (RenderTreeNode* obj)
{
	return (effect == obj->effect);
}
/* ------------------------------------------------------- */



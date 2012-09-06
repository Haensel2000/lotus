/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lgroup.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Group:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Group::Group()
: Spatial()
{
}
/* ------------------------------------------------------- */
Group::Group(const Group& g)
: Spatial(g)
{	
}
/* ------------------------------------------------------- */
Group::~Group()
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		delete (*i);
	}
}
/* ------------------------------------------------------- */
void Group::load(Stream& stream)
{
	Spatial::load(stream);

	stream.read(m_children);
}
/* ------------------------------------------------------- */
void Group::link(PtrLinker& linker)
{
	Spatial::link(linker);

	linker.link(m_children);
}
/* ------------------------------------------------------- */
void Group::save(Stream& stream) const
{
	Spatial::save(stream);

	stream.write(m_children);
}
/* ------------------------------------------------------- */
int Group::getDiskUsed() const
{
	return	Spatial::getDiskUsed() + 
			m_children.getDiskUsed();
}
/* ------------------------------------------------------- */
bool Group::fowardAll(Fowarder& c)
{
	if (Spatial::fowardAll(c))
	{
		for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
		{
			(*i)->fowardAll(c);
		}
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
void Group::updateBound()
{
	if (!m_worldBoundIsCurrent)
	{
		cout << getName().toCharArray() << " [B]" << endl;
		if (!m_worldBound)
			m_worldBound = newBoundingVolume();

		assert(m_children.size() > 0);
		if (m_children.size() == 0)
			return;
		else if (m_children.size() == 1)
		{
			*m_worldBound = *m_children.front()->getWorldBound();
		}
		else
		{
			for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
			{
				m_worldBound->growToContain((*i)->getWorldBound());
			}
		}
	}
}
/* ------------------------------------------------------- */
int Group::childCount()
{
	return m_children.size();
}
/* ------------------------------------------------------- */
List<Spatial*>& Group::getChildren()
{
	return m_children;
}
/* ------------------------------------------------------- */
void Group::attach(Spatial* child)
{
	m_children.insertFront(child->copy());
}
/* ------------------------------------------------------- */
void Group::detach(Spatial* child)
{
	if (m_children.remove(child))
	{
		delete child;
	}
}
/* ------------------------------------------------------- */
void Group::addEffect(Ptr<Effect> effect)
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		(*i)->addEffect(effect);
	}
}
/* ------------------------------------------------------- */
void Group::removeEffect(Ptr<Effect> effect)
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		(*i)->removeEffect(effect);
	}
}
/* ------------------------------------------------------- */
void Group::addRenderPass(Ptr<RenderPass>& renderPass)
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		(*i)->addRenderPass(renderPass);
	}
}
/* ------------------------------------------------------- */
void Group::removeRenderPass(Ptr<RenderPass>& renderPass)
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		(*i)->removeRenderPass(renderPass);
	}
}
/* ------------------------------------------------------- */
Group* Group::getGroup(const String& name)
{
	register Group* result = dynamic_cast<Group*>(getChild(name));
	assert(result);
	return result;
}
/* ------------------------------------------------------- */
Spatial* Group::getChild(const String& name)
{
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		if ((*i)->getName() == name)
			return *i;
	}
	assert(false);
	return 0;
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
Spatial* Group::copy()
{
	Group* result = new Group(*this);
	for (List<Spatial*>::Iterator i = m_children.begin(); i != false; i++)
	{
		result->m_children.insertFront((*i)->copy());
	}
	return result;
}
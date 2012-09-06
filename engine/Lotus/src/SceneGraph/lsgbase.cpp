/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lsgbase.h>
#include <scenegraph\ltraverser.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Object :                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Object::Object()
{}
/* ------------------------------------------------------- */
Object::Object(const String& name)
{
	setName(name);
}
/* ------------------------------------------------------- */
void Object::setName(const String& name)
{
	m_name = name;
}
/* ------------------------------------------------------- */
const String& Object::getName() const
{
	return m_name;
}
/* ------------------------------------------------------- */
/*                   PUBLIC VIRTUAL                        */
/* ------------------------------------------------------- */
void Object::load(Stream& stream)
{
	//Serializable::load(stream, linker);

	stream.read(m_name);
}
/* ------------------------------------------------------- */
void Object::save(Stream& stream) const
{
	Serializable::save(stream);

	stream.write(m_name);
}
/* ------------------------------------------------------- */
int Object::getDiskUsed() const
{
	return	Serializable::getDiskUsed() +					
			m_name.getDiskUsed();							// name
}
/* ------------------------------------------------------- */
bool Object::fowardAll(Fowarder& c)
{
	return c((Object*)this);
}
/* ------------------------------------------------------- */
Object* Object::getObject(const String& name) const
{
	GraphTraverser<Seeker> s = GraphTraverser<Seeker>(Seeker(name));
	s.apply((Object*)this);
	return s.getOperation().getTarget();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Controllable:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
void Controllable::load(Stream& stream)
{
	Object::load(stream);

	stream.read(m_controllers);
}
/* ------------------------------------------------------- */
void Controllable::link(PtrLinker& linker)
{
	Object::link(linker);
	
	linker.link(m_controllers);
}
/* ------------------------------------------------------- */
void Controllable::save(Stream& stream) const
{	
	Object::save(stream);

	stream.write(m_controllers);
}
/* ------------------------------------------------------- */
int Controllable::getDiskUsed() const
{
	return	Object::getDiskUsed()	+
			m_controllers.getDiskUsed();	
}
/* ------------------------------------------------------- */
bool Controllable::fowardAll(Fowarder& c)
{
	if (Object::fowardAll(c))
	{
		for (List< Ptr<Controller> >::Iterator i = m_controllers.begin(); i != false; i++)
		{
			(*i)->fowardAll(c);
		}
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
void Controllable::addController(Ptr<Controller>& controller)
{
	controller->setObject(this);
	m_controllers.insertFront(controller);
}
/* ------------------------------------------------------- */
void Controllable::removeController(Ptr<Controller>& controller)
{
	controller->setObject(0);
	m_controllers.remove(controller);
}
/* ------------------------------------------------------- */
void Controllable::removeAllControllers()
{
	for (List< Ptr<Controller> >::Iterator i = m_controllers.begin(); i != false; i++)
	{
		removeController(*i);
	}
}
/* ------------------------------------------------------- */
int Controllable::getControllerCount()
{
	return m_controllers.size();
}
/* ------------------------------------------------------- */
void Controllable::updateControllers(double time)
{
	for (List< Ptr<Controller> >::Iterator i = m_controllers.begin(); i != false; i++)
	{
		(*i)->update(time);
	}
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Controller  :                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
void Controller::setObject(Object* obj)
{
	m_object = obj;
}

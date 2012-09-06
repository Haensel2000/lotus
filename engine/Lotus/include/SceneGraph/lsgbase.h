/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSGBASE_H
#define _HDR_LSGBASE_H

#include <system\lstream.h>
#include <system\llist.h>
#include <system\lstring.h>
#include <system\lserializable.h>

namespace Lotus
{

	class Controller;
	class Fowarder;

	/* class Object
	 * This class is the base class for all objects that are used in the scenegraph.
	 * It gives the facility to name objects in the scenegraph, and to search for objects
	 * by name. Notice that not all of the derived classes are direct members of a hierachical 
	 * scene tree but members of the scenegraph (i.e. Controller). */
	class Object : public Serializable
	{
	private:
		String m_name;	
	public:
		Object();
		Object(const String& name);
		void setName(const String& name);
		const String& getName() const;
		Object* getObject(const String& name) const;

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);	
	};
	

	/* class Controllable
	 * In a . */
	class Controllable : public Object
	{
	private:
		mutable List< Ptr<Controller> > m_controllers;
	public:

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		// Controllers:
		void addController(Ptr<Controller>& controller);
		void removeController(Ptr<Controller>& controller);
		void removeAllControllers();
		int getControllerCount();
		void updateControllers(double time);
	};

	class Controller : public Object
	{
	protected:
		Object* m_object;
	public:
		//Controller();
		void setObject(Object* obj);
		virtual void update(double time) = 0;
	};

}

#endif
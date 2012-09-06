/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSERIALIZABLE_H
#define _HDR_LSERIALIZABLE_H

#include <system\lstream.h>
#include <system\lptrlinker.h>
#include <system\llist.h>
#include <system\lstring.h>
#include <system\lplatforms.h>

namespace Lotus
{
	/* class Serializable
	 * Every class that is intended to be used by the streaming system has to be
	 * derived from Serializable. It has to expose a parameterless contstructor.
	 * Notice the requirement to register derived classes in the RegisterClasses
	 * method of the stream class (register.cpp). */
	class Serializable
	{
	private:
		unsigned int m_ID;
		static unsigned int s_nextID;
	public:
		Serializable();

		template <class T> static Serializable* Factory(Stream& stream, PtrLinker& linker)
		{
			T* object = new T();
			Serializable* linkID;
			stream.read(linkID);
			linker.addLink(linkID, object);
			object->load(stream);
			return object;
		}

		int getID() const;
		virtual String getType() const;

		virtual void load(Stream& stream) = 0;
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
	};

}

#endif
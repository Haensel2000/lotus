/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LPTRLINKER_H
#define _HDR_LPTRLINKER_H

#include <system\llist.h>
#include <system\lpointer.h>

#include <map>

using std::map;

namespace Lotus
{
	class Serializable;

	class PtrLinker
	{
	private:
		map<Serializable*, Serializable*> m_objectLinks;
	public:
		PtrLinker();

		void addLink(Serializable* oldPtr, Serializable* newPtr);
		Serializable* getLink(Serializable* from);

		template <class T> void link(T*& ptr);
		template <class T> void link(List<T>& list);
		template <class T> void link(Ptr<T>& ptr);

		void link();
	};

#include "lptrlinker.inl"
}

#endif
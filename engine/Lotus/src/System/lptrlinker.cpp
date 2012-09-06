/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lptrlinker.h>
#include <system\lserializable.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class PtrLinker:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
PtrLinker::PtrLinker()
{
}
/* ------------------------------------------------------- */
void PtrLinker::addLink(Serializable* oldPtr, Serializable* newPtr)
{
	m_objectLinks[oldPtr] = newPtr;
}
/* ------------------------------------------------------- */
Serializable* PtrLinker::getLink(Serializable* from)
{
	return m_objectLinks[from];
}
/* ------------------------------------------------------- */
void PtrLinker::link()
{
	for (map<Serializable*, Serializable*>::iterator i = m_objectLinks.begin(); i != m_objectLinks.end(); i++)
	{
		(*i).second->link(*this);
	}
}
/* ------------------------------------------------------- */
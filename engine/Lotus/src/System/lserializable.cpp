/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lserializable.h>

using namespace Lotus;

unsigned int Serializable::s_nextID = 0;

/* ------------------------------------------------------- */
/* class Serializable:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Serializable::Serializable()
{
	m_ID = s_nextID++;
}
/* ------------------------------------------------------- */
int Serializable::getID() const
{
	return m_ID;
}
/* ------------------------------------------------------- */
/*                   PUBLIC VIRTUAL                        */
/* ------------------------------------------------------- */
void Serializable::link(PtrLinker& linker)
{
	// nothing to link here
}
/* ------------------------------------------------------- */
void Serializable::save(Stream& stream) const
{
	stream.write(getType());
	stream.write(this);
}
/* ------------------------------------------------------- */
int Serializable::getDiskUsed() const
{
	return	getType().getDiskUsed()	+						// class name
			sizeof(Serializable*);							// object pointer
}
/* ------------------------------------------------------- */
String Serializable::getType() const
{
	return TypeName(typeid(*this).name());
}
/* ------------------------------------------------------- */
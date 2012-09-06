/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lresourcestream.h>

using namespace Lotus;

String ResourceStream::END_OF_RESOURCE("EOR");
bool ResourceStream::s_registered = false;
HashTable<String, FactoryFunction> ResourceStream::s_factory(ResourceStream::FACTORY_SIZE);

/* ------------------------------------------------------- */
/* class ResourceStream:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
ResourceStream::ResourceStream(const string& filename, bool read) 
	: Stream(filename, read)
{
	if (!s_registered)
	{
		RegisterClasses();
		s_registered = true;
	}
}
/* ------------------------------------------------------- */
Resource* ResourceStream::readResource()
{
	PtrLinker linker;
	Resource* result = static_cast<Resource*>(readObject(linker));
	while (readObject(linker))  ;
	linker.link();
	return result;
}
/* ------------------------------------------------------- */
void ResourceStream::writeResource(const Resource& resource)
{
	resource.save(*this);
	Array<Serializable*> attached = resource.getAttached();
	for (Array<Serializable*>::Iterator i = attached.begin(); i != attached.end(); i++)
	{
		(*i)->save(*this);
	}
	write(END_OF_RESOURCE);
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
Serializable* ResourceStream::readObject(PtrLinker& linker)
{
	String className;
	read(className);
	
	if (className == END_OF_RESOURCE)
	{
		return 0;
	}

	FactoryFunction factory = s_factory.get(className);
	if (!factory)
		throw ClassNotFoundException("Class " + className.toString() + " is not registered");

	unsigned int pos = m_filePos;
	Serializable* object = factory(*this, linker);
	unsigned int read = m_filePos - pos;
	assert(read == object->getDiskUsed());

	return object;
}

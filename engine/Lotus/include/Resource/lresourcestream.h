/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LRESOURCESTREAM_H
#define _HDR_LRESOURCESTREAM_H

#include <resource\lresource.h>
#include <system\lstream.h>
#include <system\lptrlinker.h>

namespace Lotus
{
	typedef Serializable* (*FactoryFunction)(Stream&, PtrLinker&);

	/* class ResourceStream
	 * A ResourceStream loads resourcedata and puts it into the resource pool. */
	class ResourceStream : public Stream
	{
	private:
		static const int FACTORY_SIZE = 257;
		static bool s_registered;
		static HashTable<String, FactoryFunction> s_factory;
		static String END_OF_RESOURCE;

		Serializable* readObject(PtrLinker& linker);		
	public:
		static void RegisterClasses();
		
		ResourceStream(const string& filename, bool read);

		Resource* readResource();
		void writeResource(const Resource& resource);	
	};
}

#endif
/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <Resource\ltexture.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Texture:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Texture::Texture()
{}
/* ------------------------------------------------------- */
Texture::Texture(ArrayPtr<unsigned int>& data)
: m_data(data)
{}
/* ------------------------------------------------------- */
void Texture::load(Stream& stream)
{
	Object::load(stream);
	int size;
	stream.read(size);
	unsigned int* iarr = new unsigned int[size];
	stream.read(iarr, size);
	m_data = ArrayPtr<unsigned int>(iarr, size);
}
/* ------------------------------------------------------- */
void Texture::save(Stream& stream) const
{
	Object::save(stream);
	stream.write(m_data.size());
	stream.write(m_data.toInternal(), m_data.size());
}
/* ------------------------------------------------------- */
int Texture::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(int) + sizeof(unsigned int)*m_data.size();
}
/* ------------------------------------------------------- */
String Texture::getType() const
{
	return String("Lotus::Texture");
}
/* ------------------------------------------------------- */
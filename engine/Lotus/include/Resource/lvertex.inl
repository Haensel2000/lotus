 /****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class VertexBuffer:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> void VertexBuffer::add(Array<T>& data, VertexElement element)
{
	if (m_size == 0)
		m_size = data.size();
	else if (data.size() != m_size)
		throw IncompatibleArgumentException("New VertexElement Array does not match in size with the vertexbuffer");
	assert(sizeof(T) == m_vertexType.getVertexElementSize(element));
	addData(reinterpret_cast<const void*>(data.toInternal()), data.size()*sizeof(T), element);
}
/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class Stream:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> void Stream::write(const T& value)
{
	writeToBuffer(&value, sizeof(T));
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::write(const Ptr<T> value)
{
	const T* ptr = value.toInternal();
	writeToBuffer(&ptr, sizeof(T*));
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::write(const T* arr, int length)
{
	writeToBuffer(arr, sizeof(T)*length);
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::write(const List<T>& list)
{
	write(list.size());
	for (const List<T>::Iterator i = list.begin(); i != false; i++)
	{
		write(*i);
	}
}
/* ------------------------------------------------------- */
template <class T> void Stream::write(const Array<T>& arr)
{
	write(arr.size());
	write(arr.toInternal(), arr.size());
}
/* ------------------------------------------------------- */
template <class T> void Stream::read(T& value)
{
	readFromBuffer(&value, sizeof(T));
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::read(Ptr<T>& value)
{
	T* tmp;
	readFromBuffer(&tmp, sizeof(T*));
	if (!m_sharedLinks->exists(tmp))
		m_sharedLinks->insert(tmp, Ptr<Serializable>(tmp));
	value = cast<T>(m_sharedLinks->get(tmp));
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::read(T* arr, int length)
{
	readFromBuffer(arr, sizeof(T)*length);
	assert(m_localBufferPos <= m_bufferSize);
}
/* ------------------------------------------------------- */
template <class T> void Stream::read(List<T>& list)
{
	int size;
	read(size);
	T obj;
	for (int i = 0; i < size; i++)
	{
		read(obj);
		list.insertFront(obj);
	}
}
/* ------------------------------------------------------- */
template <class T> void Stream::read(Array<T>& arr)
{
	int size;
	read(size);
	arr.setCapacity(size);
	T obj;
	for (int i = 0; i < size; i++)
	{
		read(obj);
		arr.append(obj);
	}
}
/* ------------------------------------------------------- */
template <class T> unsigned int Stream::getDiskUsed(const T& obj)
{
	return sizeof(T);
}
/* ------------------------------------------------------- */
template <class T> unsigned int Stream::getDiskUsed(const Ptr<T>& obj)
{
	return sizeof(T*);
}
/* ------------------------------------------------------- */

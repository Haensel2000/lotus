/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class RefCounter:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> RefCounter<T>::RefCounter(T* a_ptr, int a_initalValue = 1) : m_ptr(a_ptr), m_refCount(a_initalValue)
{}
/* ------------------------------------------------------- */
template <class T> void RefCounter<T>::operator++()
{
	m_refCount++;
}
/* ------------------------------------------------------- */
template <class T> void RefCounter<T>::operator--()
{
	m_refCount--;
	assert(m_refCount >= 0);
}
/* ------------------------------------------------------- */
template <class T> bool RefCounter<T>::isNull()
{
	return (m_refCount == 0);
}
/* ------------------------------------------------------- */
template <class T> unsigned int RefCounter<T>::refCount()
{
	return m_refCount;
}
/* ------------------------------------------------------- */
template <class T> T* RefCounter<T>::getPtr()
{
	return m_ptr;
}
/* ------------------------------------------------------- */
template <class T> void RefCounter<T>::setPtr(T* to)
{
	m_ptr = to;
}
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* class Ptr:                                              */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> Ptr<T>::Ptr(T* a_objPtr)
: m_ptr(a_objPtr), m_refCount(0)
{
	//m_object = (a_objPtr) ? new RefCounter<T>(a_objPtr) : NULL;
	if (m_ptr)
		m_refCount = new int(1);
}
/* ------------------------------------------------------- */
template <class T> Ptr<T>::Ptr(const Ptr<T>& a_ptr) 
: m_ptr(a_ptr.m_ptr), m_refCount(a_ptr.m_refCount)
{
	incr();
}
/* ------------------------------------------------------- */
template <class T> Ptr<T>::~Ptr()
{
	release();
}
/* ------------------------------------------------------- */
template <class T> void Ptr<T>::operator=(T* a_objPtr)
{
	if (m_ptr == a_objPtr)
		return;
	release();	
	m_ptr = a_objPtr;
	if (m_ptr)
		m_refCount = new int(1);
}
/* ------------------------------------------------------- */
template <class T> void Ptr<T>::operator=(const Ptr<T>& a_ptr)
{
	if (m_ptr == a_ptr.m_ptr)
		return;
	release();	
	m_ptr = a_ptr.m_ptr;
	m_refCount = a_ptr.m_refCount;
	incr();
}
/* ------------------------------------------------------- */
template <class T> template <class R> Ptr<T>::operator Ptr<R>() 
{
	return Ptr<R>(m_ptr, m_refCount);
}
/* ------------------------------------------------------- */
template <class T> template <class R> Ptr<R> Ptr<T>::cast()
{
	R* ptr = (R*)(m_ptr);
	int* rcount = (ptr) ? m_refCount : 0;
	return Ptr<R>(ptr, rcount);
}	
/* ------------------------------------------------------- */
template <class T> Ptr<T>::operator bool() const
{
	return (m_ptr != 0);
}
/* ------------------------------------------------------- */
template <class T> bool Ptr<T>::operator==(const Ptr<T>& a_ptr) const
{
	return (m_ptr == a_ptr.m_ptr);
}
/* ------------------------------------------------------- */
template <class T> bool Ptr<T>::operator!=(const Ptr<T>& a_ptr) const
{
	return (m_ptr != a_ptr.m_ptr);
}
/* ------------------------------------------------------- */
template <class T> T* Ptr<T>::operator->()
{
	assert(m_ptr);
	return m_ptr;
}
/* ------------------------------------------------------- */
template <class T> const T* Ptr<T>::operator->() const
{
	assert(m_ptr);
	return m_ptr;
}
/* ------------------------------------------------------- */
template <class T> T& Ptr<T>::operator*()
{
	assert(m_ptr);
	return *m_ptr;
}
/* ------------------------------------------------------- */
template <class T> T* Ptr<T>::toInternal() const
{
	assert(m_ptr);
	return m_ptr;
}
/* ------------------------------------------------------- */
template <class T> unsigned int Ptr<T>::hash() const
{
	return (reinterpret_cast<unsigned int>(m_ptr) >> 3) * 2654435761;
}
/* ------------------------------------------------------- */
template <class T> unsigned int Ptr<T>::refCount() const
{
	return *m_refCount;
}
/* ------------------------------------------------------- */
/*                     PRIVATE                             */
/* ------------------------------------------------------- */
template <class T> Ptr<T>::Ptr(T* a_objPtr, int* a_refCount)
: m_ptr(a_objPtr), m_refCount(a_refCount)
{
	incr();
}
/* ------------------------------------------------------- */
template <class T> void Ptr<T>::release()
{
	if (m_refCount)
	{
		--(*m_refCount);
		if (*m_refCount == 0)
		{
			delete m_ptr;
			delete m_refCount;

		}
	}
}
/* ------------------------------------------------------- */
template <class T> void Ptr<T>::incr()
{
	if (m_refCount)
		++(*m_refCount);
}
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/* class ArrayPtr:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::ArrayPtr()
: m_size(0)
{
	m_object = 0;
}
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::ArrayPtr(int a_size) : m_size(a_size)
{
	assert(a_size > 0);
	m_object = new RefCounter<T>(new T[a_size]);
}
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::ArrayPtr(T* a_arrPtr, int a_size) : m_size(a_size)
{
	assert(a_size > 0 && a_arrPtr);
	m_object = new RefCounter<T>(a_arrPtr);
	//memcpy(m_object->getPtr(), a_arrPtr, sizeof(T)*a_size);
}
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::ArrayPtr(const ArrayPtr<T>& a_ptr) : m_object(a_ptr.m_object), m_size(a_ptr.m_size)
{
	incr();
}
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::~ArrayPtr()
{
	release();
}
/* ------------------------------------------------------- */
template <class T> void ArrayPtr<T>::operator=(const ArrayPtr<T>& a_ptr)
{
	if (m_object == a_ptr.m_object)
		return;
	release();	
	m_object = a_ptr.m_object;
	m_size = a_ptr.m_size;
	incr();
}
/* ------------------------------------------------------- */
template <class T> bool ArrayPtr<T>::operator==(const ArrayPtr<T>& a_ptr) const
{
	return (m_object->getPtr() == a_ptr.m_object->getPtr());
}
/* ------------------------------------------------------- */
template <class T> bool ArrayPtr<T>::operator!=(const ArrayPtr<T>& a_ptr) const
{
	return (m_object->getPtr() != a_ptr.m_object->getPtr());
}
/* ------------------------------------------------------- */
template <class T> T& ArrayPtr<T>::operator[](int a_index)
{
	assert(a_index >= 0 && a_index < m_size && m_object);
	return m_object->getPtr()[a_index];
}
/* ------------------------------------------------------- */
template <class T> const T& ArrayPtr<T>::operator[](int a_index) const
{
	assert(a_index >= 0 && a_index < m_size && m_object);
	return m_object->getPtr()[a_index];
}
/* ------------------------------------------------------- */
template <class T> int ArrayPtr<T>::size() const
{
	assert(m_object);
	return m_size;
}
/* ------------------------------------------------------- */
template <class T> ArrayPtr<T>::operator bool() const
{
	return (m_object != 0);
}
/* ------------------------------------------------------- */
template <class T> const T* ArrayPtr<T>::toInternal() const
{
	assert(m_object);
	return m_object->getPtr();
}
/* ------------------------------------------------------- */
/*                     PRIVATE                             */
/* ------------------------------------------------------- */
template <class T> void ArrayPtr<T>::release()
{
	if (m_object)
	{
		--(*m_object);
		if (m_object->isNull())
		{
			delete[] m_object->getPtr();
			delete m_object;
		}
	}
}
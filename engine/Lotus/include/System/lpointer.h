/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LPOINTER_H
#define _HDR_LPOINTER_H

#include <system\lsystem.h>

namespace Lotus
{
	class PtrLinker;

	/* class RefCounter<T>:
	 * Implements a reference counter, that is assigned to one
	 * certain pointer. It has to be guaranteed by the 
	 * application programmer, that there exists only one 
	 * RefCounter to a certain pointer
	 * Constraints on T: none. */
	template <class T> class RefCounter
	{
	private:
		T* m_ptr;
		int m_refCount;
	public:
		RefCounter(T* a_ptr, int a_initalValue = 1);
		void operator++();
		void operator--();
		bool isNull();
		unsigned int refCount();
		T* getPtr();
		void setPtr(T* to);
	};


	/* class Ptr<T>:
	 * Implements a smart pointer pointing on a type T. It counts the 
	 * references and deletes the object if the reference count
	 * reaches zero. It is not recommended to use a mix of smart
	 * pointers and normal pointers for the same data pointer.
	 * Constraints on T: none. */
	template <class T> class Ptr
	{
	private:
		T* m_ptr;
		int* m_refCount;
		void release(); // decrements reference counter, and deletes the objPtr if necessary	
		void incr();
		
	public:
		// It is not recommended to call this constructor
		Ptr(T* a_objPtr, int* a_refCount);
		/* Call this constructor only if a new pointer is introduced.
		 * The normal call would be: Ptr<MyClass> myPtr = new MyClass(...)*/
		Ptr(T* a_objPtr = 0);
		Ptr(const Ptr<T>& a_ptr);
		~Ptr();
		/* Call this assigment only if a new pointer is introduced or the pointer
		 * is assigned NULL. */
		void operator=(T* a_objPtr);
		void operator=(const Ptr<T>& a_ptr);
		template <class R> operator Ptr<R>();
		template <class R> Ptr<R> cast();
		operator bool() const;
		bool operator==(const Ptr<T>& a_ptr) const;
		bool operator!=(const Ptr<T>& a_ptr) const;
		T* operator->();
		const T* operator->() const;
		T& operator*();

		T* toInternal() const;

		unsigned int hash() const;
		unsigned int refCount() const;

		friend PtrLinker;
	};

	template <class R, class T> Ptr<R> cast(Ptr<T>& ptr)
	{
		return ptr.cast<R>();
	}

	/* class ArrayPtr:
	 * Implements a simple wrapper for a ArrayPtr based on the class Ptr.
	 * The content is automatically destroyed, if there is no reference on 
	 * the data left. This class does only check for out of bounds exceptions
	 * in debug configuration. Some code is duplicated from Ptr to avoid a need
	 * for a virtual destructor and the performance overhead resulting in this. 
	 * Constraints on T: none. */
	template <class T> class ArrayPtr
	{
	private:
		int m_size;
		RefCounter<T>* m_object;
		void release(); // decrements reference counter, and deletes the objPtr if necessary	
		void incr()
		{
			if (m_object)
				++(*m_object);
		}	
	public:
		ArrayPtr();
		ArrayPtr(int a_size);
		ArrayPtr(T* a_arrPtr, int a_size);
		ArrayPtr(const ArrayPtr<T>& a_ptr);
		~ArrayPtr();
		void operator=(const ArrayPtr<T>& a_ptr);
		bool operator==(const ArrayPtr<T>& a_ptr) const;
		bool operator!=(const ArrayPtr<T>& a_ptr) const;
		T& operator[](int a_index);
		const T& operator[](int a_index) const;
		int size() const;
		operator bool() const;

		const T* toInternal() const;
	};

#include "lpointer.inl"
}

#endif
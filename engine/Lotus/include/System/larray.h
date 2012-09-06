/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LARRAY_H
#define _HDR_LARRAY_H

#include "lsystem.h"

namespace Lotus
{		
	/* class Array:
	 * Implements a growable array. The copy semantic is to copy the
	 * data. The initial capacity and growing size can be specified, and capacity
	 * can be set by the method setCapacity(int).
	 * Constraints on T:	operator==
	 *						operator= */
	template <class T> class Array
	{
	private:
		T* m_data;
		int m_capacity;
		int m_growBy;
		int m_size;
	public:
		class Iterator;
		Array(int a_initialCapacity, int a_growBy = 0);
		Array(const Array<T>& a_array);
		~Array();
		void setCapacity(int a_capacity);
		void operator=(Array<T>& a_array);
		// remove returns true, iff the given object was found
		bool removeObject(const T&  a_obj);
		void remove(int a_index);
		void removeAll();
		bool insert(const T& a_obj, int a_index); // returns true iff capacity had to be extended
		bool append(const T& a_obj); // returns true iff capacity had to be extended
		int search(const T& a_obj) const;
		int size() const;
		int capacity() const;
		T& operator[](int a_index);
		const T& operator[](int a_index) const;

		const T* toInternal() const;

		Iterator begin();
		Iterator end();
	};

	/* class Set
	 * Implements a set based on an array data structure. The class
	 * inherits all methods from array but overwrites the insertion
	 * methods (insert, append) so that every object appears in the
	 * set only once. The class adds a method exists that simply calls
	 * search. */
	template <class T> class Set : public Array<T>
	{
	private:
	public:
		Set(int a_initialCapacity, int a_growBy = 0);
		Set(Set<T>& a_set);
		bool insert(const T& a_obj, int a_index); // returns true if item wasn't in the set
		bool append(const T& a_obj); // returns true if item wasn't in the set
		const T& operator[](int a_index);
		bool operator[](const T& a_obj);
		bool contains(const T& a_obj);
	};

#include "larray.inl"
}

#endif
/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LLIST_H
#define _HDR_LLIST_H

#include <system\lsystem.h>

namespace Lotus
{
	/* class List 
	 * Implements a simple linked list.
	 * Constraints on T: operator!=() */
	template <class T> class List
	{
	private:
		class ListItem;
		ListItem* m_begin;
		void deepCopy(const List& a_list);
	public:
		class Iterator;
		List();
		List(const List& a_list);
		~List();
		void operator=(List& a_list);

		bool insert(const T& a_obj, const T& a_after);
		void insertFront(const T& a_obj);
		template <class C> void insertOrdered(const T& a_obj, C comparator); // comparator is smallerThan
		void append(const T& a_obj);
		bool remove(const T& a_obj);
		void removeBack();
		void removeFront();
		void removeAll();
		bool contains(const T& obj) const;
		template <class C> T& find(bool& found, C condition = C());

		T& front();
		const T& front() const;
		T& back();
		const T& back() const;
		Iterator begin();
		const Iterator begin() const;
		int size() const;

		int getDiskUsed() const;
	};

#include "llist.inl"
}

#endif
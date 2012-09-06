/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSTACK_H
#define _HDR_LSTACK_H

#include "lsystem.h"

namespace Lotus
{
	/* class Stack:
	 * Implements a Stack of constant size that is allocated in
	 * stack-memory. It provides beside the compulsory pop and push methods
	 * a method peek that returns the top of the stack but does not remove it.
	 * Constraints on T: operator= */
	template <class T, int SIZE> class Stack
	{
	private:
		T m_data[SIZE];
		int m_current;
	public:
		Stack();
		Stack(Stack<T,SIZE>& a_stack);
		void operator=(Stack<T,SIZE>& a_stack);
		
		void clear();
		void push(const T& a_element);		
		
		T& pop();
		T& peek();
		
		bool isEmpty();
		bool isFull();		
	};

#include "lstack.inl"
}



#endif
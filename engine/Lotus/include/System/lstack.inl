/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class Stack:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T, int SIZE> Stack<T,SIZE>::Stack() : m_current(-1)
{
}
/* ------------------------------------------------------- */
template <class T, int SIZE> Stack<T,SIZE>::Stack(Stack<T,SIZE>& a_stack)
{
	operator=(a_stack);
}
/* ------------------------------------------------------- */
template <class T, int SIZE> void Stack<T,SIZE>::operator=(Stack<T,SIZE>& a_stack)
{
	for (int i = 0; i <= a_stack.m_current; i++)
	{
		m_data[i] = a_stack.m_data[i];
	}
	m_current = a_stack.m_current;
}
/* ------------------------------------------------------- */
template <class T, int SIZE> void Stack<T,SIZE>::clear()
{
	m_current = -1;
}
/* ------------------------------------------------------- */
template <class T, int SIZE> void Stack<T,SIZE>::push(const T& a_element)
{
	assert(m_current < SIZE-1);
	m_data[++m_current] = a_element;
}
/* ------------------------------------------------------- */
template <class T, int SIZE> T& Stack<T,SIZE>::pop()
{
	assert(m_current >= 0);
	return m_data[m_current--];
}
/* ------------------------------------------------------- */
template <class T, int SIZE> T& Stack<T,SIZE>::peek()
{
	return m_data[m_current];
}
/* ------------------------------------------------------- */
template <class T, int SIZE> bool Stack<T,SIZE>::isEmpty()
{
	return (m_current == -1);
}
/* ------------------------------------------------------- */
template <class T, int SIZE> bool Stack<T,SIZE>::isFull()
{
	return (m_current == SIZE-1);
}
/* ------------------------------------------------------- */
 /****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class List :                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> class List<T>::Iterator
{
private:
	mutable ListItem* m_current;
public:
	Iterator(ListItem* a_current) : m_current(a_current)
	{}
	
	Iterator operator++(int) const
	{
		Iterator result(m_current);
		m_current = m_current->next();
		return result;
	}

	T& operator*()
	{
		return m_current->getValue();
	}

	const T& operator*() const
	{
		return m_current->getValue();
	}

	T* operator->()
	{
		return &(m_current->getValue());
	}

	const T* operator->() const
	{
		return &(m_current->getValue());
	}

	operator bool() const
	{
		return (m_current != 0);
	}
};
/* ------------------------------------------------------- */
template <class T> List<T>::List() : m_begin(0)
{}
/* ------------------------------------------------------- */
template <class T> List<T>::List(const List& a_list)
{
	deepCopy(a_list);
}
/* ------------------------------------------------------- */
template <class T> List<T>::~List()
{
	removeAll();
}
/* ------------------------------------------------------- */
template <class T> void List<T>::operator=(List& a_list)
{
	if (m_begin == a_list.m_begin) // shared data
		return;
	removeAll();
	deepCopy(a_list);
}
/* ------------------------------------------------------- */
template <class T> bool List<T>::insert(const T& a_obj, const T& a_after)
{
	ListItem* current = m_begin;
	while (current && current->getValue() != a_after)
		current = current->next();
	if (!current)
		return false;
	ListItem* tmp = current->next();
	current->setNext(new ListItem(a_obj, tmp));
	return true;
}
/* ------------------------------------------------------- */
template <class T> void List<T>::insertFront(const T& a_obj)
{
	m_begin = new ListItem(a_obj, m_begin);
}
/* ------------------------------------------------------- */
template <class T> template <class C> void List<T>::insertOrdered(const T& a_obj, C comparator)
{
	ListItem* current = m_begin;
	if (!current)
	{
		m_begin = new ListItem(a_obj, 0);
		return;
	}
	while (current->next() && comparator(current->next()->getValue(), a_obj))
	{
		current = current->next();
	}
	current->setNext(new ListItem(a_obj, current->next()));
}
/* ------------------------------------------------------- */
template <class T> void List<T>::append(const T& a_obj)
{
	ListItem* current = m_begin;
	if (!current)
	{
		m_begin = new ListItem(a_obj, 0);
		return;
	}
	while (current->next())
		current = current->next();
	current->setNext(new ListItem(a_obj, 0));
}
/* ------------------------------------------------------- */
template <class T> bool List<T>::remove(const T& a_obj)
{
	ListItem* current = m_begin;
	ListItem* prev = 0;
	while (current && current->getValue() != a_obj)
	{
		prev = current;
		current = current->next();
	}
	if (!current)
		return false;
	if (prev)
		prev->setNext(current->next());
	else
		m_begin = 0;
	delete current;
	return true;
}
/* ------------------------------------------------------- */
template <class T> void List<T>::removeBack()
{
	ListItem* current = m_begin;
	if (!current)
		return;
	if (!current->next())
	{
		delete current;
		m_begin = 0;
		return;
	}
	while (current->next()->next())
		current = current->next();
	delete current->next();
	current->setNext(0);
}
/* ------------------------------------------------------- */
template <class T> void List<T>::removeFront()
{
	if (!m_begin)
		return;
	ListItem* toDelete = m_begin;
	m_begin = m_begin->next();
	delete toDelete;
}
/* ------------------------------------------------------- */
template <class T> void List<T>::removeAll()
{
	ListItem* current = m_begin;
	ListItem* toDelete;
	while (current)
	{
		toDelete = current;
		current = current->next();
		delete toDelete;
	}
	m_begin = 0;
}
/* ------------------------------------------------------- */
template <class T> bool List<T>::contains(const T& obj) const
{
	ListItem* current = m_begin;
	while (current)
	{
		if (obj == current->getValue())
			return true;
		current = current->next();
	}
	return false;
}
/* ------------------------------------------------------- */
template <class T> template <class C> T& List<T>::find(bool& found, C condition)
{
	ListItem* current = m_begin;
	while (current)
	{
		if (condition(current->getValue()))
		{
			found = true;
			return current->getValue();
		}
		current = current->next();
	}
	found = false;
	T null;
	return null;
}
/* ------------------------------------------------------- */
template <class T> T& List<T>::front()
{
	assert(m_begin);
	return m_begin->getValue();
}
/* ------------------------------------------------------- */
template <class T> const T& List<T>::front() const
{
	assert(m_begin);
	return m_begin->getValue();
}
/* ------------------------------------------------------- */
template <class T> T& List<T>::back()
{
	assert(m_begin);
	ListItem* current = m_begin;
	while (current->next())
		current = current->next();
	return current->getValue();
}
/* ------------------------------------------------------- */
template <class T> const T& List<T>::back() const
{
	assert(m_begin);
	ListItem* current = m_begin;
	while (current->next())
		current = current->next();
	return current->getValue();
}
/* ------------------------------------------------------- */
template <class T> typename List<T>::Iterator List<T>::begin()
{
	return List<T>::Iterator(m_begin);
}
/* ------------------------------------------------------- */
template <class T> typename const List<T>::Iterator List<T>::begin() const
{
	return List<T>::Iterator(m_begin);
}
/* ------------------------------------------------------- */
template <class T> int List<T>::size() const
{
	int result = 0;
	ListItem* current = m_begin;
	while (current)
	{
		current = current->next();
		result++;
	}
	return result;
}
/* ------------------------------------------------------- */
template <class T> int List<T>::getDiskUsed() const
{
	return sizeof(int) + size()*Stream::getDiskUsed<T>();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/*                     PRIVATE                             */
/* ------------------------------------------------------- */
template <class T> void List<T>::deepCopy(const List& a_list)
{
	ListItem* argCurrent = a_list.m_begin;
	if (!argCurrent)
	{
		m_begin = 0;
		return;
	}
	ListItem* current = m_begin = new ListItem(argCurrent->getValue(), 0);
	argCurrent = argCurrent->next();
	while (argCurrent)
	{
		current->setNext(new ListItem(argCurrent->getValue(), 0));
		argCurrent = argCurrent->next();
		current = current->next();
	}
}
/* ------------------------------------------------------- */
template <class T> class List<T>::ListItem
{
private:
	T m_value;
	ListItem* m_next;
public:
	ListItem(const T& a_value, ListItem* a_next) : m_value(a_value), m_next(a_next)
	{}

	T& getValue()
	{
		return m_value;
	}

	ListItem* next()
	{
		return m_next;
	}

	void setNext(ListItem* a_next)
	{
		m_next = a_next;
	}
};
/* ------------------------------------------------------- */
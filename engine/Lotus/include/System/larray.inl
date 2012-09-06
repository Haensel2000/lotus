/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class Array:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> Array<T>::Array(int a_initialCapacity, int a_growBy = 0) 
	: m_capacity(a_initialCapacity), m_growBy(a_growBy), m_size(0)
{
	assert(a_initialCapacity > 0 && a_growBy >= 0);
	m_data = new T[m_capacity];
}
/* ------------------------------------------------------- */
template <class T> Array<T>::Array(const Array<T>& a_array)
	: m_capacity(a_array.m_capacity), m_growBy(a_array.m_growBy), m_size(a_array.m_size)
{
	m_data = new T[m_capacity];
	copy_backward(a_array.m_data, a_array.m_data + m_size, m_data + m_size);
}
/* ------------------------------------------------------- */
template <class T> Array<T>::~Array()
{
	delete[] m_data;
}
/* ------------------------------------------------------- */
template <class T> void Array<T>::setCapacity(int a_capacity)
{
	assert(a_capacity > 0);
	if (a_capacity == m_capacity)
		return;	
	m_size = min(m_size, a_capacity);
	T* tmp = new T[a_capacity];
	copy_backward(m_data, m_data + m_size, tmp + m_size);
	delete[] m_data;
	m_data = tmp;
	m_capacity = a_capacity;
}
/* ------------------------------------------------------- */
template <class T> void Array<T>::operator=(Array<T>& a_array)
{
	assert(m_data != a_array.m_data);
	delete[] m_data;
	m_capacity = a_array.m_capacity;
	m_size = a_array.m_size;
	m_growBy = a_array.m_growBy;
	m_data = new T[m_capacity];
	copy_backward(a_array.m_data, a_array.m_data + m_size, m_data + m_size);
}
/* ------------------------------------------------------- */
template <class T> bool Array<T>::removeObject(const T&  a_obj)
{
	int i = search(a_obj);
	if (i >= 0)
	{
		remove(i);
		return true;
	}
	else
	{
		return false;
	}
}
/* ------------------------------------------------------- */
template <class T> void Array<T>::remove(int a_index)
{
	assert(a_index >= 0 && a_index < m_size);
	if (m_size - a_index > 0)
		copy(m_data + a_index + 1, m_data + m_size, m_data + a_index); 
	m_size--;
	if (m_capacity - m_size >= m_growBy && m_size > 0)
		setCapacity(m_size);
}
/* ------------------------------------------------------- */
template <class T> void Array<T>::removeAll()
{
	setCapacity(m_growBy);
	m_size = 0;
}
/* ------------------------------------------------------- */
template <class T> bool Array<T>::insert(const T&  a_obj, int a_index)
{
	assert(a_index >= 0 && a_index < m_size);
	if (m_size+1 > m_capacity)
	{
		setCapacity(m_capacity + m_growBy);
		return true;
	}
	copy_backward(m_data + a_index, m_data + m_size, m_data + m_size + 1);
	m_data[a_index] = a_obj;
	m_size++;
	return false;
}
/* ------------------------------------------------------- */
template <class T> bool Array<T>::append(const T&  a_obj)
{
	if (m_size+1 > m_capacity)
	{
		setCapacity(m_capacity + m_growBy);
		return true;
	}
	m_data[m_size] = a_obj;
	m_size++;
	return false;
}
/* ------------------------------------------------------- */
template <class T> int Array<T>::search(const T&  a_obj) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (a_obj == m_data[i])
			return i;
	}
	return -1;
}
/* ------------------------------------------------------- */
template <class T> int Array<T>::size() const
{
	return m_size;
}
/* ------------------------------------------------------- */
template <class T> int Array<T>::capacity() const
{
	return m_capacity;
}
/* ------------------------------------------------------- */
template <class T> T& Array<T>::operator[](int a_index)
{
	assert(a_index >= 0 && a_index < m_size);
	return m_data[a_index];
}
/* ------------------------------------------------------- */
template <class T> const T& Array<T>::operator[](int a_index) const
{
	assert(a_index >= 0 && a_index < m_size);
	return m_data[a_index];
}
/* ------------------------------------------------------- */
template <class T> const T* Array<T>::toInternal() const
{
	return m_data;
}
/* ------------------------------------------------------- */
template <class T> class Array<T>::Iterator
{
private:
	T* m_ptr;
	int m_size;
	int m_curPos;
public:
	Iterator(T* a_arrayPtr, int a_size, int a_curPos) 
		: m_ptr(a_arrayPtr), m_size(a_size), m_curPos(a_curPos)
	{}

	operator bool()
	{
		return (m_curPos >= 0 && m_curPos < m_size);
	}

	bool operator==(Iterator& a_iterator)
	{
		return (m_ptr == a_iterator.m_ptr);
	}

	bool operator!=(Iterator& a_iterator)
	{
		return (m_ptr != a_iterator.m_ptr);
	}

	T& operator*()
	{
		assert(m_curPos >= 0 && m_curPos < m_size);
		return m_ptr[m_curPos];
	}
	
	T* operator->()
	{
		assert(m_curPos >= 0 && m_curPos < m_size);
		return m_ptr + m_curPos;
	}


	Iterator& operator++() // prefix
	{
		m_curPos++;
		++m_ptr;
		return *this;
	}

	Iterator operator++(int) // postfix
	{
		Iterator result(m_ptr, m_size, m_curPos);
		m_curPos++;
		return result;
	}

	Iterator& operator--() // prefix
	{
		m_curPos--;
		return --m_ptr;
	}

	Iterator operator--(int) // postfix
	{
		m_curPos--;
		return m_ptr--;
	}

};
/* ------------------------------------------------------- */
template <class T> typename Array<T>::Iterator Array<T>::begin()
{
	return Iterator(m_data, m_size, 0);
}
/* ------------------------------------------------------- */
template <class T> typename Array<T>::Iterator Array<T>::end()
{
	return Iterator(m_data + m_size, m_size, m_size);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Set  :                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> Set<T>::Set(int a_initialCapacity, int a_growBy = 0) 
	: Array(a_initialCapacity, a_growBy)
{}
/* ------------------------------------------------------- */
template <class T> Set<T>::Set(Set<T>& a_set)
	: Array(a_set)
{}
/* ------------------------------------------------------- */
template <class T> bool Set<T>::insert(const T& a_obj, int a_index)
{
	if (search(a_obj) >= 0) // object found
		return false;
	Array<T>::insert(a_obj, a_index);
	return true;
}	
/* ------------------------------------------------------- */
template <class T> bool Set<T>::append(const T& a_obj)
{
	if (search(a_obj) >= 0) // object found
		return false;
	Array<T>::append(a_obj);
	return true;
}
/* ------------------------------------------------------- */
template <class T> const T& Set<T>::operator[](int a_index)
{
	return Array<T>::operator[](a_index);
}
/* ------------------------------------------------------- */
template <class T> bool Set<T>::operator[](const T& a_obj)
{
	return (search(a_obj) >= 0);
}
/* ------------------------------------------------------- */
template <class T> bool Set<T>::contains(const T& a_obj)
{
	return (search(a_obj) >= 0);
}
/* ------------------------------------------------------- */
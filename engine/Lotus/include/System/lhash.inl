 /****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* The predefined HashFunctions:                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K> unsigned int HashFunction<K>::operator()(const K& key)
{
	key.hash();	
}
/* ------------------------------------------------------- */
template <class K> unsigned int HashFunction<K*>::operator()(K* key)
{
	return (reinterpret_cast<unsigned int>(key) >> 3) * 2654435761;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class _HashTableItem:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K, class V> _HashTableItem<K,V>::_HashTableItem(const K& a_key, const V& a_value, _HashTableItem<K,V>* a_next = 0) 
	: m_key(a_key), m_value(a_value), m_next(a_next)
{}
/* ------------------------------------------------------- */
template <class K, class V>	K& _HashTableItem<K,V>::getKey()
{
	return m_key;
}
/* ------------------------------------------------------- */
template <class K, class V>	V& _HashTableItem<K,V>::getValue()
{
	return m_value;
}
/* ------------------------------------------------------- */
template <class K, class V>	_HashTableItem<K,V>* _HashTableItem<K,V>::next()
{
	return m_next;
}
/* ------------------------------------------------------- */
template <class K, class V> void _HashTableItem<K,V>::setNext(_HashTableItem<K,V>* a_item)
{
	m_next = a_item;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class _HashSetItem:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K> _HashSetItem<K>::_HashSetItem(const K& a_key, const K& a_value, _HashSetItem<K>* a_next = 0) 
	: m_key(a_key), m_next(a_next)
{}
/* ------------------------------------------------------- */
template <class K>	K& _HashSetItem<K>::getKey()
{
	return m_key;
}
/* ------------------------------------------------------- */
template <class K>	K& _HashSetItem<K>::getValue()
{
	return m_key;
}
/* ------------------------------------------------------- */
template <class K>	_HashSetItem<K>* _HashSetItem<K>::next()
{
	return m_next;
}
/* ------------------------------------------------------- */
template <class K> void _HashSetItem<K>::setNext(_HashSetItem<K>* a_item)
{
	m_next = a_item;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class _HashIterator:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K, class V, class Item> 
_HashIterator<K,V,Item>::_HashIterator(Item** arr, int currentIndex, int arraySize, Item* current)
: m_array(arr), m_currentIndex(currentIndex), m_maxIndex(arraySize-1), m_current(current)
{
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> 
_HashIterator<K,V,Item>::_HashIterator(const _HashIterator& iterator)
: m_array(iterator.m_array), m_currentIndex(iterator.m_currentIndex),
	m_maxIndex(iterator.m_maxIndex), m_current(iterator.m_current)
{
}
/* ------------------------------------------------------- */
template <class K, class V, class Item>  
void _HashIterator<K,V,Item>::operator=(const _HashIterator& iterator)
{
	m_array = iterator.m_array;
	m_currentIndex = iterator.m_currentIndex;
	m_maxIndex = iterator.m_maxIndex;
	m_current = iterator.m_current;
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> _HashIterator<K,V,Item>::operator bool()
{
	return (m_currentIndex != m_maxIndex) || (m_current != 0);
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> 
bool _HashIterator<K,V,Item>::operator==(_HashIterator& iterator)
{
	return	(m_array == iterator.m_array) &&
			(m_currentIndex == iterator.m_currentIndex) &&
			(m_current == iterator.m_current);
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> 
bool _HashIterator<K,V,Item>::operator!=(_HashIterator& iterator)
{
	return ! operator==(iterator);
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> V& _HashIterator<K,V,Item>::operator*()
{
	return getValue();
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> V& _HashIterator<K,V,Item>::getValue()
{
	return m_current->getValue();
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> K& _HashIterator<K,V,Item>::getKey()
{
	return m_current->getKey();
}
/* ------------------------------------------------------- */
template <class K, class V, class Item>
_HashIterator<K,V,Item>& _HashIterator<K,V,Item>::operator++()
{
	incr();
	return (*this);
}
/* ------------------------------------------------------- */
template <class K, class V, class Item> _HashIterator<K,V,Item> _HashIterator<K,V,Item>::operator++(int)
{
	_HashIterator<K,V,Item> res(m_array, m_currentIndex, m_maxIndex+1, m_current);
	incr();
	return res;
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
template <class K, class V, class Item> void  _HashIterator<K,V,Item>::incr()
{
	if (m_current)
		m_current = m_current->next();
	while (m_current == 0 && m_currentIndex < m_maxIndex)
	{
		m_currentIndex++;
		m_current = m_array[m_currentIndex];
	}
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class HashTable:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> HashTable<K,V,H,Item>::HashTable(int a_size, H a_hashFunction) 
	: m_arraySize(a_size), m_hashFunction(a_hashFunction)
{
	assert(a_size > 0);
	m_array = new Item*[a_size];
	for (int i = 0; i < m_arraySize; i++)
	{
		m_array[i] = 0;
	}
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> HashTable<K,V,H,Item>::HashTable(HashTable<K,V,H,Item>& a_htable)
{
	deepCopy(a_htable);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> HashTable<K,V,H,Item>::~HashTable()
{
	removeAll();
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> void HashTable<K,V,H,Item>::operator=(HashTable<K,V,H,Item>& a_htable)
{
	if (m_array[0] == a_htable.m_array[0]) // shared data
		return;
	removeAll();
	deepCopy(a_htable);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> V& HashTable<K,V,H,Item>::operator[](const K& a_key)
{
	return get(a_key);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> const V& HashTable<K,V,H,Item>::operator[](const K& a_key) const
{
	return get(a_key);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> V& HashTable<K,V,H,Item>::get(const K& a_key, bool assertExists = false)
{
	Item* item = getItem(a_key);
	if (item)
		return item->getValue();
	else
	{
		if (assertExists)
			throw ElementNotFoundException("HashTable<K,V,H,Item>::get(const K& a_key, true): a_key was not found.");
		return insertReturn(a_key, V());
	}
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> const V& HashTable<K,V,H,Item>::get(const K& a_key) const
{
	Item* item = getItem(a_key);
	assert(item);
	return item->getValue();
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> bool HashTable<K,V,H,Item>::insert(const K& a_key, const V& a_value)
{
	unsigned int index = m_hashFunction(a_key)%m_arraySize;
	if (!search(a_key, index))
	{
		m_array[index] = new Item(a_key, a_value, m_array[index]);
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> bool HashTable<K,V,H,Item>::remove(const K& a_key)
{
	unsigned int index = m_hashFunction(a_key)%m_arraySize;
	Item* current = m_array[index];
	Item* prev = 0;
	while (current && current->getKey() != a_key)
	{
		prev = current;
		current = current->next();
	}
	if (!current) // key not found
		return false;
	if (prev)
		prev->setNext(current->next());
	else
		m_array[index] = 0;
	delete current;
	return true;
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> void HashTable<K,V,H,Item>::removeAll()
{
	Item* current;
	Item* tmp;
	for (int i = 0; i < m_arraySize; i++)
	{
		current = m_array[i];
		while (current)
		{
			tmp = current;
			current = current->next();
			delete tmp;
		}
		m_array[i] = 0;
	}
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item>  bool HashTable<K,V,H,Item>::exists(const K& a_key)
{
	return (getItem(a_key) != NULL);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> 
typename HashTable<K,V,H,Item>::Iterator HashTable<K,V,H,Item>::begin()
{
	Iterator i = Iterator(m_array, -1, m_arraySize, 0);
	return ++i;
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> 
typename HashTable<K,V,H,Item>::Iterator HashTable<K,V,H,Item>::end()
{
	Item* current = m_array[m_arraySize-1];
	while (current)
		current++;
	return Iterator(m_array, m_arraySize-1, m_arraySize, current);
}
/* ------------------------------------------------------- */
/*                     PRIVATE                             */
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> void HashTable<K,V,H,Item>::deepCopy(HashTable<K,V,H,Item>& a_htable)
{
	m_hashFunction = a_htable.m_hashFunction;
	m_arraySize = a_htable.m_arraySize;
	m_array = new Item*[m_arraySize];
	Item* current;
	Item* currentRemote;
	for (int i = 0; i < m_arraySize; i++)
	{
		if (a_htable.m_array[i])
		{
			current = m_array[i] = new Item(a_htable.m_array[i]->getKey(), a_htable.m_array[i]->getValue());
			currentRemote = a_htable.m_array[i]->next();
			while (currentRemote)
			{
				current->setNext(new Item(currentRemote->getKey(), currentRemote->getValue()));
				current = current->next();
				currentRemote = currentRemote->next();
			}
		}
		else
		{
			m_array[i] = 0;
		}
	}
}
/* ------------------------------------------------------- */
/*                     PROTECTED                           */
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> Item* HashTable<K,V,H,Item>::getItem(const K& a_key)
{
	unsigned int index = m_hashFunction(a_key)%m_arraySize;
	return search(a_key, index);
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> Item* HashTable<K,V,H,Item>::search(const K& a_key, int a_index)
{
	Item* current = m_array[a_index];
	while (current && current->getKey() != a_key)
		current = current->next();
	return current;
}
/* ------------------------------------------------------- */
template <class K, class V, class H, class Item> V& HashTable<K,V,H,Item>::insertReturn(const K& a_key, const V& a_value)
{
	unsigned int index = m_hashFunction(a_key)%m_arraySize;
	Item* item = search(a_key, index);
	if (!item)
	{
		m_array[index] = new Item(a_key, a_value, m_array[index]);
		return m_array[index]->getValue();
	}
	return item->getValue();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class HashSet  :                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class K, class H> HashSet<K,H>::HashSet(int a_size, H a_hashFunction = H())
	: HashTable<K,K,H,_HashSetItem<K> >(a_size, a_hashFunction)
{}
/* ------------------------------------------------------- */
template <class K, class H> HashSet<K,H>::HashSet(HashSet<K,H>& a_hset)
	: HashTable<K,K,H,_HashSetItem<K> >(a_hset)
{}
/* ------------------------------------------------------- */
template <class K, class H> void HashSet<K,H>::operator=(HashSet<K,H>& a_hset)
{
	HashTable<K,K,H,_HashSetItem<K> >::operator=(a_hset);
}
/* ------------------------------------------------------- */
template <class K, class H> bool HashSet<K,H>::operator[](const K& a_key)
{
	return exists(a_key);
}
/* ------------------------------------------------------- */
template <class K, class H> bool HashSet<K,H>::insert(const K& a_key)
{
	return HashTable<K,K,H,_HashSetItem<K> >::insert(a_key, a_key);
}
/* ------------------------------------------------------- */
template <class K, class H> bool HashSet<K,H>::remove(const K& a_key)
{
	return HashTable<K,K,H,_HashSetItem<K> >::remove(a_key);
}
/* ------------------------------------------------------- */
template <class K, class H> void HashSet<K,H>::removeAll()
{
	HashTable<K,K,H,_HashSetItem<K> >::removeAll();
}
/* ------------------------------------------------------- */
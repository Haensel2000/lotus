/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LHASH_H
#define _HDR_LHASH_H

#include <system\lsystem.h>
#include <system\lstring.h>

namespace Lotus
{
	/* HashFunctions:
	 * The following classes are a collection of common
	 * hashfunctions, that are implemented through template
	 * specialization. If an application programmer needs his
	 * own function he either can add a new template specialization
	 * or define the function .hash() in his class. A third
	 * possibility is to create an arbitrary class with the
	 * operator() and pass it through as template argument to
	 * the hash table. */
	template <class K> class HashFunction
	{
	public:
		unsigned int operator()(const K& key);
	};

	template <class K> class HashFunction<K*>
	{
	public:
		unsigned int operator()(K* key);
	};

	template <> class HashFunction<char*>
	{
	public:
		unsigned int operator()(const char* key);
	};

	template <> class HashFunction<string> : HashFunction<char*>
	{
	public:
		unsigned int operator()(const string& key);
	};

	template <> class HashFunction<String> : HashFunction<char*>
	{
	public:
		unsigned int operator()(const String& key);
	};

	template <> class HashFunction<int>
	{
	public:
		unsigned int operator()(const int& key);
	};

	/* class _HashTableItem
	 * Helper class that encapsulates one entry in the hash table.
	 * By putting out this class form the HashTable representation
	 * It is possible to extend the HashTable in a much more flexible
	 * way. */
	template <class K, class V> class _HashTableItem
	{
	private:
		K m_key;
		V m_value;
		_HashTableItem* m_next;	
	public:
		_HashTableItem(const K& a_key, const V& a_value, _HashTableItem* a_next = 0);
		K& getKey();
		V& getValue();
		_HashTableItem* next();
		void setNext(_HashTableItem* a_item);
	};

	/* class _HashSetItem
	 * This helper class demonstrates the flexibility in which the
	 * HashTable class can be extended. By replacing _HashTableItem
	 * with _HashSetItem it is easy to implement a HashSet */
	template <class K> class _HashSetItem
	{
	private:
		K m_key;
		_HashSetItem* m_next;	
	public:
		_HashSetItem(const K& a_key, const K& a_value, _HashSetItem* a_next = 0);
		K& getKey();
		K& getValue();
		_HashSetItem* next();
		void setNext(_HashSetItem* a_item);
	};

	template <class K, class V, class Item> class _HashIterator
	{
	private:
		Item** m_array;
		int m_currentIndex;
		int m_maxIndex;
		Item* m_current;
		void incr();
	public:
		_HashIterator(Item** m_array, int m_currentIndex, int m_arraySize, Item* m_current);
		_HashIterator(const _HashIterator& iterator);
		void operator=(const _HashIterator& iterator);
		operator bool();
		bool operator==(_HashIterator& iterator);
		bool operator!=(_HashIterator& iterator);		
		V& operator*();
		V& getValue();
		K& getKey();
		_HashIterator& operator++(); // prefix
		_HashIterator operator++(int); // postfix
	};

	/* class HashTable
	 * Implements a associative container based on a hash table
	 * that deals with collisions through a linked list chaining
	 * mechanism. The key has to be unique.
	 * Constraints on K: operator!=, K(&K)
	 * Constraints on V: V(&V), V() */
	template <class K, class V, class H = HashFunction<K>, class Item = _HashTableItem<K,V> > class HashTable
	{
	private:
		Item** m_array;
		int m_arraySize;
		H m_hashFunction;
		void deepCopy(HashTable<K,V,H,Item>& a_htable);
	protected:
		Item* getItem(const K& a_key);
		Item* search(const K& a_key, int a_index);
		V& insertReturn(const K& a_key, const V& a_value);
	public:
		typedef _HashIterator<K,V,Item> Iterator;
		
		HashTable(int a_size, H a_hashFunction = H());
		HashTable(HashTable<K,V,H,Item>& a_htable);
		~HashTable();
		void operator=(HashTable<K,V,H,Item>& a_htable);
		
		V& operator[](const K& a_key);
		const V& operator[](const K& a_key) const;

		V& get(const K& a_key, bool assertExists = false);
		const V& get(const K& a_key) const;
	
		bool insert(const K& a_key, const V& a_value);
		bool remove(const K& a_key);
		void removeAll();

		bool exists(const K& a_key);

		Iterator begin();
		Iterator end();
	};

	/* class HashSet:
	 * Implements a hash set that manages its objects in a hash table
	 * but only has the possibility to insert/remove elements, and
	 * check, if they are in the set */
	template <class K, class H = HashFunction<K> > class HashSet : public HashTable<K, K, H, _HashSetItem<K> >
	{
	public:
		HashSet(int a_size, H a_hashFunction = H());
		HashSet(HashSet<K,H>& a_hset);
		void operator=(HashSet<K,H>& a_hset);
		
		bool operator[](const K& a_key);
		
	
		bool insert(const K& a_key);
		bool remove(const K& a_key);
		void removeAll();
	};


	
#include "lhash.inl"
}

#endif
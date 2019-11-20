
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "List.h"

template <class K, class V>
class HashTable
{
private:
	int size;
	List<K, V>** buckets;
	size_t(*getHashCode)(const K& key);
public:
	HashTable()
	{
		size = 1000;
		buckets = new List<K, V>*[size];
		for (int i = 0; i < this->size; i++)
			buckets[i] = new List<K, V>();
		getHashCode = NULL;
	}
	HashTable(int size, size_t(*getHashCode)(const K& key))
	{
		this->size = (size < 1) ? (1) : (size);
		buckets = new List<K, V>*[size];
		for (int i = 0; i < this->size; i++)
			buckets[i] = new List<K, V>();
		this->getHashCode = getHashCode;
	}
	~HashTable()
	{
		for (int i = 0; i < size; i++)
			delete buckets[i];
		delete[] buckets;
	}
	void setHashFunction(size_t(*getHashCode)(const K& key))
	{
		this->getHashCode = getHashCode;
	}
	void add(const K& key, const V& value)
	{
		if (getHashCode == NULL)
			return;
		return buckets[getHashCode(key) % size].add(key, value);
	}
	V* get(const K& key, int& size) const
	{
		if (getHashCode == NULL)
			return NULL;
		return buckets[getHashCode(key) % size].get(key, size);
	}
	V* _delete(const K& key, int& size)
	{
		if (getHashCode == NULL)
			return NULL;
		return buckets[getHashCode(key) % size]._delete(key, size);
	}
};

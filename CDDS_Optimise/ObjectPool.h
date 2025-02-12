#pragma once
#include "Node.h"
#include "Iterator.h"
#include "initializer_list"
#include "Critter.h"
#include "List.h"

template<typename T>
class ObjectPool
{
private:
	List<T>* m_objectsInPool;
	List<T>* m_objectsOutOfPool;
public:
	ObjectPool<T>();
	~ObjectPool();
	// Return an object from the pool
	T allocate();
	// Return an object back into the pool
	void deallocate(T* object);
	void destroyObjectPool();
};

template<typename T>
inline ObjectPool<T>::ObjectPool() : m_objectsInPool()
{

}

template<typename T>
inline ObjectPool<T>::~ObjectPool()
{
	// destroy the object pool here

	delete m_objectsInPool;
	m_objectsInPool = nullptr;
}

template<typename T>
inline T ObjectPool<T>::allocate()
{
	// If the pool is empty, return new T
	if (m_objectsInPool.m_length == 0)
		return new T;
	// Getting the last object in the list
	auto obj = m_objectsInPool.m_tail;
	m_objectsInPool.popBack();
	return obj;
}

template<typename T>
inline void ObjectPool<T>::deallocate(T* object)
{

}

template<typename T>
inline void ObjectPool<T>::destroyObjectPool()
{
	for (int i = 0; i < ObjectPool.m_length; i++)
	{
		m_objectsOutOfPool.popBack();
	}
}



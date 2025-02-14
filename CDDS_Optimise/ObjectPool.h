#pragma once
#include "Node.h"
#include "Iterator.h"
#include "initializer_list"
#include "Critter.h"
#include "List.h"

template <typename T>
class ObjectPool {
private:
    struct Node {
        T* value;
        Node* next;
        Node(T* obj) : value(obj), next(nullptr) {}
    };

    /*Node* m_head;
    Node* m_tail;*/
    int m_poolSize;
    List<T*> m_objectsInPool;
    List<T*> m_objectsOutOfPool;

public:
    ObjectPool(int size) : m_poolSize(size) 
    {
        for (int i = 0; i < size; ++i) 
        {
            T* obj = new T();
            Node* newNode = new Node(obj);
            if (!m_objectsInPool.first()) 
            {
                m_objectsInPool.first() = newNode;
                m_objectsInPool.last() = newNode;
            }
            else 
            {
                m_objectsInPool.last()->next = newNode;
                m_objectsInPool.last() = newNode;
            }
        }
    }

    ~ObjectPool() 
    {
        m_objectsInPool.destroy();
        m_objectsOutOfPool.destroy();
    }

    T* allocate() {
        if (!m_objectsInPool.first()) 
        {
            return nullptr;
        }
        Node* temp = m_objectsInPool.first();
        m_objectsInPool.first() = m_objectsInPool.first()->next;
        if (!m_objectsInPool.first()) 
        {
            m_objectsInPool.last();
        }
        T* obj = temp->value;
        delete temp;
        return obj;
    }

    void deallocate(T* obj) {
        Node* newNode = new Node(obj);
        if (!m_objectsInPool.first()) 
        {
            m_objectsInPool.first() = newNode;
            m_objectsInPool.last() = newNode;
        }
        else 
        {
            m_objectsInPool.last()->next = newNode;
            m_objectsInPool.last() = newNode;
        }
    }
};

//template<typename T>
//class ObjectPool
//{
//private:
//	List<T*> m_objectsInPool;
//	List<T*> m_objectsOutOfPool;
//	int m_objectPoolSize;
//public:
//	ObjectPool<T>(int size);
//	~ObjectPool();
//	// Return an object from the pool
//	T* allocate();
//	// Return an object back into the pool
//	void deallocate(T* obj);
//	void destroyObjectPool();
//};
//
//template<typename T>
//inline ObjectPool<T>::ObjectPool(int size) : m_objectPoolSize()
//{
//	for (int i = 0; i < m_objectPoolSize; i++)
//	{
//		m_objectsInPool->pushBack(new T());
//	}
//	
//}
//
//template<typename T>
//inline ObjectPool<T>::~ObjectPool()
//{
//	m_objectsInPool->destroy();
//	m_objectsOutOfPool.destroy();
//}
//
//template<typename T>
//inline T* ObjectPool<T>::allocate()
//{
//	// If the pool is empty, return new T
//	if (m_objectsInPool.empty())
//		return nullptr;
//	// Getting the last object in the list
//	T* obj = m_objectsInPool.m_tail;
//	m_objectsInPool.popBack();
//	m_objectsOutOfPool->pushBack(obj);
//	return obj;
//}
//
//template<typename T>
//inline void ObjectPool<T>::deallocate(T* obj)
//{
//	auto object = std::find(m_objectsOutOfPool->begin(), m_objectsOutOfPool->end(), obj);
//	if (object != m_objectsOutOfPool->end())
//	{
//		m_objectsOutOfPool->remove(obj);
//		m_objectsInPool->pushBack(obj);
//	}
//}
//
//template<typename T>
//inline void ObjectPool<T>::destroyObjectPool()
//{
//	for (int i = 0; i < ObjectPool.m_length; i++)
//	{
//		m_objectsOutOfPool.popBack();
//	}
//}
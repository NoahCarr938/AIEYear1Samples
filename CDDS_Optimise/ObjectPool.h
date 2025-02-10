#pragma once
#include "Node.h"
#include "Iterator.h"
#include "initializer_list"
#include "Critter.h"

template<typename T>
class ObjectPool
{
public:
	ObjectPool<T>();
	ObjectPool<T>(std::initializer_list<T> list);
	~ObjectPool();
	void pushFront(const T& value);
	void pushBack(const T& value);
	T popFront();
	T popBack();
	bool insert(const T& value, int index);
	int remove(const T& value);
	bool allocate();
	bool deallocate();
	bool isAlive();
	T objectPoolFirst() const;
	T objectPoolLast() const;
	Iterator<T> objectPoolBegin() const;
	Iterator<T> objectPoolEnd() const;
	void destroy();
	void spawn();
	int getLength() const;

private:
	bool m_active = false;
	bool m_inactive = true;
	int m_length;
	int m_countActive;
	int m_countInactive;
	float m_lifetime;
	Node<T*> m_head;
	Node<T*> m_tail;
};

template<typename T>
inline ObjectPool<T>::ObjectPool()
{
}

template<typename T>
inline ObjectPool<T>::ObjectPool(std::initializer_list<T> list)
{
}

template<typename T>
inline ObjectPool<T>::~ObjectPool()
{
}

template<typename T>
inline void ObjectPool<T>::pushFront(const T& value)
{
}

template<typename T>
inline void ObjectPool<T>::pushBack(const T& value)
{
}

template<typename T>
inline T ObjectPool<T>::popFront()
{
	return T();
}

template<typename T>
inline T ObjectPool<T>::popBack()
{
	return T();
}

template<typename T>
inline bool ObjectPool<T>::insert(const T& value, int index)
{
	return false;
}

template<typename T>
inline int ObjectPool<T>::remove(const T& value)
{
	return 0;
}

template<typename T>
inline bool ObjectPool<T>::allocate()
{
	return false;
}

template<typename T>
inline bool ObjectPool<T>::deallocate()
{
	return false;
}

template<typename T>
inline bool ObjectPool<T>::isAlive()
{
	return false;
}

template<typename T>
inline T ObjectPool<T>::objectPoolFirst() const
{
	return T();
}

template<typename T>
inline T ObjectPool<T>::objectPoolLast() const
{
	return T();
}

template<typename T>
inline Iterator<T> ObjectPool<T>::objectPoolBegin() const
{
	return Iterator<T>();
}

template<typename T>
inline Iterator<T> ObjectPool<T>::objectPoolEnd() const
{
	return Iterator<T>();
}

template<typename T>
inline void ObjectPool<T>::destroy()
{
}

template<typename T>
inline void ObjectPool<T>::spawn()
{
}

template<typename T>
inline int ObjectPool<T>::getLength() const
{
	return m_length;
}

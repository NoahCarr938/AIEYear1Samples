#pragma once
#include "Node.h"
#include "Iterator.h"
#include "initializer_list"
#include "Critter.h"
#include "List.h"

template <typename T>
class ObjectPool {
private:

public:
    typedef T(*CreateItemSignature)();
    ObjectPool<T>(int size, CreateItemSignature createItemFunction);
    ~ObjectPool();
    void activateObject(T &value);
    void activateObjectIndex(int index);
    void deactivateObject(T& value);
    void poolAdd(T& value, int index);
    

    List<T*> m_objectsInPool;
    List<T*> m_objectsOutOfPool;

    
    // Getters for these and store them as lists
    int getActiveCount() { return m_objectsInPool.getLength(); }
    int getInactiveCount() { return m_objectsInPool.getLength(); }
    int getTotalCount() { return m_objectsInPool.getLength() + m_objectsOutOfPool.getLength(); }
};

template<typename T>
inline ObjectPool<T>::ObjectPool(int size, CreateItemSignature createItemFunction)
{
    if (size <= 0)
    {
        // Initialize lists with nothing in them
        List<T*> m_objectsInPool{};
        List<T*> m_objectsOutOfPool{};
    }
    // Object pool should take a default size and activate everything in here. Object pool should take a function pointer.
    else
    {
        for (int i = 0; i < size; i++)
        {
            // Add item to my inactiveList
            T item = createItemFunction();
            m_objectsInPool.pushBack(&item);
        }
    }
}

template<typename T>
inline ObjectPool<T>::~ObjectPool()
{
    m_objectsInPool.destroy();
    m_objectsOutOfPool.destroy();
}

template<typename T>
inline void ObjectPool<T>::activateObject(T& value)
{
    // Activating and pushing a new object into the active object list
    m_objectsOutOfPool.pushBack(&value);
}

template<typename T>
inline void ObjectPool<T>::activateObjectIndex(int index)
{
    // Inserts an object from the pool out of the game to the pool in the game.
    m_objectsOutOfPool.insert(m_objectsInPool.popFront(), index);
}

template<typename T>
inline void ObjectPool<T>::deactivateObject(T& value)
{
    // Adding a new object to the pool out of the game
    m_objectsInPool.pushBack(&value);
    // Removing an inactive object from the pool in the game
    m_objectsOutOfPool.remove(&value);
}

template<typename T>
inline void ObjectPool<T>::poolAdd(T& value, int index)
{
    // Adding to the pool in the game
    m_objectsOutOfPool.pushBack(&value);
}

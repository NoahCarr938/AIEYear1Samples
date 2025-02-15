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
    ObjectPool<T>();
    ~ObjectPool<T>();
    void activateObject(T &value);
    void activateObjectIndex(int index);
    void deactivateObject(T& value);
    void poolAdd(T& value, int index);
    List<T*> m_objectsInPool;
    List<T*> m_objectsOutOfPool;
};

template<typename T>
inline ObjectPool<T>::ObjectPool()
{
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

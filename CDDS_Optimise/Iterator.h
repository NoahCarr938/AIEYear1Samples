#pragma once
#include "Node.h"

// Need iterator to be templated
template<typename T>
class Iterator
{
public:
	Iterator<T>();
	Iterator<T>(Node<T>* node);

	// Overloading a bunch of operators to get access to the raw data
	T operator*() const;
	// Pre-increment
	Iterator<T> operator++();
	Iterator<T> operator++(int);
	// Post-increment
	Iterator<T> operator--();
	Iterator<T> operator--(int);
	// Overloading to compare iterators
	const bool operator==(const Iterator<T>& other) const;
	// Always overload a not equals operator as well
	const bool operator!=(const Iterator<T>& other) const;

private:
	// pointing to the current node
	Node<T>* m_current;
};

// Sets m_current to null
template<typename T>
inline Iterator<T>::Iterator() : m_current(nullptr)
{
}

// Sets m_current to be that node
template<typename T>
inline Iterator<T>::Iterator(Node<T>* node) : m_current(node)
{

}

// Return the current nodes value
template<typename T>
inline T Iterator<T>::operator*() const
{
	return m_current->value;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++()
{
	// Check to make sure it is not nullptr
	if (m_current)
	{
		// If pointer is valid return a new iterator
		// Make a new iterator
		// Make sure to set your current iterator to m_current
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}
	// if m_current is null
	// return a new iterator that is null
	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
	if (m_current)
	{
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--()
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--(int)
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

template<typename T>
inline const bool Iterator<T>::operator==(const Iterator<T>& other) const
{
	// Check to make sure they point to the same thing
	return m_current == other.m_current;
}

template<typename T>
inline const bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
	// Check to make sure they dont point to the same thing
	return m_current != other.m_current;
}
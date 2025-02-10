#pragma once
// Be clear to what you are including, it is fine because the headers have pragma once
#include "Node.h"
#include "Iterator.h"
#include "initializer_list"

// Add in copy constructors they need to copy a head tail and nodes
// Pop front give me front of the list and remove
// Peak front only looks at the front and does not remove it
template<typename T>
class List
{
public:
	List<T>();
	// Needs <T> because it is templated
	List<T>(std::initializer_list<T> list);
	~List<T>();

	// Adds a value to the start of the list
	// Taking in const T& to validate that the value will not be changed
	void pushFront(const T& value);
	// Adds a value to the end of the list
	void pushBack(const T& value);
	T popFront();
	T popBack();
	bool insert(const T& value, int index);
	int remove(const T& value);
	// Not going to remove the thing they are just going to get you it
	T first() const;
	T last() const;
	// Make an iterator that points to the first and last thing of the list, is const because we are not changing anything
	Iterator<T> begin() const;
	Iterator<T> end() const;
	void destroy();
	// Const because we are not changing anything
	int getLength() const;
private:
	Node<T>* m_head;
	Node<T>* m_tail;
	int m_length;
};

// If the list is blank or empty the head and tail would be null
template<typename T>
inline List<T>::List() : m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

// If the length is 0 do nothing
// Make sure to do <= 0 because sometimes a list can be -1 so we are catching that exception
// Member initializer list runs before the member body
template<typename T>
inline List<T>::List(std::initializer_list<T> list) : m_length(0), m_head(nullptr), m_tail(nullptr)
{
	if (list.size() <= 0)
		return;

	// If the length is 1 both the head and the tail are the same
	// Create the head and set it equal to the tail
	/*else if (m_length == 1)
	{
		m_head = new Node<T>(list[0]);
		m_tail = m_head;
	}*/
	// Otherwise if we have an actual list

	// Shortened syntax gives an actual value, derefernces the iter for you
	for (T item : list)
	{
		pushBack(item);
	}
}

template<typename T>
inline List<T>::~List()
{
	// delete does a null check
	// in case head and tail are the same thing make the head nullptr after deleting
	destroy();
	delete m_head;
	m_head = nullptr;
	delete m_tail;
	m_tail = nullptr;

	// Set them to nullptr
	// m_head and m_tail are node pointers so they are stored in the heap
	// if you had a pointer to the pointer that points to the data
	// and you dereference the middle pointer it becomes undefined behavior
	// if you make the middle pointer nullptr it is no longer undefined behavior

}

template<typename T>
inline void List<T>::pushFront(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	// remember to keep track of the length
	m_length++;
	// Dont need to check for head because if we have no tail we have no head
	// if tail is null
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}

	// Hooking the head to the newNode using previous
	m_head->previous = newNode;
	// Hooking the newNode to the head using next
	newNode->next = m_head;
	m_head = newNode;
}

template<typename T>
inline void List<T>::pushBack(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}
	m_tail->next = newNode;
	newNode->previous = m_tail;
	m_tail = newNode;
}

template<typename T>
inline T List<T>::popFront()
{
	// if our list is empty
	// return basically nothing
	// Reminder to make a unit test for if our list has integers
	// Case check for what if our list has 0
	// If we dont have a tail
	if (!m_tail)
		return T();

	// get our value off of the head
	T value = m_head->value;

	// move the head to the next node
	// head's previous points to the node we are trying to get rid of
	// Check to make sure head->next is not valid, meaning we only have one node
	if (!m_head->next)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	else
	{
		// Now we can safely delete m_head->previous without causing a memory leak
		m_head = m_head->next;
		delete m_head->previous;
		// Reminder to set m_head->previous = nullptr after deleting
		m_head->previous = nullptr;
		// If our head has a next
		m_length--;
	}
	// we can return value at the end of the if statements because both if statements return value
	return value;
}

template<typename T>
inline T List<T>::popBack()
{
	// If we do not have a tail return T()
	if (!m_tail)
		return T();

	// If we pass this, the list does have a tail
	T value = m_tail->value;

	// If tail has no previous
	if (!m_tail->previous)
	{
		delete m_tail;
		m_tail = nullptr;
		m_head = nullptr;
		m_length = 0;
		return value;
	}
	else
	{
		m_tail = m_tail->previous;
		delete m_tail->next;
		m_length--;
	}
	// we can return value at the end of the if statements because both if statements return value
	return value;
}

template<typename T>
inline bool List<T>::insert(const T& value, int index)
{
	// guard clause
	if (index < 0 || index > m_length)
		return false;

	// If we dont have a tail or our index is 0
	if (!m_tail || index == 0)
	{
		// We can just pushFront the value and return true
		pushFront(value);
		return true;
	}

	// We know we have stuff in the list and we are not trying to add to the beginning
	// Add to the end of the list
	if (index == m_length)
	{
		// if our index is our last thing we just use pushback
		// otherwise we would have to loop through the entire list
		pushBack(value);
		return true;
	}

	// Loop through the entire index and whenever we find the specific spot in the list we want to perform the insert
	// Reminder optimize for if we have an index close to the end of the list to where we have to loop less
	// making a node pointer to hold our head
	Node<T>* node = m_head;
	for (int i = 0; i < index; i++)
	{
		// check if our node->next is equal to nullptr
		// if our node->next is nullptr, return false because either the list is broken or we arrived at the end before expected
		if (node->next == nullptr)
			return false;

		// otherwise loop our way down and set node to node->next
		// Iterate through the nodes
		node = node->next;
	}

	// Make a new node 
	Node<T>* newNode = new Node<T>(value);
	// Set our new node previous to the old node previous
	newNode->previous = node->previous;
	// Set our newNode next equal to node
	newNode->next = node;
	// Set node previous equal to the newNode
	node->previous = newNode;
	// Set previous node's next to the newNode;
	newNode->previous->next = newNode;
	// Update length
	m_length++;
	return true;
}

template<typename T>
inline int List<T>::remove(const T& value)
{
	// Accounting for edge cases below

	// If there is nothing in the list then remove nothing
	// If there is nothing in the list, the list is empty
	if (!m_tail)
		return 0;

	int count = 0;


	// Iterate and remove
	Node<T>* node = m_head;
	// If head value is the value to remove
	// if node is not valid then dont run the rest of code
	// while node is valid
	while (node && node->value == value)
	{
		popFront();
		node = m_head;
		count++;
	}

	// Verify node is valid
	// Then verify tail is valid
	// If tail's next is nullptr
	while (node && m_tail && node != m_tail->next)
	{
		// If the node's value is the value to remove
		if (node->value == value)
		{
			// if we find the node we want to unhook it 
			// Remove node
			// Unconnecting the previous and next nodes from ours we are trying to move.
			// If node is not the head
			if (node != m_head)
			{
				node->previous->next = node->next;
			}
			else
			{
				popFront();
				node = m_head;
				count++;
				// If we removed the head, no need to check the tail
				continue;
			}
			node->previous->next = node->next;
			if (node != m_tail)
			{
				node->next->previous = node->previous;
				// Making a temportary node pointer
				// Gives two pointers pointing to the same thing
				Node<T>* temp = node;
				node = node->next;
				delete temp;
				// Decrement length
				m_length--;
				count++;
			}
			else
			{
				popBack();
				node = m_tail;
				count++;
			}

		}
		else
		{
			node = node->next;
		}
	}
	// If we get to the end and did not find anything return count
	return count;
}

template<typename T>
inline T List<T>::first() const
{
	// check to make sure head is not null
	if (!m_head)
		return T();
	// return the head value
	return m_head->value;
}

template<typename T>
inline T List<T>::last() const
{
	// check to make sure tail is not null
	if (!m_tail)
		return T();
	// return the tail value
	return m_tail->value;
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	if (!m_head)
		return Iterator<T>();
	return Iterator<T>(m_head);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	if (!m_tail)
		return Iterator<T>();
	return Iterator<T>(m_tail->next);
}

template<typename T>
inline void List<T>::destroy()
{
	// If there is nothing in the list or tail
	if (!m_tail)
		return;
	// Otherwise
	// Loop over the entire length of the list
	for (int i = 0; i < m_length; i++)
	{
		// Pop everything off of the end
		popBack();
	}

	// Make sure to reinitialize everything
	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

template<typename T>
inline int List<T>::getLength() const
{
	return m_length;
}
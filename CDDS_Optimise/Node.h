#pragma once
// Needs to be a templated struct
template<typename T>
struct Node
{
public:
	Node<T>();
	Node<T>(T value);
	// Explicitely stating that the default node destructor is the destructor
	~Node<T>() = default;

public:
	// Holds the actual value
	T value;
	// Points to the next node
	Node<T>* next;
	// Points to the previous node
	Node<T>* previous;
};

// Currently setting value to not be anything
template<typename T>
inline Node<T>::Node() : next(nullptr), previous(nullptr)
{
}

// Sets next and previous to null and stores the value
// The code after : is called an initializer list
// we use an initializer list to move in the variable by reference, it prevents constructors from running multiple times
// It moves the things in instead of copying them in
template<typename T>
inline Node<T>::Node(T value) : next(nullptr), previous(nullptr), value(value)
{
}
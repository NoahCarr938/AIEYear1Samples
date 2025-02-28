#pragma once
#include <iostream>

class Singleton
{
public:

	// returns the single instance of this class
	// Can also be called from anywhere
	// Thread safe
	static Singleton& Get()
	{
		static Singleton* Get = new Singleton();
		return *Get;
	}

	void Function() {};
private:
	// The Constructor is private to prevent instantiating multiple times
	Singleton() {};
	static Singleton m_singletonInstance;
};

Singleton Singleton::m_singletonInstance;

int main()
{
	Singleton instance = Singleton::Get();
}
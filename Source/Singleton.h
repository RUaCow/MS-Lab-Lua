/*
* File: Singleton.h
* Part of Ultra Engine project
* Description: Singleton class for one instanced classes.
*/

#ifndef _ULTRA_SINGLETON_H
#define _ULTRA_SINGLETON_H

template<class T> class Singleton {

	static T* singleton_ptr; // Pointer to singleton

public:

	// Default constructor
	Singleton() {
		singleton_ptr = static_cast<T*>(this);
	}

	// Destructor
	virtual ~Singleton() {

	}

	static T& GetSingleton() {
		return *singleton_ptr;
	}

	// Returns the pointer to the singleton
	static T* GetSingletonPtr() {
		return singleton_ptr;
	}

}; // class Singleton

// Prevent link errors
template<class T> T* Singleton<T>::singleton_ptr = 0;

#endif // _ULTRA_SINGLETON_H

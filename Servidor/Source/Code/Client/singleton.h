#ifndef SINGLETON_H
#define SINGLETON_H

#include <utility>

// Generic, lazy, singleton base-class
// that supports any number of arguments
template<typename T>
class Singleton
{
public:
	// Gets the only instance of the inherited class
	template<typename ...Args>
	static T& instance(Args... args)
	{
		static T instance(std::forward<Args>(args)...);

		return instance;
	}

protected:
	Singleton() {};
	virtual ~Singleton() {}
};

#endif
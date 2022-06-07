#include "Singleton.h"

Singleton::Singleton()
{
	if (!InitializeCriticalSectionAndSpinCount(&SingletonScopeLock, 0x00000400))
		return;
}


Singleton::~Singleton()
{
	DeleteCriticalSection(&SingletonScopeLock);
}

volatile Singleton* Singleton::getInstance()
{
	if (uniqueInstance == nullptr)
	{
		EnterCriticalSection(&SingletonScopeLock);
		//
		if (uniqueInstance == nullptr)
		{
			uniqueInstance = new Singleton();
		}
		//
		LeaveCriticalSection(&SingletonScopeLock);
	}

	return uniqueInstance;
}

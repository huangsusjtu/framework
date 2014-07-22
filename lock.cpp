#include "lock.h"

Lock::Lock()
{
	pthread_mutex_init(&mMutex ,NULL);
}

Lock::~Lock()
{
	pthread_mutex_destroy(&mMutex);
}

void Lock::lock()
{
	pthread_mutex_lock(&mMutex);
}

void Lock::unlock()
{
	pthread_mutex_unlock(&mMutex);
}

void Lock::trylock()
{
	pthread_mutex_trylock(&mMutex);
}

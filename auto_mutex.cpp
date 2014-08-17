#include "auto_mutex.h"
#include <cstdio>
AutoMutex::AutoMutex(mutex* m)
{
	if(m)
	{
		mMutex = m;
		pthread_mutex_lock(mMutex);
	}else{
		mMutex = NULL;
	}
}


AutoMutex::~AutoMutex()
{
	if(mMutex)
		pthread_mutex_unlock(mMutex);
}


AutoMutex1::AutoMutex1(Lock* m)
{
	if(m)
	{
		lock = m;
		m->lock();
	}else{
		lock = NULL;
	}
}


AutoMutex1::~AutoMutex1()
{
	if(lock)
		lock->unlock();
}

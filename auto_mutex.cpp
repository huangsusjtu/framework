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


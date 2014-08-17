#ifndef AUTOMUTEX
#define AUTOMUTEX

#include <pthread.h>
#include "lock.h"

class AutoMutex
{
	typedef pthread_mutex_t mutex;
	public:
		AutoMutex(mutex *m);
		~AutoMutex();
	private:
		AutoMutex(const AutoMutex& t);
		AutoMutex& operator=(const AutoMutex& t);
	private:
		mutex *mMutex = NULL;
};

class AutoMutex1
{
	public:
		AutoMutex1(Lock *m);
		~AutoMutex1();
	private:
		AutoMutex1(const AutoMutex1& t);
		AutoMutex1& operator=(const AutoMutex1& t);
	private:
		Lock *lock = NULL;
};

#endif

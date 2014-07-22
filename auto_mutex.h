#ifndef AUTOMUTEX
#define AUTOMUTEX

#include <pthread.h>

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

#endif

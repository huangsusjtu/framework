#ifndef LOCK_
#define LOCK_
#include <pthread.h>

class Lock
{
	typedef pthread_mutex_t mutex;
	public:
		Lock();
		virtual ~Lock();

		void lock();
		void unlock();
		void trylock();
	private:
		Lock(const Lock& T);
		Lock& operator=(const Lock& T);
		mutex mMutex;
};


#endif

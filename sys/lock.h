#ifndef LOCK_
#define LOCK_
#include <pthread.h>

namespace sys{

class Lock
{
	typedef pthread_mutex_t mutex;
	public:
		Lock();
		virtual ~Lock();

		void lock();
		void unlock();
		bool trylock();
	private:
		Lock(const Lock& T);
		Lock& operator=(const Lock& T);
		mutex mMutex;
};

}
#endif

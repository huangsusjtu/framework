#ifndef THREAD
#define THREAD
#include <pthread.h>

#include "runnable.h"

class Thread : public Runnable{
	public:
		Thread();
		virtual ~Thread(){};
		

	static void* thread_func(void *this_);
		void start();
		void stop();
		void join();
		pthread_t getThreadID();


	private:
		Thread(const Thread&);
		Thread& operator=(const Thread&);
	private:
		bool mStop;
		pthread_t mTid;

};
#endif

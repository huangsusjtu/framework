#include "thread.h"

Thread::Thread():mStop(true)
{
	
}

void Thread::start()
{
	mStop = false;	
	pthread_create(&mTid, NULL,thread_func, this);
}

void Thread::join()
{
	pthread_join(mTid, NULL);
}

void Thread::stop()
{
	mStop = true;
	pthread_exit(0);
}

void* Thread::Thread::thread_func(void *this_)
{
	if(this_)
		( static_cast<Thread*>(this_))->run();
}


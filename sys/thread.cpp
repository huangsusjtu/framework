#include "thread.h"

namespace sys{

Thread::Thread():mStop(true)
{
	
}

Thread::~Thread(){
	
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

void Thread::detach()
{
	pthread_detach(mTid);
}

void Thread::stop()
{
	mStop = true;
	//pthread_exit(0);
}

void* Thread::thread_func(void *this_)
{
	if(this_ )
		( static_cast<Thread*>(this_))->run();
}

//class 
ThreadManager ThreadManager::self;

void ThreadManager::add(Thread *T)
{
	if(T)
	_threads.push_back(T);
}

void ThreadManager::waitForTerminate()
{	
	for(int i=0;i<_threads.size();i++)
	{
		Thread *tmp = _threads[i];
		tmp->join();
	}
}

}

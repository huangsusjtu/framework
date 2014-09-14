#include "thread.h"

namespace sys{

Thread::Thread():_stop(true),_finish(true)
{
	
}

Thread::~Thread(){
	
}

void Thread::start()
{
	_stop = false;
	_finish = false;	
	pthread_create(&_tid, NULL,thread_func, (void*)this);
	detach();
}

void Thread::join()
{
	pthread_join(_tid, NULL);
}

void Thread::detach()
{
	pthread_detach(_tid);
}

void Thread::stop()
{
	_stop = true;
	//pthread_exit(0);
}

void* Thread::thread_func(void *this_)
{
	if(this_ )
	{
		Thread *tmp =  static_cast<Thread*>(this_);
		tmp->run();
		tmp->finish();
	}
}
/////////////////////////////////////////////
ThreadExecuter::ThreadExecuter(Runnable *run)
{
	_runner = run;
}


/////////////////////////////////////////////class 
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

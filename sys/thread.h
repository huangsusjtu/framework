#ifndef THREAD
#define THREAD
#include <pthread.h>
#include <vector>
#include "runnable.h"

namespace sys{

class Thread : public Runnable{
	public:
		Thread();
		virtual ~Thread();
		

		pthread_t getThreadHandle(){
			return _tid;
		}
		
		
		static void* thread_func(void *this_);
		void start();
		void stop();
		void join();
		void detach();

		bool needRun(){
			return _stop==false;		
		}
		void finish(){
			_finish = true;		
		}
		
	protected:
		virtual void run()=0;

	private:
		Thread(const Thread&);
		Thread& operator=(const Thread&);
	private:
		bool _stop;
		bool _finish;
		pthread_t _tid=0;

};
using std::vector;
class ThreadManager
{
	
	typedef vector<Thread*> Container;
	public:
		static ThreadManager& instance(){
			return self;	
		}

		void add(Thread *T);
		void waitForTerminate();
	private:
		Container _threads; 
		static ThreadManager self;
};

}

#endif

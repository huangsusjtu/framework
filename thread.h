#ifndef THREAD
#define THREAD
#include <pthread.h>

#include "runnable.h"

namespace sys{

class Thread : public Runnable{
	public:
		Thread();
		virtual ~Thread(){};
		

		pthread_t getThreadHandle(){
			return mTid;
		}
		
		
		static void* thread_func(void *this_);
		void start();
		void stop();
		void join();

		bool needRun(){
			return mStop==false;		
		}
	protected:
		virtual void run()=0;

	private:
		Thread(const Thread&);
		Thread& operator=(const Thread&);
	private:
		bool mStop;
		pthread_t mTid;

};

}

#endif

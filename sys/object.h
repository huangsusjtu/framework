#ifndef OBJECT
#define OBJECT
#include <pthread.h>

class Object
{
	typedef pthread_mutex_t mutex;
	typedef pthread_cond_t condition;
	public:
		Object();	
		virtual ~Object();

		Object(const Object &T);
		Object& operator=(const Object &T);

		void wait();
		void wait(int sec);
		void notify();
		void notifyAll();

		virtual const char* toString();
	private:

		mutex mMutexCond;
		condition mCond;

		

};

#endif

#include <time.h>

#include "object.h"

Object::Object()
{
	pthread_mutex_init(&mMutexCond,NULL);
	pthread_cond_init( &mCond, NULL );
}

Object::~Object()
{
	pthread_cond_destroy(&mCond);
	pthread_mutex_destroy(&mMutexCond);
}

Object::Object(const Object &T)
{
	pthread_mutex_init(&mMutexCond,NULL);
	pthread_cond_init( &mCond, NULL);
}

Object& Object::operator=(const Object &T)
{
	if( &T == this ){
		return *this;
	}
	pthread_cond_destroy(&mCond);
	pthread_mutex_destroy(&mMutexCond);
	pthread_mutex_init(&mMutexCond,NULL);
	pthread_cond_init(&mCond, NULL);
	return *this;
}



void Object::wait()
{
	pthread_mutex_lock(&mMutexCond);
	pthread_cond_wait(&mCond, &mMutexCond);
	pthread_mutex_unlock(&mMutexCond);
}

void Object::wait(int sec)
{
	if(sec<0)sec=0;
	struct timespec tp;
	if(0==clock_gettime(CLOCK_REALTIME, &tp)){
		pthread_mutex_lock(&mMutexCond);
		pthread_cond_timedwait(&mCond, &mMutexCond, &tp);
		pthread_mutex_unlock(&mMutexCond);
	}else{
		wait();
	}
}

void Object::notify()
{
	pthread_mutex_lock(&mMutexCond);
	pthread_cond_signal(&mCond);
	pthread_mutex_unlock(&mMutexCond);
}

void Object::notifyAll()
{
	pthread_mutex_lock(&mMutexCond);
	pthread_cond_broadcast(&mCond);
	pthread_mutex_unlock(&mMutexCond);
}

const char* Object::toString()
{
	return "Object";
}

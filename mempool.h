#ifndef MEMPOOL
#define MEMPOOL

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include "auto_mutex.h"
using namespace std;

#define TEMPLATE  template<class T, size_t EXPANSION_SIZE >

template<class T, size_t EXPANSION_SIZE=128 >
class Mempool
{
	private:
		//enum{
		//	EXPANSION_SIZE = 10
		//};

		static pthread_mutex_t mMutex ;
		static Mempool<T, EXPANSION_SIZE> *self;
		static size_t objsize ;
		
		Mempool<T, EXPANSION_SIZE> *next;
		size_t length;
	private:
		Mempool<T, EXPANSION_SIZE>& operator=(const Mempool<T,EXPANSION_SIZE>& );
		Mempool(const Mempool<T, EXPANSION_SIZE>& );
		Mempool(size_t size = EXPANSION_SIZE);
		~Mempool();
		
		void expand(size_t size = EXPANSION_SIZE);
		void shrink();
	public:
			static class Mempool<T, EXPANSION_SIZE>& GetInstance(size_t size=EXPANSION_SIZE){
				//printf("1");
				if(self)
					return *self;
				//printf("2");
				AutoMutex m(&mMutex);
				//printf("3");
				self = new Mempool<T, EXPANSION_SIZE>();
				//printf("4");
				return *self;
			}
			static void ReleaseInstance(){
				if(self)
					delete self;
			}		
			
		void* alloc();
		void free(void*);
};

TEMPLATE
Mempool<T, EXPANSION_SIZE>* Mempool<T, EXPANSION_SIZE>::self = NULL;

TEMPLATE
size_t Mempool<T, EXPANSION_SIZE>::objsize = sizeof(Mempool<T, EXPANSION_SIZE>)>sizeof(T)?sizeof(Mempool<T, EXPANSION_SIZE>):sizeof(T);

TEMPLATE
pthread_mutex_t Mempool<T, EXPANSION_SIZE>::mMutex = PTHREAD_MUTEX_INITIALIZER;

TEMPLATE
Mempool<T, EXPANSION_SIZE>::Mempool(size_t size) : next(NULL),length(0)
{
	expand(size);
}

TEMPLATE
Mempool<T, EXPANSION_SIZE>::~Mempool()
{
	if(next)
	{
		AutoMutex m(&mMutex);
		while(next)
		{
			char *p = (char*)next;
			next = next->next;
			delete []p;
		}
	}
	pthread_mutex_destroy(&mMutex);
}

TEMPLATE
void* Mempool<T, EXPANSION_SIZE>::alloc()
{
	AutoMutex m(&mMutex);
	if(!next)
		expand();
	void *r = (void*)next;
	next = next->next;
	length--;
	return r;
}

TEMPLATE
void Mempool<T, EXPANSION_SIZE>::free(void* p)
{
	if(!p)
		return ;
	AutoMutex m(&mMutex);
	Mempool<T, EXPANSION_SIZE> *head = (Mempool<T,EXPANSION_SIZE>*)p;
	head->next = next;
	next = head;
	length++;
	shrink();
}

/**Note: it is not thread safe*/
TEMPLATE
void Mempool<T, EXPANSION_SIZE>::expand(size_t size)
{
	for(int i=0;i<size;i++)
	{
		Mempool<T, EXPANSION_SIZE>* head = (Mempool<T,EXPANSION_SIZE>*)new char[objsize];
		head->next = next;
		next = head;
		length++;
	}
}

/**it is not thread safe*/
TEMPLATE
void Mempool<T,EXPANSION_SIZE>::shrink()
{
	if(length <= EXPANSION_SIZE)
		return;
	char *p = (char*)next;
	next = next->next;
	delete []p;
	length--;
}

#endif

/**
 * The main.cpp is used to test all the modules
 */
#include "thread.h"
#include "mempool.h"
#include "messagequeue.h"
#include "message.h"
#include "event_driver.h"
#include "status.h"
#include <stdio.h>

class mythread : public Thread
{
	void run()
	{
		printf("hehe");
	}
};

class packet{
	public:
		static Mempool<packet> *mempool;
		
		void* operator new (size_t size)
		{
			return mempool->alloc();
		}
		void operator delete (void *p, size_t size)
		{
			mempool->free(p);
		}

};
Mempool<packet> *packet::mempool = NULL;


int main()
{
	printf("0");
/*	
    //test the mempool
 	packet::mempool = &(Mempool<packet>::GetInstance());
	for(int i=0;i<10;i++)
	{
		packet *p = new packet;
		delete p;
	}

	//test thread class;
	mythread th;
	th.start();
	th.join();
*/
	//MessageQueue::test();
	//
	
//	EventManager::test();
	status::test();
	return 0;
}

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
using namespace sys;
using namespace net;

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

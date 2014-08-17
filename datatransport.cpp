#include <exception>
#include "datatransport.h"
#include "netevent.h"
#include "logger.h"

namespace net{
using std::exception;
using sys::Logger;

Transport *Transport::self = NULL;

Transport::Transport()
{
	try{
		readQueue = new PacketQueue();
		writeQueue = new PacketQueue();
		writeCommondQueue = new CommondQueue();
		readCommondQueue = new CommondQueue();
		readThread = new TaskQueueThread(readCommondQueue);
		writeThread = new TaskQueueThread(writeCommondQueue);
	}
	catch(exception &e)
	{
		Logger::e("Allocate gloable object err");
		exit(0);
	}
	
}

Transport::~Transport()
{
	if(readThread)delete readThread;
	if(writeThread)delete writeThread;

	if(readCommondQueue)delete readCommondQueue;
	if(writeCommondQueue)delete writeCommondQueue;
	
	if(readQueue)delete readQueue;	
	if(writeQueue)delete writeQueue;

}

void Transport::start()
{
	readThread->start();
	writeThread->start();
}


}

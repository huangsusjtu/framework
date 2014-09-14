#include <exception>
#include <unistd.h>
#include "datatransport.h"
#include "datastream.h"
#include "netevent.h"
#include "logger.h"

namespace net{
using std::exception;
using sys::Logger;

Transport *Transport::self = NULL;

Transport::Transport()
{
	try{
		_defaultstream = new NormalDataStream();
		_readQueue = new PacketQueue();
		_writeQueue = new PacketQueue();
		_commondQueue = new CommondQueue();
		_readwriteThread = new CommondThread(_commondQueue);
		_errThread = new CommondThread(_commondQueue);
	}
	catch(exception &e)
	{
		Logger::e("Allocate gloable object err");
		_exit(0);
	}
	
}

Transport::~Transport()
{
	if(_readwriteThread)delete _readwriteThread;
	if(_errThread) delete _errThread;

	if(_commondQueue)delete _commondQueue;
	
	
	if(_readQueue)delete _readQueue;	
	if(_writeQueue)delete _writeQueue;
	
	if(_defaultstream)delete _defaultstream;

}

void Transport::start()
{
	_readwriteThread->start();
}


}

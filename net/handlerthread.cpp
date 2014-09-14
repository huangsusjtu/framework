#include "handlerthread.h"
#include <cassert>
namespace net
{

HandlerThread::HandlerThread() 
	: _requestQueue(NULL),_responseQueue(NULL)
{
}

HandlerThread::~HandlerThread()
{}

void HandlerThread::prepare(IHandler* handler,TaskQueue *requestQueue, TaskQueue *responseQueue)
{
	assert(handler!=NULL && responseQueue!=NULL && responseQueue!=NULL);
	_handler = handler;
	setInput(responseQueue);
	setOutput(responseQueue);
}

void HandlerThread::setInput(TaskQueue *t)
{
	_requestQueue = t;
}
void HandlerThread::setOutput(TaskQueue *t)
{
	_responseQueue = t;
}

void HandlerThread::run()
{
	if(_requestQueue == NULL || _handler ==NULL)
		return ;
	IPacket *request = NULL;
	IPacket *response = NULL;
	while( Thread::needRun() )
	{
		request = _requestQueue->pop();
		_handler->doPacket(request, &response);
		if(_responseQueue!=NULL && response!=NULL)
			_responseQueue->push(response);	
	}
}




}

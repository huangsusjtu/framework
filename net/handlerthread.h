#ifndef _HANDLER_THREAD_
#define _HANDLER_THREAD_

#include "thread.h"
#include "Ipacket.h"
#include "serverhandler.h"
namespace net
{

class HandlerThread : public Thread
{
	typedef PacketQueue TaskQueue;
	public:
		HandlerThread();
		~HandlerThread();
	
		void prepare(IHandler *handler,TaskQueue *requestQueue, TaskQueue *responseQueue);
	protected:
		virtual void run();	
	private:
		void setInput(TaskQueue *t);
		void setOutput(TaskQueue *t);
	private:
		HandlerThread(const HandlerThread& T);
		HandlerThread& operator=(const HandlerThread &T);

		IHandler *_handler;
		TaskQueue *_requestQueue;
		TaskQueue *_responseQueue;

};


}



#endif


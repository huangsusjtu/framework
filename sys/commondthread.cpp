#include "commondthread.h"
#include <cassert>

namespace sys{

CommondThread::CommondThread(CommondQueue *queue) : mQueue(queue) 
{
	assert(queue!=NULL);
}

CommondThread::~CommondThread()
{}


//重载父类，具体要做的事情
void CommondThread::run()
{
	while( Thread::needRun() )
	{
		//取出一条命令， 执行
		Commond *tmp = mQueue->pop(); 
		if(tmp!=NULL){
			tmp->onCommond();
		}
	}
}



}

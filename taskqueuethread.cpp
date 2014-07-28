#include "taskqueuethread.h"
#include <cassert>

namespace sys{

TaskQueueThread::TaskQueueThread(CommondQueue *queue) : mQueue(queue) 
{
	assert(queue!=NULL);
}

TaskQueueThread::~TaskQueueThread()
{}


//重载父类，具体要做的事情
void TaskQueueThread::run()
{
	while( Thread::needRun() )
	{
		//取出一条命令， 执行
		Commond *tmp = mQueue->getFront(); 
		if(tmp!=NULL){
			tmp->onCommond();
		}else{
			Object::wait();
		}
	}
}



}

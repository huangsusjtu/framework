#ifndef TASK_QUEUE_THREAD_
#define TASK_QUEUE_THREAD_
#include "queue.h"
#include "commond.h"
#include "thread.h"
#include "object.h"
namespace sys{

/**
 * 任务队列， 交给单独的线程处理
 */
/*class CommondQueue : public Queue<Commond>
{
	public:	
		CommondQueue(){}
		~CommondQueue(){}

	private:
		CommondQueue(const CommondQueue &T);
		CommondQueue& operator=(const CommondQueue &T);

};
*/
typedef  Queue<Commond> CommondQueue;

/**
 * 处理任务队列的线程
 */
class TaskQueueThread : public Thread , virtual public Object
{
	public:
		TaskQueueThread(CommondQueue *queue);
		~TaskQueueThread();

	protected:
		//重载
		virtual void run();
	private:
		TaskQueueThread(const TaskQueueThread &T);
		TaskQueueThread& operator=(const TaskQueueThread &T);

	private:
		CommondQueue *mQueue;
		
};





}


#endif

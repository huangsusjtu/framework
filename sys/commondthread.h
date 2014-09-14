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
typedef  BlockQueue<Commond> CommondQueue;

/**
 * 处理任务队列的线程
 */
class CommondThread : public Thread
{
	public:
		CommondThread(CommondQueue *queue);
		~CommondThread();

	protected:
		//重载
		virtual void run();
	private:
		CommondThread(const CommondThread &T);
		CommondThread& operator=(const CommondThread &T);

	private:
		CommondQueue *mQueue;
		
};





}


#endif

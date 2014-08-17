#ifndef NET_EVENT_
#define NET_EVENT_
#include "queue.h"
#include "commond.h"
#include "connection.h"
namespace net{
using sys::Commond;

/**
*  命令模式， 该对象是描述一个命令， 最终提交到队列被处理。
*  该对象实例由 监听线程创建提交， 有数据读线程处理。
*/
class NetReadCommond : public Commond{
	
	public:
		NetReadCommond(Connection *con);
		
		virtual void onCommond();
	
		~NetReadCommond();
	private:
		Connection *_con = NULL;
	
};

/**
* 网络读命令的队列， 
*/

using sys::Queue;
/*class NetReadQueue : public Queue<NetReadCommond>
{
	public:
		//static NetReadQueue& instance(){
		//	return self;
		//}
		NetReadQueue() : Queue<NetReadCommond>() {}
		virtual ~NetReadQueue(){}
	private:
		
		NetReadQueue(const NetReadQueue &T);
		NetReadQueue& operator=(const NetReadQueue &T);
		
		//static NetReadQueue self;
};
*/
typedef Queue<NetReadCommond> NetReadQueue;
/**
*  命令模式， 该对象是描述一个写数据命令， 最终提交到队列被处理 。
*  该对象实例由 外部创建提交， 由数据写线程处理。
*/
class NetWriteCommond : public Commond
{
	public:
		NetWriteCommond(Connection *con);
		~NetWriteCommond();
	
		virtual void onCommond();
	
	private:
		Connection *_con = NULL;
	
};

/**
* 网络写命令的队列， 
*/
/*class NetWriteQueue : public Queue<NetWriteCommond>
{
	public:
		//static NetWriteQueue& instance(){
		//	return self;
		//}
		NetWriteQueue() : Queue<NetWriteCommond>() {}
		virtual ~NetWriteQueue(){}
	private:
		
		NetWriteQueue(const NetWriteQueue &T);
		NetWriteQueue& operator=(const NetWriteQueue &T);
		
		//static NetWriteQueue self;
};

*/
typedef Queue<NetWriteCommond> NetWriteQueue;
}



#endif

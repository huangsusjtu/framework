#ifndef NET_EVENT_
#define NET_EVENT_
#include <cassert>

#include "queue.h"
#include "commond.h"
#include "connection.h"
namespace net{
using sys::Commond;
using sys::Queue;

/**
*  命令模式， 该对象是描述一个命令， 最终提交到队列被处理。
*  该对象实例由 监听线程创建提交， 有数据读线程处理。
*/
class NetReadCommond : public Commond{
	
	public:
		NetReadCommond(Connection *con = NULL);
		
		void setConnection(Connection *con){
			_con = con;
		}
		Connection *getConnection(){
			return _con;		
		}

		virtual void onCommond();
	
		~NetReadCommond();
	private:
		Connection *_con = NULL;
	
};

/**
* 网络读命令的队列， 
*/

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
class NetWriteCommond : public Commond{
	
	public:
		NetWriteCommond(IPacket *p = NULL);
		
		void setPacket(IPacket *p){
			_out = p;
			assert(p!=NULL);
		}
		IPacket *getPacket(){
			return _out;		
		}
		virtual void onCommond();
	
		~NetWriteCommond();
	private:
		IPacket *_out =NULL;
};


}



#endif

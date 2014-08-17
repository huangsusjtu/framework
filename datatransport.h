#ifndef PACKET_TRANSPORT
#define PACKET_TRANSPORT

#include "packetqueue.h"
#include "taskqueuethread.h"


namespace net{
using sys::TaskQueueThread;
using sys::CommondQueue;
/**
 * data transport through network
 * 全局的数据收发， 包含了收发队列，和收发线程 
 */
class Transport{
	
	public:
		virtual ~Transport();
		static Transport& instance(){
			if(NULL==self)
				self = new Transport();
			return *self;	
		}
	
		void start();

		PacketQueue *getReadPacketQueue(){
			return readQueue;
		}

		PacketQueue *getWritePacketQueue(){
			return writeQueue;
		}

		TaskQueueThread *getReadThread(){
			return readThread;
		}

		TaskQueueThread *getWriteThread(){
			return writeThread;
		}

		TaskQueueThread *getErrThread(){
			return errThread;
		}
	
		CommondQueue *getWriteCommondQueue(){
			return writeCommondQueue;
		}

		CommondQueue *getReadCommondQueue(){
			return readCommondQueue;
		}

	private:
		Transport();
		Transport(const Transport &T);
		Transport& operator=(const Transport &T);

	private:
		static Transport *self;
		PacketQueue *readQueue;
		PacketQueue *writeQueue;
		TaskQueueThread *readThread;
		TaskQueueThread *writeThread;
		TaskQueueThread *errThread;
		//typedef CommondQueue Queue<Commond>
		CommondQueue *writeCommondQueue;
		CommondQueue *readCommondQueue;
};

}


#endif

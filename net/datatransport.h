#ifndef PACKET_TRANSPORT
#define PACKET_TRANSPORT

#include "Ipacket.h"
#include "taskqueuethread.h"

namespace net{
using namespace sys;
using sys::TaskQueueThread;
using sys::CommondQueue;
/**
 * data transport through network
 * 全局的数据收发， 包含了收发队列，和收发线程 
 */
class DataStream;
class Transport{
	
	public:
		virtual ~Transport();
		static Transport& instance(){
			if(NULL==self)
				self = new Transport();
			return *self;	
		}
	
		void start();
		
		DataStream *getStream(){
			return 	_stream==NULL? _defaultstream : _stream;	
		}	
		void setStream(DataStream *stream)
		{
			if( stream !=NULL )
				_stream = stream; 
		}

		PacketQueue *getReadPacketQueue(){
			return _readQueue;
		}

		PacketQueue *getWritePacketQueue(){
			return _writeQueue;
		}

		TaskQueueThread *getThread(){
			return _readwriteThread;
		}

	
		TaskQueueThread *getErrThread(){
			return _errThread;
		}
	
		CommondQueue *getCommondQueue(){
			return _commondQueue;
		}

	private:
		Transport();
		Transport(const Transport &T);
		Transport& operator=(const Transport &T);

	private:
		static Transport *self;
		//包队列， 包含了读写队列
		PacketQueue *_readQueue;
		PacketQueue *_writeQueue;
		//读写线程
		TaskQueueThread *_readwriteThread;
		TaskQueueThread *_errThread;
		//typedef BlockQueue<Commond> CommondQueue
		//命令队列， 读写命令
		CommondQueue *_commondQueue;
		//数据的编码解码流
		DataStream *_stream = NULL;
		DataStream *_defaultstream;
};

}


#endif

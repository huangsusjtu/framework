#ifndef _CONNECTION_
#define _CONNECTION_
#include "memblockpool.h"
#include "socket.h"
#include "datastream.h"
#include "refcount.h"

namespace net {

using namespace sys;


/**
 * 代表了服务端到客户端的一条连接，该连接可以收发数据包。
 * 关联到数据包队列 : public StrongRef
 */
class IPacket;
class Connection{
	public:
		Connection(int sockfd);
		virtual ~Connection();

		//初始化时，添加的信息		
		void prepare(DataStream *ss);
		void setAddress(sockaddr *addr, size_t addrlen);		

		int getHandle(){return _fd;}
			
	
		//read or write binary data;
		void readData();
		void writeData();
		
		// encode or decode binary data to packet;
		void decode();	
		void encode(const IPacket *p);

		void shutdown();

		void setWriteable(bool t){
			_writeable = t;		
		}
		bool getWriteable(){
			return _writeable;		
		}

		void setReadable(){
			_readable = true;		
		}
		bool getReadable(){
			return _readable;		
		}
		
		void setErr(bool t){
			_err = t;		
		}
		bool getErr(){
			return _err;		
		}
		void setNeedClose(bool t){
			_needclose = t;		
		}
		bool getNeedClose(){
			return _needclose;		
		}	

	private:
	

	private:
		int _fd;
		//int _port;
		//int protocol;
		//远端的IP地址
		size_t _addr_len;
		struct sockaddr _addr;
		//一条连接对应一个套接字
		class Socket *_socket;
		DataStream *_streamer;			
	
		Lock _readlock;
		MemBuffer *_readbuf;
		Lock _writelock;
		MemBuffer *_writebuf;		
	
		bool _writeable = false;
		bool _readable = false;
		bool _err = false;
		bool _needclose = false;		
};


}

#endif

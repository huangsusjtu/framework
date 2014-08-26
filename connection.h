#ifndef _CONNECTION_
#define _CONNECTION_
#include "packet.h"
#include "packetqueue.h"
#include "socket.h"
#include "socketstream.h"
#include "refcount.h"

namespace net {

/**
 * 代表了服务端到客户端的一条连接，该连接可以收发数据包。
 * 关联到数据包队列 : public StrongRef
 */
class Connection{
	public:
		Connection(int sockfd);
		virtual ~Connection();

		//初始化时，添加的信息		
		void prepare(PacketQueue *in, PacketQueue *out);
		void setAddress(sockaddr *addr, size_t addrlen);		

		int getHandle(){return _fd;}
			
	

		void readPacket();
		void writePacket();
		
		void shutdown();

		void setWriteable(bool t){
			_writeable = t;		
		}
		bool getWriteable(){
			return _writeable;		
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
		//一条连接对应一个数据流
		class SocketStream *_streamer;				
	
		//数据包队列
		PacketQueue *_out = NULL;
		PacketQueue *_in = NULL; 
	public:
		bool _writeable = false;
		bool _err = false;
		bool _needclose = false;		
};


}

#endif

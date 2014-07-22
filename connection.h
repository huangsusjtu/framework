#ifndef _CONNECTION_
#define _CONNECTION_
#include "packet.h"
#include "packetqueue.h"
#include "socket.h"
#include "socketstream.h"


namespace net {

/**
 * 代表了服务端到客户端的一条连接，该连接可以收发数据包。
 * 关联到数据包队列
 */
class Connection{
	public:
		Connection(Socket* sock, sockaddr *addr=NULL, size_t addrlen=0);
		virtual ~Connection();

		//初始化时，添加的信息		
		void prepare();
		void setPacketQueue(PacketQueue *in, PacketQueue *out);
		void setAddress(sockaddr *addr, size_t addrlen);		

		int getHandle(){return _fd;}
				

		bool readPacket();
		bool writePacket();

	private:
		void postPacketToQueue();
		bool getPacketFromQueue();

	private:
		int _fd;
		//int _port;
		//int protocol;
		size_t _addr_len;
		struct sockaddr _addr;
		class Socket *_socket;	
		class SocketStream *_streamer;				
	
		class PacketQueue *_out;
		class PacketQueue *_in;
		class PacketQueue *_own;
		class Packet *_cur_in;
		class Packet *_cur_out;	
};


}

#endif

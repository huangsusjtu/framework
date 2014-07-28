#ifndef _SOCKET_STREAM__
#define _SOCKET_STREAM__


#include "socket.h"
#include "packet.h"
#include "packetqueue.h"
/**
负责将数据包从soclet中读出， 或者写入数据包
*/
namespace net{
	
	class SocketStream{
		//class Packet;
		public:
			SocketStream(Socket *soc);
			virtual ~SocketStream();

			void readToPacket(PacketQueue *p);
			bool writeFromPacket(PacketQueue *p);
		private:	
			Socket *_socket;

			
			Packet *_cur_in = NULL;
			Packet *_cur_out = NULL;
			//读取数据包头部的信息
			char _buffer_in[16];
			size_t _pos_in = 0;
			size_t _size_in = sizeof(class PacketHeader);
			//写出数据包头部的信息
			char _buffer_out[16];
			size_t _pos_out = 0;
			size_t _size_out = sizeof(class PacketHeader);

			
	};

}


#endif

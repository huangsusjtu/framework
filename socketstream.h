#ifndef _SOCKET_STREAM__
#define _SOCKET_STREAM__


#include "socket.h"
#include "packet.h"
/**
负责将数据包从soclet中读出， 或者写入数据包
*/
namespace net{
	
	class SocketStream{
		//class Packet;
		public:
			SocketStream(Socket *soc);
			virtual ~SocketStream();

			bool readToPacket(class Packet *p);
			bool writeFromPacket(const class Packet *p);
		private:	
			Socket *_socket;
	};

}


#endif

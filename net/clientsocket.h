#ifndef CLIENTSOCKET
#define CLIENTSOCKET
#include "socket.h"
#include <netinet/in.h>  
namespace net{

class ClientSocket : public Socket
{
	public:
		ClientSocket();
		~ClientSocket();
	
		//the addr is server domain name
		bool createByAddr(const char* addr, const int port);
		//客户端主动连接远端， 获得一个连接
		class Connection * getConnect();
		
	private:
		
		ClientSocket(const ClientSocket &T);
		ClientSocket& operator=(const ClientSocket &T);
	protected:
		struct sockaddr_in  remote_address;		
		int remote_port;
};

}

#endif

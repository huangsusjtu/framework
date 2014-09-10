#ifndef SERVERSOCKET
#define SERVERSOCKET

#include "socket.h"

#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace net{

/**
* 用于创建服务端的 监听套接字
*/
class ServerSocket : public Socket
{
	
	public:
		ServerSocket();
		~ServerSocket();


		bool createSocketAndListen(const int port, int backlog = 1024);
		
		// for block mode
		int accept();
	private:
		bool socketListen(struct sockaddr *sa, socklen_t len, int backlog);
		
		ServerSocket(const ServerSocket &T);
		ServerSocket&  operator=(const ServerSocket &T);
	protected:
		char *hostname;
		struct sockaddr_in  local_address;	
};



}

#endif

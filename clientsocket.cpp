#include "clientsocket.h"
#include "connection.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace net{

ClientSocket::ClientSocket(): Socket()
{}

ClientSocket::~ClientSocket()
{}

//remote address, remote port
bool ClientSocket::createByAddr(const char* addr, const int port)
{
		int rv;
    	char portstr[6];  /* strlen("65535") + 1; */
    	struct addrinfo hints, *servinfo, *p;

    	snprintf(portstr,sizeof(portstr),"%d",port);
    	memset(&hints,0,sizeof(hints));
		hints.ai_family = AF_INET; //ipv4
		hints.ai_socktype = SOCK_STREAM;

    	if ((rv = getaddrinfo(addr,portstr,&hints,&servinfo)) != 0) {
        	return false;
    	}

		for (p = servinfo; p != NULL; p = p->ai_next) {		
			if(createSocket(p->ai_family,p->ai_socktype,p->ai_protocol))
			{
				remote_address = *(struct sockaddr_in *)(p->ai_addr);
				remote_port = port;
				freeaddrinfo(servinfo);
				return true;
			}

		}
		freeaddrinfo(servinfo);
		return false;
}



Connection* ClientSocket::getConnect()
{
	if(-1==::connect(sock_fd, (struct sockaddr*)&remote_address, sizeof(struct sockaddr)))
	{	
		::close(sock_fd);
		sock_fd = -1;
		return NULL;
	}
	
	Socket *socket = new ConnectedSocket(sock_fd);
	Connection *con = new Connection(socket);	
	return con;
}

}

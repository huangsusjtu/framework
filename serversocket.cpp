#include "serversocket.h"
#include "logger.h"
#include "event_driver.h"
#include "listensocketevent.h"
#include "neteventdriver.h"
#include "connection.h"

#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>

namespace net{

ServerSocket::ServerSocket():Socket(),hostname(NULL)
{
	char name[1024];
	//获得本机域名
	if(gethostname(name, 1024)==0){
		hostname = strdup(name);
	}else{
		//Logger::e("获得本地域名失败");
		std::cerr<<"获得本地域名失败 "<<std::endl;
		exit(0);
	}
}

ServerSocket::~ServerSocket()
{
	if(hostname)
		::free(hostname);
}

bool ServerSocket::createSocketAndListen(const int port, int blacklog)
{
	int s, rv;
    	char _port[6];  /* strlen("65535") */
    	struct addrinfo hints, *servinfo, *p;

    	snprintf(_port,6,"%d",port);
	    	
	memset(&hints,0,sizeof(hints));
    	hints.ai_family = AF_UNSPEC;
    	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE;    /* No effect if bindaddr != NULL */

    	if ((rv = getaddrinfo(hostname,_port,&hints,&servinfo)) != 0) {
       		return false;
    	}
    	for (p = servinfo; p != NULL; p = p->ai_next) {
			if(p->ai_family == AF_INET){
				//ipv4
				if (false==createSocket(p->ai_family,p->ai_socktype,p->ai_protocol) )
					continue;
				
				if(p->ai_socktype == SOCK_STREAM ){
					//tcp,套接字监听， 创建监听事件并加入到队列
					if(false==socketListen(p->ai_addr,p->ai_addrlen, blacklog))
						continue;
					EventDescripter *desc = new ListenEvent(sock_fd);
					NetEventDriver::instance().addEventDescripter(desc);
					ListenEventQueue::instance().add((ListenEvent*)desc);
				}else if(p->ai_socktype == SOCK_DGRAM){
					//udp
					
				}
			}else if(p->ai_family == AF_INET6)
			{
				//ipv6
				if (false==createSocket(p->ai_family,p->ai_socktype,p->ai_protocol) )
					continue ;
				if(p->ai_socktype == SOCK_STREAM ){
					//tcp,套接字监听， 创建监听事件并加入到队列
					if(false==socketListen(p->ai_addr,p->ai_addrlen, blacklog))
						continue;
					EventDescripter *desc = new ListenEvent(sock_fd);
					NetEventDriver::instance().addEventDescripter(desc);
					ListenEventQueue::instance().add((ListenEvent*)desc);
				}else if(p->ai_socktype == SOCK_DGRAM){
					//udp				
				}
			}
			
		}
		freeaddrinfo(servinfo);
		return false;
}

bool ServerSocket::socketListen(struct sockaddr *sa, socklen_t len, int backlog)
{
    	if (::bind(sock_fd,sa,len) == -1) {
        	::close(sock_fd);
		sock_fd = -1;
        	return false;
    	}

    	if (::listen(sock_fd, backlog) == -1) {
        	::close(sock_fd);
		sock_fd = -1;
        	return false;
    	}
    	return true;
}

/**
Connection* ServerSocket::getConnection()
{
	int fd;
	struct sockaddr_storage sa;
    	socklen_t salen = sizeof(sa);
    	while(1) {
        	fd = ::accept(sock_fd, (sockaddr*)&sa, &salen);
        	if (fd == -1) {
            	if (errno == EINTR)
                	continue;
           	else
                	return NULL;
        	}
    	}

	Socket *socket = new ConnectedSocket(fd);
	Connection *con = new Connection(socket);
	
	if (sa.ss_family == AF_INET) { //ipv4
		struct sockaddr_in *s = (struct sockaddr_in *)&sa;
		//con->addr = *(sockaddr*)s;
		//con->port = ntohs(s->sin_port);
		con->setAddress( (struct sockaddr*)&sa, sizeof(struct sockaddr), ntohs(s->sin_port));
	} else { //ipv6
		//struct sockaddr_in6 s = *((struct sockaddr_in6 *)&sa);
		//con->port = ntohs(s->sin6_port);
	}

   	return con;
}
*/

}

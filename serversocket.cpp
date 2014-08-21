#include "serversocket.h"
#include "logger.h"
#include "event_driver.h"
#include "listensocketevent.h"
#include "neteventdriver.h"
#include "connection.h"
#include "logger.h"

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
		std::cerr<<name<<std::endl;
	}else{
		sys::Logger::e("获得本地域名失败");
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
	bool res = false;
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
		std::cerr<<"get local addr err"<<std::endl;   
		//sys::Logger::e("get local addr err");       	
		return false;
    	}
	std::cerr<<"get local addr Ok"<<std::endl;   
	//sys::Logger::i("get local addr Ok");      
    	for (p = servinfo; p != NULL; p = p->ai_next) {
			if(p->ai_family == AF_INET){
				//ipv4
				if (false==createSocket(p->ai_family,p->ai_socktype,p->ai_protocol) )
					continue;
				//setNonBlock();
				setBlock();
				//sys::Logger::i("Create socket IPV4 Ok"); 
				std::cerr<<"Create socket IPV4 Ok"<<std::endl;   
				if(p->ai_socktype == SOCK_STREAM ){
					//tcp,套接字监听， 创建监听事件并加入到队列
					if(false==socketListen(p->ai_addr,p->ai_addrlen, blacklog))
					{
						std::cerr<<"Socket IPV4 tcp listening err!"<<std::endl;   
						//sys::Logger::i("Socket IPV4 listening err!"); 
						continue;
					}
					
					local_address = *(struct sockaddr_in*)(p->ai_addr);
					EventDescripter *desc = new ListenEvent(sock_fd);
					NetEventDriver::instance().addEventDescripter(desc);
					//ListenEventQueue::instance().add((ListenEvent*)desc);
					//sys::Logger::i("Socket is IPV4 tcp listening!");   
					std::cerr<<"Socket is IPV4 tcp listening!"<<std::endl;  
					res = true; 
				}else if(p->ai_socktype == SOCK_DGRAM){
					//udp
					std::cerr<<"Socket IPV4 tcp listening ok!"<<std::endl;   
					//sys::Logger::i("Socket is IPV4 udp listening!");   
					res = true; 
				}
			}else if(p->ai_family == AF_INET6)
			{
				//ipv6
				if (false==createSocket(p->ai_family,p->ai_socktype,p->ai_protocol) )
					continue ;
				if(p->ai_socktype == SOCK_STREAM ){
					//tcp,套接字监听， 创建监听事件并加入到队列
					if(false==socketListen(p->ai_addr,p->ai_addrlen, blacklog))
					{
						std::cerr<<"Socket is IPV6 tcp listen  err!"<<std::endl;  
						//sys::Logger::i("Socket IPV6 listening err!");   					
						continue;
					}
					EventDescripter *desc = new ListenEvent(sock_fd);
					NetEventDriver::instance().addEventDescripter(desc);
					ListenEventQueue::instance().add((ListenEvent*)desc);
					std::cerr<<"Socket is IPV6 tcp listen  ok!"<<std::endl;  
					//sys::Logger::i("Socket IPV6 is listening!");   
					res = true; 
				}else if(p->ai_socktype == SOCK_DGRAM){
					//udp	
					sys::Logger::i("Socket IPV6 is listening!");   
					res = true; 			
				}
			}
			
		}
		freeaddrinfo(servinfo);
		return res;
}

bool ServerSocket::socketListen(struct sockaddr *sa, socklen_t len, int backlog)
{
    	if (::bind(sock_fd,sa,len) == -1) {
        	::close(sock_fd);
		sock_fd = -1;
		std::cerr<<"Socket bind err!"<<errno<<std::endl;  
        	return false;
    	}

    	if (::listen(sock_fd, backlog) == -1) {
        	::close(sock_fd);
		sock_fd = -1;
		std::cerr<<"Socket listen err!"<<errno<<std::endl;  
        	return false;
    	}
    	return true;
}

//for block mode
int ServerSocket::accept()
{
	struct sockaddr addr;
	socklen_t addrlen;
	return ::accept(sock_fd, &addr, &addrlen);
}

}

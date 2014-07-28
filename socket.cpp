#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socket.h"
namespace net{

Socket::Socket(int fd):sock_fd(fd)
{
}

Socket::~Socket()
{
}


/*const status NetworkSocket::createClientAndConnect(const char* addr, int port)
{
	int s = ANET_ERR, rv;
	char portstr[6];  
	struct addrinfo hints, *servinfo, *p;

	snprintf(portstr,sizeof(portstr),"%d",port);
	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(addr,portstr,&hints,&servinfo)) != 0) {
		return status::obtainStatus("Socket getaddrinfo err");
	}
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ( status::obtainStatusOK()=!SocketClient(p->ai_family,p->ai_socktype,p->ai_protocol))
			continue;
		if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
			 freeaddrinfo(servinfo);
			return status::obtainStatus("Socket connect err");	
		}
	}
	 freeaddrinfo(servinfo);
	return status::obtainStatusOK();
}*/

bool Socket::createSocket(int family, int type, int protocol)
{
	if( (sock_fd=::socket(family, type, protocol)) == -1)
		return false;
	if( setReuse() == -1 ){
		goto err;
	}
	if( setNonBlock() !=0){
		goto err;
	}
	return true;
err:
	::close(sock_fd);
	sock_fd = -1;
	return false;
}

bool Socket::closeSocket()
{
	if(sock_fd>0)
		::close(sock_fd);
	sock_fd = -1;
}

bool Socket::enableNoDelay()
{
	if(setNoDelay(1)!=0)
		return false;
	return true;
}

bool Socket::disableNoDelay()
{
	if(setNoDelay(0)!=0)
		return false;
	return true;

}

bool Socket::setSendBuffer(int bufsize)
{
	if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize)) == -1)
	{
		return false;
	}
	return true;
}


/**
 *
 */


//create socket
/*int NetworkSocket::createSocket(int domain, int socktype,int protocal)
{
	sock_fd = socket(domain, socktype, protocol);
	if(sock_fd<0)
		return -1;
	return 0;
}*/

int Socket::setReuse()
{
	int yes = 1;
	return setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
}
int Socket::setNonBlock()
{
	int flags;
	/* Set the socket non-blocking.
	 *      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
	 *           * interrupted by a signal. */
	if ((flags = fcntl(sock_fd, F_GETFL)) == -1) {
		return -1;
	}
	if (fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		return -2;
	}
	return 0;
}

int Socket::keepLive(int interval)
{
	int val = 1;
	if(setsockopt(sock_fd, SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val)==-1 ))
	return -1;

	val = interval;
	/* Send first probe after interval. */
	if (setsockopt(sock_fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val)) < 0) {
		return -2;
	}

	/* Send next probes after the specified interval. Note that we set the
	 *      * delay as interval / 3, as we send three probes before detecting
	 *           * an error (see the next setsockopt call). */
	val = interval/3;
	if (val == 0) val = 1;
	if (setsockopt(sock_fd, IPPROTO_TCP, TCP_KEEPINTVL, &val, sizeof(val)) < 0) {
		return -3;
	}

	/* Consider the socket in error state after three we send three ACK
	 *      * probes without getting a reply. */
	val = 3;
	if (setsockopt(sock_fd, IPPROTO_TCP, TCP_KEEPCNT, &val, sizeof(val)) < 0) {
		return -4;
	}
	return 0;
}


int Socket::setNoDelay(int val)
{
	if (setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) == -1)
	{
		return -1;
	}
	return 0;
}

int Socket::read(char* buf, int count)
{
	if(sock_fd<0)return -1;
        return ::read(sock_fd,buf,count);

}

int Socket::write(const char* buf, int count)
{
	if(sock_fd<0)return -1;
        return ::write(sock_fd,buf,count);
}

//get remote
bool Socket::getPeer(char *ip, size_t ip_len, int *port) {
    struct sockaddr_storage sa;
    socklen_t salen = sizeof(sa);

    if (getpeername(sock_fd,(struct sockaddr*)&sa,&salen) == -1) {
        if (port) *port = 0;
        ip[0] = '?';
        ip[1] = '\0';
        return false;
    }
    if (sa.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&sa;
        if (ip) inet_ntop(AF_INET,(void*)&(s->sin_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin_port);
    } else {
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&sa;
        if (ip) inet_ntop(AF_INET6,(void*)&(s->sin6_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin6_port);
    }
    return true;
}

//get local 
bool Socket::getSockName(char *ip, size_t ip_len, int *port) {
    struct sockaddr_storage sa;
    socklen_t salen = sizeof(sa);

    if (getsockname(sock_fd,(struct sockaddr*)&sa,&salen) == -1) {
        if (port) *port = 0;
        ip[0] = '?';
        ip[1] = '\0';
        return false;
    }
    if (sa.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&sa;
        if (ip) inet_ntop(AF_INET,(void*)&(s->sin_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin_port);
    } else {
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&sa;
        if (ip) inet_ntop(AF_INET6,(void*)&(s->sin6_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin6_port);
    }
    return true;
}



}


#ifndef CONNECTED_SOCKET_EVENT
#define CONNECTED_SOCKET_EVENT

#include "event_driver.h"
#include "connection.h"
namespace net{
using sys::EventDescripter;
/**
 * 已经建立连接的套接字，以及当该套接字有事件时的处理函数
 */
class TcpSocketEvent : public EventDescripter
{
	public:
		TcpSocketEvent(int fd, Connection *con=NULL, uint32_t eventtype= EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLET);
		~TcpSocketEvent();

		//当该tcp连接上 发生时间时调用的函数
		virtual void eventHandler(struct epoll_event &ev);

		
	private:
		TcpSocketEvent(const TcpSocketEvent &T);
		TcpSocketEvent& operator=(const TcpSocketEvent &T);

	private:
		Connection *_con = NULL;

};



}


#endif

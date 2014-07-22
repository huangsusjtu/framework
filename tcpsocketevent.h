#ifndef CONNECTED_SOCKET_EVENT
#define CONNECTED_SOCKET_EVENT

#include "event_driver.h"

namespace net{

/**
 * 已经建立连接的套接字，以及当该套接字有事件时的处理函数
 */
class TcpSocketEvent : public EventDescripter
{
	public:
		TcpSocketEvent(int fd, uint32_t eventtype= EPOLLIN | EPOLLOUT |EPOLLRDHUP);
		~TcpSocketEvent();

		virtual void eventHandler(struct epoll_event &ev);

		void setNext(TcpSocketEvent *T){
			next = T;
		}
		TcpSocketEvent* getNext()
		{
			return next;
		}
	private:
		TcpSocketEvent(const TcpSocketEvent &T);
		TcpSocketEvent& operator=(const TcpSocketEvent &T);

	private:
		bool _writeable = false;
		bool _err = false;
		bool _needclose = false;
		TcpSocketEvent *next = NULL;
		

};

/**
 * 维护所以的套接字连接
 */
class TcpSocketQueue
{
	public:
		static TcpSocketQueue& instance(){
			return self;		
		}
		~TcpSocketQueue();
		
		TcpSocketEvent* find(int fd);
		void add(TcpSocketEvent *T);
		
		TcpSocketEvent* front(){
			return _head;
		}

	private:
		TcpSocketQueue();
		TcpSocketQueue(const TcpSocketQueue &T);
		TcpSocketQueue& operator=(const TcpSocketQueue &T);

	private:
		TcpSocketEvent *_head;
		TcpSocketEvent *_tail;
		int _len;
		static TcpSocketQueue self;

};


}


#endif

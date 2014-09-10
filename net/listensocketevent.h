#ifndef LISTEN_SOCKET_EVENT_
#define LISTEN_SOCKET_EVENT_

#include "event_driver.h"
#include "socket.h"
namespace net{
using namespace sys;
/**
 * 需要被监听的套接字描述符以及对应的处理该描述符上的事件
 * ,该套接字是服务器的，等待客户端建立连接
 */
class ListenEvent : public EventDescripter{

	public:
		ListenEvent(int fd, uint32_t eventtype = EPOLLIN | EPOLLRDHUP | EPOLLET);
		~ListenEvent();

		void handleConnectEvent();

		void setNext(ListenEvent *n){
			next = n;
		}
		ListenEvent* getNext(){
			return next;
		}

		virtual void eventHandler(struct epoll_event &ev);
	private:
		void handleConEvent(int fd);

	private:
		ListenEvent(const ListenEvent &T);
		ListenEvent& operator=(const ListenEvent &T);

	private:
		ListenEvent *next;

};


/**
 * 服务端所有的监听套接字， 考虑到服务器的IP不止一个
 
 */
class ListenEventQueue{
	public:
		static ListenEventQueue& instance(){
			return self;
		}
		~ListenEventQueue();

		ListenEvent *find(int fd);
		void add(ListenEvent *T);
		
		ListenEvent *front(){
			return _head;
		}
		
	private:
		ListenEventQueue();
		ListenEventQueue(const ListenEventQueue &T);
		ListenEventQueue& operator=(const ListenEventQueue &T);
	private:
		ListenEvent *_head;
		ListenEvent *_tail;
		int _len;
		static ListenEventQueue self;
};

}


#endif

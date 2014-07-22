#include "listensocketevent.h"
#include "connection.h"
#include "connectionmanager.h"
#include "neteventdriver.h"
#include "event_driver.h"
#include "tcpsocketevent.h"


#include <unistd.h>
#include <cassert>
#include <sys/types.h>
#include <sys/socket.h>

namespace net{

/**
 * ListenEvent
 */
ListenEvent::ListenEvent(int fd):
	EventDescripter(fd),
	next(NULL)
{
	assert(fd>0);
}

ListenEvent::~ListenEvent()
{
}

//当epoll通知事件发生，该函数要做处理。
void ListenEvent::eventHandler(struct epoll_event &ev)
{
	//通知有客户端建立连接请求
	//获得事件描述符
	EventDescripter *desc = (EventDescripter*)ev.data.ptr;	
	assert(desc!=NULL);
	//有连接请求
	if(ev.events & EPOLLIN)
	{
		handleConEvent(desc->getfd());		
	}
	//出错
	else if(ev.events & EPOLLERR)
	{
		
	}else if(ev.events & EPOLLRDHUP){
	
	}
	return ;
}

void ListenEvent::handleConEvent(int fd)
{
	assert(fd>0);
	int con_fd;
	struct sockaddr_storage sa;
	socklen_t salen = sizeof(sa);
	while(1) {
		con_fd = ::accept(fd, (sockaddr*)&sa, &salen);
		if (con_fd == -1) {
			return ;
		}
		//创建连接,添加到连接管理器
		//Socket *socket = new Socket(con_fd);
		//socket->setNonBlock();	
		//Connection *con = new Connection(socket);
		//ConnectionManager::instance().addConnection(con);		
	
		//将该新套接字 添加到事件监听当中
		EventDescripter *desc = new TcpSocketEvent(con_fd);
		NetEventDriver::instance().addEventDescripter(desc);
		TcpSocketQueue::instance().add((TcpSocketEvent*)desc);
	}
}

/**
 * ListenEventQueue
 */
ListenEventQueue ListenEventQueue::self;


ListenEventQueue::ListenEventQueue():
	_head(NULL),_tail(NULL),_len(0)
{}

ListenEventQueue::~ListenEventQueue()
{
	while(_len>0)
	{
		ListenEvent *p = _head->getNext();
		delete _head;
		_head = p;
		_len--;
	}
}

ListenEvent* ListenEventQueue::find(int fd)
{
	ListenEvent* p = _head;
	while(p)
	{
		if(p->getfd()==fd)
			return p;
		p = p->getNext();
	}
	return NULL;
}

void ListenEventQueue::add(ListenEvent *T)
{
	if(0==_len)
	{
		_head = _tail = T;
		_len = 1;
	}else{
		_tail->setNext(T);
		_tail = T;
		_len++;
	}
}



}


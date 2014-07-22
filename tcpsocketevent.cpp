#include "tcpsocketevent.h"

#include <cassert>

namespace net{

/**
 *
 */
TcpSocketEvent::TcpSocketEvent(int fd, uint32_t eventtype )
	:EventDescripter(fd, eventtype)
{}

TcpSocketEvent::~TcpSocketEvent()
{}

void TcpSocketEvent::eventHandler(struct epoll_event &ev)
{
	EventDescripter *desc = (EventDescripter*)ev.data.ptr;	
	assert(desc!=NULL);
	if(ev.events & EPOLLIN)
	{
		//创建一个读IO事件，并加入读事件队列
		// . . . .	
	}
	else if(ev.events & EPOLLOUT)
	{
		_writeable = true;
	}
	else if(ev.events & EPOLLERR)
	{
		_err = true;
	}
	else if(ev.events & EPOLLRDHUP)
	{
		_needclose = true;
	}
	return ;
}


/**
 *
 */
TcpSocketQueue TcpSocketQueue::self;

TcpSocketQueue::TcpSocketQueue():
	_head(NULL),_tail(NULL),_len(0)
{}

TcpSocketQueue::~TcpSocketQueue()
{
	while(_len>0)
	{
		TcpSocketEvent *p = _head;
		_head = _head->getNext();
		delete p;
		_len--;
	}
}


TcpSocketEvent* TcpSocketQueue::find(int fd)
{
	TcpSocketEvent* p = _head;
	while(p)
	{
		if(p->getfd()==fd)
			return p;
		p = p->getNext();
	}
	return NULL;
}
	


void TcpSocketQueue::add(TcpSocketEvent *T)
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

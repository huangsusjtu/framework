#include "commond.h"
#include "netevent.h"
#include "tcpsocketevent.h"
#include "logger.h"
#include <cassert>

namespace net{

using sys::Logger;
using sys::Commond;
/**
 *
 */
TcpSocketEvent::TcpSocketEvent(int fd, uint32_t eventtype , Connection *con)
	:EventDescripter(fd, eventtype), _con(con)
{
	assert(con!=NULL);
}

TcpSocketEvent::~TcpSocketEvent()
{}


/**
* 当tcp套接字有消息时，需要做的处理例程
*/
void TcpSocketEvent::eventHandler(struct epoll_event &ev)
{
	EventDescripter *desc = (EventDescripter*)ev.data.ptr;	
	assert(desc!=NULL);
	if(_con==NULL){
		sys::Logger::w("A tcpsocket event occur on null connection!");
		return ;
	}
	if(ev.events & EPOLLIN)
	{
		//创建一个读IO事件，并加入读事件队列
		// . . . .
		NetReadCommond *nm = new NetReadCommond(_con);
		NetReadQueue::instance().addBack(nm);		

	}
	else if(ev.events & EPOLLOUT)
	{
		//套接字可写，标记下就可以了
		_con->_writeable = true;

	}
	else if(ev.events & EPOLLERR)
	{
		sys::Logger::w("A writeable on null connection!");
		_con->_err = true;
	}
	else if(ev.events & EPOLLRDHUP)
	{
		_con->_needclose = true;
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

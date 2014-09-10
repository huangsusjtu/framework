#include "commond.h"
#include "netevent.h"
#include "tcpsocketevent.h"
#include "datatransport.h"
#include "logger.h"
#include <cassert>

namespace net{

using sys::Logger;
using sys::Commond;
/**
 *
 */
TcpSocketEvent::TcpSocketEvent(int fd, Connection *con,uint32_t eventtype)
	:EventDescripter(fd, eventtype), _con(con)
{
	//assert(con!=NULL);
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
		std::cerr<<"A tcpsocket event occur on null connection!"<<std::endl;
		return ;
	}
	if(ev.events & EPOLLIN)
	{
		//创建一个读IO事件，并加入读事件队列
		// . . . .
		_con->readData();
		Commond *nm = new NetReadCommond(_con);
		Transport::instance().getCommondQueue()->push(nm);		
		sys::Logger::i("A tcpsocket read event occur on connection!");
		std::cerr<<"A tcpsocket read event occur on connection!"<<std::endl;
	}
	else if(ev.events & EPOLLOUT)
	{
		//套接字可写，标记
		_con->setWriteable(true);
		//_con->writeData();
		sys::Logger::i("A tcpsocket writable occur on connection!");
		std::cerr<<"A tcpsocket writable occur on connection!"<<std::endl;

	}
	else if(ev.events & EPOLLERR)
	{
		sys::Logger::i("A tcpsocket err occur on connection!");
		std::cerr<<"A tcpsocket err occur on connection!"<<std::endl;

		_con->setErr(true);
	}
	else if(ev.events & EPOLLRDHUP)
	{
		sys::Logger::i("A tcpsocket remote close occur on connection!");
		std::cerr<<"A tcpsocket remote close occur on connection!"<<std::endl;

		_con->setNeedClose(true);
	}
	return ;
}


/**
 *
 */


}

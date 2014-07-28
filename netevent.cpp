#include "logger.h"
#include "netevent.h"
#include <cassert>

namespace net{

NetReadCommond::NetReadCommond(Connection *con)
	: Commond(TYPE::READ), _con(con)
{
	assert(con!=NULL);
}

NetReadCommond::~NetReadCommond()
{
}

void NetReadCommond::onCommond()
{
	TYPE type = getType();

	//...do something  读数据的
	if(_con)
		_con->readPacket();
	return ;
}

/**
* 全局的读事件 队列
*/
NetReadQueue NetReadQueue::self;


/**
* 
*/
NetWriteCommond::NetWriteCommond(Connection *con)
	: Commond(TYPE::WRITE), _con(con)
{
	assert(con!=NULL);
}

NetWriteCommond::~NetWriteCommond()
{
}

void NetWriteCommond::onCommond()
{
	//写事件的处理
	if(_con)
		_con->writePacket();
	return ;
}

/**
* 全局的写事件 队列
*/
NetWriteQueue NetWriteQueue::self;


}

#include "logger.h"
#include "netevent.h"
#include "logger.h"


namespace net{
using sys::Logger;

NetReadCommond::NetReadCommond(Connection *con)
	: Commond(TYPE::READ), _con(con)
{
	//assert(con!=NULL);
}

NetReadCommond::~NetReadCommond()
{
}

void NetReadCommond::onCommond()
{
	//TYPE type = getType();

	//...do something  读数据的
	if(!_con)
	{
		Logger::w("No connection to read for this commond");
		return ;
	}	
	//数据包解析
	_con->decode();
}

/**/
NetWriteCommond::NetWriteCommond(IPacket *p)
	: Commond(TYPE::WRITE), _out(p)
{
	//assert(p!=NULL);
}

NetWriteCommond::~NetWriteCommond()
{}

void NetWriteCommond::onCommond()
{
	Connection *con = _out->getConnection();
	if(!con)
	{
		Logger::w("No connection to write for this commond");
		return ;
	}	
	//编码成二进制，写入缓冲区,发送
	con->encode(_out);
}

}

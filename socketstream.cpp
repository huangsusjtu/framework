#include "memblockpool.h"
#include "socketstream.h"
#include <cassert>

namespace net{


SocketStream::SocketStream(Socket *soc):_socket(soc)
{
	assert(soc!=NULL );
}

SocketStream::~SocketStream()
{}

bool SocketStream::readToPacket(Packet *p)
{
	//首次为该packet读数据
	if(0==p->_len)
	{
		_socket->read((char*)&p->_len, sizeof(p->_len));
		//为packet分配缓冲区
		MemBuffer T;
		if(MemBlockPool::instance().getMemBuffer(&T, p->_len))
			p->setByMemBuffer(&T);
		else
			return false;
	}
	assert(p->_len < (1<<22) );
	size_t len = p->_len;
	size_t pos = p->_pos;
	size_t readlen = 0;
	while(pos<len){
		readlen = _socket->read(p->buf+pos,len-pos);
		pos += readlen;	
		if(readlen ==-1)return false;
	}
	return true;
}

bool SocketStream::writeFromPacket(const Packet* p)
{
	assert(p!=NULL && p->_len>0);
	size_t writelen = 0;
	size_t total = 0;
	while(total < p->_len)
	{
		writelen = _socket->write(p->buf+writelen, p->_len-writelen);
		if(writelen<0)return false;
		total += writelen;
	}
	return true;
}

}

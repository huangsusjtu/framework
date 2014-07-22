#include "connection.h"
namespace net{

Connection::Connection(Socket* sock, sockaddr *addr, size_t addrlen) :
	_socket(sock),_addr(*addr),_addr_len(addrlen),
	_out(NULL),_in(NULL),_own(NULL),_cur_in(NULL),_cur_out(NULL)
{
	assert(sock!=NULL && addr!=NULL);
	_fd = sock->getSocketHandle();
}

void Connection::setAddress(sockaddr *addr, size_t addrlen)
{
	_addr = *addr;
	_addr_len = addrlen;
	
}

void Connection::prepare()
{
	_streamer = new SocketStream(_socket);
	_own = new PacketQueue();
}

Connection::~Connection()
{
	if(_socket)delete _socket;
	if(_cur_in)delete _cur_in;
	if(_streamer)delete _streamer;
	if(_own)delete _own;
}

void Connection::setPacketQueue(PacketQueue *in, PacketQueue *out)
{
	_in = in;
	_out = out;
}

/**读取数据包并放到队列
 */
bool Connection::readPacket()
{
	if(!_cur_in || !_streamer)return false;
	if(!_streamer->readToPacket(_cur_in))
		return false;
	if(_in)
		postPacketToQueue();
	else
	{
		_own->addBack(_cur_in);
	}
	_cur_in = NULL;
	return true;
}

/**
 * 从队列取包并且发送
 */
bool Connection::writePacket()
{
	if( !getPacketFromQueue() || !_streamer)
		return false;
	return _streamer->writeFromPacket(_cur_out);
}

void Connection::postPacketToQueue()
{
	_in->addBack(_cur_in);
}

bool Connection::getPacketFromQueue()
{
	_cur_out = _out->getFront();
	return _cur_out!=NULL;
}

}



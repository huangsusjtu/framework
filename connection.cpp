#include "connection.h"
namespace net{

Connection::Connection(Socket* sock, sockaddr *addr, size_t addrlen) :
	_socket(sock),_addr(*addr),_addr_len(addrlen)
{
	assert(sock!=NULL && addr!=NULL);
	_fd = sock->getSocketHandle();
}

void Connection::setAddress(sockaddr *addr, size_t addrlen)
{
	_addr = *addr;
	_addr_len = addrlen;
	
}

//初始化数据流
void Connection::prepare()
{
	_in = new PacketQueue();
	_out = new PacketQueue();
	_streamer = new SocketStream(_socket);
}


Connection::~Connection()
{
	if(_streamer)delete _streamer;
	if(_in)delete _in;		
	if(_out)delete _out;
	if(_socket)delete _socket;
}


/**
* 读取数据包并放到队列
* 将缓冲区的数据全部读完
*/
void Connection::readPacket()
{
	if(!_streamer || !_in)return ;
	_streamer->readToPacket(_in);
}

/**
 * 从队列取包并且发送
 * @return false: 数据没有写完，内核缓冲区已满。 true: 数据写完
 */
void Connection::writePacket()
{
	if( !_streamer || !_out)
		return ;
	if( false == _streamer->writeFromPacket(_out) )
	{
		//数据没写完，缓冲区已满。
		setWriteable(false);
		return ;
	}
	return ;
}




}



#include "connection.h"
#include "logger.h"
namespace net{

using sys::Logger;

Connection::Connection(Socket* sock, sockaddr *addr, size_t addrlen) :
	_socket(sock),_addr(*addr),_addr_len(addrlen)
{
	assert(sock!=NULL && addr!=NULL);
	_fd = sock->getSocketHandle();
	Logger::i("A new connection created");
}

void Connection::setAddress(sockaddr *addr, size_t addrlen)
{
	_addr = *addr;
	_addr_len = addrlen;
	
}

//初始化数据流
void Connection::prepare(PacketQueue *in, PacketQueue *out)
{
	assert(in!=NULL && out !=NULL);
	_in = in;
	_out = out;
	_streamer = new SocketStream(_socket);
	Logger::i("A connection prepared for data transfer");	
}


Connection::~Connection()
{
	if(_streamer)delete _streamer;
	if(_in)delete _in;		
	if(_out)delete _out;
	if(_socket)delete _socket;
	Logger::i("A connection destory");
}


/**
* 读取数据包并放到队列
* 将缓冲区的数据全部读完
*/
void Connection::readPacket()
{
	if(_needclose)
	{
		Logger::w("The connection need to be closed");
		return ;
	}
	if(_err){	
		Logger::w("The err connection can not read");
		return ;
	}
	if(!_streamer || !_in)
	{
		Logger::w("The connection is not prepared ");
		return ;
	}
	_streamer->readToPacket(_in);
}

/**
 * 从队列取包并且发送'';完
 */
void Connection::writePacket()
{
	if(_needclose)
	{
		Logger::w("The connection need to be closed");
		return ;
	}
	if(_err)
	{
		Logger::w("The err connection can not write data");
		return ;
	}
	if(!_writeable)
	{
		Logger::i("The connection is not writable");
		return ;
	}
	if( !_streamer || !_out)
	{
		Logger::w("The connection is not prepared");
		return ;
	}
	if( false == _streamer->writeFromPacket(_out) )
	{
		//数据没写完，缓冲区已满。
		_writeable = false ;
		return ;
	}
	return ;
}




}



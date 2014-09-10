#include "connection.h"
#include "logger.h"
#include "datatransport.h"
#include "Ipacket.h"
#include <sys/socket.h>

namespace net{

using sys::Logger;


Connection::Connection(int sockfd):
	_fd(sockfd)
{
	assert(sockfd>0);
	_socket = new Socket(_fd); //socket for data transfer
	_readbuf = new MemBuffer(); // databuf for read
	_writebuf = new MemBuffer(); // databuf for write
	_streamer = Transport::instance().getStream(); // to encode and decode
	Logger::i("A new connection created");
}

/**set the client address
 */
void Connection::setAddress(sockaddr *addr, size_t addrlen)
{
	_addr = *addr;
	_addr_len = addrlen;
	
}

//初始化数据流, to encode and decode data stream
void Connection::prepare(DataStream *ss)
{
	if(ss == NULL)
		ss = new NormalDataStream();
	_streamer = ss;
	Logger::i("A connection prepared for data encode and decode");	
}


Connection::~Connection()
{
	if(_streamer)delete _streamer;
	if(_socket)delete _socket;
	if(_readbuf) delete _readbuf;
	if(_writebuf) delete _writebuf;
	Logger::i("A connection destory");
}

void Connection::shutdown()
{
	::shutdown(_fd ,SHUT_WR);
}
/**
* 读取数据包并放到队列
* 将缓冲区的数据全部读完
*/
void Connection::readData()
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
	if(!_streamer || !_readbuf)
	{
		Logger::w("The connection is not prepared ");
		return ;
	}
	//read all the data
	_readlock.lock();
	while(1)	
	{	size_t count =  _readbuf->getFreeSize();
		size_t res;
		res = _socket->read(_readbuf->getBuf(), count );
		if(res>0)
			_readbuf->pour(res);
		if(res<count)
			break;
		_readbuf->expand();	
	}
	_readlock.unlock();
	
}

/**
 * 从队列取包并且发送'';完
 */
void Connection::writeData()
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
	if( !_streamer || !_writebuf)
	{
		Logger::w("The connection is not prepared");
		return ;
	}
	
	_writelock.lock();	
	while(1)
	{
		size_t count =  _writebuf->getDataLen();
		if(0==count)return;
		size_t res = _socket->write(_writebuf->getBuf(), count );
		//数据没写完，缓冲区已满。
		if(res<0){
			sys::Logger::e("Connection send data err!");
			break ;	
		}		
		else if(res==count){
			_writebuf->clear();
			break;
		}else if(res < count){
			_writebuf->drain(res);
			_writebuf->shrink();
			_writeable = false ;
			break;
		}
	}
	_writelock.unlock();
	return ;
}

/** 将数据解码，放到缓冲区 并发送
 */
void Connection::encode(const IPacket *p){
	if(!p) return;
	_writelock.lock();
	_streamer->encodeToStream(_writebuf, p);
	_writelock.unlock();
	writeData();
}

/**将缓冲区的数据 解码为请求，并且放置请求队列
 */
void Connection::decode(){
	IPacket *p = NULL;
	_readlock.lock();
	while(  (p = _streamer->decodeToPacket(_readbuf) ) !=NULL ){
		p->setConnection( const_cast<const Connection*>(this) );
		Transport::instance().getWritePacketQueue()->push(p);	
	}
	_readlock.unlock();
}


}



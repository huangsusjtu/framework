#include "memblockpool.h"
#include "socketstream.h"
#include <cassert>

namespace net{


SocketStream::SocketStream(Socket *soc):_socket(soc)
{
	assert(soc!=NULL );	
	_cur_in = new Packet();
}

SocketStream::~SocketStream()
{
	if(_cur_in)delete _cur_in;
	if(_cur_out)delete _cur_out;
}

/**
* 读取数据包， 如果数据包完整的读下来加入队列。
* @para 接受的数据包队列
* @return 把全部在缓存区的数据都读完
*/
void SocketStream::readToPacket(PacketQueue *queue)
{

	assert( queue!=NULL && _cur_in !=NULL);
	size_t readlen = 0;
	do
	{
		//先读取 数据包头
		if(_pos_in != _size_in){
			readlen = _socket->read(_buffer_in+_pos_in, _size_in - _pos_in);
			if(readlen<=0)
				return ;
			_pos_in += readlen;
			//数据包头没读完。
			if(_pos_in != _size_in)
				return ;
			else{
			//读到完整的数据包头,分配数据包内存
				 uint32_t n = _buffer_in[0];
       				 n <<= 8;
        			 n |= _buffer_in[1];
       				 n <<= 8;
        			 n |= _buffer_in[2];
       				 n <<= 8;
       				 n |= _buffer_in[3];
				_cur_in->_len = n;
				_cur_in->allocMem(n);				
			}		
		}
		
		//将数据读到packet中
		readlen = _socket->read(_cur_in->buf+_cur_in->_pos, _cur_in->_len - _cur_in->_pos);
		if(readlen<=0)
			return ;
		_cur_in->_pos += readlen;
		
		//如果该packet读完整， 加入队列
		if(_cur_in->_pos==_cur_in->_len){
			queue->addBack(_cur_in);
			_cur_in = new Packet();
			_pos_in = 0;	
		}
			
	}while(1);
}

/**
* 数据流对象发送数据
* @para 数据包队列
* @return false:套接字缓存区已经满，数据没写完， true：数据写完 
*/
bool SocketStream::writeFromPacket(PacketQueue* queue)
{
	assert(queue!=NULL );
	size_t writelen = 0;
	size_t total = 0;
	if(_cur_out==NULL)
		_cur_out = queue->getFront();
	while( NULL!=_cur_out )
	{	
		total = 0;
		writelen = 0;
		//数据头要先发送
		while(_pos_out < _size_out){
			writelen = _socket->write(_buffer_out+_pos_out, _size_out - _pos_out);
			if(writelen <0)return false ;
			_pos_out += writelen;
			
		}
		
		//头部发送完毕， 发数据主体
		writelen = 0;
		while(total < _cur_out->_len)
		{
			writelen = _socket->write(_cur_out->buf+total, _cur_out->_len-total);
			if(writelen <=0)return false ;
			total += writelen;
		}

		//数据发送完，发下一个数据包
		delete _cur_out;
		_cur_out= queue->getFront();
		if(_cur_out){
			size_t n = _cur_out->_len;
       			 _buffer_out[3] = (unsigned char)n;
        		 n >>= 8;
       			 _buffer_out[2] = (unsigned char)n;
        		 n >>= 8;
        		 _buffer_out[1] = (unsigned char)n;
        		 n >>= 8;
        		 _buffer_out[0] = (unsigned char)n;		
		}
	}
	return true;
}

}

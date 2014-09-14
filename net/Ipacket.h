#ifndef _BASE_PACKET__
#define _BASE_PACKET__

#include <cstdio>
#include "mempool.h"
#include "membuffer.h"
#include "queue.h"

/**
 * virtual base packet for network data transfer
 */
namespace net{
using namespace sys;

class PacketHeader{
	public:
		size_t _data_len;
};

class Connection;
class IPacket
{
	friend class DataStream;
	public:
		IPacket();
		virtual ~IPacket();

	private:
		PacketHeader _head;
		Connection *_con;
	public:
		void setConnection(const Connection *con){
			_con = const_cast<Connection*>(con);
		}
		Connection *getConnection(){
			return _con;		
		}		

		void allocMem(size_t size);


		/*static Mempool<Packet> &packetpool;
		void *operator new(size_t size){
			return packetpool.alloc();
		}
		void operator delete (void *p, size_t size){
			packetpool.free(p);
		}*/
};
typedef BlockQueue<IPacket> PacketQueue;

// normal packet for plaintext
class NormalPacket : public IPacket
{
	public:
		NormalPacket()
		{
			data = new MemBuffer();
		}
		virtual ~NormalPacket(){
			delete data;		
		}
		MemBuffer* getText(){
			return data;		
		}
		
		const char* getData(){
			return data->getBuf();		
		}		
		size_t getDataLen(){
			return data->getDataLen();		
		}
		void appendString(const char *buf, size_t len){
			if(buf!=NULL)			
				data->writeString(buf, len);		
		}
	private:
		MemBuffer *data;
};


}



#endif

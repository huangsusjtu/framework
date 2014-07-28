#ifndef _BASE_PACKET__
#define _BASE_PACKET__

#include <cstdio>
#include "membuffer.h"
#include "mempool.h"

/**
 * virtual base packet for network data transfer
 */
namespace net{

	class PacketHeader{
		public:
			size_t _data_len;
	};

	class Packet
	{
		friend class SocketStream;
		public:
			Packet(char* addr=NULL, size_t size=0);
			Packet(const MemBuffer *T);
			virtual ~Packet();

		private:
			char *buf;
			
			size_t _pos;			
			size_t _len;
			Packet *next;
		public:
			
			PacketHeader _head;
			bool _headready = false;

			void setByMemBuffer(const MemBuffer *T);
			void setByCommon( char *addr, size_t size);
			void allocMem(size_t size);

			void setNext(Packet *n){next = n;}	


			static Mempool<Packet> &packetpool;
			void *operator new(size_t size){
				return packetpool.alloc();
			}
			void operator delete (void *p, size_t size){
				packetpool.free(p);
			}
	};


}



#endif

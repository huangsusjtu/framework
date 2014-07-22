
#include "packet.h"

namespace net{
	Mempool<Packet>& Packet::packetpool= Mempool<Packet>::GetInstance();	

	Packet::Packet():buf(NULL),_len(0),_pos(0),next(NULL)
	{}

	Packet::Packet(char *addr, size_t size):buf(addr),_len(size),_pos(0),next(NULL)
	{}

	Packet::~Packet()
	{}

	Packet::Packet(const MemBuffer *T)
	{
		buf = T->mData;
		_len = T->mPos;
		_pos = 0;
		next = NULL;
	}

	void Packet::setByCommon(char *addr, size_t size)
	{
		buf = addr;
		_pos = 0;
		_len = size;
		next = NULL;
	}

	void Packet::setByMemBuffer(const MemBuffer* T)
	{
		buf = T->mData;
		_len = T->mPos;
		_pos = 0;
		next = NULL;
	}

}

#include "packetqueue.h"

namespace net{

PacketQueue::PacketQueue()
{
}

PacketQueue::~PacketQueue()
{
	Lock::lock();
	while( !mPacketList.empty())
	{
		Packet *q = mPacketList.front();
		mPacketList.pop_front();
		delete q;	
	}
	Lock:unlock();
}

void PacketQueue::addFront(Packet *p)
{
	if(!p)return ;
	Lock::lock();
	mPacketList.push_front(p);
	Lock:unlock();
}

void PacketQueue::addBack(Packet *p)
{
	if(!p)return ;
	Lock::lock();
	mPacketList.push_back(p);
	Lock:unlock();
}

bool PacketQueue::isEmpty()
{
	return mPacketList.empty();
}

size_t PacketQueue::size()
{
	return mPacketList.size();
}

	
Packet* PacketQueue::getFront()
{
	Packet *res = NULL;
	Lock::lock();
	if(!isEmpty()){
		res = 	mPacketList.front();
		mPacketList.pop_front();
	}
	Lock::unlock();
	return res;
}

Packet* PacketQueue::getBack()
{
	Packet *res = NULL;
	Lock::lock();
	if(!isEmpty()){
		res = 	mPacketList.back();
		mPacketList.pop_back();
	}
	Lock::unlock();
	return res;
}


}

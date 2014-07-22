#ifndef PACKETQUEUE
#define PACKETQUEUE
#include <cassert>
#include <list>
#include "packet.h"
#include "auto_mutex.h"
#include "lock.h"
namespace net{

class PacketQueue : public Lock{
	
	typedef std::list<Packet*> Collection;
	
	public:
		PacketQueue();
		~PacketQueue();

		void addFront(Packet *p);
		void addBack(Packet *p);
		Packet* getFront();
		Packet* getBack();
		bool isEmpty();
		size_t size();
		
	private:
		Collection mPacketList;
};

}
#endif

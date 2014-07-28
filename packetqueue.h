#ifndef PACKETQUEUE
#define PACKETQUEUE
#include <cassert>
#include <list>
#include "packet.h"
#include "auto_mutex.h"
#include "lock.h"

namespace net{

class PacketQueue : public Lock{
	
	typedef std::list<class Packet*> Collection;
	
	public:
		PacketQueue();
		~PacketQueue();

		void addFront(class Packet *p);
		void addBack(class Packet *p);
		class Packet* getFront();
		class Packet* getBack();
		bool isEmpty();
		size_t size();
		
	private:
		Collection mPacketList;
};

}
#endif

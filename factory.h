#ifndef FACTORY__
#define FACTORY__

#include "packet.h"
#include "netevent.h"
#include "connection.h"
using namespace net;

class IFactory{
	
	public:
		IFactory(){};
		virtual ~IFactory(){};

		virtual Packet* createPacket()=0;
		virtual NetWriteCommond* createNetWriteCommond(Connection *con)=0;
		virtual NetReadCommond* createNetReadCommond(Connection *con)=0;
		
	private:
		



};

class Factory : public IFactory
{
	public:
		Factory(){};
		~Factory(){};
		
		Packet* createPacket();
		NetWriteCommond* createNetWriteCommond(Connection *con);
		NetReadCommond* createNetReadCommond(Connection *con);
};



#endif

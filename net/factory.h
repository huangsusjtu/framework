#ifndef FACTORY__
#define FACTORY__

#include "netevent.h"
#include "connection.h"
using namespace net;

class IFactory{
	
	public:
		IFactory(){};
		virtual ~IFactory(){};

		virtual IPacket* createPacket()=0;
		virtual NetWriteCommond* createNetWriteCommond()=0;
		virtual NetReadCommond* createNetReadCommond()=0;
		
	private:
		



};

class Factory : public IFactory
{
	public:
		Factory(){};
		~Factory(){};
		
		IPacket* createPacket();
		NetWriteCommond* createNetWriteCommond();
		NetReadCommond* createNetReadCommond();
};



#endif

#ifndef FACTORY__
#define FACTORY__

#include "netevent.h"
#include "connection.h"
#include "refcount.h"
using namespace net;

using sys::StrongRef;
class IFactory : virtual public StrongRef{
	
	public:
		IFactory(){};
		virtual ~IFactory(){};

		virtual IPacket* createRequest() = 0;
		virtual IPacket* createResponse() = 0;
	private:
		



};

class EchoFactory: public IFactory
{
	public:
		EchoFactory(){};
		~EchoFactory(){};
		
		IPacket* createRequest();
		IPacket* createResponse();
};



#endif

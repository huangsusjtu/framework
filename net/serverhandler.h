#ifndef _SERVER_HANDLER_
#define _SERVER_HANDLER_

#include "Ipacket.h"
#include "Ifactory.h"
namespace net{

//handler to do request	and generate response
class IHandler{
	public:
		IHandler(){};
		virtual ~IHandler(){};

		virtual	void doPacket(IPacket *request, IPacket **response) = 0;

};


class NormalHandler : public IHandler
{
	public:
		NormalHandler(IFactory* factory);
		virtual ~NormalHandler();
		
		virtual void doPacket(IPacket *request, IPacket **response);
	protected:	
		virtual void doRequest(IPacket *request, IPacket *response);
	private:
		IFactory *_factory;
		
};


}



#endif


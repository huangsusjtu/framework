#include "serverhandler.h"

namespace net
{



////////////////////for test
NormalHandler::NormalHandler(IFactory *factory)
{
	_factory = factory;
}

NormalHandler::~NormalHandler()
{
	if(_factory)
		delete _factory;
}

void NormalHandler::doPacket(IPacket *request, IPacket **response)
{	
	*response = _factory->createResponse();
	doRequest(request, *response);
	delete request;
}

void NormalHandler::doRequest(IPacket *request, IPacket *response)
{
	NormalPacket *mRequest = dynamic_cast<NormalPacket*>(request);
	NormalPacket *mResponse = dynamic_cast<NormalPacket*>(response);
	mResponse->appendString(mRequest->getData(), mRequest->getDataLen());
}

}

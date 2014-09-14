#include "Ifactory.h"



IPacket* EchoFactory::createRequest()
{
	return new NormalPacket();
}

IPacket* EchoFactory::createResponse()
{
	return new NormalPacket();
}


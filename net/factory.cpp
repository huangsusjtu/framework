#include "factory.h"



IPacket* Factory::createPacket()
{
	return new NormalPacket();
}

NetWriteCommond* Factory::createNetWriteCommond()
{
	return new NetWriteCommond();
}

NetReadCommond* Factory::createNetReadCommond()
{
	return new NetReadCommond();
}

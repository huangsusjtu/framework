#include "factory.h"



Packet* Factory::createPacket()
{
	return new Packet();
}

NetWriteCommond* Factory::createNetWriteCommond(Connection *con)
{
	return new NetWriteCommond(con);
}

NetReadCommond* Factory::createNetReadCommond(Connection *con)
{
	return new NetReadCommond(con);
}

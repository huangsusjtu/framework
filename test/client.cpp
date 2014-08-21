#include "clientsocket.h"

#include <iostream>
int main()
{
	using namespace net;
	ClientSocket *client = new ClientSocket();
	if(client->createByAddr("huangsu-Lenovo-IdeaPad-Y410P", 10000) ==true )
	{
		client->getConnect();
		std::cerr<<"create client ok"<<std::endl;
		char line[1024];
		client->read(line,1024);
		std::cerr<<line<<std::endl;
		client->closeSocket();		
	}else{
		std::cerr<<"create client err"<<std::endl;
	}
	return 0;
}

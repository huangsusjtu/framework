#include "clientsocket.h"

#include <iostream>
int main()
{
	using namespace sys;
	using namespace net;
	ClientSocket *client = new ClientSocket();
	if(client->createByAddr("huangsu-Lenovo-IdeaPad-Y410P", 10000) ==true )
	{
		client->getConnect();
		std::cerr<<"create client ok"<<std::endl;
		while(1)
		{
		}
		client->closeSocket();		
	}else{
		std::cerr<<"create client err"<<std::endl;
	}
	return 0;
}

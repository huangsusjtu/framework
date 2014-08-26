#include "serversocket.h"
#include "logger.h"
#include "thread.h"
#include "neteventdriver.h"
#include "listensocketevent.h"
#include "datatransport.h"
#include "connection.h"
#include <iostream>

int main()
{
	std::cerr<<"in server test"<<std::endl;
	using namespace net;
	using namespace sys;
	Logger& log = Logger::instance();
	Transport::instance();


	
	ServerSocket *server = new ServerSocket();
	
	if(true == server->createSocketAndListen(10000) )
	{
		std::cerr<<"create server ok"<<std::endl;
		//Socket *con = new Socket(server->accept());
		//const char *line =  "heheh";
		//con->write(line,5);
		//std::cerr<<line<<std::endl;	
		//con->closeSocket();
		ListenEvent *le = new ListenEvent(server->getSocketHandle());
		NetEventDriver::instance().addEventDescripter(le);
		//无限循环
		NetEventDriver::instance().handleEventLoop();
		server->closeSocket();		
	}else{
		std::cerr<<"create serve err"<<std::endl;	
	}	
	ThreadManager::instance().waitForTerminate();
	return 0;
}

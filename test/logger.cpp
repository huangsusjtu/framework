#include "logger.h"

#include <iostream>
int main()
{
	std::cerr<<"int logger test"<<std::endl;
	using namespace sys;
	Logger& log = Logger::instance();
	int c = 100000;
	std::cin>>c;
while(c--)
{	

	if(false==log.appendLine(ERR, "1234567890"))
	{
		std::cout<<"err append"<<std::endl;
	}
}
	log.forceFlush();
	LogThread::instance().join();
	return 0;
}


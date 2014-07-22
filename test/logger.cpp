#include "logger.h"

#include <iostream>
int main()
{
	using namespace sys;
	Logger& log = Logger::instance();
	int c = 100000;
while(c--)
{
	if(false==log.appendLine(ERR, "heheheheheheheh..."))
	{
		std::cout<<"err append"<<std::endl;
	}
}
	log.forceFlush(true);
	return 0;
}


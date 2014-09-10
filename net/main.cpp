/**
 * The main.cpp is used to test all the modules
 */
#include "thread.h"
#include "mempool.h"
#include "datatransport.h"
#include "event_driver.h"
#include "status.h"
#include <stdio.h>

using namespace sys;
using namespace net;

int main()
{
	printf("0\n");

	//gloable varible init	
	Transport::instance().start();
		
	


	return 0;
}

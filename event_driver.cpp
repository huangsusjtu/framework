#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

#include "event_driver.h"

EventDriver::EventDriver()
{
	epollfd = epoll_create1(0);
	if(epollfd < 0)
		exit(-1);
	std::cout<<"create epool , the mem"<<std::endl;
	eventbuffer = new struct epoll_event[MAX_ACTIVE_EVENT];
}

EventDriver::~EventDriver()
{
	close(epollfd);
	delete []eventbuffer;
}

bool EventDriver::addEventDescripter(EventDescripter *eventdesc)
{
	if(!eventdesc)
		return false;
	if(-1==epoll_ctl(epollfd, EPOLL_CTL_ADD,eventdesc->getfd(),eventdesc->getEvent()) )
	{
		perror("epoll_ctl add event descriper err!");
		return false;
	}
	return true;
}

void EventDriver::handleEventLoop()
{
	for(;;)
	{
		std::cout<<"begin"<<std::endl;
		int nfds = epoll_wait(epollfd, eventbuffer,MAX_ACTIVE_EVENT, -1);
		std::cout<<"after"<<nfds<<std::endl;
		for(int i=0; i<nfds;i++)
	   {
		   dispatchEvent(eventbuffer[i]);
	   }
	}
}

/*必须由子类实现的接口
void EventDriver::dispatchEvent(struct epoll_event &activeEvent)
{

	/*according to the , handle
	std::cout<<"in dispatch"<<std::endl;
	//. . . 
	return ;
}
*/


void EventDriver::test()
{

	//class EventDescripter ed3(2);
	//class EventDriver em;
	//em.addEventDescripter(&ed3);
	//em.handleEventLoop();	
		
}




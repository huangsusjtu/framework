#include "neteventdriver.h"

#include <cassert>

namespace net{
NetEventDriver NetEventDriver::self;

NetEventDriver::NetEventDriver()
{}

NetEventDriver::~NetEventDriver()
{}

/**
 * 该事件处理函数本质上 调用事件描述符的事件处理函数.
 */
void NetEventDriver::dispatchEvent(struct epoll_event &activeEvent)
{
	EventDescripter *desc = (EventDescripter*)activeEvent.data.ptr;
	assert(desc!=NULL);
	desc->eventHandler(activeEvent);
		
}




}



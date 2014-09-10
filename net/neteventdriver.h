#ifndef NETWORK_EVENT_DRIVER_
#define NETWORK_EVENT_DRIVER

#include "event_driver.h"

namespace net{
using sys::EventDriver;
using sys::EventDescripter;
/**
 * 管理所以的网络相关的事件驱动
 */
class NetEventDriver : public EventDriver
{
	public:
		static NetEventDriver& instance(){
			return self;		
		}
		~NetEventDriver();

		virtual void dispatchEvent(struct epoll_event &activeEvent);
	private:
		NetEventDriver();
		NetEventDriver(const NetEventDriver &T);
		NetEventDriver& operator=(const NetEventDriver &T);

	private:
		static NetEventDriver self;
};



}

#endif

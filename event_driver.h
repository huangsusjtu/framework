/**
 * an object of event which is also a runnable object.
 * EventDriver is a base class, derived class have to implement the interface dispatchEvent();
 */
#ifndef EVENT_DRIVER_
#define EVENT_DRIVER_
#include <sys/epoll.h>
#include <unistd.h>
#include "thread.h"


/**
*  基类，表示需要监听事件的对象，所有需要加入事件监听的 对象都继承自它
*/
class EventDescripter 
{
	public:
		EventDescripter():fd(-1){}
		EventDescripter(int FD,  uint32_t eventtype ):fd(FD){
			if(fd>0)
				setEvent(fd, eventtype);
		}
		virtual ~EventDescripter()
		{
			if(fd>0)
				::close(fd);
		}
		
		void setEvent(int FD,uint32_t eventtype)
		{
			if(FD < 0)
				return ;
			fd = FD;
			event.events = eventtype;
			event.data.ptr = (void*)this;
		}
		
		struct epoll_event* getEvent(){
			return &event;
		}
		int getfd()const{
			return fd;
		}
		
		//派生类必须实现该接口， 该接口是处理事件的。
		virtual void eventHandler(struct epoll_event &ev)=0;
	private:
		EventDescripter(const EventDescripter& T);
		EventDescripter& operator=(const EventDescripter& T);
	private:
		int fd;
		struct epoll_event event;
};

/**
* 事件驱动的基类，负责添加事件，监控事件发生，以及处理分发事件等。
* 派生类需要实现 dispatchEvent()函数来处理事件
*/
class EventDriver
{
	public:
		static void test();
		enum{
			MAX_ACTIVE_EVENT = 1000
		};
		EventDriver();
		virtual ~EventDriver();

		virtual bool addEventDescripter(EventDescripter *eventdesc);
		void handleEventLoop();

		virtual void dispatchEvent(struct epoll_event &activeEvent)=0;
	private:
		EventDriver(EventDriver& T);
		EventDriver& operator=(EventDriver& T);
	private:
		int epollfd;
		struct epoll_event ev;	
		struct epoll_event *eventbuffer;
};


#endif

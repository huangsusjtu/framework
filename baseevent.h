#ifndef BASE_EVENT_
#define BASE_EVENT_

namespace sys{

/**
 * 基类 描述事件对象
 */

enum TYPE{
	DEFAULT = 0,
	WRITE,
	READ,
	ERR
};
	
class Event{
	public:
		Event();
		virtual ~Event();

		virtual void onEvent()=0;
	private:
		TYPE _type = sys::DEFAULT;
		
};




}


#endif

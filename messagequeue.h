#ifndef MESSAGE_QUEUE
#define MESSAGE_QUEUE
#include <sys/epoll.h>
#include <pthread.h>
#include "message.h"
#include "object.h"

class Message;
class MessageQueue : public Object
{
	typedef pthread_mutex_t mutex;
	public:
		static void test();

		MessageQueue();
		~MessageQueue();
			
		void postMessage(Message* m);
		void loopHandleMessage();
		void start(){mStart = true ;}

		Message* getMessage();
		int getLength(){return mLength;}
	protected:
		/**the return of  method means there are something to do.*/
		
	private:
		Message *mHead;
		Message *mTail;
		size_t mLength;
		mutex  mMutex;

		
		bool mStart;

};

#endif

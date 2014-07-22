#include "messagequeue.h"
#include "auto_mutex.h"

MessageQueue::MessageQueue():mHead(NULL),
			   mTail(NULL),
			   mLength(0),
			   mMutex(PTHREAD_MUTEX_INITIALIZER),
			   mStart(false)
{
}

MessageQueue::~MessageQueue()
{
	if(mLength)
	{
		while(mHead)
		{
			Message *q = getMessage();
			delete q;
		}
	}
	pthread_mutex_destroy(&mMutex);
}

Message* MessageQueue::getMessage()
{
	if(!mHead)return NULL;
	AutoMutex m(&mMutex);
	Message* r = mHead;
	if(mHead==mTail){
		mHead = mTail = NULL;	
	}else{
		mHead = mHead->getNext();
	}
	mLength--;
	return r;
}

void MessageQueue::postMessage(Message* m)
{
	AutoMutex mLock(&mMutex);
	if(!mHead){
		mHead = mTail = m;
	}else{
		mTail->setNext(m);
		mTail = m;
	}
	mLength++;
}

void MessageQueue::loopHandleMessage()
{
	while(true){
		this->wait();
		if(false==mStart)
			continue;
		Message *instance = getMessage();
		if(!instance){
			mStart = false;
			continue;
		}
		instance->run();
		Message::clear(instance);
	}
}




#include <iostream>	
void MessageQueue::test()
{
class TestMessage : public Message
{
	public:
		static Message* obtain()
		{
			return new TestMessage();
		}
		static Message* obtain(const char* m)
		{
			return new TestMessage(m);
		}
		static Message* obtain(string &m)
		{
			return new TestMessage(m);
		}
	protected:
		TestMessage() : Message(){};
		~TestMessage(){};
		TestMessage(const char*m): Message(m){}
		TestMessage(string &m) : Message(m){}
	public:
		void run()
		{
			std::cout<<toString()<<std::endl;
			std::cout<<"In run"<<std::endl;
		}

};


	//test the messagequeue
	Message *tm = TestMessage::obtain();
	string s = "12";
	Message *tm2 =TestMessage::obtain(s);
	Message *tm3 = TestMessage::obtain("123");
	
	
	MessageQueue queue;
	queue.start();
	queue.postMessage(tm);
	queue.postMessage(tm2);
	queue.postMessage(tm3);
	
/*	Message *tmp = queue.getMessage();
	tmp->run();
	std::cout<<queue.getLength()<<std::endl;
	tmp = queue.getMessage();	
	tmp->run();
	tmp = queue.getMessage();
	tmp->run();
*/
	queue.loopHandleMessage();

}

#ifndef MESSAGE
#define MESSAGE

#include <string>
using std::string;
#include "thread.h"
#include "runnable.h"
class Runnable;
/**
 * Message is an abstract class.
 */
class Message : public Runnable
{
	public:
		static Message* obtain();
		static Message* obtain(const char* m);
		static Message* obtain(string &m);
		//static Message* obtain(int what, int arg1, void *arg2);
		//static Message* obtain(Message& m);
		static void clear(Message *m){ delete m;}
		

		string& toString(){
			return what;
		}
		virtual ~Message(){};
		Message* getNext(){return next;}
		void setNext(Message* m){next = m;}
	protected:
		Message():next(NULL){};
		Message(const char* m):what(m),next(NULL){};
		Message(string &m): what(m),next(NULL){};
	private:
		Message(const Message &m){};
		Message& operator=(const Message &m){};
	
	private:
		Message *next;
		string what;
};

#endif

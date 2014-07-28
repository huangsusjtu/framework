#ifndef BASE_QUEUE_
#define BASE_QUEUE_
#include <cassert>
#include <list>

#include "auto_mutex.h"
#include "lock.h"
namespace sys{

/**
* 多线程下的队列
*/
template<class T>
class Queue : public Lock{
	
	typedef std::list<T*> Collection;
	//friend Queue<T>;
	public:
		
		Queue(){
		}

		virtual ~Queue()
		{	
			Lock::lock();
			while( !mList.empty())
			{
				T *q = mList.front();
				mList.pop_front();
				delete q;	
			}
			Lock:unlock();
		}		
	

		void addFront(T *p)
		{
			if(!p)return ;
			Lock::lock();
			mList.push_front(p);
			Lock:unlock();
		}

		void addBack(T *p)
		{
			if(!p)return ;
			Lock::lock();
			mList.push_back(p);
			Lock:unlock();
		}


		//有对象就返回，没有返回空
		T* getFront()
		{
			T *res = NULL;
			Lock::lock();
			if(!isEmpty()){
				res = 	mList.front();
				mList.pop_front();
			}
			Lock::unlock();
			return res;
		}
	

		T* getBack()
		{
			T *res = NULL;
			Lock::lock();
			if(!isEmpty()){
				res = 	mList.back();
				mList.pop_back();
			}
			Lock::unlock();
			return res;
		}


		bool isEmpty(){
			return mList.empty();		
		}
		size_t size(){
			return mList.size();
		}
		
		void merge(Queue<T*> q)
		{
			Lock::lock();
			q->lock();
			if(q->empty()){
				q->unlock();
				return;			
			}
			mList.splice(mList.end(), q->mList, q->mList.begin(),q->mList.end());
			q->unlock();			
			Lock::unlock();
		}	
	private:
		Collection mList;
};

}
#endif

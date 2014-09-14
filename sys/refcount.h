#ifndef REFCOUNT
#define REFCOUNT
#include "atomic.h"

namespace sys{

class StrongRef
{
	public:
		StrongRef();	
		virtual ~StrongRef();

		void increaseRef();
		void decreaseRef();

		// an interface to release resources.
	public:
		//virtual void finalize(){}
	
	private:
		atomic_t ref;

};
/*
template<class T>
class sp
{
	public:
		sp(T* obj);
		~sp();
		sp(const sp<T>& t);
		
	private:
		T *_obj;
};*/

}
#endif

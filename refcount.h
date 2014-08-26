#ifndef REFCOUNT
#define REFCOUNT
#include "atomic.h"

class StrongRef
{
	public:
		StrongRef();	
		virtual ~StrongRef();

		void increase();
		void decrease();

		// an interface to release resources.
	public:
		//virtual void finalize(){}
	
	private:
		atomic_t ref;

};

#endif

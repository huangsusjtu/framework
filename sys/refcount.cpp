#include "refcount.h"

namespace sys{

StrongRef::StrongRef()
{
	 atomic_set(&ref,0);
}

StrongRef::~StrongRef()
{}

void StrongRef::increaseRef()
{
	atomic_inc(&ref);
}

void StrongRef::decreaseRef()
{
	if( 0==atomic_dec_and_test(&ref) )
	{ 
		delete this;
		//finalize();
	}
}
}

#include "refcount.h"

StrongRef::StrongRef()
{
	 atomic_set(&ref,0);
}

StrongRef::~StrongRef()
{}

void StrongRef::increase()
{
	atomic_inc(&ref);
}

void StrongRef::decrease()
{
	if( 0==atomic_dec_and_test(&ref) )
	{
		finalize();
	}
}


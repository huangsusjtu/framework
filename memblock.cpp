#include "memblock.h"

//memblock
MemBlock::MemBlock(MemBlockPool *parent, int blocksize):StrongRef(),buffer(NULL)
	,pos(0),freesize(0),bufsize(0), mParent(parent)
{}

MemBlock::~MemBlock()
{
}

//当引用计数为0，该函数会被调用
void MemBlock::finalize()
{
	if(mParent!=NULL)
	{
		mParent->putMemBlock(this);
	}else{
		delete this;	
	}
}


bool MemBlock::allocMemBuffer(MemBuffer &T,size_t need)
{
	Lock::lock();
	if( freesize < need )
	{
		Lock::unlock();		
		return false;
	}
	T.mData = buffer+pos;
	T.mPos = 0;
	T.mSize = need;
	pos += need;
	freesize -= need;
	StrongRef::increase();
	Lock::unlock();
	return true;
}

void MemBlock::freeMemBuffer(MemBuffer& T)
{
	if(!contains(T))return ;
	Lock::lock();
	if(T.mData+T.mSize == buffer+pos){
		pos -= T.mSize;
		freesize += T.mSize;
	}
	StrongRef::decrease();
	Lock::unlock();
}


bool MemBlock::contains(const MemBuffer& T){
	return (T.mData>=buffer &&
		T.mData+T.mSize <= buffer+bufsize );
}


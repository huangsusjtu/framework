#include "memblockpool.h"
#include <cassert>

namespace sys{

//memblockpool
	
MemBlockPool MemBlockPool::self;

MemBlockPool::MemBlockPool(int blockNum, int blocksize)
{
	assert(blockNum>0 && blocksize>0);
	blocksize = align(blocksize);
	_blocksize = blocksize;
	pthread_mutex_init(&mMutex,NULL);
	mDataBlocks.resize(blockNum);
	for(int i=0;i<blockNum; i++)
	{
		try{
			mDataBlocks.push_back( new MemBlock(this, _blocksize) );
		}catch(...){
		}
	}
}


MemBlockPool::~MemBlockPool()
{
	AutoMutex m(&mMutex);
	while(!mDataBlocks.empty())
	{
		MemBlock *tmp = mDataBlocks.front();
		mDataBlocks.pop_front();
		delete tmp;		
	}
	pthread_mutex_destroy(&mMutex);
}

/**
当内存池的空闲不够用的时候，需要扩展
*/
bool MemBlockPool::expandMemBlock(int num)
{
	AutoMutex m(&mMutex);
	assert(mDataBlocks.size() < BLOCKNUM);
	
	for(int i=0;i<num;i++)
	{
		try{
			mDataBlocks.push_back( new MemBlock( this, _blocksize) );
		}catch(...){
		}
	}	
	return true;
}

/**
当内存池的空闲太多的时候，需要回收到系统
*/
bool MemBlockPool::shrinkMemBlock()
{
	AutoMutex m(&mMutex);
	while(mDataBlocks.size() > BLOCKNUM)
	{
		MemBlock *tmp = mDataBlocks.front();
		mDataBlocks.pop_front();
		delete tmp;
	}
}

MemBlock* MemBlockPool::getMemBlock()
{
	AutoMutex m(&mMutex);
	if(mDataBlocks.empty())
		expandMemBlock(BLOCKNUM);
	MemBlock *cur = mDataBlocks.front();
	mDataBlocks.pop_front();
	return cur;
}

//把memblock添加到pool
void MemBlockPool::putMemBlock(MemBlock* T)
{
	if(T==NULL)
		return;
	AutoMutex m(&mMutex);
	mDataBlocks.push_front(T);
}



}








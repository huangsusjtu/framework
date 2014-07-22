#include "memblockpool.h"
#include <cassert>

//memblockpool
MemBlockPool MemBlockPool::self;
	
MemBlockPool::MemBlockPool(int blockNum)
{
	assert(blockNum>0);
	pthread_mutex_init(&mMutex,NULL);
	mDataBlocks.resize(blockNum);
	for(int i=0;i<blockNum; i++)
	{
		try{
			mDataBlocks.push_back( new MemBlock(this, BLOCKSIZE) );
		}catch(...){
		}
	}
	cur = NULL;
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
bool MemBlockPool::expandMemBlock()
{
	AutoMutex m(&mMutex);
	assert(mDataBlocks.size() < BLOCKNUM);
	
	for(int i=0;i<BLOCKNUM;i++)
	{
		try{
			mDataBlocks.push_back( new MemBlock( this, BLOCKSIZE) );
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

bool MemBlockPool::getMemBuffer(MemBuffer *T,size_t need)
{
	assert(T!=NULL && need<= BLOCKSIZE);
	
	if(cur==NULL || !cur->hasSpace(need))
	{
		AutoMutex m(&mMutex);
		if(mDataBlocks.empty())return false;
		cur = mDataBlocks.front();
		mDataBlocks.pop_front();
	}	
	return cur->allocMemBuffer(*T, need);
}

//把memblock添加到pool
void MemBlockPool::putMemBlock(MemBlock* T)
{
	assert(T!=NULL);
	AutoMutex m(&mMutex);
	mDataBlocks.push_back(T);
}












#include <cassert>
#include "memblock.h"

namespace sys{

//memblock
MemBlock::MemBlock(MemBlockPool *parent, int blocksize): _pos(0), _parent(parent)
{
	assert(blocksize>0 && blocksize < MAX_SIZE);
	_size = blocksize;
	_freesize = blocksize;
	_buf = new char[_size];
}

MemBlock::~MemBlock()
{
	delete []_buf;
}

//将内存交还给池子
void MemBlock::free()
{
	if(_parent!=NULL)
	{
		_parent->putMemBlock(this);
	}else{
		delete this;	
	}
}

//只分配内存，不管释放， 因为释放 是由整个block释放。
char* MemBlock::alloc(size_t need)
{
	size_t realsize = align(need);
	if( _freesize < realsize )
	{
		return NULL;
	}
	_pos += realsize;
	_freesize -= realsize;
	
	char *res = _buf;
	_buf += realsize;
	return res;
}

}



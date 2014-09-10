#ifndef MEMBLOCK
#define MEMBLOCK


#include "refcount.h"
#include "lock.h"
#include "object.h"

#include "memblockpool.h"
#include "auto_mutex.h"


namespace sys{

/**
 * a memory block, . it is allocated from pool, not directly from heap.
 * 一大块内存， 实际需要内存时，直接从内存块上取。
 */
class MemBlockPool;

#define ALIGN(s,m)  (((s)+(m))&(~(m)))
#define MAX_SIZE ((1<<20)+1)

const size_t align_size = sizeof(unsigned long);

inline size_t align(size_t size){
	return ALIGN(size, align_size-1);
}

class MemBlock
{
	public:
		MemBlock(MemBlockPool *parent, int blocksize);
		virtual ~MemBlock();
			


		inline bool hasSpace(size_t need){
			return _freesize>=need;
		}
		char* alloc(size_t need);
		void free();
	
	private:
		MemBlock(const MemBlock& T);
		MemBlock& operator=(const MemBlock& T);
				

		inline bool contains(const char *p){
			return p>=_buf && p<_buf+_size;		
		}
	private:
		MemBlockPool *_parent;
		char* _buf;
		size_t _pos, _freesize;
		size_t _size;


};
}


#endif

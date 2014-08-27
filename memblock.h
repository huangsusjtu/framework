#ifndef MEMBLOCK
#define MEMBLOCK


#include "refcount.h"
#include "lock.h"
#include "object.h"

#include "memblockpool.h"
#include "auto_mutex.h"
#include "membuffer.h"
/**
 * a memory block, . it is allocated from pool, not directly from heap.
 */
class MemBlockPool;

class MemBlock
{
	enum{
		align_size = sizeof(unsigned long),
		align_mask = align_size-1
	}
	public:
		MemBlock(MemBlockPool *parent, int blocksize);
		virtual ~MemBlock();
			


		inline bool hasSpace(size_t need){
			return freesize>=need;
		}
		char* allocMemBuffer(size_t need);
		void finalize();
	
	private:
		MemBlock(const MemBlock& T);
		MemBlock& operator=(const MemBlock& T);
		inline size_t align(size_t size){
			return (size +align_mask)&(~align_mask) ;
		}		

		inline bool contains(const char *p){
			return p>=buffer && p<buffer+size;		
		}
	private:
		MemBlockPool *mParent;
		char* buffer;
		size_t pos, freesize;
		size_t size;


};



#endif

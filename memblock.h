#ifndef MEMBLOCK
#define MEMBLOCK


#include "refcount.h"
#include "lock.h"
#include "object.h"

#include "memblockpool.h"
#include "auto_mutex.h"
#include "membuffer.h"
/**
 * a memory block, it is thread safe. it is allocated from pool, not directly from heap.
 */
class MemBlockPool;
class MemBlock : public StrongRef ,public Lock
{
	
	public:
		MemBlock(MemBlockPool *parent, int blocksize);
		virtual ~MemBlock();
			
		

		inline bool hasSpace(size_t need){
			return freesize>=need;
		}
		bool allocMemBuffer(MemBuffer &T, size_t need);
		void freeMemBuffer(MemBuffer& T);

	public:
		void finalize();
	
	private:
		MemBlock(const MemBlock& T);
		MemBlock& operator=(const MemBlock& T);

		inline bool contains(const MemBuffer &T);
	private:
		MemBlockPool *mParent;
		char* buffer;
		size_t pos, freesize;
		size_t bufsize;


};



#endif

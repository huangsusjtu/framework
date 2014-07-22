#ifndef MEM_BLOCK_POOL
#define MEM_BLOCK_POOL

#include <pthread.h>
#include <list>
#include "auto_mutex.h"
#include "membuffer.h"
#include "memblock.h"
#include "atomic.h"



/**
 * memory pool based on block
 */
class MemBlockPool
{
	typedef pthread_mutex_t mutex;
	typedef std::list<class MemBlock*> Collection;
	typedef Collection::iterator Iterator;
	
	enum{
		BLOCKNUM = 10,
		BLOCKSIZE = 1<<20
	};
	public:
		static MemBlockPool self;		
		static MemBlockPool& instance(){
			return self;
		}
		MemBlockPool(int blockNum = BLOCKNUM);
		~MemBlockPool();
			
		int getLength(){
			return 	mDataBlocks.size();	
		}

		//when the pool is not enough,need expand
		bool expandMemBlock();
		bool shrinkMemBlock();
	
		//to allocate  a fit mem
		bool getMemBuffer(MemBuffer *T,size_t need);
		
		//add a memblock to pool
		void putMemBlock(MemBlock* T);



	private:
		MemBlockPool(const MemBlockPool& T);
		MemBlockPool operator=(const MemBlockPool& T);
	private:
		Collection mDataBlocks;
		MemBlock* cur;
		mutex mMutex;
};


#endif

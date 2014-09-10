#ifndef MEM_BLOCK_POOL
#define MEM_BLOCK_POOL

#include <pthread.h>
#include <list>
#include "auto_mutex.h"
#include "memblock.h"
#include "atomic.h"


namespace sys{
/**
 * memory pool based on block
 */
class MemBlockPool
{
	typedef pthread_mutex_t mutex;
	typedef std::list<class MemBlock*> Collection;
	typedef Collection::iterator Iterator;
	
	enum{
		BLOCKNUM = 128,
		BLOCKSIZE = 1<<12
	};
	public:	
		static MemBlockPool* CreateMemPool(int num = BLOCKNUM , int blocksize = BLOCKSIZE){
			return new MemBlockPool(num, blocksize);
		}
	
		static MemBlockPool& instance()
		{
			return self;
		}
		~MemBlockPool();
			
		int getLength(){
			return 	mDataBlocks.size();	
		}

		//when the pool is not enough,need expand
		bool expandMemBlock(int num = BLOCKNUM);
		bool shrinkMemBlock();
	
		//to allocate  a fit mem
		MemBlock* getMemBlock();
		
		//add a memblock to pool
		void putMemBlock(MemBlock* T);



	private:
		MemBlockPool(int blockNum = BLOCKNUM, int blocksize = BLOCKSIZE );
		MemBlockPool(const MemBlockPool& T);
		MemBlockPool operator=(const MemBlockPool& T);
	private:
		Collection mDataBlocks;
		int _blocksize;
		mutex mMutex;
		static MemBlockPool self;
};

}
#endif

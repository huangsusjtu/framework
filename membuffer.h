#ifndef MEM_BUFFER_
#define MEM_BUFFER_

/**
 * 描述内存缓存区域，是由MemBlock上分配而来
 */
class MemBuffer
{
	class MemBlock;	
	public :
		MemBuffer();
		~MemBuffer();
	
		MemBuffer(char* data, size_t size);
		MemBuffer(const MemBuffer& T);
		MemBuffer& operator=(const MemBuffer& T);
		
		inline bool operator==(const MemBuffer& T)const;

		//copy data from ... to buffer
		inline bool copyToBuffer(const char* data, size_t size);
		inline bool copyFromBuffer(char* data, size_t size);
		
		inline bool copyToBuffer(const MemBuffer &T);
		inline bool copyFromBuffer(MemBuffer &T);

		inline bool append(const char*data, size_t size);
		inline bool append(MemBuffer &T);

		//MemBuffer split into two
	//	inline bool splitFromFront(MemBuffer& T, size_t s);

		inline bool  isFree(){
			return mPos==0;
		}	
		
		char* mData;
		size_t mSize;
		size_t mPos;
		MemBlock* owner;

};

#endif

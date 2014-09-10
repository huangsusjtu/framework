#ifndef MEM_BUFFER_
#define MEM_BUFFER_
#include <cassert>
#include <string>

namespace sys{
using std::string;
/**
 * 描述内存缓存区域, 用于数据存储，以及提供了数据读写的函数。
 */
class MemBuffer
{
	class MemBlock;	
	public :
		enum{
			default_bufsize = 1024,
			mask = default_bufsize - 1
		};
		
		~MemBuffer();
	
		MemBuffer();
		
		inline bool operator==(const MemBuffer& T)const;

		void clear(){
			_begin = _end = 0;		
		}		
		void drain(size_t len){
			assert(len>0);
			if(_end-_begin>len)				
				_begin += len;
			else
				clear();
		}
		void pour(size_t len){
			assert(len>0);
			if(_size - _end > len)
				_end += len;		
		}

		inline size_t getFreeSize(){
			return _size-_end;		
		}
		inline size_t getDataLen(){
			return _end-_begin;	
		}
		inline char* getBuf(){
			return _data+_begin;		
		}
		
		
		uint8_t read8(){
			assert(_begin>_end);
			return _data[_begin++];
		}
		uint16_t read16(){
			uint16_t res;
			assert(_size-_begin>1);
			res = _data[_begin++];
			res<<8;
			res |= _data[_begin++];			
		}

		uint32_t read32()
		{
			uint32_t res = _data[_begin++];
			assert(_size-_begin>3);
			res<<8;
			res |= _data[_begin++];
			res<<8;
			res |= _data[_begin++];
			res<<8;
			res |= _data[_begin++];
			return res;		
		}
		
		void write8(uint8_t t){
			if( _size < _end+1 )
				expand();
			_data[_end++] = t;		
		}		
		void write16(uint16_t t){
			if(_size < _end+2)
				expand();
			_data[_end++] = t;
			t >>= 8;
			_data[_end++] = t; 			
		}
		void write32(uint32_t t){
			if(_size < _end+4)
				expand();
			_data[_end++] = t;
			t >>=8;
			_data[_end++] = t;
			t >>=8;
			_data[_end++] = t;
			t >>=8;
			_data[_end++] = t;
		}
	
		void expand();
		void shrink();

		//copy data from ... to buffer
		void writeString(const char *data, size_t size);
		void writeString(string &s);

		bool readString(char *data, size_t size);
		bool readString(string &s)
;
		inline bool append(MemBuffer &T);
		//MemBuffer split into two
	//	inline bool splitFromFront(MemBuffer& T, size_t s);

		inline bool  isFree(){
			return _begin==0;
		}	
	private:
		MemBuffer(const MemBuffer& T);
		MemBuffer& operator=(const MemBuffer& T);

		char* _data;
		size_t _size;
		size_t _begin;
		size_t _end;
};
}
#endif

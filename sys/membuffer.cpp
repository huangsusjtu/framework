#include <string.h>
#include "membuffer.h"

namespace sys{

MemBuffer::~MemBuffer()
{
	if(_data)
		delete []_data;
}

MemBuffer::MemBuffer():_begin(0), _end(0)
{
	_data = new char[default_bufsize];
	_size = default_bufsize;	
}



bool MemBuffer::operator==(const MemBuffer& T)const
{
	return T==*this ||(T._data == this->_data && T._size==this->_size);
}



bool MemBuffer::readString(char *data, size_t size)
{
	if(NULL==data || size>(_end-_begin) )return false;
	memcpy((void*)data, (const void*)(_data+_begin), size);
	_begin += size; 
	return true;
}

bool MemBuffer::readString( string &s)
{
	read32();
	s.append(_data+_begin, _end-_begin);
	return true;
}


void MemBuffer::writeString(const char* data, size_t size)
{
	if(NULL==data )return ;
	while( size > _size-_begin )
		expand();
	memcpy(_data+_begin, data, size);
	_begin += size;
}

void MemBuffer::writeString(string &s)
{
	write32(s.size());
	writeString(s.c_str(), s.size());
}

bool MemBuffer::append(MemBuffer &T)
{
	size_t len = T._end-T._begin;
	size_t free = _end - _begin;	
	if(NULL==T._data ||  len > free)return false;
	
	memcpy(_data+_end, T._data+T._begin, len);
	_end += len;
	return true;
}


void MemBuffer::expand()
{
	size_t len = _end-_begin;
	char *tmp = new char[_size<<1];
	memcpy(tmp, _data+_begin, len);
	delete []_data;
	_data = tmp;
	_begin = 0;
	_end = len;
	_size = _size<<1;
}

void MemBuffer::shrink()
{
	size_t len = _end-_begin;
	size_t free = _size - len;
	size_t size;
	if( free < default_bufsize )
		return ;
	size = (len+mask) & (~mask);
	char *tmp = new char[size];
	memcpy(tmp, _data+_begin, len);
	delete []_data;
	_data = tmp;
	_begin = 0;
	_end = len;
	_size = size;
}

}










#include <string.h>
#include "membuffer.h"

MemBuffer::MemBuffer():mData(NULL),mSize(0),mPos(0),owner(NULL)
{}

MemBuffer::~MemBuffer()
{}

MemBuffer::MemBuffer(char* data, size_t size):mData(data),mSize(size),mPos(0),owner(NULL)
{}

MemBuffer::MemBuffer(const MemBuffer& T)
{
	this->mData = T.mData;
	this->mSize = T.mSize;
	this->mPos = T.mPos;
	this->owner = T.owner;
}

MemBuffer& MemBuffer::operator=(const MemBuffer &T)
{
	if(*this==T)
		return *this;
	this->mData = T.mData;
	this->mSize = T.mSize;
	this->mPos = T.mPos;
	this->owner = T.owner;
	return *this;
}

bool MemBuffer::operator==(const MemBuffer& T)const
{
	return T==*this ||(T.mData == this->mData && T.mSize==this->mSize);
}

bool MemBuffer::copyToBuffer(const char* data, size_t size)
{
	if(NULL==data || size>mSize)
		return false;
	memcpy(mData, data, size);
	mPos = size;
	return true;
}

bool MemBuffer::copyFromBuffer(char *data, size_t size)
{
	if(NULL==data || size<mPos)return false;
	memcpy(data, mData, mPos);
	return true;
}

bool MemBuffer::copyToBuffer(const MemBuffer& T)
{
	if(NULL==T.mData || T.mPos>mSize)return false;
	memmove(mData, T.mData , T.mPos);
	mPos = T.mPos;
}

bool MemBuffer::copyFromBuffer(MemBuffer &T)
{
	if(NULL==T.mData || T.mSize<mPos)return false;
	memmove(T.mData, mData, mPos);
	return true;
}

bool MemBuffer::append(const char* data, size_t size)
{
	if(NULL==data || size>mSize-mPos)return false;
	memcpy(mData+mPos, data, size);
	mPos += size;
	return true;
}

bool MemBuffer::append(MemBuffer &T)
{
	if(NULL==T.mData || T.mPos> mSize-mPos)return false;
	memcpy(mData+mPos, T.mData, T.mPos);
	mPos += T.mPos;
	return true;
}
/*
bool MemBuffer::splitFromFront(MemBuffer& T, size_t s)
{
	if(s>=mSize || !isFree()) return false;
	T.mData = mData;
	T.mSize = s;
	T.mPos = 0;
	mData += s;
	mSize -= s;
	return true;
}*/










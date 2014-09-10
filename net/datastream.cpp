#include "memblockpool.h"
#include "datastream.h"
#include <cassert>

namespace net{


DataStream::DataStream()
{
}

DataStream::~DataStream()
{
}


/////////////
/**
* 编码包，成二进制数据。
* @para 
* @return
*/
void NormalDataStream::encodeToStream(MemBuffer *out, const IPacket *p)
{
	assert( out !=NULL && p !=NULL);
	NormalPacket *np = (NormalPacket*)p;
	MemBuffer *mb = np->getText();
	out->writeString( mb->getBuf(), mb->getDataLen() );
	mb->clear();		

}

/**
* 将数据解码成 包
* @para 
* @return 
*/
IPacket* NormalDataStream::decodeToPacket(const MemBuffer *in)
{
	assert(in!=NULL);
	NormalPacket *np = new NormalPacket();
	MemBuffer *mb = np->getText();
	MemBuffer *tmp = const_cast<MemBuffer*>(in);
	mb->writeString(  tmp->getBuf(), tmp->getDataLen() );	
	tmp->clear();
	return np;
}	

}

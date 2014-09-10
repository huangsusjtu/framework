#ifndef _SOCKET_STREAM__
#define _SOCKET_STREAM__

#include "membuffer.h"
#include "Ipacket.h"
/**
 * decode or encode the data
*/
namespace net{
using sys::MemBuffer;

class DataStream{
	
	public:
		DataStream();
		virtual ~DataStream();

		virtual void encodeToStream(MemBuffer* out, const IPacket *p) = 0;
		virtual IPacket* decodeToPacket(const MemBuffer* in) = 0;
};

/**普通的编码解码器， 仅仅拷贝数据，不做任何解码
 */
class NormalDataStream : public DataStream
{
	public:
		virtual void encodeToStream(MemBuffer* out, const IPacket *p);
		virtual IPacket* decodeToPacket(const MemBuffer* in);
};

}


#endif

#ifndef PACKET_TRANSPORT
#define PACKET_TRANSPORT

namespace net{

/**
 * data transport through network
 */
class Transport{
	class Packet;
	class PacketQueue;
	class Connection;
	public:
		Transport();
		~Transport();

		bool setConnection(Connection *con);
		void setPacketQueue(PacketQueue* q);
	private:
		PacketQueue *mQueue;
		Connection *mConection;

};

}


#endif

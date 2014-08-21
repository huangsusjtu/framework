/**
 * 
 */
#ifndef SOCKET
#define SOCKET

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include "status.h"

namespace net{

/**
* base class
*/
class Socket
{
	public:
		Socket(int fd=-1);
		virtual ~Socket();

		bool createSocket(int family, int type, int protocol);
		bool closeSocket();

		bool enableNoDelay();
		bool disableNoDelay();
		bool setSendBuffer(int bufsize);
		int setReuse();
		int setNonBlock();
		int setBlock();	
		int keepLive(int interval=7200);

		int read(char* buf, int count);
		int write(const char* buf, int count);

		bool getPeer(char *ip, size_t ip_len, int *port);
		bool getSockName(char *ip, size_t ip_len, int *port);

		int getSocketHandle(){return sock_fd;}
		void setSocketHandle(int fd){sock_fd = fd;}
	private:
		int setNoDelay(int val);
	protected:
		int sock_fd;
		
};

class ConnectedSocket : public Socket
{
	public:	
		ConnectedSocket(int sockfd){sock_fd = sockfd;}
		~ConnectedSocket(){::close(sock_fd);}
};

}


#endif

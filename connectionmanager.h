#ifndef _CONNECTION_MANAGER_
#define _CONNECTION_MANAGER

#include <forward_list>
#include <unordered_map>

#include "connection.h"
#include "lock.h"

namespace net{

/**
 * 支持多线程,本程序只在单线程使用
 */
class ConnectionManager : public Lock{
	/**
	 * the first is socket desc
	 */
	typedef std::unordered_map<int, class Connection*> HashCollection;
	typedef HashCollection::iterator HashIter;
	typedef std::forward_list<class Connection*> ListCollection;
	typedef ListCollection::iterator ListIter;
	enum{
		HashBucketSize = 1024
	};
	private:
		ConnectionManager();
		~ConnectionManager();
		ConnectionManager(const ConnectionManager &T);
		ConnectionManager& operator=(const ConnectionManager &T);

	public:
		static ConnectionManager& instance();
		static ConnectionManager* pinstance();
		
		
		void addConnection(Connection *con);
		Connection *findConByKey(int fd);

		void removeConByKey(int fd);
		void removeCon(Connection *con);
	private:
		HashCollection _conhashtable;
		ListCollection _conlist;
		static ConnectionManager *self;

};

}


#endif

#include "connectionmanager.h"

namespace net{
ConnectionManager* ConnectionManager::self=NULL;

ConnectionManager& ConnectionManager::instance()
{
	return *(ConnectionManager::pinstance());
}
	
ConnectionManager* ConnectionManager::pinstance()
{
	if(!self)
		self = new ConnectionManager();
	return self;
}

ConnectionManager::ConnectionManager()
{
	_conhashtable.reserve(HashBucketSize);
	
}

//释放掉所有的connection资源
ConnectionManager::~ConnectionManager()
{
	Lock::lock();
	ListIter it = _conlist.begin();
	while(it!=_conlist.end())
	{
		if(*it)
			delete *it;
		it++;
	}
	Lock::unlock();
}

void ConnectionManager::addConnection(Connection *con)
{
	if(!con)return;
	Lock::lock();
	_conlist.remove(con);
	_conlist.push_front(con);
	_conhashtable[con->getHandle()] = con;
	Lock::unlock();
}

Connection* ConnectionManager::findConByKey(int fd)
{
	HashIter it = _conhashtable.find(fd);	
	if(_conhashtable.end()!=it)
		return it->second;
	return NULL;
}

void ConnectionManager::removeConByKey(int fd)
{
	Lock::lock();
	HashIter it = _conhashtable.find(fd);
	if(_conhashtable.end()==it)
	{
		Lock::unlock();
		return ;
	}
	_conhashtable.erase(it);
	Connection *con= it->second;
	_conlist.remove(con);
	Lock::unlock();
	delete con;
}

void ConnectionManager::removeCon(Connection *con)
{
	if(con)
		removeConByKey(con->getHandle());
}

}

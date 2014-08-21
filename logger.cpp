#include "logger.h"

#include <cstring>
#include <cassert>
#include <iostream>
#include <fstream>

namespace sys{


/**
 * LogBuffer
 */

const char* logFileName = "LOG";

LoggerBuffer::LoggerBuffer():
	_buf(NULL),_start(0),
	_pos(0), _logfile(NULL)
{
	try{
		_size = LOGBUF_SIZE;
		_buf = new unsigned char[_size]; 
	}catch(...){
		std::cerr<<"Logger: log memory allocated err!"<<std::endl;
		exit(0);
	}
}

LoggerBuffer::~LoggerBuffer()
{
	if(_buf)
		delete []_buf;
	if(_logfile)
		delete [] _logfile;
}

bool LoggerBuffer::append(const char*level, const char *info, size_t size)
{
	assert(level!=NULL && info!=NULL);
	int len = strlen(level);
	if(len+size+1 > _size-_pos){
		//std::cerr<<_size<<_pos<<len<<std::endl;	
		return false;
	}
	memcpy(_buf+_pos, level, len);
	_pos += len;
	memcpy(_buf+_pos, info, size);
	_pos += size;
	*(_buf+_pos) = '\n';
	_pos++;
	return true;
}




/**
 * Logger
 */
Logger Logger::self;

Logger::Logger():
	_fileID(0),_logfile(NULL),_cur(NULL)
{
}

Logger::~Logger()
{
	forceFlush();
	if(_logfile)delete _logfile;
}

bool Logger::appendLine(const char* level,const char *line)
{
	forceFlush(false);
	assert(line!=NULL);
	AutoMutex1 m(dynamic_cast<Lock*>(this));
	
	int size = strlen(line);
	if(NULL==_cur)
		_cur = new LoggerBuffer();
	
	//写入缓冲区
	if(_cur->append(level, line, size))
	{
		return true;
	}
	
	//缓存区写不下，需要持久化该缓存区
	forceFlush(true);
	
	
	_cur = new LoggerBuffer();
	if(_cur->append(level, line, size)==false)
	{
		std::cerr<<"Logger: write log mem err!"<<std::endl;
		return false;
	}
	return true;
}

/**
* 刷新当前的缓冲区， 为了满足实时性
*/
bool Logger::forceFlush(bool newfile)
{
	if(_cur==NULL)	
		return false;
	generateLogFileName(newfile);
	_cur->setFile(_logfile);
	LogThread::instance().pushTask(_cur);
	
}

/**
* 获得新日记文件的名
*/
void Logger::generateLogFileName(bool newfile)
{
	int len = strlen(logFileName);
	len += 32;
	if(_logfile == NULL)
		_logfile = new char[len];
	try{
		if(newfile)
			_fileID++;
		
		snprintf(_logfile, len,"%s-%d",logFileName,_fileID);
	}catch(...){
		std::cerr<<"Logger: generate log file name err"<<std::endl;
		exit(0);
	}
	//std::cerr<<_logfile<<std::endl;	
	//std::cerr.flush();
}

/**
* 刷新内存日记到文件,
* @para 内存缓存 ， 是否创建新的日志文件
*/
void LoggerBuffer::flushToFile()
{
	std::ofstream of;
	//std::cerr<<"LoggerBuffer: flushToFile!"<<std::endl;
	//std::cerr.flush();
	try{
		
			//std::cerr<<this->_logfile<<std::endl;
			//std::cerr.flush();
		of.open(this->_logfile, std::ofstream::out | std::ofstream::app);
		if(of.good()){

			of.write((const char*)this->_buf, this->_pos);
			of.flush();
		}else{
			std::cerr<<this->_logfile<<std::endl;
			std::cerr<<"LoggerBuffer: err ofstream"<<std::endl;
			std::cerr.flush();
		}
		of.close();	
	}catch(...){
		std::cerr<<"LoggerBuffer: flush log data err!"<<std::endl;
		std::cerr.flush();
	}
	
}

/**
* LogThread
*/
LogThread* LogThread::self = NULL;

LogThread::LogThread()
{
}

LogThread::~LogThread()
{}



void LogThread::run()
{
	LoggerBuffer *_cur;
	while( _cur = _queue.pop() )
	{
		_cur->flushToFile();	
		delete _cur;
	}
}

void LogThread::pushTask(LoggerBuffer *T)
{
	_queue.push(T);
}

}



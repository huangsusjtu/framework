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
	_pos(0)
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
}

bool LoggerBuffer::append(const char*level, const char *info, size_t size)
{
	assert(level!=NULL && info!=NULL);
	int len = strlen(level);
	if(len+size+1 > _size-_pos)
		return false;
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
	_fileID(0),_logfile(NULL)
{
	_cur = &_logbuf1;
}

Logger::~Logger()
{
	forceFlush();
}

bool Logger::appendLine(const char* level,const char *line)
{
	assert(line!=NULL && _cur!=NULL);
	Lock::lock();
	int size = strlen(line);
	if(_cur->append(level, line, size)==false)
	{
		flushToFile(_cur);
		if(_cur == &_logbuf1){
			_cur = &_logbuf2;
		}else{
			_cur = &_logbuf1;
		}
		if(_cur->append(level, line, size)==false)
		{
			std::cerr<<"Logger: write log mem err!"<<std::endl;
			Lock::unlock();
			return false;
		}
	}

	
	Lock::unlock();
	return true;
}

bool Logger::forceFlush(bool newfile)
{
	assert(_cur!=NULL);
	flushToFile(_cur, newfile);
}

void Logger::generateLogFileName(bool newfile)
{
	int len = strlen(logFileName);
	len += 16;
	if(_logfile)
		delete _logfile;
	try{
		if(newfile)
			_fileID++;
		_logfile = new char[len];
		snprintf(_logfile, len,"%s-%d",logFileName,_fileID);
	}catch(...){
		std::cerr<<"Logger: generate log file name err"<<std::endl;
		exit(0);
	}
}

void Logger::flushToFile(LoggerBuffer *cur, bool newfile)
{
	generateLogFileName(newfile);

	std::ofstream of;
	try{
		of.open(_logfile, std::ofstream::out | std::ofstream::app);
		if(of.good() && cur!=NULL){
			of.write((const char*)cur->_buf, cur->_pos);
			of.flush();
			cur->_pos = 0;
			cur->_start = 0;
		}else{
			std::cerr<<"Logger: err ofstream"<<std::endl;
		}
	}catch(...){
		std::cerr<<"Logger: flush log data err!"<<std::endl;
	}
}



}



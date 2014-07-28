#ifndef LOGGER_
#define LOGGER_

#include "lock.h"

#include <cstdio>
#include <unistd.h>
namespace sys{


enum{
	LOGBUF_SIZE = 4096,
};

#define ERR "error: "
#define INFO "info: "
#define WARN "warn: "
#define DEBUG "debug: "
#define CONTENT "nothing!"

class LoggerBuffer{
	public:
		unsigned char* _buf;
		size_t _start;
		size_t _pos;
		size_t _size;

	public:
		LoggerBuffer();
		~LoggerBuffer();
		
		//预留一个换行符
		bool hasFreeSpace(size_t need){return need<_size-_pos;}
		bool append(const char *level,const char* info, size_t size);	
	private:
		LoggerBuffer(const LoggerBuffer &T);
		LoggerBuffer& operator=(const LoggerBuffer &T);
		
};

class Logger : public Lock{

	public:
		static Logger& instance(){
			return self;
		}
		~Logger();


		static void i(const char *line){
			self.appendLine(INFO,line);		
		}
		static void d(const char *line){
			self.appendLine(DEBUG,line);		
		}
		static void e(const char *line){
			self.appendLine(ERR,line);		
		}
		static void w(const char *line){
			self.appendLine(WARN,line);		
		}

		bool appendLine(const char *level=DEBUG,const char *line=CONTENT);

		bool forceFlush(bool newfile=false);
	private:
		Logger();
		Logger(const Logger &T);
		Logger& operator=(const Logger &T);
		
		void generateLogFileName(bool newfile=false);
		void flushToFile(LoggerBuffer *cur, bool newfile=false);
	private:
		class LoggerBuffer *_cur;
		class LoggerBuffer _logbuf1;
		class LoggerBuffer _logbuf2;

		static Logger self;
		char *_logfile;
		int _fileID;

};

}
#endif

#ifndef LOGGER_
#define LOGGER_

#include "lock.h"
#include "thread.h"
#include "queue.h"
#include "object.h"

#include <stdarg.h>
#include <cstdio>
#include <cstring>
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


class LoggerBuffer {
	public:
		unsigned char* _buf;
		size_t _start;
		size_t _pos;
		size_t _size;
		char* _logfile;

	public:
		LoggerBuffer();
		~LoggerBuffer();
		
		//预留一个换行符
		bool hasFreeSpace(size_t need){return need<_size-_pos;}
		bool append(const char *level,const char* info, size_t size);
		void setFile(char *T){
			_logfile = strdup(T);		
		}	
		void flushToFile();
	private:
		LoggerBuffer(const LoggerBuffer &T);
		LoggerBuffer& operator=(const LoggerBuffer &T);
		
};

class Logger : public Lock{
	friend class  LogThread;
	static const int MAX_LOG_LINE = 1024;
	public:
		static Logger& instance(){
			return self;
		}
		~Logger();

		static void i(const char *fmt, ...){
			char line[MAX_LOG_LINE];
			 va_list ap;
    			 va_start(ap, fmt);
    			 vsnprintf(line, MAX_LOG_LINE, fmt, ap);
   			 va_end(ap);
			self.appendLine(INFO,line);	
		}
		static void d(const char *fmt, ...){
			char line[MAX_LOG_LINE];
			 va_list ap;
    			 va_start(ap, fmt);
    			 vsnprintf(line,MAX_LOG_LINE, fmt, ap);
   			 va_end(ap);
			self.appendLine(DEBUG,line);	
		}
		static void e(const char *fmt, ...){
			char line[MAX_LOG_LINE];
			 va_list ap;
    			 va_start(ap, fmt);
    			 vsnprintf(line, MAX_LOG_LINE, fmt, ap);
   			 va_end(ap);
			self.appendLine(ERR,line);
		}
		static void w(const char *fmt, ...){
			 char line[MAX_LOG_LINE];
			 va_list ap;
    			 va_start(ap, fmt);
    			 vsnprintf(line, MAX_LOG_LINE, fmt, ap);
   			 va_end(ap);
			 self.appendLine(WARN,line);
		}

		bool appendLine(const char *level=DEBUG,const char *line=CONTENT);

		bool forceFlush(bool newfile=false);
		
	private:
		Logger();
		Logger(const Logger &T);
		Logger& operator=(const Logger &T);
		
		void generateLogFileName(bool newfile=false);
		
	private:
		class LoggerBuffer *_cur;
		
		
		//a thread to write memory log data to log file		
		Thread *logThread;

		static Logger self;
		char *_logfile;
		int _fileID;

};

/**
 *  线程用于 日志持久化
 */
class LogThread : public Thread, public Object
{
	typedef BlockQueue<LoggerBuffer> LogBufQueue;
	public:
		static LogThread& instance(){
			if(self==NULL)
			{
				self = new LogThread();
				self->start();
				//self->detach();
			}	
			return *self;
		}
		~LogThread();

		void pushTask(LoggerBuffer *T);
		//inline void setOutBuffer(Logger *T,LoggerBuffer *cur);
	protected:
		virtual void run();
	private:
		
		LogBufQueue _queue;
	
	private :
		LogThread();
		LogThread(const LogThread &T);
		LogThread& operator=(const LogThread &T);
		static LogThread *self;
		
};
	

}
#endif

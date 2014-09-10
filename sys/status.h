#ifndef STATUS
#define STATUS
#include <string.h>
#include "auto_mutex.h"

namespace sys{

typedef int status_t;

const char* err_message[]=
{
	"ok",
	"",
};

const int OK = 0;

const int MaxCode = -1; 



static const char* getErrMessage(int code){
	code = 0-code;
	if(code > MaxCode)
		code = code>MaxCode;
	return err_message[code];
};

}
#endif


#ifndef STATUS
#define STATUS
#include <string.h>
#include "auto_mutex.h"
class status
{
	public:
		static void test(){
			const status& s1 = status::obtainStatus(" ");
			const status& s2 = status::obtainStatusOK();
		}
	//static
	public:
		static const status obtainStatusOK(){
			return mStatusOK ;
		}
		/*. . . */

		//create a user specified status.
		static status obtainStatus(const char* m){
			status tmp(m);
			return tmp;
		}

		const char* getWhat()const{
			return what;
		}

		bool operator==(const status& T)const{
			const char* p = T.getWhat();
			if(p==what)return true;
			if(p && what)
				return strcmp(what,p);
			return false;
		}
		bool operator!=(const status& T)const{
			return !(*this==T);
		}

	public:
		status(const status& T){
			what = T.getWhat();
		};

		status(const char* w){
			what = w;
		};
		~status(){};
	private:
		static const status mStatusOK;
		status(){};
		
		const char* what;
};
#endif


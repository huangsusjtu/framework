#ifndef BASE_EVENT_
#define BASE_EVENT_

namespace sys{

/**
 * 基类 描述命令对象，用于一个线程传递给另一个线程的命令
 */

	
class Commond
{

	public:
		enum TYPE{
			DEFAULT,
			WRITE,
			READ,
			ERROR
		};


		Commond(TYPE type = TYPE::DEFAULT);
		virtual ~Commond();

		TYPE getType(){
			return _type;		
		} 
		void setType(TYPE type){
			_type = type;		
		}

		virtual void onCommond()=0;
	private:
		TYPE _type ;
		
};




}


#endif

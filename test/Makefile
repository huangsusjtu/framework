

TOPDIR =  $(shell pwd)


CXX = g++
LINK = g++
INCLUDE := ../
LIBS = -lpthread 
CFLAG = -std=c++11  -I$(INCLUDE)



#本目录下的obj
TESTOBJS = \
	 logger.o\



#外部的obj
OBJS = ../auto_mutex.o ../clientsocket.o ../lock.o \
	../messagequeue.o  ../event_driver.o \
	../memblock.o ../memblockpool.o ../membuffer.o ../object.o \
	../packet.o ../packetqueue.o ../socket.o ../serversocket.o \
	../status.o ../thread.o  \
	../refcount.o ../socketstream.o ../connection.o \
	../connectionmanager.o   ../logger.o  \
	../listensocketevent.o ../tcpsocketevent.o \
	../neteventdriver.o ../commond.o ../netevent.o \


#本目录下的.cpp
TESTSRC=${TESTOBJS:%.o=%.cpp}
#本目录下要生成的二进制可执行文件 
TESTS=${TESTOBJS:%.o=%test}

.PHONY: work
work: depend $(TESTS)
	echo "create test!"
	echo $(TOPDIR)

depend:  ../.depend
	make clean
	$(CXX) $(CFLAG) -MM $(TESTSRC)  > .depend  
-include .depend

$(TESTS): $(TESTOBJS)
	$(LINK) -o $@  $(TESTOBJS) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $<  $(CFLAG)

.PHONY: clean
clean:
	rm -f  $(TESTS) $(TESTOBJS) *~ 

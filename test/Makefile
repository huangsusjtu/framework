

TOPDIR =  $(shell pwd)


CXX = g++
LINK = g++
INCLUDE := ../
LIBS = -lpthread 
CFLAG = -g -std=c++11  -I$(INCLUDE)



#本目录下的obj
TESTOBJS = logger.o client.o  server.o  \


#外部的obj
OBJS = ../lib/auto_mutex.o ../lib/clientsocket.o ../lib/lock.o \
	../lib/messagequeue.o  ../lib/event_driver.o \
	../lib/memblock.o ../lib/memblockpool.o ../lib/membuffer.o ../lib/object.o \
	../lib/packet.o ../lib/packetqueue.o ../lib/socket.o ../lib/serversocket.o \
	../lib/status.o ../lib/thread.o  \
	../lib/refcount.o ../lib/socketstream.o ../lib/connection.o \
	../lib/connectionmanager.o   ../lib/logger.o  \
	../lib/listensocketevent.o ../lib/tcpsocketevent.o \
	../lib/neteventdriver.o ../lib/commond.o ../lib/netevent.o \
	../lib/datatransport.o ../lib/taskqueuethread.o  \


#本目录下的.cpp
TESTSRC=${TESTOBJS:%.o=%.cpp}
#本目录下要生成的二进制可执行文件 
TESTS=${TESTOBJS:%.o=%test}

.PHONY: depend
all: depend $(TESTOBJS)
	echo "create test!"
	echo $(TOPDIR)
	$(LINK)  -o logger logger.o $(OBJS) $(LIBS)
	$(LINK)  -o client client.o $(OBJS) $(LIBS)
	$(LINK)  -o server server.o $(OBJS) $(LIBS)

depend:  ../.depend
	make clean
	$(CXX) $(CFLAG) -MM $(TESTSRC)  > .depend  
-include .depend



%.o: %.cpp
	$(CXX) -c $<  $(CFLAG)

.PHONY: clean
clean:
	rm -f  $(TESTS) $(TESTOBJS) *~ 



CXX = g++
LINK = g++
LIBS = -lpthread 
CFLAG = -std=c++11  


SUBDIRS := test
SERVER_NAME = server

 
OBJS = auto_mutex.o \
	clientsocket.o lock.o \
	messagequeue.o  event_driver.o \
	memblock.o memblockpool.o \
	membuffer.o object.o \
	packet.o packetqueue.o \
	socket.o serversocket.o \
	status.o main.o thread.o  \
	refcount.o socketstream.o connection.o \
	connectionmanager.o  logger.o   \
	listensocketevent.o tcpsocketevent.o neteventdriver.o\
	baseevent.o netevent.o \




SRCS = ${OBJS:%.o=%.cpp} 
TARGET = $(SERVER_NAME) 

  
.PHONY: all
all: depend $(TARGET) subdirs 
	i=1;
	for t in $(TARGET);do echo "create $$t ok!";done;
	 

depend:  
	@$(CC) $(CFLAG) -MM $(SRCS) $(TESTS)  > .depend  
-include .depend

$(TARGET): $(OBJS)
	$(LINK) -o $(TARGET) $(OBJS) $(LIBS)


%.o: %.cpp
	$(CXX) -c $<  $(CFLAG)



.PHONY: test
test: subdirs
subdirs:
	 for n in $(SUBDIRS); do $(MAKE) -C $$n ; echo "compile $$n";done;


#
#status.o : status.cpp status.h
#	$(CXX) -c status.cpp -o status.o $(CFLAG)
#
#auto_mutex.o: auto_mutex.cpp auto_mutex.h
#	$(CXX) -c  auto_mutex.cpp -o auto_mutex.o $(CFLAG)

#thread.o: thread.cpp thread.h 
#	$(CXX) -c thread.cpp -o thread.o $(CFLAG)


#messagequeue.o : messagequeue.cpp messagequeue.h
#	$(CXX) -c messagequeue.cpp -o messagequeue.o  $(CFLAG)

#event_driver.o: event_driver.cpp event_driver.h 
#	$(CXX) -c event_driver.cpp -o event_driver.o $(CFLAG)
	
#network.o : network.cpp network.h
#	$(CXX) -c network.cpp -o network.o $(CFLAG)

#main.o: main.cpp $(DEPEND)
#	$(CXX) -c main.cpp -o main.o  $(CFLAG)
#

.PHONY: clean
clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
	rm -f  $(TARGET) $(OBJS) *~ all
	

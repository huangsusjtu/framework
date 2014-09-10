

CXX = g++
LINK = g++
LIBS = -lpthread 
CFLAG = -std=c++11  -g

TOPDIR := ../
LIBDIR := $(TOPDIR)lib


SRCS = $(wildcard *.cpp)  
OBJS = ${SRCS:%.cpp=%.o} 



  
.PHONY: all
all: depend $(OBJS)
	if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR);  fi
	for t in $(OBJS);do mv $$t $(LIBDIR); done 

depend:  
	@$(CC) $(CFLAG) -MM $(SRCS) $(TESTS)  > .depend  
-include .depend
	

%.o: %.cpp
	$(CXX) -c $<  $(CFLAG)


.PHONY: clean
clean:
	rm -f  $(TARGET) $(OBJS) *~ 
	rm ./lib -rf
	

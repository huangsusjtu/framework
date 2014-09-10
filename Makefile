

SUBDIRS := ./sys ./net ./test

OBJS = ./lib/$(wildcard *.o) 
LIBS = -lpthread 

.PHONY: all
all: sys net test
	echo "FINISH !"
	#for t in $(SUBDIRS);do $(MAKE) -C $$t; done
	#$(MAKE) -C ./sys
	#$(MAKE) -C ./net 
	#g++  -o server main.o $(OBJS) $(LIBS)

.PHONY: sys
sys:
	make -C ./sys

.PHONY: net
net:
	make -C ./net

.PHONY: test
test:
	make -C ./test

.PHONY: clean
clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
	rm -f  *~ 
	rm ./lib -rf
	

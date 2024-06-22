CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=driver.o

HEADERS=driver.h

BINS=driver 

all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
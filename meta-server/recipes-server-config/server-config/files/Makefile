CROSS_COMPILE=

ifeq ($(CC),)
        CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
        CFLAGS= -g
endif

all: serverapplication 
default: serverapplication 

serverapplication : server.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o serverapplication server.o $(LDFLAGS)


server.o : server.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c server.c $(LDFLAGS)

clean :
	 rm -f serverapplication *.o 

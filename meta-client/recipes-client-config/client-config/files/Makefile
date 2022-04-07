CROSS_COMPILE=

ifeq ($(CC),)
        CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
        CFLAGS= -g -Wall -Werror
endif

all: clientapplication 
default: clientapplication 

clientapplication : client.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o clientapplication client.o $(LDFLAGS)


client.o : client.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c client.c $(LDFLAGS)

clean :
	rm -f clientapplication *.o 

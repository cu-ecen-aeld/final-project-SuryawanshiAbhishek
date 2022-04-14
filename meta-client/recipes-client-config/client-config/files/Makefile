CROSS_COMPILE=

ifeq ($(CC),)
        CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
        CFLAGS= -g -Wall -Werror
endif

all: clientapplication utctimeapp
default: clientapplication utctimeapp

clientapplication : client.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o clientapplication client.o $(LDFLAGS)

utctimeapp : utctime.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o utctimeapp utctime.o $(LDFLAGS)

client.o : client.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c client.c $(LDFLAGS)

utctime.o :utctime.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c utctime.c $(LDFLAGS)

clean :
	rm -f clientapplication utctimeapp *.o 

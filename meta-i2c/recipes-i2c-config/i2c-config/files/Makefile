CROSS_COMPILE=

ifeq ($(CC),)
        CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

all: mlx90614test htud21test
default: mlx90614test htud21test

mlx90614test : mlx90614.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o mlx90614test mlx90614.o $(LDFLAGS)

htud21test : htud21.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o htud21test htud21.o $(LDFLAGS)

mlx90614.o : mlx90614.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c mlx90614.c $(LDFLAGS)
		
htud21.o : htud21.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c htud21.c $(LDFLAGS)

clean :
	 rm -f mlx90614test htud21test *.o

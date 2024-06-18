CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -ggdb
LDFLAGS = -lm  

OBJS = minish.o builtins.o linea2argv.o ejecutar.o raices.o

minish: $(OBJS)
	$(CC) $(CFLAGS) -o minish $(OBJS) $(LDFLAGS)

minish.o: minish.c minish.h
	$(CC) $(CFLAGS) -c minish.c

builtins.o: builtins.c minish.h
	$(CC) $(CFLAGS) -c builtins.c

linea2argv.o: linea2argv.c minish.h
	$(CC) $(CFLAGS) -c linea2argv.c

ejecutar.o: ejecutar.c minish.h
	$(CC) $(CFLAGS) -c ejecutar.c

raices.o: raices.c  
	$(CC) $(CFLAGS) -c raices.c

clean:
	rm -f *.o minish

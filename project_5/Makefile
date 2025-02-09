CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

all: llist

llist: main.o llist.o
	$(CC) $(CFLAGS) -o llist main.o llist.o

main.o: main.c llist.h
	$(CC) $(CFLAGS) -c main.c

llist.o: llist.c llist.h
	$(CC) $(CFLAGS) -c llist.c

clean:
	rm -f llist main.o llist.o

run: llist
	./llist

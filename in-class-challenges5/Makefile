CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: pointer pointerstruct ub malloctest mmaptest

pointer: pointer.c
	$(CC) $(CFLAGS) -o pointer pointer.c

pointerstruct: pointerstruct.c
	$(CC) $(CFLAGS) -o pointerstruct pointerstruct.c

ub: ub.c
	$(CC) $(CFLAGS) -o ub ub.c

malloctest: malloctest.c
	$(CC) $(CFLAGS) -o malloctest malloctest.c

mmaptest: mmaptest.c
	$(CC) $(CFLAGS) -o mmaptest mmaptest.c

clean:
	rm -f pointer pointerstruct ub malloctest mmaptest
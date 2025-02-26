CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: bitwise pt mlpt

bitwise: bitwise.c
	$(CC) $(CFLAGS) -o bitwise bitwise.c

pt: pt.c
	$(CC) $(CFLAGS) -o pt pt.c

mlpt: mlpt.c
	$(CC) $(CFLAGS) -o mlpt mlpt.c

clean:
	rm -f bitwise pt mlpt

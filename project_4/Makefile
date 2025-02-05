CC = gcc
CFLAGS = -Wall -Wextra -O2

all: redirout lswc

redirout: redirout.c
	$(CC) $(CFLAGS) -o redirout redirout.c

pipe_ls_wc: pipe_ls_wc.c
	$(CC) $(CFLAGS) -o lswc lswc.c

clean:
	rm -f redirout lswc

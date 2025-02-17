CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
TARGET = myalloc
SRC = myalloc.c
OBJ = myalloc.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean $(TARGET)

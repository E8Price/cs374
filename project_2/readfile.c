#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Usage: ./readfile <filename>\n", 29);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    int bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(1, buffer, bytesRead);
    }

    close(fd);
    return 0;
}

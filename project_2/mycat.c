#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    int fd, bytesRead;

    if (argc == 1) {
        fd = 0;  
    } else {
        for (int i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror("open");
                continue;
            }
            while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
                write(1, buffer, bytesRead);
            close(fd);
        }
        return 0;
    }

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
        write(1, buffer, bytesRead);

    return 0;
}

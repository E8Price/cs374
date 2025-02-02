#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("usage: redirout filename command arg\n");
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) return 1;

    if (fork() == 0) {  
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execvp(argv[2], &argv[2]);
        exit(1);
    }

    close(fd);
    return 0;
}

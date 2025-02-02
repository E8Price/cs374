#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    
    if (fork() == 0) {  
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); close(fd[1]);
        execlp("wc", "wc", "-l", NULL);
        exit(1);
    }
    
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]); close(fd[1]);
    execlp("ls", "ls", "-1a", (argc > 1) ? argv[1] : NULL, NULL);
    exit(1);
}

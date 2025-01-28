#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pfds[2];        
    char buffer[128];   

    if (pipe(pfds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
    
        close(pfds[0]);
        const char *message = "Hello, parent!\n";
        write(pfds[1], message, strlen(message));
        close(pfds[1]); 
    } else {
        close(pfds[1]); 
        int bytes_read = read(pfds[0], buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0'; 
        write(STDOUT_FILENO, buffer, bytes_read);
        close(pfds[0]); 
        wait(NULL);   
    }

    return 0;
}

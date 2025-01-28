#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pfds[2]; 
    char buffer[100];

    pipe(pfds);

    const char *message = "Hello\n";
    write(pfds[1], message, strlen(message));

    int bytes_read = read(pfds[0], buffer, sizeof(buffer) - 1);

    buffer[bytes_read] = '\0';

    write(STDOUT_FILENO, buffer, bytes_read);

    return 0;
}
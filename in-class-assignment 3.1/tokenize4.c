#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *tokens[128] = {0};

    printf("prompt> ");
    fflush(stdout);  

    char line[1024];
    fgets(line, sizeof(line), stdin); 
    line[strcspn(line, "\n")] = '\0';  

    char *token = strtok(line, " "); 
    int index = 0;

    while (token != NULL && index < 127) {  
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }

    tokens[index] = NULL; 

    execvp(tokens[0], tokens);  

    perror("execvp failed");  

    return 1;
}

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    (void)argc; 

    char *token;
    int index = 0;

    token = strtok(argv[1], " ");  

    while (token != NULL) {
        printf("%d: %s\n", index++, token);
        token = strtok(NULL, " ");  
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *tokens[128] = {0};

    char line[1024];
    fgets(line, sizeof(line), stdin); 
    line[strcspn(line, "\n")] = '\0';  

    char *token = strtok(line, " "); 
    int index = 0;

    while (token != NULL && index < 128) {
        tokens[index++] = token;  
        token = strtok(NULL, " ");  
    }

    for (int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);

    return 0;
}

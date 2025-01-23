#include <stdio.h>
#include <string.h>

int main()
{
    char line[1024];
    char *token;
    int index = 0;

    fgets(line, sizeof(line), stdin); 

    line[strcspn(line, "\n")] = '\0';  

    token = strtok(line, " ");  

    while (token != NULL) {
        printf("%d: %s\n", index++, token);
        token = strtok(NULL, " "); 
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct animal {
    char *name;
    int leg_count;
};

int main(void)
{
    struct animal *a;

    a = malloc(sizeof(struct animal));
    if (a == NULL) {
        printf("Memory allocation failed\n");
        return 1; 
    }

    a->name = "Antelope";
    a->leg_count = 4;
    printf("%s %d\n", a->name, a->leg_count);

    free(a);

    return 0;
}

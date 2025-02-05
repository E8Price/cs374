#include <stdio.h>
#include <stdlib.h>

struct animal {
    char *name;
    int leg_count;
};

struct animal *construct_animal(char *name, int leg_count)
{
    struct animal *a = malloc(sizeof(struct animal)); 
    if (!a) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    a->name = name;
    a->leg_count = leg_count;

    return a;
}

int main(void)
{
    struct animal *a1, *a2;

    a1 = construct_animal("Antelope", 4);
    a2 = construct_animal("Centipede", 100);

    if (a1 && a2) {
        printf("%s %d\n", a1->name, a1->leg_count);
        printf("%s %d\n", a2->name, a2->leg_count);
    }

    free(a1);
    free(a2);

    return 0;
}

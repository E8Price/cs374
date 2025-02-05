#include <stdio.h>

struct animal {
    char *name;
    int leg_count;
};

void increment_leg_count(struct animal *p)
{
    p->leg_count++; 
}

int main(void)
{
    struct animal a = {.name="Antelope", .leg_count=3};

    increment_leg_count(&a); 

    printf("%d\n", a.leg_count); 
}

#include <stdio.h>

void increment(int *x)
{
    (*x)++;
}

int main(void)
{
    int a = 12;

    increment(&a); 

    printf("%d\n", a);
}

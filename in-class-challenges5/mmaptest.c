#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>

struct animal {
    char *name;
    int leg_count;
};

int main(void)
{
    struct animal *a;

    a = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (a == MAP_FAILED) {
        perror("mmap");
        exit(1); 
    }

    a->name = "Antelope";
    a->leg_count = 4;
    printf("%s %d\n", a->name, a->leg_count);

    if (munmap(a, 4096) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}

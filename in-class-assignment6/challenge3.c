#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    for (int i = 1; i <= 9; i++) {
        void *heap = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        printf("Iteration %d: Address = %p\n", i, heap);
    }

    return 0;
}

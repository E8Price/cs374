#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

const int SIZE = 1024;  

struct bicycle {
    int wheel_count;
    char name[32];
};

int main(void)
{
    void *heap = mmap(NULL, SIZE, PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE, -1, 0);

    if (heap == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    char *char_heap = (char *)heap;
    strcpy(char_heap, "Hello, mmap!");
    printf("Stored string: %s\n", char_heap);

    int *int_heap = (int *)heap;
    for (int i = 0; i < 5; i++) {
        int_heap[i] = i * 10;
    }
    for (int i = 0; i < 5; i++) {
        printf("Int %d: %d\n", i, int_heap[i]);
    }

    struct bicycle *bike_heap = (struct bicycle *)heap;
    struct bicycle bikes[3] = {
        {2, "Mountain Bike"},
        {3, "Tricycle"},
        {2, "Road Bike"}
    };
    for (int i = 0; i < 3; i++) {
        bike_heap[i] = bikes[i];
    }
    for (int i = 0; i < 3; i++) {
        printf("Bike %d: %s with %d wheels\n", i, bike_heap[i].name, bike_heap[i].wheel_count);
    }

    char_heap = (char *)heap;
    strcpy(char_heap, "Array Notation!");
    printf("Stored string (array notation): %s\n", char_heap);

    int_heap = (int *)heap;
    for (int i = 0; i < 5; i++) {
        int_heap[i] = i * 10;
    }
    for (int i = 0; i < 5; i++) {
        printf("Int (array notation) %d: %d\n", i, int_heap[i]);
    }

    bike_heap = (struct bicycle *)heap;
    for (int i = 0; i < 3; i++) {
        bike_heap[i] = bikes[i];
    }
    for (int i = 0; i < 3; i++) {
        printf("Bike (array notation) %d: %s with %d wheels\n", i, bike_heap[i].name, bike_heap[i].wheel_count);
    }

    char *string_section = (char *)heap;
    strcpy(string_section, "Heap Mixed Data");
    int *int_section = (int *)(heap + 32);
    for (int i = 0; i < 5; i++) {
        int_section[i] = i * 10;
    }
    for (int i = 0; i < 5; i++) {
        printf("Int in mixed section %d: %d\n", i, int_section[i]);
    }
    printf("Stored string in mixed section: %s\n", string_section);

    munmap(heap, SIZE);

    return 0;
}

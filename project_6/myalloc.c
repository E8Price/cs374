#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

//constants
#define HEAP_SIZE 1024  
#define ALIGNMENT 16    

#define PADDED_SIZE(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define PTR_OFFSET(p, offset) ((void *)((char *)(p) + (offset)))


struct block {
    int size;        
    int in_use;      
    struct block *next;
};

static struct block *head = NULL;

void *myalloc(int size) {
    if (size <= 0) return NULL;

    int actual_size = PADDED_SIZE(size);
\
    if (head == NULL) {
        void *heap = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,
                          MAP_ANON | MAP_PRIVATE, -1, 0);
        if (heap == MAP_FAILED) return NULL;

        head = (struct block *)heap;
        head->size = HEAP_SIZE - PADDED_SIZE(sizeof(struct block));
        head->in_use = 0;
        head->next = NULL;
    }

    struct block *current = head;
    while (current != NULL) {
        if (!current->in_use && current->size >= actual_size) {
            current->in_use = 1;
            return PTR_OFFSET(current, PADDED_SIZE(sizeof(struct block)));
        }
        current = current->next;
    }

    return NULL;
}

void myfree(void *p)
{
    // TODO
    (void)p;  // silence unused variable warnings
}

// ---------------------------------------------------------
// No mods past this point, please
// ---------------------------------------------------------

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        fflush(stdout);

        b = b->next;
    }

    printf("\n");
}

int parse_num_arg(char *progname, char *s)
{
    char *end;

    int value = strtol(s, &end, 10);

    if (*end != '\0') {
        fprintf(stderr, "%s: failed to parse numeric argument \"%s\"\n", progname, s);
        exit(1);
    }

    return value;
}

/*
 * Usage:
 *
 * You can specify the following commands:
 *
 * p       - print the list
 * a size  - allocate `size` bytes
 * f num   - free allocation number `num`
 *
 * For example, if we run this:
 *
 *   ./myalloc a 64 a 128 p f 2 p f 1 p
 *
 * Allocation #1 of 64 bytes occurs
 * Allocation #2 of 128 bytes occurs
 * The list is printed
 * Allocation #2 is freed (the 128-byte chunk)
 * The list is printed
 * Allocation #1 is freed (the 64-byte chunk)
 * The list is printed
 *
 * Failed allocations aren't counted for the 'f' argument, for example:
 *
 *   ./myalloc a 999999 f 1
 *
 * is an error, since that allocation will have failed.
 */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "usage: %s [p|a size|f index] ...\n", argv[0]);
        return 1;
    }

    int i = 1;

    // This is how many allocs we can support on the command line
    void *ptr[128];
    int ptr_count = 0;

    while (i < argc) {
        if (strcmp(argv[i], "p") == 0)
            print_data();

        else if (strcmp(argv[i], "a") == 0) {
            i++;

            int size = parse_num_arg(argv[0], argv[i]);
            
            void *p = myalloc(size); 

            if (p == NULL)
                printf("failed to allocate %d byte%s\n", size, size == 1? "": "s");
            else
                ptr[ptr_count++] = p;

        } else if (strcmp(argv[i], "f") == 0) {
            i++;

            if (argv[i] == NULL) {
                fprintf(stderr, "%s: missing num argument for 'f' command\n", argv[0]);
                return 1;
            }

            int index = parse_num_arg(argv[0], argv[i]);

            if (index < 1 || index > ptr_count) {
                fprintf(stderr, "%s: 'f' command: argument %d out of range\n", argv[0], index);
                return 1;
            }

            myfree(ptr[index - 1]);

        } else {
            fprintf(stderr, "%s: unknown command: %s\n", argv[0], argv[i]);
            return 1;
        }

        i++;
    }
}

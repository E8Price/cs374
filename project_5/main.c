#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

int main(int argc, char *argv[]) {
    struct node *head = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0 && i + 1 < argc) {
            int val = atoi(argv[++i]);
            llist_insert_head(&head, node_alloc(val));
        } 
        else if (strcmp(argv[i], "it") == 0 && i + 1 < argc) {
            int val = atoi(argv[++i]);
            llist_insert_tail(&head, node_alloc(val));
        } 
        else if (strcmp(argv[i], "dh") == 0) {
            struct node *deleted = llist_delete_head(&head);
            if (deleted) node_free(deleted);
        } 
        else if (strcmp(argv[i], "p") == 0) {
            llist_print(head);
        } 
        else if (strcmp(argv[i], "f") == 0) {
            llist_free(&head);
        }
    }

    return 0;
}

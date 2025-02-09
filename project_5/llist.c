#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

struct node *node_alloc(int value) {
    struct node *n = malloc(sizeof(struct node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    n->value = value;
    n->next = NULL;
    return n;
}

void node_free(struct node *n) {
    free(n);
}

void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head;
    *head = n;
}

void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = n;
        return;
    }

    struct node *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = n;
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) return NULL; 

    struct node *temp = *head;
    *head = temp->next;
    temp->next = NULL;

    return temp;
}

void llist_print(struct node *head) {
    if (!head) {
        printf("[empty]\n");
        return;
    }

    struct node *temp = head;
    while (temp) {
        printf("%d", temp->value);
        if (temp->next) printf(" -> ");
        temp = temp->next;
    }
    printf("\n");
}

void llist_free(struct node **head) {
    struct node *temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        node_free(temp);
    }
}

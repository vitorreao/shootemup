#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct ListNode {
    void *userData;
    struct ListNode *next;
} ListNode;

typedef struct List {
    struct ListNode *head;
    struct ListNode *tail;
} List;

bool ListPush(List *list, void *data);

#endif // LIST_H

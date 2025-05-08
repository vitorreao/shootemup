#include "list.h"

#include <SDL3/SDL.h>

bool ListPush(List *head, void *data)
{
    ListNode *newNode = SDL_malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return false;
    }
    newNode->userData = data;
    newNode->next = NULL;
    if (head->tail) {
        ListNode *tail = head->tail;
        tail->next = newNode;
    } else {
        head->head = newNode;
    }
    head->tail = newNode;
    return true;
}

#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct Array Array;

Array *CreateArray(size_t itemSize, size_t capacity);
void DestroyArray(Array *arr);
int AppendToArray(Array *arr, void *elem);
size_t GetArrayLength(Array *arr);
void *GetArrayElem(Array *arr, int idx);

#endif // ARRAY_H

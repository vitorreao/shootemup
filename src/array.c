#include <SDL3/SDL.h>

#include "array.h"

struct Array {
    void *userData;
    size_t itemSize;
    size_t capacity;
    size_t length;
};

Array *CreateArray(size_t itemSize, size_t capacity)
{
    struct Array *arr = SDL_malloc(sizeof(struct Array));
    if (arr == NULL) {
        return NULL;
    }
    SDL_memset(arr, 0, sizeof(struct Array));
    arr->userData = SDL_malloc(itemSize * capacity);
    if (arr->userData == NULL) {
        SDL_free(arr);
        return NULL;
    }
    arr->itemSize = itemSize;
    arr->capacity = capacity;
    return arr;
}

void DestroyArray(Array *arr)
{
    if (arr == NULL) {
        return;
    }
    SDL_free(arr->userData);
    SDL_free(arr);
}

bool reallocArray(Array *arr)
{
    size_t newCapacity = 1;
    if (arr->capacity > 0) {
        newCapacity *= arr->capacity * 2;
    }
    void *newUserData = SDL_realloc(arr->userData, newCapacity * sizeof(arr->itemSize));
    if (newUserData == NULL) {
        return false;
    }
    arr->userData = newUserData;
    arr->capacity = newCapacity;
    return true;
}

bool AppendToArray(Array *arr, void *elem)
{
    if (arr == NULL) {
        return false;
    }
    if (arr->length >= arr->capacity && !reallocArray(arr)) {
        return false;
    }
    size_t idx = arr->length;
    char *ptr = (char *)arr->userData;
    SDL_memcpy(ptr + (idx * arr->itemSize), elem, arr->itemSize);
    arr->length++;
    return true;
}

size_t GetArrayLength(Array *arr)
{
    return arr->length;
}

void *GetArrayElem(Array *arr, int idx)
{
    char *ptr = (char *)arr->userData;
    return ptr + (idx * arr->itemSize);
}

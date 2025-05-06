#ifndef OPAQUE_H
#define OPAQUE_H

#include <stdlib.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "app.h"
#include "array.h"

struct _RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct AppContext {
    struct _RenderContext *renders;
    size_t rendersLength;
    size_t rendersCapacity;

    Array *cleanUpsArr;

    zip_t *zipArchive;

    bool quitRequested;
};

#endif // OPAQUE_H

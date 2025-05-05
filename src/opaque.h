#ifndef OPAQUE_H
#define OPAQUE_H

#include <stdlib.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "app.h"

struct _RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct _AppContext {
    struct _RenderContext *renders;
    size_t rendersLength;
    size_t rendersCapacity;

    AppCleanUp *cleanUps;
    size_t cleanUpsLength;
    size_t cleanUpsCapacity;

    zip_t *zipArchive;

    bool quitRequested;
};

#endif // OPAQUE_H

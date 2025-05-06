#ifndef OPAQUE_H
#define OPAQUE_H

#include <stdlib.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "app.h"
#include "array.h"

struct RenderContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct AppContext {
    Array *renderCtxArr;
    Array *cleanUpsArr;
    zip_t *zipArchive;
    bool quitRequested;
};

#endif // OPAQUE_H

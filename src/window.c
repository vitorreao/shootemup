#include "opaque.h"
#include "window.h"

static void reallocRenders(AppContext app)
{
    size_t newCapacity = 1;
    if (app->rendersCapacity > 0) {
        newCapacity *= app->rendersCapacity * 2;
    }
    struct _RenderContext *newRender = SDL_realloc(
        app->renders, sizeof(struct _RenderContext) * newCapacity);
    if (newRender == NULL) {
        fprintf(stderr, "Cannot allocate memory for App Renderer\n");
        exit(1);
    }
    app->renders = newRender;
    app->rendersCapacity = newCapacity;
}

size_t CreateAppWindow(AppContext app, const char *title, int w, int h)
{
    if (app->rendersLength >= app->rendersCapacity) {
        reallocRenders(app);
    }
    size_t idx = app->rendersLength;
    SDL_Window *window = SDL_CreateWindow(title, w, h, 0);
    if (window == NULL) {
        fprintf(stderr, "Cannot create window: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        fprintf(stderr, "Cannot create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    app->renders[idx].window = window;
    app->renders[idx].renderer = renderer;
    app->rendersLength++;
    return idx;
}

#include "opaque.h"
#include "window.h"

size_t CreateAppWindow(AppContext *app, const char *title, int w, int h)
{
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
    struct RenderContext ctx;
    ctx.renderer = renderer;
    ctx.window = window;
    int idx = AppendToArray(app->renderCtxArr, &ctx);
    if (idx < 0) {
        fprintf(stderr, "Cannot append render context!\n");
        exit(1);
    }
    return idx;
}

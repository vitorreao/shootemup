#include <stdio.h>

#include <SDL3/SDL.h>

#include "app.h"
#include "asset.h"

const char *ASSETS_FILEPATH = "assets.dat";

struct _WindowContext {
    SDL_Renderer *renderer;
    SDL_Window *window;
};

struct _AppContext {
    struct _WindowContext *windows;
    size_t windowsLength;
    size_t windowsCapacity;

    AppCleanUp *cleanUps;
    size_t cleanUpsLength;
    size_t cleanUpsCapacity;

    bool quitRequested;
};

static void freeAppContext(AppContext app)
{
    SDL_free(app->cleanUps);
    SDL_free(app);
}

AppContext CreateAppContext()
{
    AppContext app = SDL_malloc(sizeof(struct _AppContext));
    if (app == NULL) {
        fprintf(stderr, "Cannot allocate memory for App Context\n");
        exit(1);
    }
    SDL_memset(app, 0, sizeof(struct _AppContext));
    RegisterAppCleanUp(app, freeAppContext);
    return app;
}

static void reallocCleanUps(AppContext app)
{
    size_t newCapacity = 1;
    if (app->cleanUpsCapacity > 0) {
        newCapacity *= app->cleanUpsCapacity * 2;
    }
    AppCleanUp *newCleanUps = SDL_realloc(app->cleanUps, newCapacity * sizeof(AppCleanUp));
    if (newCleanUps == NULL) {
        fprintf(stderr, "Cannot allocate memory for App Cleanups\n");
        exit(1);
    }
    app->cleanUps = newCleanUps;
    app->cleanUpsCapacity = newCapacity;
}

void RegisterAppCleanUp(AppContext app, AppCleanUp f)
{
    if (app->cleanUpsLength >= app->cleanUpsCapacity) {
        reallocCleanUps(app);
    }
    app->cleanUps[app->cleanUpsLength] = f;
    app->cleanUpsLength++;
}

static void reallocWindows(AppContext app)
{
    size_t newCapacity = 1;
    if (app->windowsCapacity > 0) {
        newCapacity *= app->windowsCapacity * 2;
    }
    struct _WindowContext *newWindows = SDL_realloc(
        app->windows, sizeof(struct _WindowContext) * newCapacity);
    if (newWindows == NULL) {
        fprintf(stderr, "Cannot allocate memory for App Window\n");
        exit(1);
    }
    app->windows = newWindows;
    app->windowsCapacity = newCapacity;
}

static void quitSDL(AppContext app)
{
    SDL_Quit();
}

void InitApp(AppContext app)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    RegisterAppCleanUp(app, quitSDL);
}

void CreateAppWindow(AppContext app, const char *title, int w, int h)
{
    if (app->windowsLength >= app->windowsCapacity) {
        reallocWindows(app);
    }
    size_t idx = app->windowsLength;
    if (idx == 0 && !initSDL(app)) {

    }
    app->windows[idx].window = SDL_CreateWindow(title, w, h, 0);
    if (app->windows[idx].window == NULL) {
        
    }
}

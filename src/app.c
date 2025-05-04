#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "app.h"
#include "opaque.h"

static void freeAppContext(AppContext app)
{
    SDL_free(app->cleanUps);
    SDL_free(app);
}

AppContext CreateAppContext(void)
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

static void quitSDL(AppContext app)
{
    (void)app;
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


void CleanUpApp(AppContext app)
{
    for (int i = app->cleanUpsLength - 1; i >= 0; i--) {
        app->cleanUps[i](app);
    }
}

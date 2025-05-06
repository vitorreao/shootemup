#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "app.h"
#include "opaque.h"

static void freeAppContext(AppContext *app)
{
    DestroyArray(app->cleanUpsArr);
    SDL_free(app);
}

AppContext *CreateAppContext(void)
{
    AppContext *app = SDL_malloc(sizeof(struct AppContext));
    if (app == NULL) {
        fprintf(stderr, "Cannot allocate memory for App Context\n");
        exit(1);
    }
    SDL_memset(app, 0, sizeof(struct AppContext));
    app->cleanUpsArr = CreateArray(sizeof(AppCleanUp), 1);
    RegisterAppCleanUp(app, freeAppContext);
    return app;
}

void RegisterAppCleanUp(AppContext *app, AppCleanUp f)
{
    if (!AppendToArray(app->cleanUpsArr, &f)) {
        fprintf(stderr, "Cannot append App Clean Up function!\n");
        exit(1);
    }
}

static void quitSDL(AppContext *app)
{
    (void)app;
    SDL_Quit();
}

static void cleanUpRenders(AppContext *app)
{
    for (size_t i = 0; i < app->rendersLength; i++) {
        SDL_DestroyRenderer(app->renders[i].renderer);
        SDL_DestroyWindow(app->renders[i].window);
    }
    SDL_free(app->renders);
}

void InitApp(AppContext *app)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    RegisterAppCleanUp(app, quitSDL);
    RegisterAppCleanUp(app, cleanUpRenders);
}


void CleanUpApp(AppContext *app)
{
    for (int i = GetArrayLength(app->cleanUpsArr) - 1; i >= 0; i--) {
        AppCleanUp *f = (AppCleanUp *)GetArrayElem(app->cleanUpsArr, i);
        (*f)(app);
    }
}

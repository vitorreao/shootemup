#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool quitRequested;
} App;

bool cleanUpApp(App *app)
{
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    return true;
}

bool initApp(App *app)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    app->window = SDL_CreateWindow("Shoot 'em up!", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (app->window == NULL) {
        fprintf(stderr, "Couldn't create the window: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (app->renderer == NULL) {
        fprintf(stderr, "Couldn't create the renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return false;
    }
    app->quitRequested = false;
    return true;
}

bool prepareScene(App *app)
{
    SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
    SDL_RenderClear(app->renderer);
    return true;
}

bool handleInput(App *app)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                app->quitRequested = true;
                break;
        }
    }
    return true;
}

bool presentScene(App *app)
{
    SDL_RenderPresent(app->renderer);
    return true;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    App app;
    if (!initApp(&app)) {
        exit(1);
    }
    while (!app.quitRequested) {
        if (!prepareScene(&app)) {
            break;
        }
        if (!handleInput(&app)) {
            break;
        }
        if (!presentScene(&app)) {
            break;
        }
    }
    cleanUpApp(&app);
    return 0;
}

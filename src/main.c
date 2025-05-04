#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "asset.h"

const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;
const char *ASSETS_FILEPATH = "assets.dat";

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool quitRequested;
} App;

bool cleanUpApp(App *app)
{
    closeAssetArchive();
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
    if (!openAssetArchive(ASSETS_FILEPATH)) {
        fprintf(stderr, "Couldn't open assets file\n");
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

void blit(App *app, SDL_Texture *texture, int x, int y)
{
    SDL_FRect srcRect;
    srcRect.x = 32;
    srcRect.y = 0;
    srcRect.w = 16;
    srcRect.h = 24;

    SDL_FRect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 16;
    destRect.h = 24;

    SDL_RenderTexture(app->renderer, texture, &srcRect, &destRect);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    App app;
    if (!initApp(&app)) {
        exit(1);
    }
    SDL_Texture *texture = loadTexture(app.renderer, "sprites/ship.png");
    while (!app.quitRequested) {
        if (!prepareScene(&app)) {
            break;
        }
        if (!handleInput(&app)) {
            break;
        }
        blit(&app, texture, 100, 100);
        if (!presentScene(&app)) {
            break;
        }
    }
    cleanUpApp(&app);
    return 0;
}

#ifndef APP_ASSET_H
#define APP_ASSET_H

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

bool OpenAssetArchive(const char *asset_archive_path);
void closeAssetArchive(void);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path);

#endif // APP_ASSET_H

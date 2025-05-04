#include <stdlib.h>

#include <zip.h>

#include "asset.h"

#define ZIP_HAS_FLAG(fs,f) ((fs & f) == f)

const size_t COPY_BUFFER_SIZE = 256;

zip_t *za = NULL;

bool openAssetArchive(const char *asset_archive_path)
{
    int err;
    if ((za = zip_open(asset_archive_path, ZIP_RDONLY, &err)) == NULL) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "unzip %s: %s",
            asset_archive_path,
            zip_error_strerror(&error)
        );
        zip_error_fini(&error);
        return false;
    }
    return true;
}

void closeAssetArchive(void)
{
    if (za != NULL) {
        zip_close(za);
    }
}

struct asset_file_stat {
    uint64_t total;
    uint64_t index;
};

static bool assetLoadFileStat(const char *path, struct asset_file_stat *stat)
{
    zip_stat_t stats;
    if (zip_stat(za, path, ZIP_FL_ENC_UTF_8, &stats) != 0) {
        zip_error_t* error = zip_get_error(za);
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "unzip %s: %s",
            path,
            zip_error_strerror(error)
        );
        zip_error_fini(error);
        return false;
    }
    if (!ZIP_HAS_FLAG(stats.valid, ZIP_STAT_SIZE) || !ZIP_HAS_FLAG(stats.valid, ZIP_STAT_INDEX)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "Cannot get the size of asset: %s",
            path
        );
        return false;
    }
    stat->total = stats.size;
    stat->index = stats.index;
    return true;
}

static bool copyFileToIOStream(SDL_IOStream* rwop, struct asset_file_stat *file_stats)
{
    uint64_t copied_bytes = 0;
    zip_file_t *zf = zip_fopen_index(za, file_stats->index, ZIP_FL_ENC_UTF_8);
    if (zf == NULL) {
        return false;
    }
    while (copied_bytes < file_stats->total) {
        char buffer[COPY_BUFFER_SIZE];
        zip_int64_t rlength = zip_fread(zf, buffer, COPY_BUFFER_SIZE);
        if (rlength < 0) {
            zip_fclose(zf);
            return false;
        }
        zip_int64_t wlength = SDL_WriteIO(rwop, buffer, (size_t)rlength);
        if (wlength != rlength) {
            zip_fclose(zf);
            return false;
        }
        copied_bytes += wlength;
    }
    zip_fclose(zf);
    return true;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path)
{
    struct asset_file_stat file_stats;
    if (!assetLoadFileStat(path, &file_stats)) {
        return NULL;
    }
    void *buffer = malloc(sizeof(char) * file_stats.total);
    if (buffer == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "Cannot allocate memory for asset: %s",
            path
        );
        return NULL;
    }
    SDL_IOStream *rwop = SDL_IOFromMem(buffer, (int)file_stats.total);
    if (rwop == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot create IOStream: %s", SDL_GetError());
        free(buffer);
        return NULL;
    }
    if (!copyFileToIOStream(rwop, &file_stats)) {
        SDL_CloseIO(rwop);
        free(buffer);
        return NULL;
    }
    if (SDL_SeekIO(rwop, 0, SDL_IO_SEEK_SET) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot seek to begining: %s", SDL_GetError());
        SDL_CloseIO(rwop);
        free(buffer);
        return NULL;
    }
    SDL_Texture *texture = IMG_LoadTexture_IO(renderer, rwop, false);
    if (texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load SDL texture: %s", SDL_GetError());
    }
    SDL_CloseIO(rwop);
    free(buffer);
    return texture;
}

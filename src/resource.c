#include <stdlib.h>

#include <SDL3/SDL.h>
#include <zip.h>

#include "opaque.h"
#include "resource.h"

static void closeZipArchive(AppContext *app)
{
    if (app->zipArchive == NULL) {
        return;
    }
    zip_close(app->zipArchive);
}

bool AttachResourceArchive(AppContext *app, const char *filepath)
{
    int err;
    zip_t *za;
    if ((za = zip_open(filepath, ZIP_RDONLY, &err)) == NULL) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "unzip %s: %s",
            filepath,
            zip_error_strerror(&error)
        );
        zip_error_fini(&error);
        return false;
    }
    app->zipArchive = za;
    RegisterAppCleanUp(app, closeZipArchive);
    return true;
}

#ifndef OPAQUE_H
#define OPAQUE_H

#include <stdlib.h>

#include <zip.h>

#include "app.h"

struct _AppContext {
    AppCleanUp *cleanUps;
    size_t cleanUpsLength;
    size_t cleanUpsCapacity;

    zip_t *zipArchive;

    bool quitRequested;
};

#endif // OPAQUE_H

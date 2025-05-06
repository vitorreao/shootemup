#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "app.h"

size_t CreateAppWindow(AppContext app, const char *title, int w, int h);

#endif // WINDOW_H

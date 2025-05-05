#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "app.h"
#include "resource.h"
#include "window.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    AppContext app = CreateAppContext();
    InitApp(app);
    AttachResourceArchive(app, "assets.dat");
    CreateAppWindow(app, "Shoot 'em up!", 1280, 720);
    CleanUpApp(app);
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "app.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    AppContext app = CreateAppContext();
    InitApp(app);
    AttachResourceArchive(app, "assets.dat");
    CleanUpApp(app);
    return 0;
}

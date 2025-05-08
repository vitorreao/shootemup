#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "app.h"
#include "list.h"
#include "resource.h"
#include "window.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    AppContext *app = CreateAppContext();
    InitApp(app);
    AttachResourceArchive(app, "assets.dat");
    CreateAppWindow(app, "Shoot 'em up!", 1280, 720);
    int i = 3, j = 4;
    List list = { .head = NULL, .tail = NULL };
    ListPush(&list, &i);
    ListPush(&list, &j);
    CleanUpApp(app);
    return 0;
}

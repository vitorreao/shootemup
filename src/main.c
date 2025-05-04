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
    CleanUpApp(app);
    return 0;
}

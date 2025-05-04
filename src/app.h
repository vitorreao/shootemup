#ifndef APP_H
#define APP_H

typedef struct _AppContext *AppContext;
typedef void (*AppCleanUp)(AppContext);
AppContext CreateAppContext(void);
void InitApp(AppContext app);
void RegisterAppCleanUp(AppContext app, AppCleanUp f);
void CleanUpApp(AppContext app);
bool AttachResourceArchive(AppContext app, const char *filepath);

#endif // APP_H

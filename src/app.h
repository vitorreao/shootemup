#ifndef APP_H
#define APP_H

typedef struct _AppContext *AppContext;
typedef void (*AppCleanUp)(AppContext);
AppContext CreateAppContext();
void InitApp(AppContext app);
void RegisterAppCleanUp(AppContext app, AppCleanUp f);
void CreateAppWindow(AppContext app, const char *title, int w, int h);

#endif // APP_H

#ifndef APP_H
#define APP_H

typedef struct AppContext AppContext;
typedef void (*AppCleanUp)(AppContext *);
AppContext *CreateAppContext(void);
void InitApp(AppContext *app);
void RegisterAppCleanUp(AppContext *app, AppCleanUp f);
void CleanUpApp(AppContext *app);

#endif // APP_H

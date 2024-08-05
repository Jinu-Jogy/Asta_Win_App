#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef DELETE_AND_NULLIFY
#define DELETE_AND_NULLIFY(X)   if (X) { delete X; X = nullptr; }
#endif


#ifndef APP_SETTINGS
#define APP_SETTINGS
#define ORGANIZATION_NAME "Future IK"
#define ORGANIZATION_DOMAIN "www.futureik.com"
#define APPLICATION_NAME "Asta CMS App"
#endif



#endif // GLOBALS_H

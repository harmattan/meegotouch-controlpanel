#ifndef PAGES_H
#define PAGES_H
#include <QString>
namespace Pages {
    typedef enum {
      NOPAGE = -1,
      MAIN,
      ACCOUNTS,
      APPLET,
      APPLETCATEGORY,
      PERSONALIZATION,
      CONNECTIVITY,
      DISPLAY,
      SOUND,
      CALL,
      DATETIME,
      SECURITY
   } Id;

   typedef struct _Handle Handle;
   struct _Handle {
        Id id;
        QString param;
    };
};
#endif // PAGES_H

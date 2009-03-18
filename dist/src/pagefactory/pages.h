#ifndef PAGES_H
#define PAGES_H
#include <QString>
namespace Pages {
    typedef enum {
      NOPAGE = -1,
      MAIN,
      SEEINGTOUCHING,
      CONNECTIVITY,
      SOUND,
      APPLICATION,
      REGIONALSETTING,
      ACCOUNTS,
      DEVICESYSTEM,
      APPLET,
      APPLETCATEGORY,
      RESETSETTINGS
   } Id;

   class Handle {
   public:
        Id id;
        QString param;
    };
};
#endif // PAGES_H

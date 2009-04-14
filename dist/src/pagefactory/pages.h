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
      APPLETFROMMOSTUSED,
      APPLETCATEGORY,
      RESETSETTINGS
   } Id;

   class Handle {
   public:
//        Handle(Id i, QString p="") {id=i;param=p;}
        Id id;
        QString param;
    };
};
#endif // PAGES_H

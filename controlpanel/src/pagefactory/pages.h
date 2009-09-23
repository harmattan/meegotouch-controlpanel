#ifndef PAGES_H
#define PAGES_H
#include <QString>

namespace Pages {
    typedef enum {
      NOPAGE = -1,
      MAIN,
      CATEGORY_PAGEID_START,  // ---
      LOOKANDFEEL,
      CONNECTIVITY,
      SOUND,
      REGIONALSETTING,
      DEVICEUTILITIES,
      ACCOUNTSANDAPPLICATIONS,
      DEVICESYSTEM,
      CATEGORY_PAGEID_END,    // ---
      APPLET,
      APPLETCATEGORY,
      PAGEID_COUNT
   } Id;

   class Handle {
   public:
//        Handle(Id i, QString p="") {id=i;param=p;}
        Id id;
        QString param;
    };
};
#endif // PAGES_H

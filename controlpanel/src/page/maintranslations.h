#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include <Pages>
#include <DuiLocale>

struct _DcpCategoryInfo
{
    const char* titleId;
    const char* titleDefault;
    const char* appletCategory;
    Pages::Id subPageId;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const char* settingsTitleId;
   extern const char* settingsTitleDefault;
   extern const char* mostRecentUsedTitleId;
   extern const char* mostRecentUsedTitleDefault;
   extern const char* quitMenuItemTextId;
   extern const char* quitMenuItemTextDefault;
};

#endif // MAINTRANSLATIONS_H



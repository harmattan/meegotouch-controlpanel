#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include <Pages>
#include <DuiLocale>

struct _DcpCategoryInfo
{
    const char* titleId;
    const char* appletCategory;
    PageHandle::PageTypeId subPageId;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const char* settingsTitleId;
   extern const char* mostRecentUsedTitleId;
   extern const char* quitMenuItemTextId;
};

#endif // MAINTRANSLATIONS_H



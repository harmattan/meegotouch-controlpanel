#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include "pages.h"

struct _DcpCategoryInfo
{
    QString title;
    QString description;
    QString appletCategory;
    Pages::Id subPageId;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const QString settingsTitle;
   extern const QString mostRecentUsedTitle;
   extern const QString quitMenuItemText;
};

#endif // MAINTRANSLATIONS_H



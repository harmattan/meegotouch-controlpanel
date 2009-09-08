#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include <Pages>

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



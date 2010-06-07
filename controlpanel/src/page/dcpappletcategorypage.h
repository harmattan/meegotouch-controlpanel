/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include <DcpPage>
#include <Pages>
#include "maintranslations.h"

class DcpAppletMetadata;
class DcpAppletButtons;

class DcpAppletCategoryPage :
        public DcpPage
{
    Q_OBJECT

public:
    DcpAppletCategoryPage (const DcpCategoryInfo *categoryInfo);
    virtual ~DcpAppletCategoryPage ();


    virtual void createContent ();
    const QString appletCategory () const;
    void setCategoryInfo (const DcpCategoryInfo *categoryInfo);

    virtual void reload();
    void setTitleId(const char* titleId);
    int appletCount();
    DcpAppletMetadata* appletMetadata(int i);

public slots:
    virtual void back();

protected:
    virtual void retranslateUi();

private:
    // the appletcategory that has already been
    // loaded. same as m_CategoryInfo->appletCategory if the
    // page's content is loaded
    QString m_LoadedAppletCategory;
    const DcpCategoryInfo  *m_CategoryInfo;
    const char* m_TitleId;
    DcpAppletButtons* m_Category;
    friend class Ut_DcpAppletCategoryPage;
};

#endif


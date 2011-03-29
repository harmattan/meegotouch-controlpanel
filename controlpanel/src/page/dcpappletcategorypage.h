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

#include "dcppage.h"
#include "pages.h"

class DcpAppletMetadata;
class DcpAppletButtons;
class Category;
class DcpMostUsed;

class DcpAppletCategoryPage : public DcpPage
{
    Q_OBJECT

public:
    DcpAppletCategoryPage (const Category *categoryInfo);
    virtual ~DcpAppletCategoryPage ();


    virtual void createContent ();
    const QString appletCategory () const;
    void setCategoryInfo (const Category *categoryInfo);

    int appletCount();
    DcpAppletMetadata* appletMetadata(int i);
    void setDelayedContent(bool);
    void createBody();

protected:
    virtual void retranslateUi();
    QGraphicsWidget* createCategories ();

protected slots:
    void onLoadingFinished ();

private slots:
    void mostUsedAppears ();

private:
    void addCategoryToLayoutOrdered (
                    QGraphicsLinearLayout* layout,
                    QGraphicsWidget* category,
                    QGraphicsWidget* appletBriefs);

    // the appletcategory that has already been
    // loaded. same as m_CategoryInfo->appletCategory if the
    // page's content is loaded
    QString m_LoadedAppletCategory;
    const Category *m_CategoryInfo;
    DcpAppletButtons* m_Category;
    DcpMostUsed *m_MostUsed;
    friend class Ut_DcpAppletCategoryPage;
    bool m_DelayedContent;
};

#endif


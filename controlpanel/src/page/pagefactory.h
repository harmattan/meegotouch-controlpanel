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

#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "pages.h"
#include <QObject>
#include <QList>
#include <QPointer>

class MApplicationPage;
class DcpPage;
class DcpAppletMetadata;
class DcpAppletObject;
class DcpMainPage;
class DcpAppletPage;
class DcpAppletCategoryPage;

/*!
 * Implements methods to create new views (pages), show views and change between
 * views.
 */
class PageFactory : public QObject
{
Q_OBJECT

public:
    static PageFactory *instance ();
    static void destroy();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage ();

public slots:
    void appletWantsToStart (int widgetId = -1);

    void changePage (const PageHandle &handle);

protected:
    PageFactory ();
    DcpPage* createMainPage ();
    DcpPage* createAppletPage(PageHandle& applet);
    DcpPage* createAppletCategoryPage (PageHandle::PageTypeId pageId);

private slots:
    void mainPageFirstShown (void);
    void pageChanged (MApplicationPage *page);

private:
    bool tryOpenPageBackward (const PageHandle &handle);
    void registerPage (DcpPage *page);

    static PageFactory     *sm_Instance;
    DcpMainPage            *m_MainPage;
    DcpAppletCategoryPage  *m_AppletCategoryPage;
    QPointer<DcpAppletPage> m_LastAppletPage;
    QList<MApplicationPage *> m_Pages;
    // for testability
    friend class Ut_PageFactory;
};

#endif


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
class DcpAppletPage;
class DcpAppletCategoryPage;
class DcpAppletLauncherIf;

/*!
 * Implements methods to create new views (pages), show views and change between
 * views.
 */
class PageFactory : public QObject
{
Q_OBJECT

public:
    ~PageFactory ();
    static PageFactory *instance ();
    static void setInProcessApplets (bool inProcess);;
    static void destroy();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage ();
    bool maybeRunOutOfProcess (const QString& appletName);

public slots:
    void appletWantsToStart (int widgetId = -1);

    bool changePage (const PageHandle &handle, bool dropOtherPages = false);
    bool changeToAppletPage (const QString& appletName);

    void onAppletLoaded (DcpAppletObject *applet);
    void preloadAppletLauncher ();
    void preloadBriefReceiver ();

protected:
    PageFactory ();
    DcpPage* createMainPage ();
    DcpPage* createAppletPage(PageHandle& applet);
    DcpPage* createAppletPage (DcpAppletMetadata* metadata);
    DcpPage* createAppletCategoryPage (const PageHandle& pageId);

private slots:
    void pageChanged (MApplicationPage *page);
    void onDisplayEntered ();
    void mainPageFirstShown ();

private:
    bool tryOpenPageBackward (const PageHandle &handle);
    void registerPage (DcpPage *page);

    static PageFactory     *sm_Instance;
    QPointer<DcpAppletPage> m_LastAppletPage;
    QList<MApplicationPage *> m_Pages;
    static DcpAppletLauncherIf *sm_AppletLauncher;

    // for testability
    friend class Ut_PageFactory;
};

#endif


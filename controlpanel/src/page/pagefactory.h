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
class MApplicationWindow;
class Category;

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
    static bool isInProcessApplets () { return sm_AppletLauncher == 0; }
    static void destroy();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage ();
    bool maybeRunOutOfProcess (const QString& appletName);
    MApplicationWindow* window ();
public slots:
    void appletWantsToStart (int widgetId = -1);

    void raiseMainWindow();
    bool changePage (const PageHandle &handle, bool dropOtherPages = false);
    bool changeToAppletPage (const QString& appletName);

    void onAppletLoaded (DcpAppletObject *applet);
    void preloadAppletLauncher ();
    void preloadBriefReceiver ();

signals:
    void resetAppletLauncherProcesses ();

protected:
    PageFactory ();
    DcpPage* createMainPage ();
    DcpAppletCategoryPage* createAppletCategoryPageIncomplete (
         const Category *);
    DcpPage* createAppletPage(PageHandle& applet);
    DcpPage* createAppletPage (DcpAppletMetadata* metadata);
    DcpPage* createAppletCategoryPage (const PageHandle& pageId);
    void appear (MApplicationPage* page);

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void pageChanged (MApplicationPage *page);
    void onDisplayEntered ();
    void mainPageFirstShown ();
    void completeCategoryPage ();
    void onMetadataLoaded ();

private:
    bool tryOpenPageBackward (const PageHandle &handle);
    void registerPage (DcpPage *page);
    void newWin ();
    bool isCurrentPage (const PageHandle &handle);
    void closeHelpPage();

    static PageFactory     *sm_Instance;
    QPointer<DcpAppletPage> m_LastAppletPage;
    QList<MApplicationPage *> m_Pages;
    static DcpAppletLauncherIf *sm_AppletLauncher;
    QPointer<MApplicationWindow> m_Win;
    /*! The page of which body needs to be created after the applets are
        registered */
    DcpAppletCategoryPage *m_PageWithDelayedContent;
    bool m_AppletsRegistered;

    // for testability
    friend class Ut_PageFactory;
};

#endif


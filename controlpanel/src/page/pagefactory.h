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
class MSceneWindow;
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
    static bool isInProcessApplets () { return sm_IsInProcessModeEnabled; }
    static void destroy();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage ();
    bool maybeRunOutOfProcess (const QString& appletName);
    MApplicationWindow* window ();
    bool hasPage () const;

public slots:
    void appletWantsToStart (int widgetId = -1);
    void enableUpdates(bool enable = true);

    void raiseMainWindow();
    bool changePage (const PageHandle &handle, bool dropOtherPages = false);
    bool changeToAppletPage (const QString& appletName);

    void onAppletLoaded (DcpAppletObject *applet);
    void preloadAppletLauncher ();
    void preloadBriefReceiver ();
    void preloadAppletPage ();

    void closeHelpPage();

signals:
    void resetAppletLauncherProcesses ();
    void windowShown ();

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
    bool popupSheetIfAny (const PageHandle& handle);

private slots:
    void completeCategoryPage ();
    void onMetadataLoaded ();

    void newMainPageInSeparateProcess ();
    void switchToMainPageWithPageDropping ();
    void destroyPageHistory ();
    void enablePageChange (bool enable = true);

private:
    bool tryOpenPageBackward (const PageHandle &handle);
    void registerPage (DcpPage *page);
    void newWin ();
    bool isCurrentPage (const PageHandle &handle);
    bool verifyAppletLauncherIsOk();

    QList< MSceneWindow * > pageHistory ();

    static PageFactory     *sm_Instance;
    QPointer<DcpAppletPage> m_LastAppletPage;

    DcpAppletLauncherIf *m_AppletLauncher;
    static bool sm_IsInProcessModeEnabled;

    QPointer<MApplicationWindow> m_Win;
    /*! The page of which body needs to be created after the applets are
        registered */
    DcpAppletCategoryPage *m_PageWithDelayedContent;
    bool m_AppletsRegistered;

    // for testability
    friend class Ut_PageFactory;

    enum StartupState {
        NothingStarted,
        BriefSupplierStarted
    } m_StartupState;

    bool m_PageChangeDisabled;
};

#endif


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

#include "mapplicationwindow-fake.h"
#include "mapplicationpage.h"
#include "mapplication.h"

#include <MSceneManager>

/*
 * See header on what this is about.
 */

MApplicationWindow::MApplicationWindow():
    MWindow(),
    m_CurrentPage(0)
{
}

MApplicationPage* MApplicationWindow::currentPage() const
{
    return m_CurrentPage;
}

void MApplicationWindow::setCurrentPage (MApplicationPage* page)
{
    m_CurrentPage = page;
    emit pageChanged(page);
}

void MWindow::raise() {
    m_IsRaised = true;
}

// this hack is to transfer the call to MWindow, because it is
// not a widget really in the tests
void QWidget::raise() {
    if ((void*)this == (void*)MApplication::activeApplicationWindow()) {
        MApplication::activeApplicationWindow()->raise();
    }
}

void MWindow::lower() {
    m_IsRaised = false;
}

bool MWindow::isRaised() {
    return m_IsRaised;
}

void MWindow::setPortraitOrientation()
{
}

void MWindow::setOrientationLocked(bool)
{
}

bool QWidget::close ()
{
    return true;
}

WId QWidget::winId () const
{
    return 0;
}

MSceneManager * MWindow::sceneManager () const
{
    static MSceneManager* manager = new MSceneManager (0,0);

    return manager;
}

MSceneManager * MWindow::sceneManager ()
{
    return ((const MWindow*) this)->sceneManager();
}

MSceneManager::MSceneManager (MScene *, QObject *parent):
    QObject (parent), d_ptr (0)
{
}

MSceneManager::~MSceneManager ()
{
}

void MSceneManager::appearSceneWindowNow (MSceneWindow *win, MSceneWindow::DeletionPolicy policy)
{
    win->appear ((MWindow*)0, policy);
}


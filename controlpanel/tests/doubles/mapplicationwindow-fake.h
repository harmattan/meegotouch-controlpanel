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

#ifndef MAPPLICATIONWINDOW_H
#define MAPPLICATIONWINDOW_H

#include <QObject>
#include "./mwindow-fake.h"

/* Fake MApplicationWindow
 *
 * Its purpose is to be able to avoid X usage when running unittests.
 *
 * ! Beware that this class is not a full replacement of M(Application)Window,
 * it works by avoiding to run its baseclass constructor (most specifically
 * QGraphicsView and QWidget), because they do not run without QApplication.
 *
 * How to use it:
 * - add the mapplicationwindow-fake.cpp to your SOURCES.
 * - extend with the functionalities you require :)
 */


class MApplicationPage;

class MApplicationWindow: public MWindow
{
    Q_OBJECT
public:
    MApplicationWindow();

    MApplicationPage* currentPage() const;
    void setCurrentPage(MApplicationPage* currentPage);

signals:
    void pageChanged(MApplicationPage *);

protected:
    MApplicationPage* m_CurrentPage;
};

#endif // MAPPLICATIONWINDOW_H


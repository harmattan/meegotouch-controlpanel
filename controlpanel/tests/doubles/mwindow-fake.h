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

#ifndef MWINDOW_H
#define MWINDOW_H

/* Fake MWindow
 *
 * See mapplicationwindow.h on details of how to use it.
 *
 */

class MWindow: public QObject {
    public:
        void raise();
        void lower();

        bool isRaised();

    private:
        bool m_IsRaised;
};

#endif // MWINDOW_H

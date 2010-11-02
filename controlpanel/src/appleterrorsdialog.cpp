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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"

#include <QGraphicsLinearLayout>
#include <MLabel>
#include <MApplication>
#include <MWindow>

static const QString 
description = "The following applets were disabled due to crash:";

AppletErrorsDialog::AppletErrorsDialog():
    MDialog ()
{
    // TODO: localization etc.
    setTitle ("Disabled applets"); 

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout (Qt::Vertical, centralWidget());

    MLabel* descLabel = new MLabel (description);
    descLabel->setWordWrap(true);
    layout->addItem(descLabel);

    const QSet<QString> badApplets = DcpWrongApplets::instance()->badApplets();
    foreach (QString badApplet, badApplets) {
        layout->addItem (new MLabel (badApplet));
    }
}

void 
AppletErrorsDialog::showAppletErrors()
{
    MWindow* window = MApplication::activeWindow();
    Q_ASSERT (window);
    if (!DcpWrongApplets::instance()->badApplets().isEmpty()) {
        (new AppletErrorsDialog)->appear(window,MSceneWindow::DestroyWhenDone);
    }
}


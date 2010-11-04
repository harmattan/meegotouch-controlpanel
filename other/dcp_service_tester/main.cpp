/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <DuiControlPanelIf>
#include <MDialog>
#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>

int main(int argc, char *argv[])
{
    bool gui = (argc == 3 && strcmp(argv[2],"win") == 0);
    if (gui) {
        new MApplication(argc, argv);
        MApplicationWindow* win = new MApplicationWindow();
        win->show();
        MApplicationPage* page = new MApplicationPage();
        page->appear(win);
        MDialog* dialog = new MDialog();
        dialog->addButton("start");
        dialog->exec();
    }

    // instantiate the interface
    DuiControlPanelIf* m_DcpIf = new DuiControlPanelIf();

    // check the interface is valid
    if (!m_DcpIf->isValid()) {
        qDebug() << "Err: Service unavailable";
        exit(1);
    }

    qDebug() << "Using service:" << m_DcpIf->serviceName();

    if (argc>1){
        QString page = argv[1];
        qDebug() << "Starting applet page" << page;
        qDebug() << m_DcpIf->appletPage(page);
    } else {
        qDebug() << "Starting main page";
        m_DcpIf->mainPage();
    }

    if (gui) {
        return qApp->exec();
    }
    return 0;
}


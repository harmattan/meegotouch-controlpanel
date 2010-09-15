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

#include <MApplicationIfProxy>
#include <MApplication>
#include <QDBusPendingReply>

const QString CONTROL_PANEL_SERVICE_NAME = "com.nokia.DuiControlPanel";

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    MApplicationIfProxy mApplicationIfProxy(CONTROL_PANEL_SERVICE_NAME, 0);

    if (mApplicationIfProxy.connection().isConnected()) {
        qWarning ("Should be working");
        QDBusPendingReply<> reply = mApplicationIfProxy.launch();
        reply.waitForFinished ();
        if (reply.isError()) {
            qWarning ("Error: %s", qPrintable(reply.error().message()));
        }
    } else {
        qWarning() << "Could not launch" << CONTROL_PANEL_SERVICE_NAME
                   << "- DBus not connected?";
    }
#if 1
    return 0;
#else
    return app.exec();
#endif
}



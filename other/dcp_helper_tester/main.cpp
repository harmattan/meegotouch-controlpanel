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

#include <QLocalSocket>
#include <QTextStream>
#include <QtDebug>

int main(int argc, const char** argv)
{
    QLocalSocket socket;
    socket.connectToServer ("dcpbriefs");
    qDebug () << "Connecting...";
    socket.waitForConnected ();

    QTextStream input (stdin);
    QString line;
    do {
        qDebug () << "?";
        line = input.readLine();
#if 0
        QString command = QString("watch %1\n").arg(line);
#else
        QString command = line;
#endif
        qDebug() << "<command>" << command << "...";
        socket.write (qPrintable(command));
        socket.waitForBytesWritten ();
#if 0
        qDebug() << "Waiting for read...";
        socket.waitForReadyRead ();
#endif
        qDebug() << "Response:";
        qDebug() << socket.readAll();
    } while (!line.isNull());
}


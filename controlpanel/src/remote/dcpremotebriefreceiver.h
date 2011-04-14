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

#ifndef DCPREMOTEBRIEFRECEIVER_H
#define DCPREMOTEBRIEFRECEIVER_H

#include <QProcess>
class DcpRemoteBrief;

class DcpRemoteBriefReceiver: public QProcess
{
    Q_OBJECT

public:
    static void setArguments (int argc, char** argv);
    static void disable ();
    static DcpRemoteBriefReceiver* instance ();
    static void destroy ();
    ~DcpRemoteBriefReceiver();

    void watch (DcpRemoteBrief* brief);
    int watchCount ();
    void unwatch (DcpRemoteBrief* brief);
    void switchToggle (const QString& appletName);
    void setValue(const QString& appletName, const QVariant& value);
    void preload (const QString& appletName);

signals:
    void firstConnected ();

protected slots:
    void onReadyRead ();
    void onFinished ( int exitCode, QProcess::ExitStatus exitStatus );
    void onConnected ();
    void onNewConnection ();

protected:
    void cmd (const QString& command, const QString& appletName);
    DcpRemoteBriefReceiver();
    void startProcess ();

private:
    class DcpRemoteBriefReceiverPriv* priv;
    void unregister (const QString& appletName);
    void createServer();
    void serverListen();
};


#endif // DCPREMOTEBRIEFRECEIVER_H


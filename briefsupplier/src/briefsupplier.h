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

#ifndef BRIEFSUPPLIER_H
#define BRIEFSUPPLIER_H

#include <QObject>

class DcpBrief;
class DcpAppletObject;
class QIODevice;

class BriefSupplier: public QObject
{
    Q_OBJECT

public:
    BriefSupplier(const QString &desktopDir = QString());
    ~BriefSupplier();

    void setIODevice (QIODevice* device);

protected slots:
    void onCommandArrival (const QString& command);
    void onBriefChanged ();
    void onLocaleChange ();
    void onConnectionDisconnected();

protected:
    // commands:
    void watch (const QString& appletName);
    void unwatch (const QString& appletName);
    void setValue (const QString& params);

    // output:
    void outputStart ();
    void outputEnd ();
    void output (const char* key, const QString& value, bool forced = false);
    void output (const char* key, int value);
    void outputBrief (DcpAppletObject* applet, bool textOnly = false);

private:
    class Stream* m_Stream;
};


#endif // BRIEFSUPPLIER_H


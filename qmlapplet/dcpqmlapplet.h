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

#ifndef DCPQMLAPPLET_H
#define DCPQMLAPPLET_H

#include <DcpAppletIf>
#include <QObject>
#include <QString>
#include <QList>
class DcpWidget;
class DcpQmlWidget;
class MAction;

class DcpQmlApplet: public QObject, public DcpAppletIf
{
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

public:
    DcpQmlApplet ();
    virtual void init();
    virtual DcpWidget* constructWidget(int widgetId);

    virtual QString title() const;
    virtual QVector<MAction *> viewMenuItems();
    virtual DcpBrief* constructBrief(int);
    virtual int partID(const QString& qmlPath);

    void requestPage (const QString& qmlPath);

    static DcpQmlApplet* instance();

    DcpQmlWidget* currentWidget() const { return m_CurrentWidget; }

private:
    QList<QString> m_QmlPaths;
    DcpQmlWidget* m_CurrentWidget;
    static DcpQmlApplet* sm_Applet;
};

#endif // DCPQMLAPPLET_H


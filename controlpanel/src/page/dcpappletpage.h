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

#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h"
#include "pages.h"

#include <QVector>

class DcpAppletWidget;
class DcpAppletObject;
class MLabel;
class MAction;

class DcpAppletPage : public DcpPage
{
    Q_OBJECT
    Q_PROPERTY(bool hasWidget READ hasWidget)

public:
    DcpAppletPage(DcpAppletObject *applet, int widgetId = -1);
    virtual ~DcpAppletPage();

    virtual void createContent ();

    bool hasError ();
    void setApplet (DcpAppletObject* applet, int widgetId = -1);
    bool hasWidget () const;
    int widgetId ();
    DcpAppletObject* applet();
    static DcpAppletWidget* constructAppletWidget (DcpAppletObject* applet,
                                             DcpPage* page, int widgetId);

    virtual bool preventQuit();

protected:
    virtual void retranslateUi ();

private:
    void loadWidget (int widgetId);
    void load ();

    DcpAppletObject   *m_Applet;
    int                m_WidgetId;
    DcpAppletWidget   *m_MainWidget;
    MLabel            *m_MissingLabel;

    friend class Ut_DcpAppletPage;
};

#endif


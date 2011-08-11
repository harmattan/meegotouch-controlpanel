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

#ifndef TOGGLEEXAMPLEBRIEF_H
#define TOGGLEEXAMPLEBRIEF_H

#include <DcpBrief>
#include <QVariant>

class ToggleExampleBrief: public DcpBrief
{
    Q_OBJECT
public:
    ToggleExampleBrief ();

    virtual QString valueText () const;
    virtual int widgetTypeID () const;
    virtual QVariant value () const;
    virtual void setValue (const QVariant& variant);

protected:
    virtual void timerEvent (QTimerEvent* event);

private:
    QVariant m_ToggleState;
    int m_Timer;
};

#endif // TOGGLEEXAMPLEBRIEF


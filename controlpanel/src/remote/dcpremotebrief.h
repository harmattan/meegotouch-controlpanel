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

#ifndef DCPREMOTEBRIEF_H
#define DCPREMOTEBRIEF_H

#include "dcpbrief.h"

class DcpRemoteBrief: public DcpBrief
{
    Q_OBJECT

public:
    DcpRemoteBrief(const QString& appletName, QObject* parent = 0);
    virtual ~DcpRemoteBrief();

    virtual int widgetTypeID() const;
    virtual QString valueText() const;
    virtual QString icon() const;
    virtual QString titleText() const;
    virtual QString helpId() const;
    virtual int minValue() const;
    virtual int maxValue() const;
    virtual QVariant value() const;
    virtual int sliderSteps() const;
    virtual void setValue(const QVariant& value);
    virtual QVariantList possibleValues () const;

    QString name () const;
    QString get (const char* id) const;
    void set (const char* id, const QString& value);
    void emitChange ();

private:
    class DcpRemoteBriefPriv* priv;
};


#endif // DCPREMOTEBRIEF_H


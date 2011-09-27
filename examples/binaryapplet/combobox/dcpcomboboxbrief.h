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

#ifndef COMBOBOXEXAMPLEBRIEF_H
#define COMBOBOXEXAMPLEBRIEF_H

#include <DcpBrief>

class ComboBoxExampleBrief: public DcpBrief
{
    Q_OBJECT
public:
    ComboBoxExampleBrief();
    virtual QString titleText() const;

    virtual QVariant value() const;
    virtual void setValue (const QVariant& newValue);
    virtual int widgetTypeID() const;

    virtual QVariantList possibleValues () const;

private:
    QString currentValueStr () const;

    int m_CurrentIndex;
    QVariantList m_PossibleValues;
};


#endif // COMBOBOXEXAMPLEBRIEF


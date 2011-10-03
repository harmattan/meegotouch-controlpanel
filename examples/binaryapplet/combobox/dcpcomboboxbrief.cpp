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

#include <DcpWidgetTypes>
#include "dcpcomboboxbrief.h"
#include <QTimer>

// #define VALUES_ALWAYS_CHANGE

ComboBoxExampleBrief::ComboBoxExampleBrief():
    m_CurrentIndex(-1)
{
    m_PossibleValues << QString("red") << QString("green") << QString ("blue")
                     << QString("Previous");

#ifdef VALUES_ALWAYS_CHANGE
    // tests if it is possible to change the value
    QTimer * timer = new QTimer (this);
    connect (timer, SIGNAL(timeout()), this, SLOT(nextValue()));
    timer->start (1000);
#endif
}

QString ComboBoxExampleBrief::currentValueStr () const
{
    QString currentValue;
    if (m_CurrentIndex < 0) {
        currentValue = "nothing";
    } else {
        currentValue = possibleValues().at(m_CurrentIndex).toString();
    }
    return currentValue;
}

QString ComboBoxExampleBrief::titleText() const
{
    return QString("ComboBox Example (%1 - %2)").arg (m_CurrentIndex)
           .arg (currentValueStr());
}

QVariant ComboBoxExampleBrief::value() const
{
    return m_CurrentIndex;
}

void ComboBoxExampleBrief::setValue (const QVariant& value)
{
    // we only update the current item if not previous was clicked:
    int lastIndex = m_PossibleValues.count()-1;
    if (value.toInt() != lastIndex) {
        m_CurrentIndex = value.toInt();

        // this demonstrates that the possible values list can change:
        // (the last item of the list is always changing)
        m_PossibleValues[lastIndex] =
            QString ("Previous (%1)").arg (currentValueStr());
    }

    // this is because we would like to update the title and list etc.:
    emit valuesChanged();
}

int ComboBoxExampleBrief::widgetTypeID() const
{
    return DcpWidgetType::ComboBox;
}

QVariantList ComboBoxExampleBrief::possibleValues () const
{
    return m_PossibleValues;
}

// this slot demonstrates that control panel reflects if the value
// changes. valuesChanged() signal has to be emitted, to notify control
// panel
void ComboBoxExampleBrief::nextValue ()
{
    setValue ((m_CurrentIndex+1) % 3);
}


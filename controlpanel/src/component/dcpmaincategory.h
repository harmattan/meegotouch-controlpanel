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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPMAINCATEGORY_H
#define DCPMAINCATEGORY_H

#include <QGraphicsLinearLayout>
#include <MSeparator>
#include <QGraphicsWidget>

/*!
 * A rectangular table like widget inside the main page and the category pages.
 */
class DcpMainCategory : public QGraphicsWidget
{
    Q_OBJECT

public:
    DcpMainCategory(QGraphicsWidget  *parent = 0);

    virtual void appendWidget (QGraphicsWidget *component);
    QGraphicsWidget* widgetAt (int i);
    int getItemCount () { return layout()->count(); };
    void deleteItems();

protected:
    QGraphicsLinearLayout* mLayout() const;

private:
    friend class Ut_DcpMainCategory;
};

inline QGraphicsLinearLayout*
DcpMainCategory::mLayout() const
{
    return (QGraphicsLinearLayout*)layout();
}

/*!
 * Appends a new item to the widget. Handles two column layout automatically.
 * There is no function to add a long line, but as I see we don't need that
 * feature right now. Anyway, it is easy to implement such a function.
 */
inline void
DcpMainCategory::appendWidget ( QGraphicsWidget *component)
{
    if (mLayout()->count() > 0) {
        MSeparator *sep = new MSeparator(this);
        sep->setStyleName("CommonHeaderDividerInverted");
        mLayout()->addItem (sep);
    }
    mLayout()->addItem (component);
}

#endif


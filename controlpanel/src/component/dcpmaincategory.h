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

#include "dcpcomponent.h"

class MLayout;

/*!
 * A rectangular table like widget inside the main page and the category pages.
 */
class DcpMainCategory : public /*DcpCategory*/ DcpComponent
{
    Q_OBJECT

public:
    DcpMainCategory(
            const QString    &title,
            QGraphicsWidget  *parent = 0,
            const QString    &logicalId = "");

    virtual void appendWidget (QGraphicsWidget *component);
    QGraphicsWidget* widgetAt (int i);
    virtual int  maxColumns ();
    virtual void setMaxColumns (int columns);
    MLayout* mLayout() const { return m_Layout; }

    void setHorizontalSpacing (int space);
    void setVerticalSpacing (int space);
    void setCreateSeparators (bool create = true);

    int getItemCount () { return m_ItemCount; };
    void deleteItems();

protected:
    virtual void createContents ();

    MLayout                    *m_Layout;
    class MGridLayoutPolicy    *m_LandscapeLayout;
    class MLinearLayoutPolicy  *m_PortraitLayout;

private:
    void appendSeparatorsIfNeeded ();
    void incrementRowAndCol ();

    int m_MaxColumns;

    /*
     * These will point to the first empty coordinate available for inserting a
     * new item.
     */
    int m_ColCount;
    int m_RowCount;
    /*
     * The number of real items added (not the separators).
     * FIXME: We can implement the whole stuff without this, can't we?
     */
    int m_ItemCount;

    bool m_CreateSeparators;
    static const QString sm_SeparatorObjectName;
    friend class Ut_DcpMainCategory;
};

#endif


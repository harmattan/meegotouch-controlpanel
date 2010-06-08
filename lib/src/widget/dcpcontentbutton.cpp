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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpcontentbutton.h"
#include "dcpcontentbutton_p.h"

#include "dcpdebug.h"


/* FIXME: this is a workaround against bug NB#170105 -
 * show/hideEvent of MContentButton does not get called
 *
 * Remove it once the bug is solved.
 */
#define NB170105


DcpContentButtonPrivate::DcpContentButtonPrivate ():
    m_Applet (0),
    m_Hidden (true)
{
}

/******************************************************************************
 * Stuff for the DcpContentButton class.
 */
DcpContentButton::DcpContentButton (
        DcpAppletObject *applet,
        QGraphicsItem   *parent):
    MButton ("...", parent),
    d_ptr (new DcpContentButtonPrivate)
{
    setApplet (applet);
}


DcpContentButton::~DcpContentButton ()
{
    delete d_ptr;
}


DcpAppletObject *
DcpContentButton::applet() const
{
    return d_ptr->m_Applet;
}

void
DcpContentButton::setApplet (DcpAppletObject *applet)
{
    d_ptr->m_Applet = applet;
    if (!d_ptr->m_Applet)
        return;

    connect (this, SIGNAL (clicked()),                                                         
             d_ptr->m_Applet, SLOT (slotClicked()));
    connect (d_ptr->m_Applet, SIGNAL (briefChanged ()), 
             this, SLOT (updateContents()));
    updateContents();
}

void
DcpContentButton::retranslateUi ()
{
    if (d_ptr->m_Applet) {
        updateText ();
    }
}


void
DcpContentButton::updateText ()
{
    setText(applet()->text2());
    qDebug() << applet()->text2();
}


/*
 * updates all displayed datas if something changes in the brief / desktop file
 */
void
DcpContentButton::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    updateText();
}


void
DcpContentButton::showEvent (QShowEvent * event)
{
#       ifndef NB170105
    if (d_ptr->m_Hidden) {
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        if (d_ptr->m_Applet)
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()), 
                this, SLOT (updateContents()));

        updateContents();
    }
#       endif // NB170105
    MButton::showEvent(event);
}

void
DcpContentButton::hideEvent (QHideEvent * event)
{
#       ifndef NB170105
    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()),
                this, SLOT (updateContents()));
    }
#       endif // NB170105
    MButton::hideEvent(event);
}

void DcpContentButton::setMattiID (const QString& mattid)
{
    d_ptr->m_MattiID = mattid;
}

QString DcpContentButton::mattiID () const
{
    return d_ptr->m_MattiID;
}


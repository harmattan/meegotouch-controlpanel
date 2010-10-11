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
#include "dcpappletdb.h"


DcpContentButtonPrivate::DcpContentButtonPrivate ():
    m_Applet (0),
    m_Metadata (0),
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
    connect (this, SIGNAL (clicked()),
             this, SLOT (onClicked()));

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
    // currently the button only supports setting the applet once, but
    // we do not use this anyway again
    Q_ASSERT (!d_ptr->m_Applet);

    d_ptr->m_Applet = applet;
    d_ptr->m_Metadata = applet ? applet->metadata() : 0;
    if (!d_ptr->m_Applet)
        return;

    // we only update if we are visible, since showEvent also updates
    if (isVisible()) {
        updateContents ();
        connect (d_ptr->m_Applet, SIGNAL (briefChanged ()),
                 this, SLOT (updateContents()));
    }
}

void
DcpContentButton::retranslateUi ()
{
    if (metadata()) {
        updateText ();
    }
}


void
DcpContentButton::updateText ()
{
    QString text = applet() ? applet()->text2() :
                   metadata () ? metadata()->text2() : "...";
    setText(text);
}


/*
 * updates all displayed datas if something changes in the brief / desktop file
 */
void
DcpContentButton::updateContents ()
{
    if (!metadata())
        return;

    updateText();
}


void
DcpContentButton::showEvent (QShowEvent * event)
{
    if (d_ptr->m_Hidden) {
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        if (d_ptr->m_Applet) {
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()),
                     this, SLOT (updateContents()));
        }

        updateContents();
    }
    MButton::showEvent(event);
}

void
DcpContentButton::hideEvent (QHideEvent * event)
{
    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()),
                this, SLOT (updateContents()));
    }
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

void DcpContentButton::setMetadata(DcpAppletMetadata* metadata)
{
    // only supports setting this once for now
    Q_ASSERT (!d_ptr->m_Metadata);
    Q_ASSERT (!d_ptr->m_Applet);

    d_ptr->m_Metadata = metadata;

    if (metadata) {
        // we only update if we are visible, since showEvent also updates
        if (isVisible()) {
            updateContents ();
        }
    }
}

DcpAppletMetadata* DcpContentButton::metadata()
{
    return d_ptr->m_Metadata;
}

void DcpContentButton::loadApplet()
{
    // do nothing if the metadata is already loaded:
    if (applet()) return;

    // do nothing if there is no metadata
    if (!metadata()) return;

    // load the applet:
    setApplet (DcpAppletDb::instance()->applet (metadata()->name()));
}

void DcpContentButton::onClicked ()
{
    if (!applet()) return;
    applet ()->setToggle (!applet ()->toggle());
}


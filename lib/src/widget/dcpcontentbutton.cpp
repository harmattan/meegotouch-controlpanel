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
    setStyleName("CommonSingleButtonInverted");

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
    dcp_failfunc_unless (!d_ptr->m_Applet);

    d_ptr->m_Applet = applet;
    d_ptr->m_Metadata = applet ? applet->metadata() : 0;

    if (applet) {
        connect (applet, SIGNAL (briefChanged ()),
                 this, SLOT (updateContents()));
    }
    updateContents ();
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
    QString text = applet() ? applet()->text1() :
                   metadata () ? metadata()->text1() : "...";
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

    if (applet() && applet()->brief()) {
        if (!isCheckable()) setCheckable (true);
        setChecked (applet()->value().toBool());
    }
}


void
DcpContentButton::showEvent (QShowEvent * event)
{
    MButton::showEvent(event);
}

void
DcpContentButton::hideEvent (QHideEvent * event)
{
    MButton::hideEvent(event);
}

void DcpContentButton::setMattiID (const QString& mattid)
{
    d_ptr->m_TDriverID = mattid;
}

QString DcpContentButton::mattiID () const
{
    return d_ptr->m_TDriverID;
}

void DcpContentButton::setTDriverID (const QString& tdriverid)
{
    d_ptr->m_TDriverID = tdriverid;
}

QString DcpContentButton::TDriverID () const
{
    return d_ptr->m_TDriverID;
}

void DcpContentButton::setMetadata (DcpAppletMetadata* metadata)
{
    // only supports setting this once for now
    dcp_failfunc_unless (!d_ptr->m_Metadata);
    dcp_failfunc_unless (!d_ptr->m_Applet);

    d_ptr->m_Metadata = metadata;

    if (metadata) {
        updateContents ();
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

    if (!applet()->brief()) {
        // if we only have an external command, we do not toggle, but invoke
        if (metadata() && metadata()->hasApplicationCommand()) {
            applet()->slotClicked ();
        }
    } else {
        // for a binary applet we toggle
        applet ()->setValue (!applet ()->value().toBool());
    }
}


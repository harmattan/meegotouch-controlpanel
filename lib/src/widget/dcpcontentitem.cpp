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

#include "dcpcontentitem.h"
#include "dcpcontentitem_p.h"

#include "dcpdebug.h"


DcpContentItemPrivate::DcpContentItemPrivate ():
    m_Applet (0),
    m_WidgetTypeId (DcpWidgetType::Label),
    m_Hidden (true)
{
}

/******************************************************************************
 * Stuff for the DcpContentItem class.
 */
DcpContentItem::DcpContentItem (
        DcpAppletObject *applet,
        QGraphicsItem   *parent):
    MContentItem (MContentItem::IconAndTwoTextLabels, parent),
    d_ptr (new DcpContentItemPrivate)
{
    setApplet (applet);
}


DcpContentItem::~DcpContentItem ()
{
    releaseImage();
    delete d_ptr;
}


static MContentItem::ContentItemStyle invertTwoLineMode (
        const MContentItem::ContentItemStyle& styl)
{
    MContentItem::ContentItemStyle newstyl;
    switch (styl) {
        case MContentItem::IconAndTwoTextLabels:
            newstyl = MContentItem::IconAndSingleTextLabel;
            break;
        case MContentItem::SingleTextLabel:
            newstyl = MContentItem::TwoTextLabels;
            break;
        case MContentItem::IconAndSingleTextLabel:
            newstyl = MContentItem::IconAndTwoTextLabels;
            break;
        case MContentItem::TwoTextLabels:
            newstyl = MContentItem::SingleTextLabel;
            break;
        case MContentItem::IconAndSingleTextLabelVertical:
            newstyl = MContentItem::IconAndTwoTextLabelsVertical;
            break;
        case MContentItem::IconAndTwoTextLabelsVertical:
            newstyl = MContentItem::IconAndSingleTextLabelVertical;
            break;
        default:
            return styl; // do nothing bad at least :)
    }
    return newstyl;
}


/*
 * Constructs the content of the DcpContentItem according to the widget type.
 * This is a separate code so the inherited classes might use other code,
 * possibly without any information about the applet variant. This way we can
 * implement internal brief widgets also.
 */
void
DcpContentItem::constructRealWidget ()
{
    d_ptr->m_WidgetTypeId = d_ptr->m_Applet->widgetTypeID();
    MContentItem::ContentItemStyle styl;
    switch (d_ptr->m_WidgetTypeId) {
        case DcpWidgetType::Image:
            DCP_DEBUG ("### DcpWidgetType::Image ###");
            styl = IconAndSingleTextLabel;
            break;

        case DcpWidgetType::Toggle:
            qWarning("Support for toggle type as briefwidget was removed from "
                     "controlpanel according to the latest specifications (%s)",
                     qPrintable(applet()->metadata()->name()));
        default:
            DCP_DEBUG ("### DcpWidgetType::Label ###");
            styl = SingleTextLabel;
            break;
    }

    if (!d_ptr->m_Applet->text2().isEmpty()) {
        styl = ::invertTwoLineMode (styl);
    }
    model()->setItemStyle(styl);
}

DcpAppletObject *
DcpContentItem::applet() const
{
    return d_ptr->m_Applet;
}

void
DcpContentItem::setApplet (DcpAppletObject *applet)
{
    /*
     * If we had an old applet object.
     */
    if (d_ptr->m_Applet) {
        /*
         * Metadata is owned by the appletdb, so not removed, only disconnected
         * both ways, but only the signals between the two participants.
         */
        disconnect (d_ptr->m_Applet, 0, this, 0);
        disconnect (this, 0, d_ptr->m_Applet, 0);
    }

    d_ptr->m_Applet = applet;

    /*
     * If we have a applet object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (d_ptr->m_Applet) {
        constructRealWidget ();
        /*
         * This will count the activations and activate the applet.
         */
        connect (this, SIGNAL (clicked()),
                d_ptr->m_Applet, SLOT (slotClicked()));
    }
}

void
DcpContentItem::retranslateUi ()
{
    if (d_ptr->m_Applet) {
        updateText ();
    }
}

/*
 * this function is a helper, it switches from two-line-mode into one-line-mode
 * and back
 */
void
DcpContentItem::invertTwoLineMode()
{
    MContentItem::ContentItemStyle newstyl =
        ::invertTwoLineMode ((MContentItem::ContentItemStyle)model()->itemStyle());
    model()->setItemStyle(newstyl);
}

void
DcpContentItem::updateText ()
{
    // --------- label specific ------------
    QString text2 = applet()->text2();
    /*
     * if emptyness of text2 changes, we will have to switch from twolinemode,
     * so that the labels remains centered
     *
     * FIXME: this is not working, the first time determines which mode the
     * item will be in, because the widget sizes are set up at setupModel time
     * only, so currently MContentItem only supports changing the value at
     * construction time (bug/feature request to libdui if it is important)
    if (text2.isEmpty() != subtitle().isEmpty()) {
        invertTwoLineMode();
    }
     */
    setTitle (applet()->text1());
    setSubtitle (text2);
}


void DcpContentItem::updateImage ()
{
    // ----------- image specific: -------------
    if (d_ptr->m_WidgetTypeId == DcpWidgetType::Image) {
        QString   source;

        /*
         * If the applet provides an image file name we set the image from that,
         * otherwise we try to set the image from the icon name.
         *
         * TODO we should clean this up. Is there a difference, or we just
         * keeping it for compatibility?
         */
        source = d_ptr->m_Applet->imageName();
        if (source.isEmpty()) {
            source = d_ptr->m_Applet->iconName();
        }

        /*
         * The image file might be big, so we need a little speed up here, otherwise
         * the paging effect is blocked when we go back to the main page.
         */
        if (source == d_ptr->m_ImageName)
            return;

        /* we release the original pixmap, if any */
        releaseImage();

        // no picture :(
        if (source.isEmpty()) return;

        // if it is a filepath, it has an extension, otherwise we have an id
        if (!source.contains('.')) {
            setImageName (source);
        } else {
            setImageFromFile (source);
        }

        d_ptr->m_ImageName = source;
    }
}

/*
 * updates all displayed datas if something changes in the brief / desktop file
 */
void
DcpContentItem::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    updateText();
    updateImage();
}

/*!
 * releases the cached image if any
 */
void
DcpContentItem::releaseImage ()
{
}


/*!
 * sets the image with the given name (id)
 */
void
DcpContentItem::setImageName (const QString& name)
{
    setImageID (name);
}

/*!
 * sets the image based on its filepath
 */
void
DcpContentItem::setImageFromFile (const QString& fileName)
{
    bool    success;
    QImage  image;

    success = image.load (fileName);
    if (!success) {
        DCP_WARNING ("The image was not loaded from %s", DCP_STR(fileName));
        return;
    }

    setImage (image);
}

void
DcpContentItem::showEvent (QShowEvent * event)
{
    if (d_ptr->m_Hidden) {
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        if (d_ptr->m_Applet)
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()), 
                this, SLOT (updateContents()));

        updateContents();
    }
    MContentItem::showEvent(event);
}

void
DcpContentItem::hideEvent (QHideEvent * event)
{
    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()),
                this, SLOT (updateContents()));
    }
    MContentItem::hideEvent(event);
}

void DcpContentItem::setMattiID (const QString& mattid)
{
    d_ptr->m_MattiID = mattid;
}

QString DcpContentItem::mattiID () const
{
    return d_ptr->m_MattiID;
}


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
#ifndef DCPCONTENTBUTTON_H
#define DCPCONTENTBUTTON_H

#include <MButton>

class DcpAppletObject;
class DcpAppletMetadata;
class QShowEvent;
class QHideEvent;
class DcpContentButtonPrivate;

/*!
 * \brief An activatable entry in the control panel.
 *
 * This class implements the brief view of an applet shown on the screen
 * in applet lists.
 *
 * It has a #DcpAppletObject associated with it, so when the user clicks
 * on the widget the applet variant is activated. The widget connects its
 * clicked() signal to the activate() signal of the #DcpAppletObject object,
 * so the applet variant will be started when the widget is clicked.
 *
 * The widget updates its contents automatically if the applet notifies it
 * about the changes, see DcpBrief::valuesChanged().
 *
 */
class DcpContentButton: public MButton
{
    Q_OBJECT

    //! @cond
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)
    Q_PROPERTY (QString TDriverID READ TDriverID WRITE setTDriverID)
    //! @endcond

public:
    /*! \brief Constructor.
     *
     * If you do not set an applet here, be sure to do that before the widget
     * gets shown on the screen. See #setApplet().
     */
    DcpContentButton (
            DcpAppletObject *applet = 0,
            QGraphicsItem *parent = 0);

    ~DcpContentButton ();

    /*! \brief Sets the applet the DcpContentItem should handle.
     *
     * Currently you can only call it before the ContentItem is popped up,
     * due to limitations of MContentItem.
     */
    void setApplet (DcpAppletObject *applet);

    void setMetadata (DcpAppletMetadata *metadata);
    DcpAppletMetadata *metadata();
    void loadApplet();

    /*! \brief Returns the applet the DcpContentButton represents */
    DcpAppletObject *applet () const;

    //! @cond
    void setMattiID (const QString& mattid);
    QString mattiID () const;
    void setTDriverID (const QString& tdriverid);
    QString TDriverID () const;
    //! @endcond

protected slots:
    /*! \brief Make the object update according to the values the applet returns
     *
     * It is connected on the DcpBrief::valuesChanged() signal if any.
     */
    void updateContents ();
    void onClicked ();

protected:
    virtual void retranslateUi ();
    virtual void showEvent (QShowEvent *event);
    virtual void hideEvent (QHideEvent *event);

    /*! \brief Updates all texts according to the values the applet returns */
    void updateText ();
private:
    DcpContentButtonPrivate* const d_ptr;

    friend class Ut_DcpContentButton;
};


#endif


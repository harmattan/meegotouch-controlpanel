/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of mcontrolpanel.
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
#ifndef DCPCONTENTITEM_H
#define DCPCONTENTITEM_H

#include <MListItem>

class DcpAppletObject;
class DcpAppletMetadata;
class DcpContentItemPrivate;
class MLayout;
class MGridLayoutPolicy;
class QGraphicsGridLayout;

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
class DcpContentItem: public MListItem
{
    Q_OBJECT

    // some readonly properties, can be used for tdriver tests
    Q_PROPERTY (QString title READ title)
    Q_PROPERTY (QString subtitle READ subtitle)
    Q_PROPERTY (bool checked READ isChecked)
    Q_PROPERTY (int widgetType READ widgetType)
    Q_PROPERTY (QString imageID READ imageID)

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
    DcpContentItem (
            DcpAppletObject *applet = 0,
            QGraphicsItem *parent = 0);

    ~DcpContentItem ();

    /*! \brief Sets the applet the DcpContentItem should handle.
     *
     * Currently you can only call it before the ContentItem is popped up,
     * due to limitations of MContentItem.
     */
    void setApplet (DcpAppletObject *applet);
    void setMetadata (DcpAppletMetadata *metadata);

    /*! \brief Returns the applet the DcpContentItem visualizes. */
    DcpAppletObject *applet () const;
    DcpAppletMetadata *metadata () const;

    void loadApplet();

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

    /*! Sets up the contentitem according to the values the applet provides:
     * widgettype, texts, icons etc. */
    virtual void constructRealWidget ();

    /*! \brief Updates all texts according to the values the applet returns */
    void updateText ();

    /*! \brief Updates the picture according to what the applet returns */
    void updateImage ();

    // image related things:
    void setImageFromFile (const QString& fileName);
    void setImageName (const QString& name);

    // getters about applet properties:
    int widgetType() const;
    bool hasTwoTextLines() const;
    bool isChecked() const;
    QString title() const;
    QString subtitle() const;
    QString imageID() const;
    QString helpID() const;

private:
    // creating widgets, layouts:
    void ensureLayoutIsCreated(QGraphicsGridLayout*& layout);
    void ensureImageIsCreated();
    void ensureToggleIsCreated();
    void ensureTextsAreCreated();
    void ensureWidgetsAreLayouted();
    void ensureHelpIsCreated();
    void clearAppletData();

    DcpContentItemPrivate* const d_ptr;

    friend class Ut_DcpContentItem;
};


#endif



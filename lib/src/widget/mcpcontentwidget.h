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
#ifndef MCPCONTENTWIDGET_H
#define MCPCONTENTWIDGET_H

#include <MListItem>

class DcpAppletObject;
class QShowEvent;
class QHideEvent;
class McpContentWidgetPrivate;
class MLayout;
class MGridLayoutPolicy;

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
class McpContentWidget: public MListItem
{
    Q_OBJECT

    // some readonly properties, can be used for matti tests
    Q_PROPERTY (QString title READ title)
    Q_PROPERTY (QString subtitle READ subtitle)
    Q_PROPERTY (QString checked READ isChecked)
    Q_PROPERTY (QString widgetType READ widgetType)
    Q_PROPERTY (QString imageID READ imageID)

    //! @cond
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)
    //! @endcond

public:
    /*! \brief Constructor.
     *
     * If you do not set an applet here, be sure to do that before the widget
     * gets shown on the screen. See #setApplet().
     */
    McpContentWidget (
            DcpAppletObject *applet = 0,
            QGraphicsItem *parent = 0);

    ~McpContentWidget ();

    /*! \brief Sets the applet the McpContentWidget should handle.
     *
     * Currently you can only call it before the ContentItem is popped up,
     * due to limitations of MContentItem.
     */
    void setApplet (DcpAppletObject *applet);

    /*! \brief Returns the applet the McpContentWidget visualizes. */
    DcpAppletObject *applet () const;

    //! @cond
    void setMattiID (const QString& mattid);
    QString mattiID () const;
    //! @endcond

protected slots:
    /*! \brief Make the object update according to the values the applet returns
     *
     * It is connected on the DcpBrief::valuesChanged() signal if any.
     */
    void updateContents ();

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

private:
    // creating widgets, layouts:
    void ensureLayoutIsCreated(MLayout*& layout, MGridLayoutPolicy*& grid);
    void ensureImageIsCreated();
    void ensureToggleIsCreated();
    void ensureTextsAreCreated();
    void ensureWidgetsAreLayouted();

    McpContentWidgetPrivate* const d_ptr;

    friend class Ut_McpContentWidget;
};


#endif



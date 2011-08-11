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

#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <MWidget>

class DcpWidgetPrivate;

/*!
 * \class DcpWidget
 * \details The base class for applet view
 *
 * The control panel applets usually have one or more views containing the
 * actual GUI of the applet. The DcpWidget is the base class for these views
 * (sometimes called pages).
 */

class DcpWidget: public MWidget 
{
    Q_OBJECT

public:
    DcpWidget (QGraphicsWidget *parent = 0);
    virtual ~DcpWidget();

    virtual void setReferer (int widgetId);

    virtual bool back ();
    virtual bool pagePans () const;

    int getWidgetId ();
    bool setWidgetId (int widgetId);

    /*!
     * \brief Enables displaying a title automatically by control panel.
     *
     * Must be set during widget constructor, otherwise control panel will
     * not care about its value.
     *
     * Default is false in which case control panel will not display the
     * applet's title, the applet has to take care of that.
     */
    void enableAutoTitle (bool enable = true);

    /*! \brief Returns if the widget would like control panel to display its title.
     *
     * If false, it means the applet would like to display its title on its own,
     * if true, control panel should display the title the common way.
     *
     * \sa enableAutoTitle()
     */
    bool isAutoTitleEnabled () const;

signals:
    /*!
     * \brief Emitted when the windget change is requested
     * \param widgetId the id of the requested widget instead of this one.
     * \details change can be requested by pressing a button on the widget, 
     *   for example.
     *
     * In that case, this signal is handled by DcpAppletPage: it destroys this
     * widget and creates and shows the new one at the given widgetId.
     */
    void changeWidget (int widgetId);

    /*!
     * \brief Should be activated to request the activation of an applet
     * \param appletName The name of the applet that should be activated
     * \returns true if the applet could be found
     *
     * This signal should be emitted by the plugin when the activation of an
     * other applet is requested. 
     */
    bool activatePluginByName (const QString &appletName) const;

private:
    DcpWidgetPrivate* const d_ptr;
    Q_DISABLE_COPY(DcpWidget);
    friend class Ut_DcpWidget;
signals:
    /*!
     * \brief Should be emitted when duicontrolpanel should close the page
     * for you
     */
    void closePage();

public:
    /*!
     * \brief Specifies the title for the page where the widget is put.
     *
     * Redefine this function to provide a title for a page of the applet.
     * If you do not need separate titles for different pages, you can
     * leave this default, and then all titles of the pages will be the
     * Name of the applet specified in the applet's desktop file.
     */
    virtual QString title() const;

public slots:
    /*!
     * \brief Show a progress indicator
     *
     * With this function the widget can show a progress indicator
     * indicating that a longer operation is running.
     * Same as calling MApplicationPage::setProgressIndicatorVisible.
     *
     * \param visible   If true, the progress indicator becomes visible.
     *                  If false, it will become hidden.
     */
    void setProgressIndicatorVisible (bool visible);

public:
    bool isProgressIndicatorVisible () const;

signals:
    /*!
     * \brief Emitted when #setProgressIndicatorVisible gets called
     *
     * \param isInProgress If true, the progress indicator becomes visible.
     *                     If false, it will become hidden.
     */
    void inProgress (bool isInProgress);
};

#endif


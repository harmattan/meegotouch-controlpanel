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

#ifndef DCPAPPLETIF_H
#define DCPAPPLETIF_H

#include <QtPlugin>

class DcpWidget;
class DcpStylableWidget;
class MAction;
class DcpBrief;
class MSheet;

/*!
 * \brief Applet interface for DuiControlPanel applets.
 *
 * The class implements the basic communication API between the DuiControlPanel
 * and the control panel applet. 
 */
class DcpAppletIf 
{
public:
    virtual ~DcpAppletIf() {}
    /*!
     * \brief Initializes applet right after loading it 
     * \param part The part name of the applet, if it implements more dialogs or
     *   views (parts) and it needs only one part
     */ 
    virtual void init () {}
    
    /*! 
     * \brief Contstructs the widget specified by widgetId that the applet
     *   provides
     * \param widgetId the Id of the widget implemented by the applet that we
     *   want to show. This widget is usually a container or a dialog
     *
     * \details The "entrance" widget (that is displayed on first page) will be
     *   queried with 0 id. Further applet pages can be requested through the
     *   DcpWidget::changeWidget signal.
     */
#   ifdef DCP_DISABLE_DEPRECATION_WARNING
    virtual DcpWidget *constructWidget (int widgetId) {
#   else
    virtual DcpWidget* Q_DECL_DEPRECATED constructWidget (int widgetId) {
#   endif
            Q_UNUSED (widgetId); return 0;
    }

    /*!
     * \brief Title of the applet that displayed in title row of applet page
     * \return A title which is displayed in title row of page. It can vary by
     *   each widget
     *
     *   This function is DEPRECATED and will be removed in near future. Please
     *   use DcpBrief::title() and DcpWidget::title() instead.
     */
#   ifdef DCP_DISABLE_DEPRECATION_WARNING
    virtual QString title () const { return QString(); }
#   else
    virtual QString Q_DECL_DEPRECATED title () const { return QString(); }
#   endif

    /*!
     * \brief Menu items that applet can provide in the main menu of the 
     *   applet page
     */
    virtual QVector <MAction *> viewMenuItems () = 0;

    /*!
     * \brief The Brief view of the applet
     * \detais Brief widget is the button-look on category pages of
     *   DuiControlpanel It displays the applet name and the current value.
     *   Value must be provided and formatted by the applet implementation.
     *   Clicking on the widget displays the applet itself.
     */
    virtual DcpBrief *constructBrief (int partId = 0) {
        Q_UNUSED (partId);
        return 0;
    }

    /*!
     * Translates Part strings which are present in the desktop file of the 
     * applet into part ids, which are used when requesting a page from the
     * applet. 
     */
    virtual int partID (const QString& partStr) { Q_UNUSED(partStr); return 0; }

    /*!
     * Control panel uses this function to determine with which version of
     * the interface the plugin was compiled with. It lets controlpanel
     * extend the interface without the need to recompile all applets.
     */
    virtual int interfaceVersion() { return 9; }

    /*!
     * \brief Contstructs the widget specified by widgetId that the applet
     *   provides
     * \param widgetId the Id of the widget implemented by the applet that we
     *   want to show. This widget is usually a container or a dialog
     *
     * \details The "entrance" widget (that is displayed on first page) will be
     *   queried with 0 id. Further applet pages can be requested through the
     *   DcpWidget::changeWidget signal.
     *
     * This is the same as the constructWidget() call, but gives back an
     * MStylableWidget instead of an MWidget which can be necessery in case
     * of using themes (.css files).
     */
    virtual DcpStylableWidget *constructStylableWidget (int widgetId) {
        Q_UNUSED (widgetId);
        return 0;
    }

    virtual MSheet *constructSheet (int widgetId) {
        Q_UNUSED (widgetId);
        return 0;
    }
};

Q_DECLARE_INTERFACE (DcpAppletIf, "com.nokia.m.core.DcpAppletIf/1.0")

#endif


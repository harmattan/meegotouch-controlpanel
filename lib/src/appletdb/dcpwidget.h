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
};

#endif


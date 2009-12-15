/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <DuiWidget>
/*!
 * \class DcpWidget
 * \details The base class for applet view
 * 
 * The control panel applets usually have one or more views containing the
 * actual GUI of the applet. The DcpWidget is the base class for these views.
 *
 * TODO: 
 *  1) To implement multi-view support.
 *  2) This is a public header, it should not contain elements that are subject
 *     of change, like inline functions and class members.
 *  3) This widget does not know its own ID!
 */
class QGraphicsWidget;
class DuiDialog;

class DcpWidget: public DuiWidget 
{
    Q_OBJECT

public:
    DcpWidget (QGraphicsWidget *parent=0);
    virtual ~DcpWidget();

    virtual void setReferer (int widgetId);
    int referer();
    
    virtual bool back();
    virtual bool pagePans() const;

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
     * \param name The name of the applet that should be activated
     *
     * This signal should be emitted by the plugin when the activation of an
     * other applet is requested. 
     */
    bool activatePluginByName (int widgetId, const QString &name) const;

private:
    int m_Referer;
};

#endif // DCPWIDGET_H


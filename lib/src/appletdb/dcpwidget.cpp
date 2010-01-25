/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpwidget.h"
#include "dcpwidget_p.h"

//#define DEBUG
#include "dcpdebug.h"


DcpWidgetPrivate::DcpWidgetPrivate ():
    m_Referer (-1),
    m_WidgetId (-1)
{
}


/*!
 * \brief The constructor. No referer for default
 */
DcpWidget::DcpWidget (QGraphicsWidget *parent) 
    : DuiWidget (parent), 
      d_ptr (new DcpWidgetPrivate)
{
    DCP_DEBUG ("*** this = %p", this);
}

DcpWidget::~DcpWidget ()
{
    DCP_DEBUG ("*** this = %p", this);
    delete d_ptr;
}


/*!
 *
 * Returns the widgetId for the DcpWidget object.
 */
int 
DcpWidget::getWidgetId ()
{
    return d_ptr->m_WidgetId;
}

/*!
 * \brief Sets the widgetId and returns true if the ID could be set.
 *
 * Sets the widgetId for the DcpWidget class widget. The WidgetId is set by the
 * controlpanel, and should not changed by the cp applet. Once the widgetId is
 * set it can not be changed.
 */
bool 
DcpWidget::setWidgetId (
        int widgetId)
{
    DCP_DEBUG ("*** this       = %p", this);
    DCP_DEBUG ("*** widgetId   = %d", widgetId);
    DCP_DEBUG ("*** m_WidgetId = %d", d_ptr->m_WidgetId);

    if (d_ptr->m_WidgetId != -1) {
        DCP_WARNING ("The widgetId already set.");
        return false;
    }

    if (widgetId < 0) {
        DCP_CRITICAL ("The widgetId should be >= 0.");
    }

    d_ptr->m_WidgetId = widgetId;
    return true;
}

/*! 
 * \brief Sets the referer for the widget
 * \param widgetId the id of a DcpWidget to switch back to.
 */
void
DcpWidget::setReferer (
        int widgetId)
{
    d_ptr->m_Referer = widgetId;
}
    
/*! 
 * \return the referer id of the widget
 */
int 
DcpWidget::referer () 
{
    return d_ptr->m_Referer;
}

/*!
 * \brief This method is called when user press 'Back' in an applet page
 * \return true if back closes the applet and true if a referer widget
 *      should be shown
 *
 */
bool 
DcpWidget::back () 
{
    if (referer() > -1) {
        // emit the changewidget signal if there is a referer set
        emit changeWidget(referer());
        return false;
    } else {
        // back is handled by main window by default
        return true; 
    }
}

/*!
 * The pannable area for the entire view (page) will be enabled if this function
 * returns true. The default implementation of the function returns true, so the
 * pannable area will be enabled.
 */
bool 
DcpWidget::pagePans () const 
{
    return true; 
}

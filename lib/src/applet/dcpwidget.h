#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <DuiWidget>
/*!
    \class DcpWidget
    \details This widget is the base of all widgets of an applet, that act like a page
    As an applet is one page, "multi-paged" applets can be implemented as replacing
    main widgets on the only page as needed.
    Each widget needs a referer, when back button clicked, which widget to "swich back"
*/
class QGraphicsWidget;
class DuiDialog;
class DcpWidget: public DuiWidget {
    Q_OBJECT
public:
    /*! \brief The constructor. No referer for default*/
    DcpWidget(QGraphicsWidget *parent=0) : DuiWidget(parent), m_Referer(-1){}
    virtual ~DcpWidget(){}
    /*! \brief Sets the referer for the widget
        \param widgetId the id of a DcpWidget to switch back to.
     */
    virtual void setReferer(int widgetId) {m_Referer = widgetId;}
    
    /*! \return the referer id of the widget*/
    int referer() {return m_Referer;}
    
    /*! \brief This method is called when user press 'Back' in an applet page
        \return true if back closes the applet and true if a referer widget
         should be shown
    */
    virtual bool back() {
	if (referer() > -1) { // emit the changewidget signal if there is a referer set
	    emit changeWidget(referer());
	    return false;
	} else {
   	    return true; // back is handled by main window
                         // by default
	}
    }

signals:
    /*! \brief Emitted when the windget change is requested
        \pagam widgetId the id of the requested widget instead of this one.
        \details change can be requested by pressing a button on the widget, for example.
        In that case, this signal is handled by DcpAppletPage: it destroys this widget and
        creates and shows the new one at the given widgetId.
    */
    void changeWidget(int widgetId);
private:
    int m_Referer;
};

#endif // DCPWIDGET_H


#ifndef DCPAPPLETIF_H
#define DCPAPPLETIF_H

#include <QtPlugin>
class DcpWidget;
class DuiAction;
class DcpBrief;

/*!
    \brief Applet interface for DuiControlPanel applets
*/
class DcpAppletIf {
public:
    virtual ~DcpAppletIf() {}
    /*! 
        \brief Initializes applet right after loading it
        \param part The part name of the applet, if it implements more dialogs or views (parts)
               and it needs only one part
    */ 
    virtual void init(QString part="") = 0;
    
    /*! 
        \brief Contstructs the widget specified by widgetId that the applet provides
        \param widgetId the Id of the widget implemented by the applet that we want to show
               This widget is usually a container or a dialog
        \details
          The "entrance" widget (that is displayed on first page) will be queried with 0 id.
          Further applet pages can be requested through the DcpWidget::changeWidget signal.
    */
    virtual DcpWidget* constructWidget(int widgetId) = 0;
    
    /*!
        \brief Title of the applet that displayed in title row of applet page
        \return A title which is displayed in title row of page. It can vary by each widget
    */
    virtual QString title() const = 0;
    
    /*!
        \brief Menu items that applet can provide in the main menu of the applet page
    */
    virtual QVector<DuiAction *> viewMenuItems() = 0;

    /*
        \brief The Brief view of the applet
        \detais Brief widget is the button-look on category pages of DuiControlpanel
        It displays the applet name and the current value. Value must be provided
        and formatted by the applet implementation. Clicking on the widget displays
        the applet itself.
    */
    virtual DcpBrief* constructBrief() = 0;
};

Q_DECLARE_INTERFACE(DcpAppletIf, "com.nokia.dui.core.DcpAppletIf/1.0")

#endif // DCPAPPLETIF_H


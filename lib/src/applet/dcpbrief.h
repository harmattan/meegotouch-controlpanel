#ifndef DCPBRIEF_H
#define DCPBRIEF_H

#include <QObject>
#include <QString>
 /*!
        \class DcpBief                                                                                   
        \brief The Brief of the applet                                                                   
        \detais Brief is the descriptor of an applet for constructing the buttons that
        launches the applet.                 
        These buttons are displaying the applet name and the current value. 
        Value must be provided and formatted by the applet implementation. 
        Clicking on this widget displays the applet itself   
        This class provides all the information from which a widget describing above can be constructed.                                                                                   
    */               
class DcpBrief: public QObject{
    Q_OBJECT
public:
    virtual ~DcpBrief();

    /*! \brief This method tell what kind of Brief Widget we need */
    virtual int widgetTypeID() const;

    /*! \brief returns the value that is to be displayed on second line
     *  \details Value should be formatted properly as the user should see it.
     *  For example language code can be formatted with DuiLocale or
         the current time that comes from the system */
    virtual QString valueText() const;
    /*! \return the current icon of the widget */
    virtual QString icon() const;

    /*! \return the alignment of the text in the brief widget. if AlignLeft
     * (default), then the text will be on the left side, the button/picture
     * on the right. */
    virtual Qt::Alignment align() const;

    /*! \brief If the widget type is toggle, then this function returns
     * the initial state of the toggle button. */
    virtual bool toggle() const;

    /*! \brief Gets called when toggle state changes
     *  \details If the widget type is toggle, and the user changes the toggle
     * button state, this function will be called, so that the applet can
     * handle the setting change.
     * \param toggle The new state
     */
    virtual void setToggle (bool toggle);

    virtual QString image() const;

signals:
    /*! Should be emitted when some of the values changed. Causes the
     * widget to be refreshed with current values. */
    void valuesChanged();
};


#endif // DCPBRIEF_H

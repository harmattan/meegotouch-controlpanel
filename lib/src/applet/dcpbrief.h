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
        This class provides all the information that a widget describing above can be constructed.                                                                                   
    */               
class DcpBrief: public QObject{
    Q_OBJECT
public:
    virtual ~DcpBrief();

    /*! \brief This method tell what kind of Brief Widget we need */
    virtual int widgetTypeID() const;

    /*! \brief This method returns the value formatted properly of the applet
        \details For example language code must be formatted with DuiLocale but
         current time comes from the system */ 
    virtual QString valueText() const;
    /*! \return the current icon of the widget */
    virtual QString icon() const;

    /*! \return the alignb of the text in the brief widget*/
    virtual Qt::Alignment align() const;

    /*! \brief Tells if the value can be toggled*/
    virtual bool toggle() const;

    /*! \brief Sets the toggle state if widget should be a toggle*/
    virtual void setToggle (bool toggle);

    virtual QString image() const;

signals:
    /*! emitted when some of the values changed */
    void valuesChanged();
};


#endif // DCPBRIEF_H

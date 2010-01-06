/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */

#ifndef DCPBRIEF_H
#define DCPBRIEF_H

#include <QObject>
#include <QString>

/*!
 * \class DcpBrief
 * \brief The Brief of the applet
 * \detais Brief is the descriptor of an applet for constructing the buttons 
 *   that launches the applet. These buttons are displaying the applet name and
 *   the current value.  Value must be provided and formatted by the applet
 *   implementation.  Clicking on this widget displays the applet itself   This
 *   class provides all the information from which a widget describing above can
 *   be constructed.
 */
class DcpBrief: public QObject
{
    Q_OBJECT

public:
    virtual ~DcpBrief();

    /*! 
     * \brief This method tell what kind of Brief Widget the applet needs.
     * 
     * Returns the brief widget type code for the plugin variant. This value
     * can also defined in the desktop file using the "DCP/WidgetType" key. If
     * none of these specified the "DCPLABEL2" will be used as default.
     *
     * FIXME: If we are defining all the acceptable IDs the return value of this
     * function should be an enum.
     */
    virtual int widgetTypeID() const;

    /*! \brief returns the value that is to be displayed on second line
     *  \details Value should be formatted properly as the user should see it.
     *  For example language code can be formatted with DuiLocale or
         the current time that comes from the system */
    virtual QString valueText () const;

    /*! 
     * \return the name of the icon for the brief 
     */
    virtual QString icon () const;

    /*!
     * \return the current icon for the toggle button 
     */
    virtual QString toggleIconId () const;

    /*!
     * \return the alignment of the text in the brief widget. if AlignLeft
     * (default), then the text will be on the left side, the button/picture
     * on the right. 
     */
    virtual Qt::Alignment align () const;

    /*! 
     * \brief Returns the initial state of the toggle in the brief widget.
     * 
     * If the widget type is toggle, then this function returns
     * the initial state of the toggle button. The default value is false.
     */
    virtual bool toggle () const;

    /*!
     * \brief Gets called when toggle state changes
     * \details If the widget type is toggle, and the user changes the toggle
     *   button state, this function will be called, so that the applet can
     *   handle the setting change.
     * \param toggle The new state
     */
    virtual void setToggle (bool toggle);

    /*!
     * \brief returns the name for the icon
     * \details The implementation should return the icon name that the applet
     *   wants to use in the brief widget.
     *
     * FIXME: The name of this function should be getIconName() and it should
     * get the widgetId as an argument!
     * FIXME: It is not clear if we use this only inside the brief or somewhere
     * else also.
     */
    virtual QString image () const;

    /*!
     * \brief Sends the activateSignal() signal to activate the applet
     */
    void activate ();

signals:
    /*! Should be emitted when some of the values changed. Causes the
     * widget to be refreshed with current values. */
    void valuesChanged();

    /*!
     * The applet can activate itself by sending this signal. The control panel
     * will start up the applet the same way it is activated when the user
     * clicked on the brief widget.
     */
    void activateSignal ();
};


#endif

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPCONTENTITEM_H
#define DCPCONTENTITEM_H

#include <MContentItem>

class DcpAppletObject;
class QShowEvent;
class QHideEvent;
class DcpContentItemPrivate;

/*!
 * \brief An activatable entry in the control panel.
 *
 * The #DcpContentItem is an activatable widget in the control panel. It
 * has a #DcpAppletObject associated with it, so when the user clicks
 * on the widget the applet variant is activated. The widget connects its
 * clicked() signal to the activate() signal of the #DcpAppletObject object,
 * so the applet variant will be started when the widget is clicked.
 *
 * This class implements the connection between the brief shown on the screen
 * and the applet describing the applet variant.
 *
 */
class DcpContentItem: public MContentItem
{
    Q_OBJECT

public:
    DcpContentItem (
            DcpAppletObject *applet = 0,
            QGraphicsItem *parent = 0);

    ~DcpContentItem ();

    void setApplet (DcpAppletObject *applet);
    DcpAppletObject *applet () const;

public slots:
    void updateContents ();

protected:
    virtual void retranslateUi ();
    virtual void showEvent (QShowEvent *event);
    virtual void hideEvent (QHideEvent *event);

    virtual void constructRealWidget ();
    void invertTwoLineMode ();
    void updateText ();
    void updateImage ();

    // image related things:
    void setImageFromFile (const QString& fileName);
    void setImageName (const QString& name);
    void releaseImage ();

private:
    DcpContentItemPrivate* const d_ptr;
};


#endif


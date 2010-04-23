/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTONALIGN_H
#define DCPBUTTONALIGN_H

#include "dcpbutton.h"
class QGraphicsLayout;
class QGraphicsLinearLayout;
class DcpButtonAlignPrivate;

/*!
 * \brief Parent class for all the brief widgets.
 *
 * The #DcpButtonAlign is the base class for all the brief widget classes. The
 * brief widgets are the widgets inside the main page and the category subpages
 * representing one applet variant.
 *
 * THIS CLASS IS DEPRECATED and will be removed soon.
 */
class DcpButtonAlign: public DcpButton
{
    Q_OBJECT

public:
    DcpButtonAlign (MWidget *parent);
    ~DcpButtonAlign ();

    void setWidgetAlignment (Qt::Alignment align);

protected:
    virtual QGraphicsLayout* createLayout ();
    void setAlignment (Qt::Alignment align);

    MWidget* alignedWidget ();
    void setAlignedWidget (MWidget* widget);

private:
    void putupWidgets ();
    DcpButtonAlignPrivate * const d_ptr;
};


#endif // DCPBUTTONALIGN_H


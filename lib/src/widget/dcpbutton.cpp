/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbutton.h"
#include "dcpbutton_p.h"
#include <DuiLabel>
#include <QGraphicsGridLayout>
#include <QGraphicsSceneMouseEvent>

#include "duiwidgetcreator.h"
DUI_REGISTER_WIDGET_NO_CREATE(DcpButton)


#include "dcpdebug.h"

/******************************************************************************
 * Stuff for the DuiStylableWidget style handling. 
 */
#ifdef USE_STYLABLE_WIDGET
class DcpButtonStyleContainerPrivate {
    bool none;
};

DcpButtonStyle::DcpButtonStyle () 
{
    DCP_DEBUG ("");
}

DcpButtonStyle::~DcpButtonStyle () 
{
    DCP_DEBUG ("");
}

DcpButtonStyleContainer::DcpButtonStyleContainer() :
    d_ptr (new DcpButtonStyleContainerPrivate)
{
    DCP_DEBUG ("");
}

DcpButtonStyleContainer::~DcpButtonStyleContainer()
{
    DCP_DEBUG ("");
}

void DcpButtonStyleContainer::reloadStyles()
{
    DuiWidgetStyleContainer::reloadStyles();
}

const char* DcpButtonStyleContainer::styleType() const
{
    return "DcpButtonStyle";
}
#endif

/******************************************************************************
 * Stuff for the private data.
 */
DcpButtonPrivate::DcpButtonPrivate ():
    textLayout (0), 
    label1 (0), 
    label2 (0)
{
}


/******************************************************************************
 * Stuff for the DcpButton widget class. 
 */
DcpButton::DcpButton (DuiWidget *parent): 
    #ifdef USE_STYLABLE_WIDGET
    DuiStylableWidget (parent), 
    #else
    DuiWidget (parent), 
    #endif
    d_ptr (new DcpButtonPrivate)
{
    DCP_DEBUG ("");
    setObjectName ("DcpButton");
    this->setLayout (createLayout());
}

/*!
 * protected constructor which avoids creating the layout
 */
DcpButton::DcpButton(DuiWidget* parent, bool): 
    #ifdef USE_STYLABLE_WIDGET
    DuiStylableWidget (parent), 
    #else
    DuiWidget (parent), 
    #endif
    d_ptr (new DcpButtonPrivate)
{
    setObjectName ("DcpButton");
}

DcpButton::~DcpButton ()
{
    delete d_ptr;
}


QGraphicsLayout *
DcpButton::createLayout ()
{
    d_ptr->label1 = new DuiLabel (this);
    d_ptr->label1->setAcceptedMouseButtons (0);
    d_ptr->label1->setTextElide (true);

    d_ptr->label2 = new DuiLabel();
    d_ptr->label2->setTextElide (true);
    d_ptr->label2->setAcceptedMouseButtons (0);
    d_ptr->label2->setObjectName ("DcpButtonLine2");

    d_ptr->textLayout = new QGraphicsGridLayout ();
    d_ptr->textLayout->setContentsMargins (0, 0, 0, 0);
    d_ptr->textLayout->addItem (d_ptr->label1, 0, 0);
    d_ptr->textLayout->addItem (d_ptr->label2, 1, 0);

    updateLabelSizes ();
    return d_ptr->textLayout;
}

void 
DcpButton::setText1 (
        const QString &text)
{
    d_ptr->label1->setText(text);
}

void 
DcpButton::setText2 (
        const QString &text)
{
    if (text == d_ptr->label2->text()) 
        return;

    d_ptr->label2->setText (text);
    updateLabelSizes ();
}

QString 
DcpButton::getText1() const
{
    return d_ptr->label1->text();
}

QString 
DcpButton::getText2() const
{
    return d_ptr->label2->text();
}

void 
DcpButton::updateLabelSizes ()
{
    if (d_ptr->label2->text().isEmpty()) {
        d_ptr->label1->setObjectName ("DcpButtonMain");
        if (textLayout()->count() > 1) {
            textLayout()->removeAt(1);
        }
        d_ptr->label2->hide();
    } else {
        d_ptr->label1->setObjectName ("DcpButtonLine1");
        if (textLayout()->count() <= 1) {
            textLayout()->addItem (d_ptr->label2, 1, 0);
        }
        d_ptr->label2->show();
    }
}

void 
DcpButton::setText (
        const QString &text1, 
        const QString &text2)
{
    setText1 (text1);
    setText2 (text2);
}

QGraphicsGridLayout *
DcpButton::textLayout()
{
    return d_ptr->textLayout;
}

void 
DcpButton::mousePressEvent (
        QGraphicsSceneMouseEvent *event)
{
    DCP_DEBUG ("");
    Q_UNUSED(event);
    // this function is only for becoming the mouse grabber item
    // so that release event is working
    //
    // visual feedback for user can be implemented here
}

void 
DcpButton::mouseReleaseEvent (
        QGraphicsSceneMouseEvent *event)
{
    DCP_DEBUG ("");
    if (QRectF(QPointF(), size()).contains(event->pos())) {
        emit clicked();
    }
}


/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbutton.h"
#include <DuiLabel>
#include <QGraphicsGridLayout>
#include <QGraphicsSceneMouseEvent>

#define DEBUG
#include "dcpdebug.h"


/******************************************************************************
 * Private data class for the DcpWidget class.
 */
class DcpButtonPrivate {
public:
    DcpButtonPrivate ();
    QGraphicsGridLayout *m_TextLayout;
    DuiLabel            *m_Label1;
    DuiLabel            *m_Label2;
};

DcpButtonPrivate::DcpButtonPrivate ():
    m_TextLayout (0), 
    m_Label1 (0), 
    m_Label2 (0)
{
}


DcpButton::DcpButton (DuiWidget *parent): 
    DuiStylableWidget (parent), 
    d_ptr (new DcpButtonPrivate)
{
    // TODO remove me, it is only a hack, seems to prevent baddrawable error
    setMaximumSize (999, 999); 
    setObjectName ("DcpButton");
    this->setLayout (createLayout());
}

/*!
 * protected constructor which avoids creating the layout
 */
DcpButton::DcpButton(DuiWidget* parent, bool): 
    DuiStylableWidget(parent), 
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
    d_ptr->m_Label1 = new DuiLabel (this);
    d_ptr->m_Label1->setAcceptedMouseButtons (0);
    d_ptr->m_Label1->setTextElide (true);

    d_ptr->m_Label2 = new DuiLabel();
    d_ptr->m_Label2->setTextElide (true);
    d_ptr->m_Label2->setAcceptedMouseButtons (0);
    d_ptr->m_Label2->setObjectName ("DcpButtonLine2");

    d_ptr->m_TextLayout = new QGraphicsGridLayout ();
    d_ptr->m_TextLayout->setContentsMargins (0, 0, 0, 0);
    d_ptr->m_TextLayout->addItem (d_ptr->m_Label1, 0, 0);
    d_ptr->m_TextLayout->addItem (d_ptr->m_Label2, 1, 0);

    updateLabelSizes ();
    return d_ptr->m_TextLayout;
}

void 
DcpButton::setText1 (
        const QString &text)
{
    d_ptr->m_Label1->setText(text);
}

void 
DcpButton::setText2 (
        const QString &text)
{
    if (text == d_ptr->m_Label2->text()) 
        return;

    d_ptr->m_Label2->setText (text);
    updateLabelSizes ();
}

QString 
DcpButton::getText1() const
{
    return d_ptr->m_Label1->text();
}

QString 
DcpButton::getText2() const
{
    return d_ptr->m_Label2->text();
}

void 
DcpButton::updateLabelSizes ()
{
    if (d_ptr->m_Label2->text().isEmpty()) {
        d_ptr->m_Label1->setObjectName ("DcpButtonMain");
        if (textLayout()->count() > 1) {
            textLayout()->removeAt(1);
        }
        d_ptr->m_Label2->hide();
    } else {
        d_ptr->m_Label1->setObjectName ("DcpButtonLine1");
        if (textLayout()->count() <= 1) {
            textLayout()->addItem (d_ptr->m_Label2, 1, 0);
        }
        d_ptr->m_Label2->show();
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
    return d_ptr->m_TextLayout;
}

void 
DcpButton::mousePressEvent (
        QGraphicsSceneMouseEvent *event)
{
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
    if (QRectF(QPointF(), size()).contains(event->pos())) {
        emit clicked();
    }
}


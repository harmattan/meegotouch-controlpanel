/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttonalign.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>

#define DEBUG
#include "dcpdebug.h"

/******************************************************************************
 * Private data class for the DcpWidget class.
 */
class DcpButtonAlignPrivate {
public:
    DcpButtonAlignPrivate ();
    DuiWidget              *m_AlignedWidget;
    QGraphicsLinearLayout  *m_AlignLayout;
    Qt::Alignment           m_Alignment;
}; 

DcpButtonAlignPrivate::DcpButtonAlignPrivate () :
    m_AlignedWidget (0), 
    m_AlignLayout (0),
    m_Alignment (Qt::AlignRight)

{
}

/*!
 * FIXME: This constructor has an unused unnamed boolean argument. It should be
 * maybe removed?
 */
DcpButtonAlign::DcpButtonAlign (
        DuiWidget *parent): 
    DcpButton (parent, false),
    d_ptr (new DcpButtonAlignPrivate)
{
}

DcpButtonAlign::~DcpButtonAlign ()
{
    delete d_ptr;
}


QGraphicsLayout *
DcpButtonAlign::createLayout ()
{
    Q_ASSERT(alignedWidget());

    // text
    DcpButton::createLayout();
    qreal left, right, top, bottom;
    textLayout()->getContentsMargins (&left, &top, &right, &bottom);
    textLayout()->setContentsMargins (0, 0, right, 0);

    // putting the widget next to the text
    d_ptr->m_AlignLayout = new QGraphicsLinearLayout (Qt::Horizontal);
    d_ptr->m_AlignLayout->setContentsMargins (left, top, right, bottom);

    putupWidgets();
    return d_ptr->m_AlignLayout;
}

void 
DcpButtonAlign::setAlignment (
        Qt::Alignment align)
{
    if (d_ptr->m_Alignment == align)
        return;

    d_ptr->m_Alignment = align;

    if (d_ptr->m_AlignLayout != NULL) {
        /* if the layout has already been created, remove and readd the items
         * in the correct order */
        d_ptr->m_AlignLayout->removeAt (0);
        d_ptr->m_AlignLayout->removeAt (1);
        putupWidgets ();
    }
}

void
DcpButtonAlign::putupWidgets ()
{
    Q_ASSERT (alignedWidget());
    Q_ASSERT (textLayout());

    switch (d_ptr->m_Alignment) {
        case Qt::AlignRight:
            d_ptr->m_AlignLayout->addItem (textLayout());
            d_ptr->m_AlignLayout->addItem (alignedWidget());
            break;

        case Qt::AlignLeft:
            d_ptr->m_AlignLayout->addItem (alignedWidget());
            d_ptr->m_AlignLayout->addItem (textLayout());
            break;

        default:
            qFatal ("DcpButtonAlign unsupported alignment");
            break;
    }

    d_ptr->m_AlignLayout->setAlignment (alignedWidget(), Qt::AlignVCenter);
}

DuiWidget *
DcpButtonAlign::alignedWidget ()
{
    return d_ptr->m_AlignedWidget;
}

void 
DcpButtonAlign::setAlignedWidget (
        DuiWidget *widget)
{
    // only lets to set it up once currently (no widget changing)
    Q_ASSERT (!d_ptr->m_AlignedWidget); 
    d_ptr->m_AlignedWidget = widget;
}



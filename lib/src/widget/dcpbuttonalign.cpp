/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttonalign.h"
#include "dcpbuttonalign_p.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>

#include "dcpdebug.h"

DcpButtonAlignPrivate::DcpButtonAlignPrivate () :
    alignedWidget (0), 
    alignLayout (0),
    alignment (Qt::AlignRight)

{
}

/*!
 * FIXME: This constructor has an unused unnamed boolean argument. It should be
 * maybe removed?
 */
DcpButtonAlign::DcpButtonAlign (
        MWidget *parent): 
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

    DcpButton::createLayout();
    qreal left, right, top, bottom;
    textLayout()->getContentsMargins (&left, &top, &right, &bottom);
    textLayout()->setContentsMargins (0, 0, right, 0);

    d_ptr->alignLayout = new QGraphicsLinearLayout (Qt::Horizontal);
    d_ptr->alignLayout->setContentsMargins (left, top, right, bottom);

    putupWidgets();
    return d_ptr->alignLayout;
}

void 
DcpButtonAlign::setAlignment (
        Qt::Alignment align)
{
    if (d_ptr->alignment == align)
        return;

    d_ptr->alignment = align;

    if (d_ptr->alignLayout != NULL) {
        /* if the layout has already been created, remove and readd the items
         * in the correct order */
        d_ptr->alignLayout->removeAt (0);
        d_ptr->alignLayout->removeAt (1);
        putupWidgets ();
    }
}

void
DcpButtonAlign::putupWidgets ()
{
    Q_ASSERT (alignedWidget());
    Q_ASSERT (textLayout());

    switch (d_ptr->alignment) {
        case Qt::AlignRight:
            d_ptr->alignLayout->addItem (textLayout());
            d_ptr->alignLayout->addItem (alignedWidget());
            break;

        case Qt::AlignLeft:
            d_ptr->alignLayout->addItem (alignedWidget());
            d_ptr->alignLayout->addItem (textLayout());
            break;

        default:
            qFatal ("DcpButtonAlign unsupported alignment");
            break;
    }

    d_ptr->alignLayout->setAlignment (alignedWidget(), Qt::AlignVCenter);
}

MWidget *
DcpButtonAlign::alignedWidget ()
{
    return d_ptr->alignedWidget;
}

void 
DcpButtonAlign::setAlignedWidget (
        MWidget *widget)
{
    // only lets to set it up once currently (no widget changing)
    Q_ASSERT (!d_ptr->alignedWidget); 
    d_ptr->alignedWidget = widget;
}



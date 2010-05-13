/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include "mlayout.h"

/* A fake mlayout
 *
 * Can be used to create tests which run without X.
 * It does nothing, handles nothing.
 *
 * If you use it, consider using one of the fake policies:
 * - mgridlayoutpolicy-fake.cpp
 * - mlinearlayoutpolicy-fake.cpp
 *
 */

#include <mabstractlayoutpolicy.h>

class MLayoutPrivate
{
public:
    QList<MAbstractLayoutPolicy*> policies;
    MAbstractLayoutPolicy *portraitPolicy;
    MAbstractLayoutPolicy *landscapePolicy;
    MLayoutAnimation *animation;
};

MLayout::MLayout(QGraphicsLayoutItem *) :
    d_ptr(new MLayoutPrivate)
{
}

MLayout::~MLayout()
{
     delete d_ptr;
}

void MLayout::invalidate()
{
}

void MLayout::invalidateLayoutOnly()
{
}

int MLayout::count() const
{
    return 0;
}

bool MLayout::isEmpty() const
{
    return true;
}

QGraphicsLayoutItem *MLayout::itemAt(int) const
{
    return 0;
}

void MLayout::removeAt(int index)
{
    (void)takeAt(index);
}

QGraphicsLayoutItem *MLayout::takeAt(int)
{
    return 0;
}

void MLayout::animatedDeleteItem(const QGraphicsLayoutItem *const)
{
}

void MLayout::animatedDeleteAt(int)
{
}

QSizeF MLayout::sizeHint(Qt::SizeHint , const QSizeF &) const
{
    return QSizeF(-1, -1);
}

void MLayout::setGeometry(const QRectF &)
{
}

int MLayout::addItem(QGraphicsLayoutItem *)
{
    return 0;
}

void MLayout::removeItem(const QGraphicsLayoutItem *const item)
{
    // this is necessery, because the item removes itself from the
    // policies through the layout when it gets destroyed
    foreach (MAbstractLayoutPolicy* layout, d_ptr->policies) {
        layout->removeItem(item);
    }
}

int MLayout::indexOf(const QGraphicsItem *) const
{
    return -1;
}

int MLayout::indexOf(const QGraphicsLayoutItem *) const
{
    return -1;
}

void MLayout::setPolicy(MAbstractLayoutPolicy *)
{
}

void MLayout::setLandscapePolicy(MAbstractLayoutPolicy *policy)
{
    d_ptr->landscapePolicy = policy;
}

MAbstractLayoutPolicy *MLayout::landscapePolicy() const
{
    return d_ptr->landscapePolicy;
}

void MLayout::setPortraitPolicy(MAbstractLayoutPolicy *policy)
{
    d_ptr->portraitPolicy = policy;
}

MAbstractLayoutPolicy *MLayout::portraitPolicy() const
{
    return d_ptr->portraitPolicy;
}

MAbstractLayoutPolicy *MLayout::policy() const
{
    return 0;
}

QList<MAbstractLayoutPolicy *> MLayout::registeredPolicies() const
{
    return d_ptr->policies;
}

void MLayout::setAnimation(MLayoutAnimation *animation)
{
    d_ptr->animation = animation;
}

MLayoutAnimation *MLayout::animation() const
{
    return d_ptr->animation;
}

void MLayout::setContentsMargins(qreal, qreal, qreal, qreal)
{
}

void MLayout::getContentsMargins(qreal *, qreal *, qreal *, qreal *) const
{
}

Qt::LayoutDirection MLayout::layoutDirection() const
{
    return (Qt::LayoutDirection) 0;
}
void MLayout::widgetEvent ( QEvent * )
{
}

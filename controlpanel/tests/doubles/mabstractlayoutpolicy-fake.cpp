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

#include <mabstractlayoutpolicy.h>
#include <QString>
#include <QList>

/* Fake abstract layout policy
 *
 * With this source you can fake the abstract layout policy,
 * so it will only handle a list of items for you, and it will not require
 * you to use X for testing.
 */

class MAbstractLayoutPolicyPrivate {
    public:
        QList<const QGraphicsLayoutItem*> items;
        qreal horizontalSpacing;
        qreal verticalSpacing;
        qreal spacing;
};

MAbstractLayoutPolicy::MAbstractLayoutPolicy(MLayout*):
    d_ptr(new MAbstractLayoutPolicyPrivate()) {}
MAbstractLayoutPolicy::MAbstractLayoutPolicy(
        MAbstractLayoutPolicyPrivate &p):
    d_ptr(&p)
{
}

MAbstractLayoutPolicy::~MAbstractLayoutPolicy(){}
void MAbstractLayoutPolicy::setContentsMargins(qreal, qreal, qreal, qreal){}
void MAbstractLayoutPolicy::unsetContentsMargins(){}
void MAbstractLayoutPolicy::getContentsMargins(qreal*, qreal*, qreal*, qreal*) const{}
MLayout* MAbstractLayoutPolicy::layout() const{ return 0; }
void MAbstractLayoutPolicy::activate(){}
bool MAbstractLayoutPolicy::isActive() const{ return false; }
QSizeF MAbstractLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100,100); }
void MAbstractLayoutPolicy::updateStyle(){}
void MAbstractLayoutPolicy::setObjectName(const QString &){}
QString MAbstractLayoutPolicy::objectName() const{ return ""; }
void MAbstractLayoutPolicy::setHorizontalSpacing(qreal space)
{
    d_ptr->horizontalSpacing = space;
}
qreal MAbstractLayoutPolicy::horizontalSpacing() const
{
    return d_ptr->horizontalSpacing;
}

void MAbstractLayoutPolicy::setVerticalSpacing(qreal space)
{
    d_ptr->verticalSpacing = space;
}

qreal MAbstractLayoutPolicy::verticalSpacing() const
{
    return d_ptr->verticalSpacing;
}
void MAbstractLayoutPolicy::setSpacing(qreal space)
{
    d_ptr->spacing = space;
}

int MAbstractLayoutPolicy::count() const
{
    return d_ptr->items.count();
}

QGraphicsLayoutItem* MAbstractLayoutPolicy::itemAt(int i) const
{
    return const_cast<QGraphicsLayoutItem*>(d_ptr->items.at(i));
}

int MAbstractLayoutPolicy::indexOf(const QGraphicsLayoutItem* item) const
{
    return d_ptr->items.indexOf(item);
}

void MAbstractLayoutPolicy::removeAt(int i)
{
    d_ptr->items.removeAt(i);
}

void MAbstractLayoutPolicy::removeItem(const QGraphicsLayoutItem* item)
{
    removeAt(indexOf(item));
}

void MAbstractLayoutPolicy::insertItem(int i, QGraphicsLayoutItem* item)
{
    d_ptr->items.insert(i, item);
}

void MAbstractLayoutPolicy::addItem(QGraphicsLayoutItem* item)
{
    d_ptr->items.append(item);
}

void MAbstractLayoutPolicy::setItemGeometry(int, const QRectF &){}
QRectF MAbstractLayoutPolicy::itemGeometry(int) const{ return QRectF(100,100,100,100); }
void MAbstractLayoutPolicy::hideItem(int){}
void MAbstractLayoutPolicy::applyStyle(){}
const MAbstractLayoutPolicyStyle* MAbstractLayoutPolicy::style() const{ return 0; }
void MAbstractLayoutPolicy::relayout(){}
void Q_DECL_DEPRECATED MAbstractLayoutPolicy::aboutToBeRemovedFromLayout(const QGraphicsLayoutItem*){}
void MAbstractLayoutPolicy::invalidatePolicyAndLayout(){}
void MAbstractLayoutPolicy::invalidate(){}
void MAbstractLayoutPolicy::updateGeometry(){}
QRectF MAbstractLayoutPolicy::contentsArea() const{ return QRectF(100,100,100,100); }
void MAbstractLayoutPolicy::activated(){}


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

#include <qgraphicslinearlayout.h>

#include <QList>
#include <QHash>

struct QGraphicsLinearLayoutFake
{
    QList<QGraphicsLayoutItem*> items;
};

static QHash<const QGraphicsLinearLayout*, QGraphicsLinearLayoutFake*> layouts;

QGraphicsLinearLayout::QGraphicsLinearLayout(QGraphicsLayoutItem* parent)
    : QGraphicsLayout(parent)
{
    layouts.insert(this, new QGraphicsLinearLayoutFake);
}

QGraphicsLinearLayout::QGraphicsLinearLayout(Qt::Orientation, QGraphicsLayoutItem* parent)
    : QGraphicsLayout(parent)
{
    layouts.insert(this, new QGraphicsLinearLayoutFake);
}

QGraphicsLinearLayout::~QGraphicsLinearLayout(){}
void QGraphicsLinearLayout::setOrientation(Qt::Orientation){}

Qt::Orientation QGraphicsLinearLayout::orientation() const
{
    return Qt::Horizontal;
}

// inline void addItem(QGraphicsLayoutItem* item){}

void QGraphicsLinearLayout::insertItem(int i, QGraphicsLayoutItem* item)
{
    layouts[this]->items.insert(i, item);
}

void QGraphicsLinearLayout::removeItem(QGraphicsLayoutItem* item)
{
    layouts[this]->items.removeOne(item);
}

void QGraphicsLinearLayout::removeAt(int index)
{
    layouts[this]->items.removeAt(index);
}

int QGraphicsLinearLayout::count() const
{
    return layouts[this]->items.count();
}

QGraphicsLayoutItem* QGraphicsLinearLayout::itemAt(int i) const
{
    return layouts[this]->items[i];
}

void QGraphicsLinearLayout::insertStretch(int, int) {}
void QGraphicsLinearLayout::setSpacing(qreal){}
qreal QGraphicsLinearLayout::spacing() const{ return 0.0f; }
void QGraphicsLinearLayout::setItemSpacing(int, qreal){}
qreal QGraphicsLinearLayout::itemSpacing(int) const{ return 0.0f; }
void QGraphicsLinearLayout::setStretchFactor(QGraphicsLayoutItem*, int){}
int QGraphicsLinearLayout::stretchFactor(QGraphicsLayoutItem*) const{ return 1; }
void QGraphicsLinearLayout::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
Qt::Alignment QGraphicsLinearLayout::alignment(QGraphicsLayoutItem*) const
{
    return Qt::AlignLeft;
}
void QGraphicsLinearLayout::setGeometry(const QRectF &){}
void QGraphicsLinearLayout::invalidate(){}
QSizeF QGraphicsLinearLayout::sizeHint(Qt::SizeHint, const QSizeF &) const
{
    return QSizeF(100,100);
}


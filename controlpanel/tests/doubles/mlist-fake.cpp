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

#include <MList>

#include <QHash>
static QHash<const MList*, QAbstractItemModel*> priv;

MList::MList(QGraphicsItem*)
{}

MList::MList(MListPrivate* , MListModel* , QGraphicsItem* )
{}

MList::~MList() {}

void MList::setItemModel(QAbstractItemModel* itemModel)
{
    priv.insert (this, itemModel);
}

QAbstractItemModel* MList::itemModel() const
{
    return priv[this];
}

void MList::setCellCreator(MCellCreator*){}
const MCellCreator* MList::cellCreator() const{ return 0; }
void MList::setColumns(int){}
int MList::columns() const{ return 1; }
QItemSelectionModel* MList::selectionModel() const { return 0; }
void MList::setSelectionModel(QItemSelectionModel* ){}
void MList::setSelectionMode(MList::SelectionMode ){}
MList::SelectionMode MList::selectionMode() const{ return MList::NoSelection; }
const QModelIndex MList::firstVisibleItem() const{ return QModelIndex(); }
const QModelIndex MList::lastVisibleItem() const{ return QModelIndex(); }
bool MList::showGroups() const{ return false; }
void MList::setShowGroups(bool){}
bool MList::indexVisible(){ return false; }
MListFilter* MList::filtering() const { return 0; }
void MList::selectItem(const QModelIndex &) {}
void MList::longTapItem(const QModelIndex &){}
void MList::scrollTo(const QModelIndex &){}
void MList::scrollTo(const QModelIndex &, ScrollHint){}
void MList::setIndexVisible(bool ){}
void MList::updateData(const QList<const char* >& ){}
void MList::contextMenuEvent(QGraphicsSceneContextMenuEvent* ){}
void MList::keyPressEvent(QKeyEvent* ){}


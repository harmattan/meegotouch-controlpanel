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

#include <MBasicListItem>
#include <QHash>
#include <MImageWidget>

class MBasicListItemPriv {
    public:
        QString title;
        QString subTitle;
        MImageWidget* image;
};

static QHash<const MBasicListItem*, MBasicListItemPriv*> priv;

MBasicListItem::MBasicListItem(MBasicListItem::ItemStyle, QGraphicsItem*)
{
    priv[this] = new MBasicListItemPriv;
    priv[this]->image = new MImageWidget();
}

MBasicListItem::~MBasicListItem()
{
    delete priv[this]->image;
    delete priv.take (this);
}

void  MBasicListItem::initLayout()
{}

void  MBasicListItem::setItemStyle(ItemStyle)
{}

void  MBasicListItem::setImageWidget(MImageWidget*)
{}

MImageWidget*  MBasicListItem::imageWidget()
{
    return priv[this]->image;
}

void  MBasicListItem::setTitle(const QString &title)
{
    priv[this]->title = title;
}

QString  MBasicListItem::title()
{
    return priv[this]->title;
}

void  MBasicListItem::setSubtitle(const QString &subtitle)
{
    priv[this]->subTitle = subtitle;
}

QString  MBasicListItem::subtitle()
{
    return priv[this]->subTitle;
}

MLabel*  MBasicListItem::titleLabelWidget()
{
    return 0;
}

MLabel*  MBasicListItem::subtitleLabelWidget()
{
    return 0;
}

QGraphicsLayout*  MBasicListItem::createLayout()
{
    return 0;
}

void  MBasicListItem::clearLayout()
{
}

void  MBasicListItem::resizeEvent(QGraphicsSceneResizeEvent*)
{
}


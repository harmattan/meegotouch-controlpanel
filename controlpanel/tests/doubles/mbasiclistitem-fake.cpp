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
#include <MLabel>

class MBasicListItemPriv {
    public:
        MLabel *title;
        MLabel *subTitle;
        MImageWidget* image;
};

static QHash<const MBasicListItem*, MBasicListItemPriv*> priv;

MBasicListItem::MBasicListItem(MBasicListItem::ItemStyle, QGraphicsItem*)
{
    priv[this] = new MBasicListItemPriv;
    priv[this]->title = new MLabel();
    priv[this]->subTitle = new MLabel();
    priv[this]->image = new MImageWidget();
}

MBasicListItem::~MBasicListItem()
{
    delete priv[this]->title;
    delete priv[this]->subTitle;
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
    priv[this]->title->setText(title);
}

QString  MBasicListItem::title()
{
    return priv[this]->title->text();
}

void  MBasicListItem::setSubtitle(const QString &subtitle)
{
    priv[this]->subTitle->setText(subtitle);
}

QString  MBasicListItem::subtitle()
{
    return priv[this]->subTitle->text();
}

MLabel*  MBasicListItem::titleLabelWidget()
{
    return priv[this]->title;
}

MLabel*  MBasicListItem::subtitleLabelWidget()
{
    return priv[this]->subTitle;
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


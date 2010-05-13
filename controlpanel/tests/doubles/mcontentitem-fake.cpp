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

#include <mcontentitem.h>

/* Fake MContentItem
 */
class MContentItemFake 
{
public:
    QString m_Title;
    QString m_Subtitle;
};

MContentItemFake f;

MContentItem::MContentItem(MContentItem::ContentItemStyle,
                               QGraphicsItem*)
{
}

MContentItem::MContentItem(MContentItemPrivate*, MContentItemModel*,
                               QGraphicsItem* )
{}

MContentItem::~MContentItem(){}

QPixmap MContentItem::pixmap() const{ return QPixmap(); }
QImage MContentItem::image() const{ return QImage(); }

QString MContentItem::title() const
{
    return f.m_Title;
}

QString MContentItem::subtitle() const
{
    return f.m_Subtitle;
}

MContentItem::ContentItemMode MContentItem::itemMode() const
{
    return Default;
}

MContentItem::ContentItemStyle MContentItem::itemStyle() const
{
    return TwoTextLabels;
}

MWidget* MContentItem::additionalItem() const{ return 0; }
MWidget* MContentItem::smallItem() const{ return 0; }
QPixmap MContentItem::optionalPixmap() const{ return QPixmap(); }
QImage MContentItem::optionalImage() const{ return QImage(); }
void MContentItem::setPixmap(const QPixmap &){}
void MContentItem::setImage(const QImage &){}

void MContentItem::setTitle(const QString &title)
{
    f.m_Title = title;
}

void MContentItem::setSubtitle(const QString &subtitle)
{
    f.m_Subtitle = subtitle;
}
void MContentItem::setItemMode(ContentItemMode){}
void MContentItem::setAdditionalItem(MWidget*){}
void MContentItem::enableProgressBar(){}
void MContentItem::setSmallItem(MWidget*){}
void MContentItem::setSmallText(QString){}
void MContentItem::setOptionalPixmap(const QPixmap&){}
void MContentItem::setOptionalImage(const QImage&){}
void MContentItem::click(){}
QVariant MContentItem::itemChange(GraphicsItemChange, const QVariant &)
{
    return QVariant();
}




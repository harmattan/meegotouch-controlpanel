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

#include <MImageWidget>

#include <QHash>
#include <QString>
#include <QImage>

class MImageWidgetFake
{
    public:
        QString imageID;
};

static QHash<const MImageWidget*, MImageWidgetFake*> fake;

MImageWidget::MImageWidget(QGraphicsItem*)
{
    fake.insert (this, new MImageWidgetFake());
}

MImageWidget::~MImageWidget()
{
    delete fake.take (this);
}

void MImageWidget::setImage(const QString &id, const QSize &)
{
    fake[this]->imageID = id;
}

void MImageWidget::setImage(const QString &id)
{
    fake[this]->imageID = id;
}

void MImageWidget::setImage(const QImage &)
{
    fake[this]->imageID = "image";
}

void MImageWidget::setPixmap(const QPixmap &)
{
    fake[this]->imageID = "image";
}


const QPixmap * MImageWidget::pixmap () const
{
    return NULL;
}

QString MImageWidget::image() const
{
    return fake[this]->imageID;
}

QSize MImageWidget::imageSize() const
{
    return QSize();
}

bool QImage::load ( const QString &, const char * )
{
    return true;
}

/*
void M_EXPORT MImageWidget::setAspectRatioMode(Qt::AspectRatioMode mode);
M_EXPORT MImageWidget::Qt::AspectRatioMode aspectRatioMode() const;
void M_EXPORT MImageWidget::setCrop(const QRectF &rect);
QRectF M_EXPORT MImageWidget::crop() const;
*/


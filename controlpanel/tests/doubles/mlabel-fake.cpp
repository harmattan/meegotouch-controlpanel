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

#include <MLabel>

class MLabelFake
{
    public:
        QString text;
};

static QHash<const MLabel*, MLabelFake *> fake;

MLabel::MLabel(QGraphicsItem *, MLabelModel *)
{
    fake.insert(this, new MLabelFake());
}

MLabel::MLabel(QString const &, QGraphicsItem *)
{
    fake.insert(this, new MLabelFake());
}

MLabel::~MLabel()
{
    delete fake.take(this);
}

QString MLabel::text()const
{
    return fake[this]->text;
}

void MLabel::setText(const QString &text)
{
    fake[this]->text = text;
}

void MLabel::setWrapMode(QTextOption::WrapMode)
{

}

void MLabel::setTextElide(bool)
{

}

void MLabel::setWordWrap(bool)
{

}

void MLabel::setAlignment(Qt::Alignment)
{
}

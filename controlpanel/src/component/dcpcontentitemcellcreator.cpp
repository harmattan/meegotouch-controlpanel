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

#include "dcpcontentitemcellcreator.h"

#include <QModelIndex>
#include <MWidgetRecycler>
#include <pagefactory.h>

MWidget * DcpContentItemCellCreator::createCell (const QModelIndex &index,
                                              MWidgetRecycler &recycler) const
{
    DcpContentItem * cell =
        qobject_cast<DcpContentItem*>(recycler.take("DcpContentItem"));
    if (!cell) {
        cell = new DcpContentItem();
        cell->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
        QObject::connect(cell, SIGNAL(helpPageOpened(const QString)),
	  PageFactory::instance(), SLOT(helpClicked(const QString)));
    }
    updateCell(index, cell);
    return cell;
}

void DcpContentItemCellCreator::updateCell (
        const QModelIndex& index, MWidget * cell) const
{
    DcpContentItem * contentItem = qobject_cast<DcpContentItem *>(cell);

    DcpAppletMetadata* metadata =
        index.data(MetadataRole).value<DcpAppletMetadata*>();
    DcpAppletObject* applet =
        index.data(AppletRole).value<DcpAppletObject*>();
    QString tdriverID = index.data(TDriverRole).toString();

    if (applet) {
        contentItem->setApplet (applet);
    } else {
        contentItem->setMetadata (metadata);
    }
    contentItem->setTDriverID (tdriverID);
}


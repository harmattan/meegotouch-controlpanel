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

#ifndef DCPCONTENTITEMCELLCREATOR_H
#define DCPCONTENTITEMCELLCREATOR_H

#include <MAbstractCellCreator>
#include <DcpContentItem>

class DcpContentItemCellCreator: public MAbstractCellCreator<DcpContentItem>
{
public:
    enum DataRole {
        MetadataRole = Qt::UserRole + 1,
        AppletRole,
        TDriverRole
    };

    virtual MWidget * createCell (const QModelIndex &index,
                                  MWidgetRecycler &recycler) const;
    virtual void updateCell(const QModelIndex& index, MWidget * cell) const;

private:
	
};

Q_DECLARE_METATYPE (DcpAppletMetadata*)
Q_DECLARE_METATYPE (DcpAppletObject*)


#endif // DCPCONTENTITEMCELLCREATOR_H

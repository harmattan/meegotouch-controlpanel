/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTONIMAGE_H
#define DCPBUTTONIMAGE_H

#include "dcpbuttonalign.h"
class MImageWidget;

class DcpButtonImagePrivate;

/*!
 * THIS CLASS IS DEPRECATED and will be removed soon.
 */
class DcpButtonImage: public DcpButtonAlign 
{
    Q_OBJECT

public:
    DcpButtonImage (MWidget *parent = 0);

    void setImageName (const QString& iconName);
    void setImageFromFile (const QString &fileName);
    
protected:
    virtual QGraphicsLayout *createLayout ();
    MImageWidget *imageWidget ();
private:
    DcpButtonImagePrivate *const d_ptr;
    Q_DISABLE_COPY(DcpButtonImage);
};


#endif // DCPBUTTONIMAGE_H

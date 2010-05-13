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
#ifndef DCPBUTTONTOGGLE_H
#define DCPBUTTONTOGGLE_H

#include "dcpbuttonalign.h"
class MButton;

class DcpButtonTogglePrivate;

/*!
 * THIS CLASS IS DEPRECATED and will be removed soon.
 */
class DcpButtonToggle: public DcpButtonAlign {
    Q_OBJECT
public:
    explicit DcpButtonToggle(MWidget* parent = 0);

    virtual void setText2(const QString& text);
    virtual void setIconId(const QString& iconId);
    QString iconId();
    virtual void setSmallToggle(bool isOn);

signals:
    void smallToggled (bool isOn);

protected slots:
    void onSmallToggled (bool isOn);

protected:
    virtual QGraphicsLayout* createLayout();
    MButton* toggleButton();

private:
    DcpButtonTogglePrivate *const d_ptr;
    Q_DISABLE_COPY(DcpButtonToggle);
};


#endif // DCPBUTTONTOGGLE_H

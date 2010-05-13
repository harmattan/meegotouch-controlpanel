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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include <DcpPage>
#include <QList>

class DcpMainCategory;
class DcpCategoryComponent;
class DcpSingleComponent;
class MContainer;

class DcpMainPage : public DcpPage
{
    Q_OBJECT

public:
    DcpMainPage();
    
    virtual void createContent ();
    virtual void createContentsLate ();

    virtual void reload();

signals:
    void firstShown (void);

public slots:
    void back();
    void shown ();

protected:
    virtual void retranslateUi();
    virtual void hideEvent(class QHideEvent*);

private:
    DcpCategoryComponent *m_RecentlyComp;
    MContainer *m_OtherComp;
    bool                  m_HasContent;
    bool                  m_WasHidden;
    QList<DcpSingleComponent *> m_CategoryButtons;
    friend class Ut_DcpMainPage;
};

#endif


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

#include <QtDebug>

#include "dcppage.h"
#include "pages.h"
#include <MLayout>
#include <QGraphicsLinearLayout>

const PageHandle aHandle(PageHandle::MAIN);

DcpPage::DcpPage() : MApplicationPage() 
{
    createLayout();
}

DcpPage::~DcpPage ()
{
}

QGraphicsLinearLayout*
DcpPage::mainLayout()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

void 
DcpPage::createContent()
{
}

void
DcpPage::createLayout ()
{
    new QGraphicsLinearLayout (Qt::Vertical, centralWidget());     
} 


PageHandle 
DcpPage::handle () const 
{
    return m_Handle;
}

void 
DcpPage::setHandle (
        const PageHandle &handle) 
{
    m_Handle = handle;
}

void 
DcpPage::setHandle (
        PageHandle::PageTypeId       id, 
        const QString               &param)
{

    m_Handle.id = id;
    m_Handle.param = param;
}

PageHandle 
DcpPage::referer () const 
{
    return aHandle;
}

void
DcpPage::setReferer (
        const PageHandle &referer) 
{
    Q_UNUSED(referer);
}

void 
DcpPage::setReferer (
        PageHandle::PageTypeId    id, 
        const QString            &param)
{
    Q_UNUSED(id);
    Q_UNUSED(param);
}

void 
DcpPage::reload ()
{
}

void
DcpPage::appendWidget(QGraphicsWidget* widget)
{
    mainLayout()->addItem(widget);
}

void
DcpPage::setTitleLabel (const QString&)
{
}

void DcpPage::setTitleStyleName (const QString&)
{
}


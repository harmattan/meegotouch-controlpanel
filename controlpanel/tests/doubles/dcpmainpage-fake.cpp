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

#include "dcpmainpage.h"

DcpMainPage::DcpMainPage():
#ifdef MOSTUSED
    m_RecentlyComp(0),
#endif
    m_OtherComp(0),
    m_HasContent(false),
    m_WasHidden(false)
{
}

void
DcpMainPage::createContent ()
{
}

void
DcpMainPage::hideEvent(QHideEvent*)
{
}

void
DcpMainPage::onLoadingFinished ()
{
}

void
DcpMainPage::retranslateUi()
{
}

void
DcpMainPage::shown()
{
}

void
DcpMainPage::reload ()
{
}

void 
DcpMainPage::back()
{
}


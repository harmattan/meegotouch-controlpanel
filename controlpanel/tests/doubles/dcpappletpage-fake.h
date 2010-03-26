/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETPAGE_FAKE_H
#define DCPAPPLETPAGE_FAKE_H
#include "dcpappletpage.h"

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId) :
    DcpPage(),
    m_MainWidget (0),
    m_MissingLabel (0)
{
    Q_UNUSED(applet);
    Q_UNUSED(widgetId);
}


DcpAppletPage::~DcpAppletPage ()
{
}

void
DcpAppletPage::createContent ()
{
}

bool 
DcpAppletPage::hasWidget ()
{
    return true;
}

bool 
DcpAppletPage::hasError ()
{
    return false;
}

void
DcpAppletPage::load ()
{
}

void 
DcpAppletPage::back ()
{
}
void
DcpAppletPage::retranslateUi()
{
}

#endif // DCPAPPLETPAGE_FAKE_H

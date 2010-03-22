/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPPAGE_FAKE_H
#define DCPPAGE_FAKE_H

#include "dcppage.h"


DcpPage::DcpPage () 
{
}


void 
DcpPage::createContent ()
{
}

void 
DcpPage::appendWidget (
        QGraphicsWidget *widget)
{
    Q_UNUSED(widget);
}

void 
DcpPage::removeWidget (
        QGraphicsWidget *widget)
{
    Q_UNUSED(widget);
}
void 
DcpPage::back ()
{
}

#endif //DCPPAGE_FAKE_H

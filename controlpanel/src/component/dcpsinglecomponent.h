/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPSINGLECOMPONENT_H
#define DCPSINGLECOMPONENT_H

#include "dcpcomponent.h"
class DcpBriefWidget;

class DcpSingleComponent: 
    public DcpComponent 
{
    Q_OBJECT

public:
    DcpSingleComponent(DcpComponent *category,
                       const QString &logicalId,
                       const QString &title, 
                       const QString &subTitle="");
    ~DcpSingleComponent ();
public slots:
    void activate ();
};

#endif // DCPSINGLECOMPONENT_H

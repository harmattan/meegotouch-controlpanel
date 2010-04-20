/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPBRIEFCOMPONENT_H
#define DCPBRIEFCOMPONENT_H

#include "dcpcomponent.h"
class DcpAppletObject;
class DcpBriefWidget;

/*
 * FIXME: This class is practically empty, it should be removed.
 */
class DcpBriefComponent: 
    public DcpComponent 
{
    Q_OBJECT
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)

public:
    DcpBriefComponent(DcpAppletObject *applet, 
            DcpComponent        *category,
            const QString       &logicalId = "");
    ~DcpBriefComponent ();


    void setApplet (DcpAppletObject *applet);

public slots:
    void activate ();

private:
    DcpBriefWidget *m_BriefWidget;
    friend class Ut_DcpBriefComponent;
};

#endif // DCPBRIEFCOMPONENT_H

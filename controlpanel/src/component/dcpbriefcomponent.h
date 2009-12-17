/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPBRIEFCOMPONENT_H
#define DCPBRIEFCOMPONENT_H

#include "dcpcomponent.h"
class DcpAppletMetadata;
class DcpBriefWidget;

class DcpBriefComponent: public DcpComponent 
{
    Q_OBJECT
    Q_PROPERTY(QString mattiID READ mattiID WRITE setMattiID)

public:
    DcpBriefComponent(DcpAppletMetadata* metadata, DcpCategory *category,
                      const QString& logicalId="");
    ~DcpBriefComponent();
    void setMetadata(DcpAppletMetadata* metadata);

    // Composite Pattern Interface, do nothing
    virtual void add(DcpComponent *) {}
    virtual void remove(DcpComponent *) {}
    virtual void createContents() {}

    QString mattiID();
    void setMattiID(const QString &mattiID);

private:
	DcpBriefWidget* m_BriefWidget;
    QString m_mattiID;
};

#endif // DCPBRIEFCOMPONENT_H

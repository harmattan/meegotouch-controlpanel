/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPSINGLECOMPONENT_H
#define DCPSINGLECOMPONENT_H

#include <MContentItem>
#include "pages.h"

class DcpSingleComponent: public MContentItem
{
    Q_OBJECT
    Q_PROPERTY (QString mattiID READ mattiID)

public:
    DcpSingleComponent(QGraphicsWidget* parent,
                       const QString &logicalId,
                       const QString &title,
                       const QString &subTitle="");
    ~DcpSingleComponent ();

    void setSubPage (const PageHandle &subPage) { m_SubPage = subPage; }
    const PageHandle &subPage() const { return m_SubPage; }

    QString mattiID() const { return m_MattiID; }

public slots:
    void activate ();

private:
    QString m_MattiID;
    PageHandle m_SubPage;

    friend class Ut_DcpSingleComponent;
};

#endif // DCPSINGLECOMPONENT_H


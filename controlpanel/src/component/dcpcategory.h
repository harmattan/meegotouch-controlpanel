/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPCATEGORY_H
#define DCPCATEGORY_H

#include "dcpcomponent.h"

class DcpCategory : public DcpComponent
{
    Q_OBJECT
public:
    explicit DcpCategory(const QString& title, QGraphicsWidget *parent = 0,
                         const QString& logicalId="");
    // Composite Pattern Interface
    virtual void add(DcpComponent *component);
    virtual void remove(DcpComponent *component);
    int childCount() { return m_Children.count(); }
    virtual DcpComponent* child(int i) const;
    virtual DcpCategory* category() const {return 0;}
public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    QString m_LogicalId;
    QVector<DcpComponent*> m_Children;
};
#endif //DCPCATEGORY_H

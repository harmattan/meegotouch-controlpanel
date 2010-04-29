/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef MCPMOSTUSEDCATEGORY_H
#define MCPMOSTUSEDCATEGORY_H

#include <DcpMainCategory>

#include "maintranslations.h"

class DcpAppletMetadata;

class DcpAppletButtons :
    public DcpMainCategory
{
    Q_OBJECT

public:
    DcpAppletButtons (
            const DcpCategoryInfo  *categoryInfo,
            const QString          &title = "",
            QGraphicsWidget        *parent = 0);
    ~DcpAppletButtons ();

    void setCategoryInfo (const DcpCategoryInfo  *categoryInfo);

    void addComponent (
            DcpAppletMetadata *metadata);

    virtual bool reload();

protected:
    virtual void createContents();

private:
    void markAllInactive();

    const DcpCategoryInfo  *m_CategoryInfo;
    friend class Ut_DcpAppletButtons;
};

#endif


/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpspaceritem.h"

#if 0
DcpSpacerItem::DcpSpacerItem(DuiWidget *parent,
                             int width, int height,
                             QSizePolicy::Policy hPolicy,
                             QSizePolicy::Policy vPolicy)
              :QGraphicsWidget(parent)
{
    setSizePolicy(hPolicy, vPolicy);
    setMinimumHeight(height);
    setMinimumWidth(width);

    if (hPolicy == QSizePolicy::Maximum ||
        hPolicy == QSizePolicy::Fixed)
    {
        setMaximumWidth(width);
    }

    if (vPolicy == QSizePolicy::Maximum ||
        vPolicy == QSizePolicy::Fixed)
    {
        setMaximumHeight(height);
    }
}

DcpSpacerItem::~DcpSpacerItem()
{
}

void DcpSpacerItem::changeSize(int width, int height,
                               QSizePolicy::Policy hPolicy,
                               QSizePolicy::Policy vPolicy)
{
    setMinimumHeight(height);
    setMaximumHeight(height);
    setMinimumWidth(width);
    setMaximumWidth(width);
    setSizePolicy(hPolicy, vPolicy);
}
#endif

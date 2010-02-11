/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPSPACERITEM_H
#define DCPSPACERITEM_H

#include <DuiWidget>

#if 0
/*!
 * I believe this class is not used in the code anywhere.
 * FIXME: Maybe this class should be removed.
 */
class DcpSpacerItem : public QGraphicsWidget
{
public:
    DcpSpacerItem(DuiWidget *parent, int width, int height,
                  QSizePolicy::Policy hPolicy = QSizePolicy::Minimum,
                  QSizePolicy::Policy vPolicy = QSizePolicy::Minimum);
    virtual ~DcpSpacerItem();

    void changeSize(int width, int height,
                    QSizePolicy::Policy hPolicy = QSizePolicy::Minimum,
                    QSizePolicy::Policy vPolicy = QSizePolicy::Minimum);

};
#endif // DCPSPACERITEM_H
#endif

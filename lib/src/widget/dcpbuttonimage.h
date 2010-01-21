/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTONIMAGE_H
#define DCPBUTTONIMAGE_H

#include "dcpbuttonalign.h"
class DuiImageWidget;

class DcpButtonImage: public DcpButtonAlign 
{
    Q_OBJECT

public:
    DcpButtonImage (DuiWidget *parent = 0);

    void setImageName (const QString& imageName);

protected:
    virtual QGraphicsLayout *createLayout ();
    DuiImageWidget *imageWidget ();
    DuiImageWidget *m_Image;
};


#endif // DCPBUTTONIMAGE_H

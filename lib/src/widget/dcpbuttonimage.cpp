/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttonimage.h"
#include "dcpbuttonimage_p.h"

#include <DuiButton>
#include <DuiImageWidget>
#include <QGraphicsLinearLayout>
#include <QtDebug>

DcpButtonImage::DcpButtonImage (
        DuiWidget *parent)
: DcpButtonAlign (parent), 
  d_ptr(new DcpButtonImagePrivate)
{
    setLayout (createLayout());
}

void 
DcpButtonImage::setImageName (
        const QString &imageName)
{
    Q_ASSERT (imageWidget());
    imageWidget()->setImage (imageName);
}

QGraphicsLayout *
DcpButtonImage::createLayout ()
{
    // we could use the icon of the button here, if it could be set to a custom
    // file
    d_ptr->image = new DuiImageWidget (this);
    d_ptr->image->setObjectName ("DcpButtonImage");
    d_ptr->image->setAspectRatioMode (Qt::IgnoreAspectRatio);

    setAlignedWidget (d_ptr->image);

    return DcpButtonAlign::createLayout();
}


DuiImageWidget *
DcpButtonImage::imageWidget ()
{
    return d_ptr->image;
}




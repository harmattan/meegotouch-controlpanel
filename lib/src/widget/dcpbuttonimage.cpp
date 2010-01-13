/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttonimage.h"

#include <DuiButton>
#include <DuiImage>
#include <QGraphicsLinearLayout>
#include <QtDebug>

DcpButtonImage::DcpButtonImage (
        DuiWidget *parent)
: DcpButtonAlign (parent)
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
    m_Image = new DuiImage (this);
    m_Image->setObjectName ("DcpButtonImage");
    m_Image->setZoomRatioMode (Qt::IgnoreAspectRatio);

    setAlignedWidget (m_Image);

    return DcpButtonAlign::createLayout();
}


DuiImage *
DcpButtonImage::imageWidget ()
{
    return m_Image;
}




/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttonimage.h"
#include "dcpbuttonimage_p.h"

#include <MButton>
#include <MImageWidget>
#include <QGraphicsLinearLayout>
#include <QtDebug>

#include "dcpdebug.h"

DcpButtonImage::DcpButtonImage (
        MWidget *parent)
: DcpButtonAlign (parent), 
  d_ptr(new DcpButtonImagePrivate)
{
    setLayout (createLayout());
}

/*!
 * Calls MImageWidget::setImage() with the provided strings, in other words it
 * sets the image from an icon name in the theme.
 */
void 
DcpButtonImage::setImageName (
        const QString &iconName)
{
    Q_ASSERT (imageWidget());
    DCP_DEBUG("calling setImage(%s)", DCP_STR(iconName));
    imageWidget()->setImage (iconName);
    d_ptr->fileName = "";
}

/*!
 * Sets the image from an image file.
 */
void 
DcpButtonImage::setImageFromFile (
        const QString &fileName)
{
    bool    success;
    QImage  image;

    /*
     * The image file might be big, so we need a little speed up here, otherwise
     * the paging effect is blocked when we go back to the main page.
     */
    if (fileName == d_ptr->fileName)
        return;

    DCP_DEBUG("calling QImage::load(%s)", DCP_STR(fileName));
    success = image.load (fileName);
    if (!success) {
        DCP_WARNING ("The image was not loaded from %s", DCP_STR(fileName));
        return;
    }

    image = image.scaled(100, 100, Qt::KeepAspectRatio);
    imageWidget()->setImage (image);

    d_ptr->fileName = fileName;
}


QGraphicsLayout *
DcpButtonImage::createLayout ()
{
    // we could use the icon of the button here, if it could be set to a custom
    // file
    d_ptr->image = new MImageWidget (this);
    d_ptr->image->setObjectName ("DcpButtonImage");
    d_ptr->image->setAspectRatioMode (Qt::IgnoreAspectRatio);

    setAlignedWidget (d_ptr->image);

    return DcpButtonAlign::createLayout();
}


MImageWidget *
DcpButtonImage::imageWidget ()
{
    return d_ptr->image;
}




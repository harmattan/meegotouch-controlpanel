#include "dcpbutton2image.h"

#include <DuiImage>
#include <DuiLayout>


DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setPixmap (const QPixmap* pixmap)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setPixmap(*pixmap);
}

void DcpButton2Image::setImageName (const QString& imageName)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setImageName(imageName);
}

void DcpButton2Image::setBorderPixmap (const QPixmap* pixmap)
{
    Q_UNUSED (pixmap);
    // TODO
}

DuiLayout* DcpButton2Image::createLayout()
{
    // image:
    DuiImage* image = new DuiImage(this);
    image->setObjectName("DcpButtonImage");

    setAlignedWidget(image);
    return DcpButton2Align::createLayout();
}


DuiImage* DcpButton2Image::imageWidget()
{
    return qobject_cast<DuiImage*>(alignedWidget());
}




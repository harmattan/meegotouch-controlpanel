#include "dcpbutton2image.h"

#include <DuiImage>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>


DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setPixmap (const QPixmap* pixmap)
{
    Q_ASSERT(imageWidget());
//    imageWidget()->setPixmap(*pixmap);
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

#include <DuiTheme>
DuiLayout* DcpButton2Image::createLayout()
{
    // image:
    DuiImage* image = new DuiImage(this);
    image->setObjectName("DcpButtonImage");
#if 0
    // border
    m_BorderWidget = new DuiImage(this);
    m_BorderWidget->setObjectName("DcpButtonImageBorder");
    // TODO: make this work
//    m_BorderWidget->setImageName("Thumbnail-frame");

    // put border on image:
    DuiLayout* imageLayout = new DuiLayout(0);
    DuiLinearLayoutPolicy* imagePolicy = new DuiLinearLayoutPolicy (imageLayout,
                                                               Qt::Vertical);
    imagePolicy->addItemAtPosition(m_BorderWidget, 0, Qt::AlignCenter);
    image->setLayout(imageLayout);
#endif

    setAlignedWidget(image);
    return DcpButton2Align::createLayout();
}


DuiImage* DcpButton2Image::imageWidget()
{
    return qobject_cast<DuiImage*>(alignedWidget());
}




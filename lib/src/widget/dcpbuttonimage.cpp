#include "dcpbuttonimage.h"

#include <DuiButton>
#include <DuiImage>
#include <QGraphicsLinearLayout>
#include <QtDebug>

DcpButtonImage::DcpButtonImage(DuiWidget* parent)
    : DcpButtonAlign(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButtonImage::setImageName (const QString& imageName)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setImage(imageName);
}

QGraphicsLayout* DcpButtonImage::createLayout()
{
    // image:
    // we could use the icon of the button here, if it could be set to a custom file
    m_Image = new DuiImage (this);
    m_Image->setObjectName("DcpButtonImage");
    m_Image->setZoomRatioMode(Qt::IgnoreAspectRatio);

    setAlignedWidget(m_Image);
    return DcpButtonAlign::createLayout();
}


DuiImage* DcpButtonImage::imageWidget()
{
    return m_Image;
}




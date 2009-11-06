#include "dcpbutton2image.h"

#include <DuiButton>
#include <DuiImage>
#include <QGraphicsLinearLayout>
#include <QtDebug>

DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setImageName (const QString& imageName)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setImage(imageName);
}

QGraphicsLayout* DcpButton2Image::createLayout()
{
    // image:
    // we could use the icon of the button here, if it could be set to a custom file
    m_Image = new DuiImage (this);
    m_Image->setObjectName("DcpButtonImage");
    m_Image->setZoomRatioMode(Qt::IgnoreAspectRatio);

    setAlignedWidget(m_Image);
    return DcpButton2Align::createLayout();
}


DuiImage* DcpButton2Image::imageWidget()
{
//    return qobject_cast<DuiButton*>(alignedWidget());
    return m_Image;
}




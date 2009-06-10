#include "dcpbutton2image.h"

#include <DuiButton>
#include <DuiImage>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>

DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setImageName (const QString& imageName)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setImageName(imageName);
}

DuiLayout* DcpButton2Image::createLayout()
{
    // border:
    DuiButton* border = new DuiButton(this); // we use button here because
                                            // DuiImage not yet supports the
                                            // features we would need:
                                            // setting the image from css etc
    border->setContentsMargins(0,0,0,0);
    border->setObjectName("DcpButtonImageBorder");
    border->setAcceptedMouseButtons(0);

    // image:
    // we could use the icon of the button here, if it could be set to a custom file
    m_Image = new DuiImage (this);
    m_Image->setObjectName("DcpButtonImage");
    m_Image->setZoomRatioMode(Qt::IgnoreAspectRatio);

    DuiLayout* borderLayout = new DuiLayout(border);
    borderLayout->setAnimator(0);
    borderLayout->setContentsMargins(0,0,0,0);
    DuiLinearLayoutPolicy* borderLayoutPolicy = new DuiLinearLayoutPolicy(
                                                    borderLayout, Qt::Vertical);
    borderLayoutPolicy->addItemAtPosition(m_Image, 0);

    setAlignedWidget(border);
    return DcpButton2Align::createLayout();
}


DuiImage* DcpButton2Image::imageWidget()
{
//    return qobject_cast<DuiButton*>(alignedWidget());
    return m_Image;
}




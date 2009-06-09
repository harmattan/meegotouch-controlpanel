#include "dcpbutton2image.h"

#include <DuiButton>
#include <DuiLayout>

DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setImageName (const QString& imageName)
{
    Q_ASSERT(imageWidget());
    imageWidget()->setIconID(imageName);
}

DuiLayout* DcpButton2Image::createLayout()
{
    // image:
    DuiButton* image = new DuiButton(this); // we use button here because
                                            // DuiImage not yet supports the 
                                            // features we would need:
                                            // setting the image from css etc
    image->setObjectName("DcpButtonImage");
    image->setAcceptedMouseButtons(0);

    setAlignedWidget(image);
    return DcpButton2Align::createLayout();
}


DuiButton* DcpButton2Image::imageWidget()
{
    return qobject_cast<DuiButton*>(alignedWidget());
}




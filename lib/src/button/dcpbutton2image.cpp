#include "dcpbutton2image.h"

#include <DuiImage>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>


DcpButton2Image::DcpButton2Image(DuiWidget* parent)
    : DcpButton2(parent, false)
{
    this->setLayout(this->createLayout());
}

void DcpButton2Image::setPixmap (const QPixmap* pixmap)
{
    m_Image->setPixmap(*pixmap);
}

void DcpButton2Image::setImageName (const QString& imageName)
{
    m_Image->setImageName(imageName);
}

void DcpButton2Image::setBorderPixmap (const QPixmap* pixmap)
{
    Q_UNUSED (pixmap);
    // TODO
}

DuiLayout* DcpButton2Image::createLayout()
{
    // text TODO XXX contains boilerplate (beginning and end)
    DuiLayout* textLayout = DcpButton2::createLayout();
    qreal left, right, top, bottom;
    textLayout->getContentsMargins(&left, &top, &right, &bottom);
    textLayout->setContentsMargins(0,0,right,0);

    // image:
    m_Image = new DuiImage(this);
    m_Image->setObjectName("DcpButtonImage");

    // putting them together on the layout:
    DuiLayout* layout = new DuiLayout(0);
    layout->setAnimator(0);
    layout->setContentsMargins(left,top,right,bottom);
    DuiLinearLayoutPolicy* vertLayoutPolicy = new DuiLinearLayoutPolicy(layout,
            Qt::Horizontal);
    vertLayoutPolicy->addItemAtPosition(textLayout, 0);
    vertLayoutPolicy->addItemAtPosition(m_Image, 1);

    return layout;
}


#include "dcpimage.h"

#include <QPixmap>

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>
#include "dcpbuttonview.h"

const float MINIMALIZE = 0.9f;

const float MINIMALIZEIMAGE = 0.8f;

const float TRANSLATEX = 10;
const float TRANSLATEY = 5;

DcpImage::DcpImage(const QString& label, const QString& image, int width, int upHeight, int downHeight, int imageWidth, const QString& cssButton, const QString& cssLabel)
{

    m_Layout = new DuiGridLayout();

    m_Layout->setColumnMinimumWidth ( 0, width );
    
    m_Layout->setColumnMaximumWidth ( 0, width );
    
    m_Layout->setRowMinimumHeight ( 0, upHeight );
    m_Layout->setRowMinimumHeight ( 1, downHeight );
    

    m_Layout->setRowMaximumHeight ( 0, upHeight );
    m_Layout->setRowMaximumHeight ( 1, downHeight );

    /* //only test
    for (int yy =0; yy<3; yy++)
        for (int xx =0; xx<3; xx++)
            m_Layout->addItem(new DuiButton("text"), xx, yy, Qt::AlignCenter);
     */

    m_Button = new DuiButton("");

    // TODO: this moves to the view config file when updating to newer dui
    m_Button->setView(new DcpButtonView(m_Button));
    // --

    m_Button->setObjectName(cssButton);

    m_Button->setMinimumWidth(width);
    m_Button->setMaximumWidth(width);
    m_Button->setMinimumHeight(upHeight + downHeight);
    m_Button->setMaximumHeight(upHeight + downHeight);


    m_Label = new DuiLabel(label);
    m_Label->setObjectName(cssLabel);
    m_Label->setMinimumWidth(width*MINIMALIZE);
    m_Label->setMaximumWidth(width*MINIMALIZE);
    m_Label->setMinimumHeight(upHeight);
    m_Label->setMaximumHeight(upHeight);
    m_Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_Label->setAcceptedMouseButtons(0);

    //QPixmap *tmpPixmap = new QPixmap(image);
    //QPixmap *copyPixmap = new QPixmap(tmpPixmap->copy(0 , 0, 50, 50));
    //m_Image = new DuiImage(copyPixmap);
    
    m_Image = new DuiImage(image);
      
    //m_DownLabel->setObjectName(cssDownLabel);
    m_Image->setMinimumWidth(imageWidth*MINIMALIZEIMAGE);
    m_Image->setMaximumWidth(imageWidth*MINIMALIZEIMAGE);
    m_Image->setMinimumHeight(downHeight*MINIMALIZEIMAGE);
    m_Image->setMaximumHeight(downHeight*MINIMALIZEIMAGE);
//    m_Image->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_Image->setAcceptedMouseButtons(0);

    m_Layout->addItem(m_Button, 0, 0, 2, 1, Qt::AlignCenter);
    m_Layout->addItem(m_Label, 0, 0, Qt::AlignCenter);
    m_Layout->addItem(m_Image, 1, 0, Qt::AlignRight|Qt::AlignVCenter);

    connect(m_Button, SIGNAL(clicked()), this, SLOT(labelButtonClicked()));

    m_Button->setZValue(1);
    
    m_Label->setZValue(2);
    m_Image->setZValue(3);

    m_Image->translate(-TRANSLATEX, -TRANSLATEY);
}


DuiGridLayout* DcpImage::layout()
{
    return m_Layout;
}

void DcpImage::labelButtonClicked()
{
    qDebug() << "labelButtonClicked";
    emit clicked("labelButtonClicked");
}


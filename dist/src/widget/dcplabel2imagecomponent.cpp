#include "dcplabel2imagecomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiimage.h>

#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

DcpLabel2ImageComponent::DcpLabel2ImageComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
    m_Type = DCPLABEL2IMAGE;

    createContents();
}


DcpLabel2ImageComponent::~DcpLabel2ImageComponent()
{
}


void DcpLabel2ImageComponent::createContents()
{

    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

    QString image = metadata()->image();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int labelWidth = 170;   //2
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int triangleSize = 20;

    int width = smallWidth*2 + labelWidth + spaceWidth + imageWidth;
    
    int height = 100;

    int imageSize = 70;     //3
    
    initColumn(smallWidth, smallWidth, labelWidth, spaceWidth, imageWidth );
    initRow2(height/2);


    m_BigButton = newButton(width, height, "BigButton");
    m_UpLabel = newLabel(height/2, upLabel, "UpLabel", Qt::AlignLeft|Qt::AlignBottom);
    m_TriangleButton = newButton(triangleSize, "TriangleButton");
    m_TriangleButton->translate(0,7); //bad

    
    m_Image =  newImage(image, imageSize, 2);

    m_DownLabel = newLabel(height/2, downLabel, "DownLabel", Qt::AlignLeft|Qt::AlignTop);


    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignCenter);

    m_GridLayout->addItem(m_Image, 0, 4, 2, 1, Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));


    initLayout();
}

#include "dcplabel2imagecomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiimage.h>

#include <duitheme.h>

#include "dcpappletmetadata.h"

DcpLabel2ImageComponent::DcpLabel2ImageComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent),
    m_Alignment(metadata->align())
{

    m_Type = DCPLABEL2IMAGE;
    m_EnableToggle = metadata->toggle();

    m_UpLabelText = this->metadata()->text1();
    m_DownLabelText = this->metadata()->text2();


    //dummy, must modify constructor  
    m_SmallWidth = 20;    //0,1
    m_SpaceWidth = 5;     //3
    m_ImageWidth = 115;     //4

    m_Width = m_SmallWidth*2 + m_LabelWidth + m_SpaceWidth + m_ImageWidth;
    
    m_Height = 100;

    m_ImageSize = 64;     //3

    createContents();
}


DcpLabel2ImageComponent::~DcpLabel2ImageComponent()
{

    delete m_BigButton;
    delete m_TriangleButton;

    delete m_UpLabel;
    delete m_DownLabel;
    delete m_Image;
}


void DcpLabel2ImageComponent::createContents()
{
  
    m_BigButton = newButton(m_Width, m_Height, "BigButton");
    m_UpLabel = newLabel(m_Height/2, m_UpLabelText, "UpLabel", Qt::AlignLeft|Qt::AlignBottom);
    m_TriangleButton = newButton(16, "TriangleButton");
    m_TriangleButton->translate(0,7); //bad

  //  m_SpacerButton = newButton(5, m_Height*0.8f, "SpacerButton");
 
    //m_Image =  newImage(metadata()->image(), m_ImageSize, 2);
    m_Image =  newImage(metadata()->image(), m_ImageSize, 2);

    m_DownLabel = newLabel(m_Height/2, m_DownLabelText, "DownLabel", Qt::AlignLeft|Qt::AlignTop);

    initRow2(m_Height/2);

    if (m_Alignment==Qt::AlignLeft)
        initLeft();
    else
        initRight();


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();
}


void DcpLabel2ImageComponent::initRight()
{


    initColumn(m_SmallWidth, m_SmallWidth, m_LabelWidth, m_SpaceWidth, m_ImageWidth );

    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignCenter);

//m_GridLayout->addItem(m_SpacerButton, 0, 3, 2, 1, Qt::AlignCenter);

    m_GridLayout->addItem(m_Image, 0, 4, 2, 1, Qt::AlignCenter);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);

}


void DcpLabel2ImageComponent::initLeft()
{

    initColumn(m_ImageWidth, m_SpaceWidth, m_SmallWidth, m_SmallWidth, m_LabelWidth);
  
    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

//m_GridLayout->addItem(m_SpacerButton, 0, 2, 2, 1, Qt::AlignCenter);

    m_GridLayout->addItem(m_TriangleButton, 0, 3, Qt::AlignCenter);

    m_GridLayout->addItem(m_Image, 0, 0, 2, 1, Qt::AlignCenter);
    m_Image->translate(15,0); // Qt::AlignCenter BUG

    m_GridLayout->addItem(m_UpLabel, 0, 4, Qt::AlignCenter);
    
    m_GridLayout->addItem(m_DownLabel, 1, 3, 1, 2, Qt::AlignCenter);
}

#include "dcplabel2imagecomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiimage.h>

#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>



DcpLabel2ImageComponent::DcpLabel2ImageComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpLabel2ImageComponent::~DcpLabel2ImageComponent() {
}


void
DcpLabel2ImageComponent::createContents()
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
    
    
    bool enable = true;

    m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 0, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 1, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 1, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 2, labelWidth );
    m_GridLayout->setColumnMaximumWidth ( 2, labelWidth );

    m_GridLayout->setColumnMinimumWidth ( 3, spaceWidth );
    m_GridLayout->setColumnMaximumWidth ( 3, spaceWidth );

    m_GridLayout->setColumnMinimumWidth ( 4, imageWidth );
    m_GridLayout->setColumnMaximumWidth ( 4, imageWidth );


    for (int i=0;i<2;i++) {
        m_GridLayout->setRowMinimumHeight ( i, height/2 );
        m_GridLayout->setRowMaximumHeight ( i, height/2 );
    }

    m_BigButton = new DuiButton;

    m_BigButton->setObjectName("BigButton");
    m_BigButton->setMinimumWidth(width);
    m_BigButton->setMaximumWidth(width);
    m_BigButton->setMinimumHeight(height);
    m_BigButton->setMaximumHeight(height);


    m_Image = new DuiImage(image);
    m_Image->setMinimumWidth(imageSize);
    m_Image->setMaximumWidth(imageSize);
    m_Image->setMinimumHeight(imageSize);
    m_Image->setMaximumHeight(imageSize);
//    m_Image->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_Image->setAcceptedMouseButtons(0);

    m_Image->setBorders(2, 2, 2, 2);
    m_Image->setBackgroundColor(QColor(128, 128, 128));

    m_TriangleButton = new DuiButton;
    m_TriangleButton->setObjectName("TriangleButton");
    m_TriangleButton->setMinimumWidth(triangleSize);
    m_TriangleButton->setMaximumWidth(triangleSize);
    m_TriangleButton->setMinimumHeight(triangleSize);
    m_TriangleButton->setMaximumHeight(triangleSize);

    
    m_UpLabel = new DuiLabel(upLabel);
    m_UpLabel->setObjectName("UpLabel");
//    m_UpLabel->setMinimumWidth(labelWidth);
//    m_UpLabel->setMaximumWidth(labelWidth);
    m_UpLabel->setMinimumHeight(height/2);
    m_UpLabel->setMaximumHeight(height/2);
    m_UpLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    m_UpLabel->setAcceptedMouseButtons(0);


    m_DownLabel = new DuiLabel(downLabel);
    m_DownLabel->setObjectName("DownLabel");
//    m_UpLabel->setMinimumWidth(smallWidth+labelWidth);
//    m_UpLabel->setMaximumWidth(smallWidth+labelWidth);
    m_UpLabel->setMinimumHeight(height/2);
    m_UpLabel->setMaximumHeight(height/2);
    m_DownLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_DownLabel->setAcceptedMouseButtons(0);



    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignBottom);

    m_GridLayout->addItem(m_Image, 0, 4, 2, 1, Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));


    m_BigButton->setZValue(1);
    m_TriangleButton->setZValue(2);
    m_Image->setZValue(3);
    m_UpLabel->setZValue(4);
    m_DownLabel->setZValue(5);


    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void
DcpLabel2ImageComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}


void DcpLabel2ImageComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpLabel2ImageComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void
DcpLabel2ImageComponent::switchToSubPage()
{
    emit openSubPage(subPage());
}

void
DcpLabel2ImageComponent::bigClicked()
{
    switchToSubPage();
}


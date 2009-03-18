#include "dcplabelbuttoncomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>



DcpLabelButtonComponent::DcpLabelButtonComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpLabelButtonComponent::~DcpLabelButtonComponent() {
}


void DcpLabelButtonComponent::createContents()
{

    QString upLabel = metadata()->text1();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int labelWidth = 170;   //2
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int triangleSize = 20;

    int width = smallWidth*2 + labelWidth + spaceWidth + imageWidth;
    
    int height = 100;

    int imageSize = 70;     
    
    
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


    m_GridLayout->setRowMinimumHeight ( 0, height );
    m_GridLayout->setRowMaximumHeight ( 0, height );
 

    m_BigButton = new DuiButton;

    m_BigButton->setObjectName("BigButton");
    m_BigButton->setMinimumWidth(width);
    m_BigButton->setMaximumWidth(width);
    m_BigButton->setMinimumHeight(height);
    m_BigButton->setMaximumHeight(height);


    m_SmallButtonOn = new DuiButton;
    m_SmallButtonOn->setObjectName("SmallButtonOn");
    m_SmallButtonOn->setMinimumWidth(imageSize);
    m_SmallButtonOn->setMaximumWidth(imageSize);
    m_SmallButtonOn->setMinimumHeight(imageSize);
    m_SmallButtonOn->setMaximumHeight(imageSize);

    m_SmallButtonOff = new DuiButton;
    m_SmallButtonOff->setObjectName("SmallButtonOff");
    m_SmallButtonOff->setMinimumWidth(imageSize);
    m_SmallButtonOff->setMaximumWidth(imageSize);
    m_SmallButtonOff->setMinimumHeight(imageSize);
    m_SmallButtonOff->setMaximumHeight(imageSize);

    m_DisableButton = new DuiButton;
    m_DisableButton->setObjectName("SmallButtonDisable");
    m_DisableButton->setMinimumWidth(imageSize);
    m_DisableButton->setMaximumWidth(imageSize);
    m_DisableButton->setMinimumHeight(imageSize);
    m_DisableButton->setMaximumHeight(imageSize);


    m_TriangleButton = new DuiButton;
    m_TriangleButton->setObjectName("TriangleButton");
    m_TriangleButton->setMinimumWidth(triangleSize);
    m_TriangleButton->setMaximumWidth(triangleSize);
    m_TriangleButton->setMinimumHeight(triangleSize);
    m_TriangleButton->setMaximumHeight(triangleSize);


    m_Label = new DuiLabel(upLabel);
    m_Label->setObjectName("UpLabel");
//    m_UpLabel->setMinimumWidth(labelWidth);
//    m_UpLabel->setMaximumWidth(labelWidth);
    m_Label->setMinimumHeight(height);
    m_Label->setMaximumHeight(height);
    m_Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_Label->setAcceptedMouseButtons(0);

  
    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignVCenter);

    m_GridLayout->addItem(m_SmallButtonOn, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_SmallButtonOff, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_DisableButton, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_Label, 0, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));

    setEnable(enable);

    m_BigButton->setZValue(1);
    m_TriangleButton->setZValue(2);
    m_SmallButtonOn->setZValue(3);
    m_SmallButtonOff->setZValue(4);
    m_DisableButton->setZValue(5);
    m_Label->setZValue(6);


    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void DcpLabelButtonComponent::setEnable(bool enable) {

    m_Enable = enable;

    if (m_Enable) {
        m_SmallButtonOn->show();
        m_SmallButtonOff->hide();
        m_DisableButton->hide();
    } else {
        m_SmallButtonOn->hide();
        m_SmallButtonOff->hide();
        m_DisableButton->show();
    }

}


void DcpLabelButtonComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}


void DcpLabelButtonComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpLabelButtonComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void DcpLabelButtonComponent::switchToSubPage()
{
    emit openSubPage(subPage());
}

void DcpLabelButtonComponent::bigClicked()
{
    switchToSubPage();
}


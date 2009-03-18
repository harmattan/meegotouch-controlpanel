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
    DcpBasicComponent(category, metadata, title, parent)
{

  createContents();
}


DcpLabelButtonComponent::~DcpLabelButtonComponent()
{
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
    
    
    m_Enable = true;

    initColumn(smallWidth, smallWidth, labelWidth, spaceWidth, imageWidth );
    initRow(height);

    
    m_BigButton = newButton(width, height, "BigButton");
    m_UpLabel = newLabel(height, upLabel, "UpLabel", Qt::AlignLeft|Qt::AlignVCenter);
    m_TriangleButton = newButton(20, "TriangleButton");


    m_SmallButtonOn = newButton(imageSize, "SmallButtonOn");
    m_SmallButtonOff = newButton(imageSize, "SmallButtonOff");
    m_DisableButton = newButton(imageSize, "SmallButtonDisable");


    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignVCenter);

    m_GridLayout->addItem(m_SmallButtonOn, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_SmallButtonOff, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_DisableButton, 0, 4, Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));

    setEnable(m_Enable);

    initLayout();
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

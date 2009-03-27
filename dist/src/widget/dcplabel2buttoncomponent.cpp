#include "dcplabel2buttoncomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>



DcpLabel2ButtonComponent::DcpLabel2ButtonComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
  m_Type = DCPLABEL2BUTTON;
   
  createContents();
}


DcpLabel2ButtonComponent::~DcpLabel2ButtonComponent()
{

    delete m_BigButton;
    delete m_UpLabel;
    delete m_TriangleButton;

    delete m_DownLabel;

    delete m_SmallButtonOn;
    delete m_SmallButtonOff;
    delete m_DisableButton;
}


void DcpLabel2ButtonComponent::createContents()
{

    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int width = smallWidth*2 + m_LabelWidth + spaceWidth + imageWidth;
    
    int height = 100;

    int imageSize = 70;     
    
    
    initColumn(smallWidth, smallWidth, m_LabelWidth, spaceWidth, imageWidth );
    initRow2(height/2);

    
    m_BigButton = newButton(width, height, "BigButton");
    m_UpLabel = newLabel(height/2, upLabel, "UpLabel", Qt::AlignLeft|Qt::AlignBottom);
    m_TriangleButton = newButton(m_TriangleSize, "TriangleButton");

    m_DownLabel = newLabel(height/2, downLabel, "DownLabel", Qt::AlignLeft|Qt::AlignTop);


    m_SmallButtonOn = newButton(imageSize, "SmallButtonOn");
    m_SmallButtonOff = newButton(imageSize, "SmallButtonOff");
    m_DisableButton = newButton(imageSize, "SmallButtonDisable");


    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignBottom);

    m_GridLayout->addItem(m_SmallButtonOn, 0, 4, 2, 1, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_SmallButtonOff, 0, 4, 2, 1,  Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_DisableButton, 0, 4, 2, 1,  Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));

    setEnableButton(true);

    initLayout();
}


void DcpLabel2ButtonComponent::setEnableButton(bool enable) {

    m_EnableButton = enable;

    if (m_EnableButton) {
        m_SmallButtonOn->show();
        m_SmallButtonOff->hide();
        m_DisableButton->hide();
    } else {
        m_SmallButtonOn->hide();
        m_SmallButtonOff->hide();
        m_DisableButton->show();
    }

}

void DcpLabel2ButtonComponent::smallClickedOn(){}
void DcpLabel2ButtonComponent::smallClickedOff(){}
void DcpLabel2ButtonComponent::disableClicked(){}


/*
void
DcpLabel2ButtonComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}


void DcpLabel2ButtonComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpLabel2ButtonComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void
DcpLabel2ButtonComponent::switchToSubPage()
{
    qDebug() << "DCP" << "EMIT";
    emit openSubPage(subPage());
}

void
DcpLabel2ButtonComponent::bigClicked()
{
    switchToSubPage();
}
*/

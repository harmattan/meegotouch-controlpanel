#include "dcplabel2togglecomponent.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include "dcpbutton.h"

#include <QDebug>

DcpLabel2ToggleComponent::DcpLabel2ToggleComponent( DcpCategory *category,
                                                    DcpAppletMetadata * metadata,
                                                    const QString& title,
                                                    QGraphicsWidget *parent):
                          DcpBasicComponent(category, metadata, title, parent),
   m_Alignment(metadata->align())
{
    m_Type = DCPLABEL2BUTTON;
    m_EnableSmallToggle = metadata->smallToggle();
    createContents();

}


DcpLabel2ToggleComponent::~DcpLabel2ToggleComponent()
{
}


void DcpLabel2ToggleComponent::createContents()
{

	if ( m_Alignment==Qt::AlignLeft ) {
        m_Button = new DcpButton(DCPLABEL2TOGGLE);
				m_Button->setAlignment(Qt::AlignLeft);
		}
    else {
        m_Button = new DcpButton(DCPLABEL2TOGGLE);
				m_Button->setAlignment(Qt::AlignRight);
		}

		m_Button->setText(metadata()->text1(), metadata()->text2());
   	m_WidgetLayoutPolicy->addItemAtPosition(m_Button, 0, 0);

		connect(m_Button, SIGNAL(clicked()), this, SLOT(bigClicked()));

/*

    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

  //dummy, must modify constructor  
    int m_SmallWidth = 20;    //0,1
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int width = m_SmallWidth*2 + m_LabelWidth + spaceWidth + imageWidth;
    
    int imageSize = 70;     
    
    m_BigButton = newButton(m_Width, m_Height, CSS_BIGBUTTON);

    m_UpLabel = newLabel(m_Height/2, upLabel, CSS_UPLABEL, Qt::AlignLeft|Qt::AlignBottom);
    m_TriangleButton = newButton(m_TriangleSize, CSS_TRIANGLEBUTTON);
 
    m_DownLabel = newLabel(m_Height/2, downLabel, CSS_DOWNLABEL, Qt::AlignLeft|Qt::AlignTop);


    if(m_EnableSmallToggle)
      m_SmallButtonOn = newButton(imageSize, CSS_SMALTOGGLEBUTTON);
    else
      m_SmallButtonOn = newButton(imageSize, CSS_SMALBUTTONON);
    
    m_SmallButtonOff = newButton(imageSize, CSS_SMALBUTTONOFF);

    m_DisableButton = newButton(imageSize, CSS_SMALLBUTTONDISBLE);


		m_TriangleButton->translate(5, -5); // TODO please remove me
		m_UpLabel->translate(5, 5);
		m_DownLabel->translate(5, -5);

		m_SmallButtonOn->translate(70, 0);


    initColumn(m_SmallWidth, 0, 0, 0, 0);
    initRow2(m_Height/2);

    m_WidgetLayoutPolicy->addItemAtPosition(m_BigButton, 0, 0, 2, 4, Qt::AlignLeft);

    m_WidgetLayoutPolicy->addItemAtPosition(m_TriangleButton, 0, 1, 1, 1, Qt::AlignBottom);

    m_WidgetLayoutPolicy->addItemAtPosition(m_UpLabel, 0, 2, 1, 1, Qt::AlignVCenter);
    m_WidgetLayoutPolicy->addItemAtPosition(m_DownLabel, 1, 1, 1, 2, Qt::AlignVCenter);

    m_WidgetLayoutPolicy->addItemAtPosition(m_SmallButtonOn, 0, 3, 2, 1, Qt::AlignVCenter|Qt::AlignRight);

    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));

    setEnableButton(true);
*/
    initLayout();
}


void DcpLabel2ToggleComponent::setEnableButton(bool enable) {
/*
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
*/
}

void DcpLabel2ToggleComponent::smallClickedOn()
{
/*
    if (m_EnableSmallToggle)
      	m_SmallButtonOn->setDown(true);
		else
				m_SmallButtonOn->setDown(false);

		m_EnableSmallToggle = !m_EnableSmallToggle;
*/
}
void DcpLabel2ToggleComponent::smallClickedOff(){}
void DcpLabel2ToggleComponent::disableClicked(){}


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

*/

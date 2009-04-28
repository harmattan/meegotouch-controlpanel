#include "dcplabel2component.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>

#include "dcpbutton.h"


DcpLabel2Component::DcpLabel2Component(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{

    m_Type = DCPLABEL2;
    m_EnableToggle = metadata->toggle();
    createContents();

	m_EnableToggle = false; // dummy must delete
}


DcpLabel2Component::~DcpLabel2Component()
{
}


void DcpLabel2Component::createContents()
{

	m_Button = new DcpButton(DCPLABEL2);

	m_Button->setText(metadata()->text1(), metadata()->text2());
   	m_WidgetLayoutPolicy->addItemAtPosition(m_Button, 0, 0);

	connect(m_Button, SIGNAL(clicked()), this, SLOT(bigClicked()));


/*
    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

   // int width = smallWidth*2 + m_LabelWidth + spaceWidth + imageWidth;
    
    initColumn(smallWidth, 0, 0);
    initRow2(m_Height/2);

    m_BigButton = newButton(m_Width, m_Height, CSS_BIGBUTTON);
    m_UpLabel = newLabel(m_Height/2, upLabel, CSS_UPLABEL, Qt::AlignLeft|Qt::AlignBottom);

    m_TriangleButton = newButton(m_TriangleSize, CSS_TRIANGLEBUTTON);
    
    m_DownLabel = newLabel(m_Height/2, downLabel, CSS_DOWNLABEL, Qt::AlignLeft|Qt::AlignTop);


    m_WidgetLayoutPolicy->addItemAtPosition(m_BigButton, 0, 0, 2, 3, Qt::AlignLeft);

    m_WidgetLayoutPolicy->addItemAtPosition(m_TriangleButton, 0, 1, 1, 1, Qt::AlignBottom);

    m_WidgetLayoutPolicy->addItemAtPosition(m_UpLabel, 0, 2, 1, 1, Qt::AlignBottom);
    m_WidgetLayoutPolicy->addItemAtPosition(m_DownLabel, 1, 1, 1, 2, Qt::AlignTop);


		m_TriangleButton->translate(5, -5); // TODO please remove me
		m_UpLabel->translate(5, 5);
		m_DownLabel->translate(5, -5);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
*/
    initLayout();
}

// FIXME: move this to basiccomponent once it has the DcpButton 
void DcpLabel2Component::setBgObjectName(const QString& objectName) {
    m_Button->setObjectName(objectName);
}


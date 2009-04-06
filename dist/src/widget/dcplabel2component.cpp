#include "dcplabel2component.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>



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
}


DcpLabel2Component::~DcpLabel2Component()
{

    delete m_BigButton;
    delete m_UpLabel;
    delete m_TriangleButton;

    delete m_DownLabel;

}


void DcpLabel2Component::createContents()
{

    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int width = smallWidth*2 + m_LabelWidth + spaceWidth + imageWidth;
    
    int height = 100;

    initColumn(smallWidth, 0, 0);
    initRow2(height/2);

    
    m_BigButton = newButton(width, height, CSS_BIGBUTTON);
    m_UpLabel = newLabel(height/2, upLabel, CSS_UPLABEL, Qt::AlignLeft|Qt::AlignBottom);
    m_TriangleButton = newButton(m_TriangleSize, CSS_TRIANGLEBUTTON);

    m_DownLabel = newLabel(height/2, downLabel, CSS_DOWNLABEL, Qt::AlignLeft|Qt::AlignTop);


    m_WidgetLayoutPolicy->addItemAtPosition(m_BigButton, 0, 0, 2, 3, Qt::AlignLeft);

    m_WidgetLayoutPolicy->addItemAtPosition(m_TriangleButton, 0, 1, 1, 1, Qt::AlignBottom);

    m_WidgetLayoutPolicy->addItemAtPosition(m_UpLabel, 0, 2, 1, 1, Qt::AlignCenter);
    m_WidgetLayoutPolicy->addItemAtPosition(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
 
    initLayout();
}

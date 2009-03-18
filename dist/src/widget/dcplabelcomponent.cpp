#include "dcplabelcomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>

DcpLabelComponent::DcpLabelComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
  createContents();
}


DcpLabelComponent::~DcpLabelComponent()
{
}


void DcpLabelComponent::createContents()
{

    //dummy, must modify constructor
    //dummy data
    QString upLabel = metadata()->text1();
 
    //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int labelWidth = 290;   //2

    int width = smallWidth*2 + labelWidth;

    int height = 100;

    initColumn(smallWidth, smallWidth, labelWidth );
    initRow(height);
  
    m_BigButton = newButton(width, height, "BigButton");
    m_UpLabel = newLabel(height, upLabel, "UpLabel", Qt::AlignLeft|Qt::AlignVCenter);
    m_TriangleButton = newButton(20, "TriangleButton");

    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 3, Qt::AlignLeft);
    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignCenter);
    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();
}

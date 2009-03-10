#include "dcpimagecomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>
#include <duiimage.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>

const float MINIMALIZE = 0.9f;

const float MINIMALIZEIMAGE = 0.8f;

const float TRANSLATEX = 10;
const float TRANSLATEY = 5;

DcpImageComponent::DcpImageComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpImageComponent::~DcpImageComponent() {
}


void
DcpImageComponent::createContents()
{

    //dummy, must modify constructor
    //dummy data
    int width  = 330;
    int upHeight = 50;
    int downHeight = 50;

    int imageWidth = 100;

QString label = m_Metadata->text1(); 
QString image = m_Metadata->image();
QString cssButton = m_Metadata->buttonCSS();
QString cssLabel = m_Metadata->label1CSS();

  
    m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, width );
    
    m_GridLayout->setColumnMaximumWidth ( 0, width );
    
    m_GridLayout->setRowMinimumHeight ( 0, upHeight );
    m_GridLayout->setRowMinimumHeight ( 1, downHeight );
    

    m_GridLayout->setRowMaximumHeight ( 0, upHeight );
    m_GridLayout->setRowMaximumHeight ( 1, downHeight );

    m_Button = new DuiButton("");

    // TODO: this moves to the view config file when updating to newer dui
//    m_Button->setView(new DcpButtonView(m_Button));
    // --

qDebug() << "-----------------------------" << cssButton << "-----------------------------";

    m_Button->setObjectName(cssButton);

    m_Button->setMinimumWidth(width);
    m_Button->setMaximumWidth(width);
    m_Button->setMinimumHeight(upHeight + downHeight);
    m_Button->setMaximumHeight(upHeight + downHeight);


    m_Label = new DuiLabel(label);
    m_Label->setObjectName(cssLabel);
    m_Label->setMinimumWidth(width*MINIMALIZE);
    m_Label->setMaximumWidth(width*MINIMALIZE);
    m_Label->setMinimumHeight(upHeight);
    m_Label->setMaximumHeight(upHeight);
    m_Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_Label->setAcceptedMouseButtons(0);

    m_Image = new DuiImage(image);
      
    m_Image->setMinimumWidth(imageWidth*MINIMALIZEIMAGE);
    m_Image->setMaximumWidth(imageWidth*MINIMALIZEIMAGE);
    m_Image->setMinimumHeight(downHeight*MINIMALIZEIMAGE);
    m_Image->setMaximumHeight(downHeight*MINIMALIZEIMAGE);

    m_Image->setAcceptedMouseButtons(0);

    m_GridLayout->addItem(m_Button, 0, 0, 2, 1, Qt::AlignCenter);
    m_GridLayout->addItem(m_Label, 0, 0, Qt::AlignCenter);
    m_GridLayout->addItem(m_Image, 1, 0, Qt::AlignRight|Qt::AlignVCenter);

//    connect(m_Button, SIGNAL(clicked()), this, SLOT(labelButtonClicked()));

    m_Button->setZValue(1);
    
    m_Label->setZValue(2);
    m_Image->setZValue(3);

    m_Image->translate(-TRANSLATEX, -TRANSLATEY);

    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void
DcpImageComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}

void DcpImageComponent::setTitleAlignment(Qt::Alignment align)
{
 //   m_Caption->setAlignment(align);
}


void DcpImageComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

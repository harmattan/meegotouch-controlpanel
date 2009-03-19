#include "dcplabelcomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>

const float MINIMALIZE = .95f;

DcpLabelComponent::DcpLabelComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpLabelComponent::~DcpLabelComponent() {
}


void
DcpLabelComponent::createContents()
{

    //dummy, must modify constructor
    //dummy data
    QString upLabel = metadata()->text1();
 


  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int labelWidth = 290;   //2

    int width = smallWidth*2 + labelWidth;


    int triangleSize = 20;
  
    int height = 100;

     m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 0, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 1, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 1, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 2, labelWidth );
    m_GridLayout->setColumnMaximumWidth ( 2, labelWidth );


    m_GridLayout->setRowMinimumHeight ( 0, height );
    m_GridLayout->setRowMaximumHeight ( 1, height );
 
    m_BigButton = new DuiButton;

    m_BigButton->setObjectName("BigButton");
    m_BigButton->setMinimumWidth(width);
    m_BigButton->setMaximumWidth(width);
    m_BigButton->setMinimumHeight(height);
    m_BigButton->setMaximumHeight(height);


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

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignCenter);

    m_GridLayout->addItem(m_Label, 0, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));


    m_BigButton->setZValue(1);
    m_TriangleButton->setZValue(2);
    m_Label->setZValue(4);
 
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void
DcpLabelComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    // DcpComponent::onOrientationChange(orientation);
    Q_UNUSED(orientation);
}


/*
void DcpButtonComponent::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    // TODO: move to stylesheet
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QColor bgColor = Qt::black;
    QColor borderColor = Qt::lightGray;
    // --

    if (m_Background.isNull() || m_Background.width() != size().width()){
        m_Background = DcpImageUtils::instance()->scaledPixmap(
                "C2-container-dark-landscape-123px", size().toSize());
        if (m_Background.isNull()) {
            qWarning ("theme lacks bg picture for settings component");
            return;
        }
    }
    painter->drawPixmap(QPoint(0, 0), m_Background);


//    DuiWidget::paint(painter, option, widget);

    // line between the title & description:
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Caption->y() + m_Caption->size().height() + 2;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);

}*/


void DcpLabelComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpLabelComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void DcpLabelComponent::bigClicked()
{
    switchToSubPage();
}

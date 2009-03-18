#include "dcplabel2component.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>



DcpLabel2Component::DcpLabel2Component(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpLabel2Component::~DcpLabel2Component() {
}


void DcpLabel2Component::createContents()
{

    QString upLabel = metadata()->text1();
    QString downLabel = metadata()->text2();

  //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
    int labelWidth = 170;   //2
    int spaceWidth = 5;     //3
    int imageWidth = 115;     //4

    int triangleSize = 20;

    int width = smallWidth*2 + labelWidth + spaceWidth + imageWidth;
    
    int height = 100;

    m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 0, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 1, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 1, smallWidth );

    m_GridLayout->setColumnMinimumWidth ( 2, labelWidth );
    m_GridLayout->setColumnMaximumWidth ( 2, labelWidth );


    for (int i=0;i<2;i++) {
        m_GridLayout->setRowMinimumHeight ( i, height/2 );
        m_GridLayout->setRowMaximumHeight ( i, height/2 );
    }

/*

 for (int yy =0; yy<2; yy++)
        for (int xx =0; xx<5; xx++) {
            DuiButton *tmp = new DuiButton("text");
            m_GridLayout->addItem(tmp, yy, xx, Qt::AlignCenter);
            tmp->setZValue(10);
         }
*/
/*
  DuiButton *tmp = new DuiButton("text");
  m_GridLayout->addItem(tmp, 0, 4, 2, 2, Qt::AlignHCenter|Qt::AlignLeft);
  tmp->setMinimumWidth(imageWidth);
  tmp->setMaximumWidth(imageWidth);
  tmp->setMinimumHeight(imageHeight);
  tmp->setMaximumHeight(imageHeight);
  tmp->setZValue(10);
*/

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
  //  m_UpLabel->setMinimumWidth(smallWidth+labelWidth);
  //  m_UpLabel->setMaximumWidth(smallWidth+labelWidth);
    m_UpLabel->setMinimumHeight(height/2);
    m_UpLabel->setMaximumHeight(height/2);
    m_DownLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_DownLabel->setAcceptedMouseButtons(0);



    m_GridLayout->addItem(m_BigButton, 0, 0, 2, 5, Qt::AlignLeft);

    m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignBottom);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
 

    m_BigButton->setZValue(1);
    m_TriangleButton->setZValue(2);
    m_UpLabel->setZValue(6);
    m_DownLabel->setZValue(7);


    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void DcpLabel2Component::onOrientationChange (const Dui::Orientation &orientation)
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


void DcpLabel2Component::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpLabel2Component::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void DcpLabel2Component::switchToSubPage()
{
    emit openSubPage(subPage());
}

void DcpLabel2Component::bigClicked()
{
    switchToSubPage();
}


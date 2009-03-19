#include "dcplabel2buttoncomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>



DcpLabel2ButtonComponent::DcpLabel2ButtonComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpLabel2ButtonComponent::~DcpLabel2ButtonComponent() {
}


void
DcpLabel2ButtonComponent::createContents()
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

    m_GridLayout->addItem(m_SmallButtonOn, 0, 4, 2, 1, Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_SmallButtonOff, 0, 4, 2, 1,  Qt::AlignVCenter|Qt::AlignLeft);
    m_GridLayout->addItem(m_DisableButton, 0, 4, 2, 1,  Qt::AlignVCenter|Qt::AlignLeft);

    m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);
    m_GridLayout->addItem(m_DownLabel, 1, 1, 1, 2, Qt::AlignCenter);


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
    m_UpLabel->setZValue(6);
    m_DownLabel->setZValue(7);


    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void DcpLabel2ButtonComponent::setEnable(bool enable) {

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


void
DcpLabel2ButtonComponent::onOrientationChange (const Dui::Orientation &orientation)
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


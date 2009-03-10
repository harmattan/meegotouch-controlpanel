#include "dcplabelcomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include "dcpbuttonview.h"

#include <QDebug>

const float MINIMALIZE = 0.9f;

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
    int width  = 330;
    int upHeight = 50;
    int downHeight = 50;

    QString upLabel = m_Metadata->text1();
    QString downLabel = m_Metadata->text2();
    QString cssButton = m_Metadata->buttonCSS();
    QString cssUpLabel = m_Metadata->label1CSS();
    QString cssDownLabel = m_Metadata->label2CSS();

  
    m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, width );
    
    m_GridLayout->setColumnMaximumWidth ( 0, width );
    
    m_GridLayout->setRowMinimumHeight ( 0, upHeight );
    m_GridLayout->setRowMinimumHeight ( 1, downHeight );
    

    m_GridLayout->setRowMaximumHeight ( 0, upHeight );
    m_GridLayout->setRowMaximumHeight ( 1, downHeight );

    m_Button = new DuiButton("");

    // TODO: this moves to the view config file when updating to newer dui
    m_Button->setView(new DcpButtonView(m_Button));
    // --

    m_Button->setObjectName(cssButton);
    m_Button->setMinimumWidth(width);
    m_Button->setMaximumWidth(width);
    m_Button->setMinimumHeight(upHeight + downHeight);
    m_Button->setMaximumHeight(upHeight + downHeight);


    m_UpLabel = new DuiLabel(upLabel);
    m_UpLabel->setObjectName(cssUpLabel);
    m_UpLabel->setMinimumWidth(width*MINIMALIZE);
    m_UpLabel->setMaximumWidth(width*MINIMALIZE);
    m_UpLabel->setMinimumHeight(upHeight);
    m_UpLabel->setMaximumHeight(upHeight);
    m_UpLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_UpLabel->setAcceptedMouseButtons(0);

    m_DownLabel = new DuiLabel(downLabel);
    m_DownLabel->setObjectName(cssDownLabel);
    m_DownLabel->setMinimumWidth(width*MINIMALIZE);
    m_DownLabel->setMaximumWidth(width*MINIMALIZE);
    m_DownLabel->setMinimumHeight(downHeight);
    m_DownLabel->setMaximumHeight(downHeight);
    m_DownLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_DownLabel->setAcceptedMouseButtons(0);

    m_GridLayout->addItem(m_Button, 0, 0, 2, 1, Qt::AlignCenter);
    m_GridLayout->addItem(m_UpLabel, 0, 0, Qt::AlignCenter);
    m_GridLayout->addItem(m_DownLabel, 1, 0, Qt::AlignCenter);


   // connect(m_Button, SIGNAL(clicked()), this, SLOT(labelButtonClicked()));

    m_Button->setZValue(1);
    
    m_UpLabel->setZValue(2);
    m_DownLabel->setZValue(3);

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

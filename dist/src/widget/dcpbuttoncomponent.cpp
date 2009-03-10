#include "dcpbuttoncomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"
#include "dcpbuttonview.h"

#include <QDebug>



DcpButtonComponent::DcpButtonComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata)
{

  createContents();
}


DcpButtonComponent::~DcpButtonComponent() {
}


void
DcpButtonComponent::createContents()
{

  //dummy, must modify constructor
  QString bigLabel = metadata()->text1();
  int bigWidth = 350;
  int bigHeight = 90;
  QString smallLabel = metadata()->text2();
  int smallX = 290;
  int smallY = 30;
  int smallWidth = 50;
  int smallHeight = 50;
  bool enable = true;

    m_GridLayout = new DuiGridLayout();

    m_GridLayout->setColumnMinimumWidth ( 0, smallX );
    m_GridLayout->setColumnMinimumWidth ( 1, smallWidth );
    m_GridLayout->setColumnMinimumWidth ( 2, bigWidth - smallX - smallWidth );

    m_GridLayout->setColumnMaximumWidth ( 0, smallX );
    m_GridLayout->setColumnMaximumWidth ( 1, smallWidth );
    m_GridLayout->setColumnMaximumWidth ( 2, bigWidth - smallX - smallWidth );


    m_GridLayout->setRowMinimumHeight ( 0, smallY );
    m_GridLayout->setRowMinimumHeight ( 1, smallHeight );
    m_GridLayout->setRowMinimumHeight ( 2, bigHeight - smallY - smallHeight );

    m_GridLayout->setRowMaximumHeight ( 0, smallY );
    m_GridLayout->setRowMaximumHeight ( 1, smallHeight );
    m_GridLayout->setRowMaximumHeight ( 2, bigHeight - smallY - smallHeight );

    /* //only test
    for (int yy =0; yy<3; yy++)
        for (int xx =0; xx<3; xx++)
            m_Layout->addItem(new DuiButton("text"), xx, yy, Qt::AlignCenter);
     */


    m_BigButton = new DuiButton(bigLabel);

    // TODO: this moves to the view config file when updating to newer dui
    m_BigButton->setView(new DcpButtonView(m_BigButton));
    // --

    m_BigButton->setObjectName("BigButton");
    m_BigButton->setMinimumWidth(bigWidth);
    m_BigButton->setMaximumWidth(bigWidth);
    m_BigButton->setMinimumHeight(bigHeight);
    m_BigButton->setMaximumHeight(bigHeight);


    m_SmallButtonOn = new DuiButton(smallLabel);
    m_SmallButtonOn->setObjectName("SmallButtonOn");
    m_SmallButtonOn->setMinimumWidth(smallWidth);
    m_SmallButtonOn->setMaximumWidth(smallWidth);
    m_SmallButtonOn->setMinimumHeight(smallHeight);
    m_SmallButtonOn->setMaximumHeight(smallHeight);

    m_SmallButtonOff = new DuiButton(smallLabel);
    m_SmallButtonOff->setObjectName("SmallButtonOff");
    m_SmallButtonOff->setMinimumWidth(smallWidth);
    m_SmallButtonOff->setMaximumWidth(smallWidth);
    m_SmallButtonOff->setMinimumHeight(smallHeight);
    m_SmallButtonOff->setMaximumHeight(smallHeight);

    m_DisableButton = new DuiButton(smallLabel);
    m_DisableButton->setObjectName("SmallButtonDisable");
    m_DisableButton->setMinimumWidth(smallWidth);
    m_DisableButton->setMaximumWidth(smallWidth);
    m_DisableButton->setMinimumHeight(smallHeight);
    m_DisableButton->setMaximumHeight(smallHeight);

    //m_Layout->addItem(m_BigButton, 0, 0, 3, 3, Qt::AlignCenter);
    m_GridLayout->addItem(m_BigButton, 0, 0, 3, 3, Qt::AlignLeft);
    m_GridLayout->addItem(m_SmallButtonOn, 1, 1, Qt::AlignCenter);
    m_GridLayout->addItem(m_SmallButtonOff, 1, 1, Qt::AlignCenter);
    m_GridLayout->addItem(m_DisableButton, 1, 1, Qt::AlignCenter);

    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));

    setEnable(enable);

    m_BigButton->setZValue(1);
    m_SmallButtonOn->setZValue(2);
    m_SmallButtonOff->setZValue(3);
    m_DisableButton->setZValue(4);

    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void DcpButtonComponent::setEnable(bool enable) {

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
DcpButtonComponent::onOrientationChange (const Dui::Orientation &orientation)
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


void DcpButtonComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpButtonComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void
DcpButtonComponent::switchToSubPage()
{
    emit openSubPage(subPageId(), m_Metadata->name());
}

void
DcpButtonComponent::bigClicked()
{
    switchToSubPage();
}


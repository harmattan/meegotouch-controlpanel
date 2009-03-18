#include "servicescontainer.h"
#include "servicesbuttonblock.h"
#include "dcpimageutils.h"

#include <qpainter.h>
#include <duitheme.h>
#include <duilinearlayout.h>
#include <duilabel.h>

ServicesContainer::ServicesContainer(QGraphicsWidget *parent)
                  :DuiWidget(parent)
{
    initContainer();
}

ServicesContainer::~ServicesContainer()
{
    /* if (m_background)
    {
        DuiTheme::releasePixmap(m_background);
    }*/
}

void ServicesContainer::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    if (!m_background.isNull())
    {
        painter->drawPixmap(QPoint(0, 0), m_background);
    }

    // draw line below the title
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal y = m_caption->y() + m_caption->size().height();
    painter->drawLine(borderWidth, y, 
                      size().width() - 2 * borderWidth, y);
}

void ServicesContainer::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);
    
    // load background pixmap
    // not a perfect solution for corner problem
    // m_background = DuiTheme::horizBoxedPixmap("C2-container-dark-landscape-123px",
    //                                          QSize(geometry().width(), geometry().height()), 
    //                                          50);
    m_background = DcpImageUtils::instance()->scaledPixmap(
                                            "C2-container-dark-landscape-123px",
                                            size().toSize());
}

void ServicesContainer::initContainer()
{
    m_mainLayout = new DuiLinearLayout(Qt::Vertical, this);

    // captionLayout
    DuiLinearLayout *captionLayout = new DuiLinearLayout(Qt::Horizontal);
    m_caption = new DuiLabel("Ovi feeds (4)", this);
    m_caption->setObjectName("ServicesContainerCaption");
    captionLayout->addItem(m_caption);

    DuiWidget *spacerItem = new DuiWidget(this);
    spacerItem->setMaximumHeight(5);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    captionLayout->addItem(spacerItem);

    DuiLabel *signLabel = new DuiLabel(">", this);
    signLabel->setObjectName("ServicesContainerSignLabel");
    captionLayout->addItem(signLabel);

    captionLayout->setAlignment(m_caption, Qt::AlignLeft  | Qt::AlignBottom);
    captionLayout->setAlignment(signLabel, Qt::AlignRight | Qt::AlignBottom);
    m_mainLayout->addItem(captionLayout);
    
    // Example how to add ServicesButtonBlock  
    ServicesButtonBlock *blockOne = new ServicesButtonBlock(this);
    m_mainLayout->addItem(blockOne);
    blockOne->addServicesButton("Language 1");
    blockOne->addServicesButton("Language 2");
    blockOne->addServicesButton("Language 3");

    ServicesButtonBlock *blockTwo = new ServicesButtonBlock(this);
    m_mainLayout->addItem(blockTwo);
    blockTwo->addServicesButton("Language");
}

void ServicesContainer::addServices(const QString &name)
{
    Q_UNUSED(name);
    // not implemented yet
}

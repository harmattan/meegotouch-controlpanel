#include "servicescontainer.h"
#include "servicesbuttonblock.h"

#include <qpainter.h>
#include <duitheme.h>
#include <duilinearlayout.h>
#include <duilabel.h>
#include <duibutton.h>

ServicesContainer::ServicesContainer(QGraphicsWidget *parent)
                  :DuiWidget(parent), m_Background(NULL)
{
    initContainer();
}

ServicesContainer::~ServicesContainer()
{
    if (m_Background)
    {
        DuiTheme::releasePixmap(m_Background);
    }
}

void ServicesContainer::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // reload pixmap if the size changes:
    QSize size = this->size().toSize();
    if (m_Background && m_Background->size() != size) {
        DuiTheme::releasePixmap(m_Background);
        m_Background = NULL;
    }
    // if not loaded:
    if (!m_Background){
        static const int border = 30;
        m_Background = DuiTheme::boxedPixmap("Mashup-container",size,
                                             border, border, border, border);
    }
    // if available, then draw it:
    if (m_Background) {
        painter->drawPixmap(0, 0, *m_Background);
    }
    

    // draw line below the title
    /* int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal y = m_caption->y() + m_caption->size().height();
    painter->drawLine(borderWidth, y, 
                      size().width() - 2 * borderWidth, y);*/
}

void ServicesContainer::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);
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

    DuiButton *signButton = new DuiButton(this);
    signButton->setObjectName("ServicesContainerSignButton");
    captionLayout->addItem(signButton);

    captionLayout->setAlignment(m_caption, Qt::AlignLeft  | Qt::AlignBottom);
    captionLayout->setAlignment(spacerItem, Qt::AlignCenter);
    captionLayout->setAlignment(signButton, Qt::AlignRight | Qt::AlignBottom);
    m_mainLayout->addItem(captionLayout);

    DuiWidget *spacerItem2 = new DuiWidget(this);
    spacerItem2->setMaximumHeight(10);
    spacerItem2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mainLayout->addItem(spacerItem2);
    
    // Example how to add ServicesButtonBlock  
    ServicesButtonBlock *blockOne = 
            new ServicesButtonBlock("Recent released display languages", this);
    m_mainLayout->addItem(blockOne);
    blockOne->addServicesButton("Language 1");
    blockOne->addServicesButton("Language 2");
    blockOne->addServicesButton("Language 3");

    ServicesButtonBlock *blockTwo = 
            new ServicesButtonBlock("Recent released keyboard languages", this);
    m_mainLayout->addItem(blockTwo);
    blockTwo->addServicesButton("Language");
}

void ServicesContainer::addServices(const QString &name)
{
    Q_UNUSED(name);
    // not implemented yet
}

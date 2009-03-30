#include "servicescontainer.h"
#include "servicesbuttonblock.h"

#include <qpainter.h>
#include <duitheme.h>
#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>
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
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0xFF, 0xAA, 0x00);
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal y = m_caption->y() + m_caption->size().height();
    painter->drawLine(borderWidth, y, 
                      geometry().size().width() - 2 * borderWidth, y);
}

void ServicesContainer::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);
}

void ServicesContainer::initContainer()
{
    m_mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy* mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    
    m_mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(10);
    mainLayoutPolicy->setContentsMargins(12.0, 5.0, 5.0, 12.0);

    // captionLayout
    DuiLayout *captionLayout = new DuiLayout(0);
    DuiLinearLayoutPolicy *captionLayoutPolicy = 
            new DuiLinearLayoutPolicy(captionLayout, Qt::Horizontal);
    captionLayout->setPolicy(captionLayoutPolicy);

    m_caption = new DuiLabel("Ovi feeds (4)", this);
    m_caption->setObjectName("ServicesContainerCaption");
    captionLayoutPolicy->addItemAtPosition(m_caption, 
                    0, Qt::AlignLeft | Qt::AlignBottom);

    DuiWidget *spacerItem = new DuiWidget(this);
    spacerItem->setMaximumHeight(5);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    captionLayoutPolicy->addItemAtPosition(spacerItem,
                    1, Qt::AlignCenter);

    DuiButton *signButton = new DuiButton(this);
    signButton->setObjectName("ServicesContainerSignButton");
    signButton->setMaximumWidth(32);
    signButton->setMaximumHeight(32);
    captionLayoutPolicy->addItemAtPosition(signButton,
                    2, Qt::AlignRight | Qt::AlignVCenter);

    mainLayoutPolicy->addItemAtPosition(captionLayout,
                    0, Qt::AlignVCenter | Qt::AlignTop);

    DuiWidget *spacerItem2 = new DuiWidget(this);
    spacerItem2->setMaximumHeight(10);
    spacerItem2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLayoutPolicy->addItemAtPosition(spacerItem2,
                    1, Qt::AlignCenter);
    
    // Example how to add ServicesButtonBlock  
    ServicesButtonBlock *blockOne = 
            new ServicesButtonBlock("Recent released display languages", this);
        blockOne->addServicesButton("Language 1");
    blockOne->addServicesButton("Language 2");
    blockOne->addServicesButton("Language 3");

    ServicesButtonBlock *blockTwo = 
            new ServicesButtonBlock("Recent released keyboard languages", this);
        blockTwo->addServicesButton("Language");

    mainLayoutPolicy->addItemAtPosition(blockOne,
                    2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(blockTwo,
                    3, Qt::AlignCenter);

    this->update();
}

void ServicesContainer::addServices(const QString &name)
{
    Q_UNUSED(name);
    // not implemented yet
}

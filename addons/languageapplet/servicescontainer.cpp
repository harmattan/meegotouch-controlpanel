#include "servicescontainer.h"
#include "servicesbuttonblock.h"
#include "languagetranslation.h"
#include "dcpspaceritem.h"

#include <qpainter.h>
#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <QGraphicsSceneResizeEvent>

ServicesContainer::ServicesContainer(QGraphicsWidget *parent)
                  :DuiWidget(parent), m_Background(NULL)
{
    initContainer();
}

ServicesContainer::~ServicesContainer()
{
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
}

void ServicesContainer::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // if available, then draw it:
    if (m_Background) {
        painter->drawPixmap(0,0, *m_Background);
    }

    // draw line below the title
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0xFF, 0xAA, 0x00);
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal y = m_Caption->y() + m_Caption->size().height();
    painter->drawLine(borderWidth, y, 
                      geometry().size().width() - 2 * borderWidth, y);
}

void ServicesContainer::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);
    
    QSize size = event->newSize().toSize();
    static const int border = 30;
    if (m_Background) {
	    DuiTheme::releasePixmap(m_Background);
    }
    m_Background = DuiTheme::boxedPixmap("Mashup-container",size,
                                         border, border, border, border);
}

void ServicesContainer::initContainer()
{
    // m_mainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setAnimator(NULL);

    // captionLayout
    DuiLayout *captionLayout = new DuiLayout(m_MainLayout);
    captionLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *captionLayoutPolicy = 
            new DuiLinearLayoutPolicy(captionLayout, Qt::Horizontal);
    captionLayout->setPolicy(captionLayoutPolicy);

    m_Caption = new DuiLabel(DcpLanguage::OviFeeds + " (4)", this);
    m_Caption->setObjectName("ServicesContainerCaption");
    captionLayoutPolicy->addItemAtPosition(m_Caption, 0, Qt::AlignLeft | Qt::AlignBottom);
    captionLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    1, Qt::AlignCenter);

    DuiButton *signButton = new DuiButton(this);
    signButton->setObjectName("ServicesContainerSignButton");
    signButton->setMaximumWidth(32);
    signButton->setMaximumHeight(32);
    captionLayoutPolicy->addItemAtPosition(signButton,
                    2, Qt::AlignRight | Qt::AlignVCenter);
    
    // Example how to add ServicesButtonBlock  
    ServicesButtonBlock *blockOne = 
            new ServicesButtonBlock(DcpLanguage::RecentDisplayText, this);
    for (int i = 0; i < 3; i++) {
        blockOne->addServicesButton("Language");
    }

    ServicesButtonBlock *blockTwo = 
            new ServicesButtonBlock(DcpLanguage::RecentKeyboardText, this);
    blockTwo->addServicesButton("Language");

    // m_mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy* mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    
    m_MainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(10);
    mainLayoutPolicy->setContentsMargins(12.0, 5.0, 5.0, 20.0);
    
    DuiWidget* captionWidget = new DuiWidget(this);
    captionWidget->setLayout(captionLayout);
    mainLayoutPolicy->addItemAtPosition(captionWidget,
                    0, Qt::AlignVCenter | Qt::AlignTop);
    mainLayoutPolicy->addItemAtPosition(blockOne,
                    1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(blockTwo,
                    2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 12, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    3, Qt::AlignCenter);
    this->setLayout(m_MainLayout);
}

void ServicesContainer::addServices(const QString &name)
{
    Q_UNUSED(name);
    // not implemented yet
}

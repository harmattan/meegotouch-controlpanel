#include "servicesbutton.h"
#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>

const int height = 90;

ServicesButton::ServicesButton(DuiWidget *parent, const QString &title)
               :DuiButton(parent)
{
    m_mainLayout = new DuiLayout(this);
    // m_mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy *landscapeLayout = 
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);

    m_mainLayout->setPolicy(landscapeLayout);

    // labelLayout
    DuiLayout *labelLayout = new DuiLayout(0);
    // labelLayout->setAnimator(0);
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
            new DuiLinearLayoutPolicy(labelLayout, Qt::Horizontal);
    labelLayout->setPolicy(labelLayoutPolicy);

    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMinimumWidth(12);
    spacer->setMaximumWidth(12);
    spacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    DuiButton *seeMoreSmall = new DuiButton(this);
    seeMoreSmall->setObjectName("ServicesButtonSeeMoreSmall");
    seeMoreSmall->setAcceptedMouseButtons(0);
    seeMoreSmall->setMaximumWidth(20);
    seeMoreSmall->setMaximumHeight(20);
    
    m_label = new DuiLabel(title, this);
    m_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_label->setObjectName("ServicesButtonLabel");
    m_label->setAcceptedMouseButtons(0);
    
    labelLayoutPolicy->addItemAtPosition(spacer, 0, Qt::AlignCenter);
    labelLayoutPolicy->addItemAtPosition(seeMoreSmall, 1, Qt::AlignCenter);
    labelLayoutPolicy->addItemAtPosition(m_label, 2, Qt::AlignCenter);

    // spacer
    DuiWidget *spacerItem = new DuiWidget(this);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    DuiWidget *spacerItem2 = new DuiWidget(this);
    spacerItem2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    landscapeLayout->addItemAtPosition(spacerItem, 0, Qt::AlignCenter);
    landscapeLayout->addItemAtPosition(labelLayout, 1, Qt::AlignCenter);
    landscapeLayout->addItemAtPosition(spacerItem2, 2, Qt::AlignCenter);
}

ServicesButton::~ServicesButton()
{   
    if (m_background)
    {
        DuiTheme::releasePixmap(m_background);
    }
}

void ServicesButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    int devide = 55;

    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMinimumHeight(height);
    setMaximumHeight(height);

    QSize size = this->size().toSize();
    static const int border = 10;
    m_background = DuiTheme::boxedPixmap("C2-container", size,
                                         border, border, border, border);
}

void ServicesButton::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    // Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // if available, then draw it:
    if (m_background) 
    {
        painter->drawPixmap(0, 0, *m_background);
    }                
}

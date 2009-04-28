#include "servicesbutton.h"
#include "dcpspaceritem.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <QGraphicsSceneResizeEvent>

const int height = 80;

ServicesButton::ServicesButton(DuiWidget *parent, const QString &title)
               :DuiButton(parent), m_Background(NULL)
{
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *landscapeLayout = 
            new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);

    m_MainLayout->setPolicy(landscapeLayout);

    // labelLayout
    DuiLayout *labelLayout = new DuiLayout(0);
    labelLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
            new DuiLinearLayoutPolicy(labelLayout, Qt::Horizontal);
    labelLayout->setPolicy(labelLayoutPolicy);

    DuiButton *seeMoreSmall = new DuiButton(this);
    seeMoreSmall->setObjectName("ServicesButtonSeeMoreSmall");
    seeMoreSmall->setAcceptedMouseButtons(0);
    seeMoreSmall->setMaximumWidth(20);
    seeMoreSmall->setMaximumHeight(20);
    
    m_Label = new DuiLabel(title, this);
    m_Label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_Label->setObjectName("ServicesButtonLabel");
    m_Label->setAcceptedMouseButtons(0);
    
    labelLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 12, 12, QSizePolicy::Fixed, QSizePolicy::Fixed), 
                    0, Qt::AlignCenter);
    labelLayoutPolicy->addItemAtPosition(seeMoreSmall, 1, Qt::AlignCenter);
    labelLayoutPolicy->addItemAtPosition(m_Label, 2, Qt::AlignCenter);

    landscapeLayout->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding), 
                    0, Qt::AlignCenter);
    landscapeLayout->addItemAtPosition(labelLayout, 1, Qt::AlignCenter);
    landscapeLayout->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding), 
                            2, Qt::AlignCenter);

    this->setLayout(m_MainLayout);
    setMinimumHeight(height);
    setMaximumHeight(height);
    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - 40);
}

ServicesButton::~ServicesButton()
{   
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
}

void ServicesButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    QSize size = event->newSize().toSize();
    static const int border = 10;
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
    
    m_Background = DuiTheme::boxedPixmap("C2-container", size,
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
    if (m_Background) {
        painter->drawPixmap(0, 0, *m_Background);
    }                
}

#include "servicesbutton.h"
#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>

const int height =  80;
const QString space = "        ";

ServicesButton::ServicesButton(QGraphicsWidget *parent, const QString &title)
               :DuiWidget(parent)
{
    m_mainLayout = new DuiLayout(this);
    DuiGridLayoutPolicy *landscapeLayout = new DuiGridLayoutPolicy(m_mainLayout);

    m_mainLayout->setPolicy(landscapeLayout);
    
    m_button = new DuiButton(this);
    m_button->setObjectName("ServicesButton");
    m_button->setMinimumHeight(height);
    m_button->setMaximumHeight(height);

    m_label = new DuiLabel(space + title, this);
    m_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_label->setMinimumHeight(height);
    m_label->setMaximumHeight(height);
    m_label->setObjectName("ServicesButtonLabel");
    m_label->setAcceptedMouseButtons(0);
    
    landscapeLayout->addItemAtPosition(m_button, 0, 0, 2, 1, Qt::AlignCenter);
    landscapeLayout->addItemAtPosition(m_label, 0, 0, 2, 1, Qt::AlignCenter);
}

void ServicesButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    int devide = 65;

    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);

    m_button->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    m_button->setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);

    m_label->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
    m_label->setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
}

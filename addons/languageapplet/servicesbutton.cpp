#include "servicesbutton.h"
#include <duigridlayout.h>
#include <duibutton.h>
#include <duilabel.h>

const int height =  85;
const QString space = "        ";

ServicesButton::ServicesButton(QGraphicsWidget *parent, const QString &title)
               :DuiWidget(parent)
{
    m_mainLayout = new DuiGridLayout(this);
    m_mainLayout->setRowMinimumHeight(0, height);
    m_mainLayout->setRowMaximumHeight(0, height);
    
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
    
    m_mainLayout->addItem(m_button, 0, 0, 2, 1, Qt::AlignCenter);
    m_mainLayout->addItem(m_label, 0, 0, Qt::AlignCenter);
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
    
    m_mainLayout->setColumnMinimumWidth(0, 
                    DuiDeviceProfile::instance()->width() / 2 - devide);
    m_mainLayout->setColumnMaximumWidth(0,
                    DuiDeviceProfile::instance()->width() / 2 - devide);
}

#include "servicesbutton.h"
#include <duilinearlayout.h>
#include <duibutton.h>

const int height =  75;

ServicesButton::ServicesButton(QGraphicsWidget *parent, const QString &title)
               :DuiWidget(parent)
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Horizontal, this);
    m_button = new DuiButton(title, this);
    m_button->setObjectName("ServicesButton");
    m_button->setMinimumHeight(height);
    m_button->setMaximumHeight(height);
    mainLayout->addItem(m_button);
    mainLayout->setAlignment(m_button, Qt::AlignCenter);
}

void ServicesButton::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    m_button->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - 80);
    m_button->setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - 80);
}

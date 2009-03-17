#include "servicesbutton.h"
#include <duilinearlayout.h>
#include <duibutton.h>

const int width  = 200;
const int height =  60;

ServicesButton::ServicesButton(QGraphicsWidget *parent, const QString &title)
               :DuiWidget(parent)
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Horizontal, this);
    m_button = new DuiButton(title, this);
    m_button->setObjectName("ServicesButton");
    m_button->setMinimumWidth(width);
    m_button->setMaximumWidth(width);
    m_button->setMinimumHeight(height);
    m_button->setMaximumHeight(height);
    mainLayout->addItem(m_button);
    mainLayout->setAlignment(m_button, Qt::AlignCenter);
}

#include "servicesbuttonblock.h"
#include "servicesbutton.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>

ServicesButtonBlock::ServicesButtonBlock(const QString &title, QGraphicsWidget *parent)
                    :DuiWidget(parent), m_Title(title)
{
    initWidget();
}

ServicesButtonBlock::~ServicesButtonBlock()
{
}

void ServicesButtonBlock::addServicesButton(const QString &name)
{
    int size = m_ButtonVector.size();
    
    m_ButtonVector.append(new ServicesButton(this, name));
    m_ButtonLayoutPolicy->addItemAtPosition(m_ButtonVector[size], size / 2, size % 2);
}

void ServicesButtonBlock::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    m_Header = new DuiLabel(m_Title, this);
    mainLayoutPolicy->addItemAtPosition(m_Header, 0, Qt::AlignLeft);

    DuiLayout *buttonLayout = new DuiLayout();
    buttonLayout->setAnimator(NULL);
    m_ButtonLayoutPolicy = new DuiGridLayoutPolicy(buttonLayout);
    buttonLayout->setPolicy(m_ButtonLayoutPolicy);
    m_ButtonLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, 3);

    mainLayoutPolicy->addItemAtPosition(buttonLayout, 1, Qt::AlignCenter);
    
    this->setLayout(mainLayout);
}

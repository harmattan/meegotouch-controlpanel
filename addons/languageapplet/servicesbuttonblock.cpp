#include "servicesbuttonblock.h"
#include "servicesbutton.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>

ServicesButtonBlock::ServicesButtonBlock(const QString &title, QGraphicsWidget *parent)
                    :DuiWidget(parent), m_title(title)
{
    initWidget();
}

ServicesButtonBlock::~ServicesButtonBlock()
{
}

void ServicesButtonBlock::addServicesButton(const QString &name)
{
    int size = m_buttonVector.size();
    
    m_buttonVector.append(new ServicesButton(this, name));
    m_buttonLayoutPolicy->addItemAtPosition(m_buttonVector[size], size / 2, size % 2);
}

void ServicesButtonBlock::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    m_header = new DuiLabel(m_title, this);
    mainLayoutPolicy->addItemAtPosition(m_header, 0, Qt::AlignLeft);

    DuiLayout *buttonLayout = new DuiLayout();
    m_buttonLayoutPolicy = new DuiGridLayoutPolicy(buttonLayout);
    buttonLayout->setPolicy(m_buttonLayoutPolicy);
    m_buttonLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, 3);

    mainLayoutPolicy->addItemAtPosition(buttonLayout, 1, Qt::AlignCenter);
}

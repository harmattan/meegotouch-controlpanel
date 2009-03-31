#include "servicesbuttonblock.h"
#include "servicesbutton.h"

#include <duilayout.h>
#include <duilinearlayout.h>
#include <duigridlayout.h>
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
    m_buttonLayout->addItem(m_buttonVector[size], size / 2, size % 2, 
                    Qt::AlignCenter);
}

void ServicesButtonBlock::initWidget()
{
    /* mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);*/
    
    m_header = new DuiLabel(m_title, this);
    // mainLayoutPolicy->addItemAtPosition(m_header, 0, Qt::AlignLeft);

    /* DuiLayout *buttonLayout = new DuiLayout(0);
    m_buttonLayoutPolicy = new DuiGridLayoutPolicy(buttonLayout);
    buttonLayout->setPolicy(m_buttonLayoutPolicy);*/
    m_buttonLayout = new DuiGridLayout(0);

    // add spacer item to keep the proper widget's width
    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMaximumHeight(5);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_buttonLayout->addItem(spacer, 0, 3, Qt::AlignCenter);
    
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    mainLayout->setContentsMargins(12.0, 12.0, 12.0, 12.0);
    mainLayout->setSpacing(10);
    mainLayout->addItem(m_header);
    mainLayout->addItem(m_buttonLayout);
    mainLayout->setAlignment(m_header, Qt::AlignCenter);
    mainLayout->setAlignment(m_buttonLayout, Qt::AlignCenter);

    // mainLayoutPolicy->addItemAtPosition(buttonLayout, 1, Qt::AlignCenter);
}

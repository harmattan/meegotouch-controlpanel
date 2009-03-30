#include "servicesbuttonblock.h"
#include "servicesbutton.h"

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
    m_buttonLayoutPolicy->addItemAtPosition(m_buttonVector[size], size / 2, size % 2, 
                    size + 1, 1, Qt::AlignCenter);
    m_header->setText(m_title + QString(" (%1)").arg(size + 1));
    this->update();
}

void ServicesButtonBlock::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    m_header = new DuiLabel(m_title, this);
    mainLayoutPolicy->addItemAtPosition(m_header, 0, Qt::AlignLeft);

    DuiLayout *buttonLayout = new DuiLayout(0);
    buttonLayout->setAnimator(0);
    m_buttonLayoutPolicy = new DuiGridLayoutPolicy(buttonLayout);
    buttonLayout->setPolicy(m_buttonLayoutPolicy);

    // add spacer item to keep the proper widget's width
    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMaximumHeight(5);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_buttonLayoutPolicy->addItemAtPosition(spacer, 0, 3, 2, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(buttonLayout, 1, Qt::AlignCenter);
}

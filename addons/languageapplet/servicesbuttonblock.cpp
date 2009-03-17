#include "servicesbuttonblock.h"
#include "servicesbutton.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>

ServicesButtonBlock::ServicesButtonBlock(QGraphicsWidget *parent)
                    :DuiWidget(parent)
{
    initWidget();
}

ServicesButtonBlock::~ServicesButtonBlock()
{
}

void ServicesButtonBlock::addServicesButton(const QString &name)
{
    int size = m_buttonVector.size();
    if (size < 3)
    {
        m_buttonVector.append(new ServicesButton(this, name));
        m_buttonLayout->addItem(m_buttonVector[size], 0, size, Qt::AlignLeft);
        m_header->setText(QString("Recent released display languages (%1)").arg(size + 1));
    } 
}

void ServicesButtonBlock::initWidget()
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    m_header = new DuiLabel(QString("Recent released display languages (%1)").arg(0), this);
    mainLayout->addItem(m_header);
    mainLayout->setAlignment(m_header, Qt::AlignLeft);

    m_buttonLayout = new DuiGridLayout(0);

    // add spacer item to keep the proper widget's width
    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMaximumHeight(5);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_buttonLayout->addItem(spacer, 0, 4, Qt::AlignCenter);
    mainLayout->addItem(m_buttonLayout);
}

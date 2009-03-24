#include "servicesbuttonblock.h"
#include "servicesbutton.h"

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
    m_buttonLayout->addItem(m_buttonVector[size], size / 2, size % 2, Qt::AlignLeft);
    m_header->setText(m_title + QString(" (%1)").arg(size + 1));
}

void ServicesButtonBlock::initWidget()
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    m_header = new DuiLabel(m_title, this);
    mainLayout->addItem(m_header);
    mainLayout->setAlignment(m_header, Qt::AlignLeft);

    m_buttonLayout = new DuiGridLayout(0);

    // add spacer item to keep the proper widget's width
    DuiWidget *spacer = new DuiWidget(this);
    spacer->setMaximumHeight(5);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_buttonLayout->addItem(spacer, 0, 3, Qt::AlignCenter);
    mainLayout->addItem(m_buttonLayout);
}

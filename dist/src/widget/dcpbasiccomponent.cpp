#include "dcpbasiccomponent.h"


#include <duilabel.h>
#include <duibutton.h>
#include <duiimage.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibasiclayoutanimator.h>

//DuiButton* DcpBasicComponent::m_TriangleButtonOriginal = NULL;

DcpBasicComponent::DcpBasicComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata), m_Button(NULL)
{

    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setContentsMargins(0,0,0,0);
    m_MainLayout->setAnimator(NULL);
    m_MainLayoutPolicy = new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);

    m_WidgetLayout = new DuiLayout(0);
    m_WidgetLayout->setContentsMargins(0,0,0,0);
    m_WidgetLayoutPolicy = new DuiGridLayoutPolicy(m_WidgetLayout);
    m_WidgetLayout->setPolicy(m_WidgetLayoutPolicy);

   // DuiBasicLayoutAnimator* animator = new DuiBasicLayoutAnimator();
   
    //animator->setAnimationSpeed(1000);
    m_WidgetLayout->setAnimator(0);

}


DcpBasicComponent::~DcpBasicComponent()
{

}


void DcpBasicComponent::initLayout()
{
    DuiWidget* widget = new DuiWidget();
    widget->setLayout(m_WidgetLayout);
    m_MainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);;
}


void DcpBasicComponent::createContents()
{
}


void DcpBasicComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpBasicComponent::addItem ( QGraphicsLayoutItem * item )
{
    //m_Layout->addItem(item);
    m_Layout->addItemAtPosition(item, m_Layout->count());
}

void DcpBasicComponent::bigClicked()
{
	switchToSubPage();
}



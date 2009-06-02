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

//DuiButton* DcpBasicComponent::m_TriangleButtonOriginal = 0;

DcpBasicComponent::DcpBasicComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(0), m_Button(0)
{

    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setContentsMargins(0,0,0,0);
    m_MainLayout->setAnimator(0);
    m_MainLayoutPolicy = new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);

    m_WidgetLayout = new DuiLayout(0);
    m_WidgetLayout->setContentsMargins(0,0,0,0);
    m_WidgetLayoutPolicy = new DuiGridLayoutPolicy(m_WidgetLayout);
    m_WidgetLayout->setPolicy(m_WidgetLayoutPolicy);

   // DuiBasicLayoutAnimator* animator = new DuiBasicLayoutAnimator();

    //animator->setAnimationSpeed(1000);
    m_WidgetLayout->setAnimator(0);

    setMetadata(metadata);
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

void DcpBasicComponent::setMetadata(DcpAppletMetadata* metadata)
{
    if (m_Metadata) {
        disconnect (m_Metadata, SIGNAL(briefChanged()),
                    this, SLOT(onMetadataChanged()));
    }
    m_Metadata = metadata;
    connect (m_Metadata, SIGNAL(briefChanged()),
             this, SLOT(onMetadataChanged()));
}

void DcpBasicComponent::onMetadataChanged()
{
    Q_ASSERT(m_Metadata);
    Q_ASSERT(m_Button);

	m_Button->setText(metadata()->text1(), metadata()->text2());
}


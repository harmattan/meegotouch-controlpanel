#include "dcpbriefwidget.h"
#include "dcpappletmetadata.h"
#include "dcpbutton2.h"
#include "dcpbutton2toggle.h"
#include "dcpwidgettypes.h"

#include <DuiLinearLayoutPolicy>

DcpBriefWidget::DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent)
    : DuiWidget(parent), m_RealWidget(0), m_Metadata(0)
{
    DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(0);
    layout->setContentsMargins(0,0,0,0);
    m_Policy = new DuiLinearLayoutPolicy (layout, Qt::Vertical);
    this->setLayout(layout);

    setMetadata(metadata);
}

void DcpBriefWidget::setMetadata(DcpAppletMetadata* metadata)
{
    // can be optimized if necessery (not recreating the widget, just updating its contents)
    if (m_RealWidget) delete m_RealWidget;

    if (m_Metadata) {
        disconnect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));
    }
    m_Metadata = metadata;

    switch(m_Metadata->widgetTypeID()) {
        case DCPLABELBUTTON:
        case DCPLABEL2BUTTON:
            m_RealWidget = new DcpButton2Toggle(this);
            ((DcpButton2Toggle*)m_RealWidget)->setSmallToggle(m_Metadata->toggle());
/*            connect (m_RealWidget, SIGNAL(smallToggled(bool)),
                     m_Metadata, SLOT(setToggle(bool))); TODO XXX */
        break;
        case DCPLABEL2IMAGE :
            // TODO
        //break;
        default:
            m_RealWidget = new DcpButton2(this);
        break;
    }

    connect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));
    connect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));

    // this currently cannot change:
    m_RealWidget->setText1(m_Metadata->text1());
    updateContents();

    m_Policy->addItemAtPosition(m_RealWidget, 0);
}


void DcpBriefWidget::updateContents()
{
    m_RealWidget->setText2(m_Metadata->text2());
}


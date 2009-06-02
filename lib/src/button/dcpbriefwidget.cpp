#include "dcpbriefwidget.h"
#include "dcpappletmetadata.h"
#include "dcpbutton2.h"
#include "dcpwidgettypes.h"

#include <DuiLinearLayoutPolicy>

DcpBriefWidget::DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent)
    : DuiWidget(parent), m_RealWidget(0)
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

    switch(metadata->widgetTypeID()) {
        case DCPLABELBUTTON:
        case DCPLABEL2BUTTON:
            // TODO
        //break;
        case DCPLABEL2IMAGE :
            // TODO
        //break;
        default:
            m_RealWidget = new DcpButton2(this);
        break;
    }

    m_RealWidget->setText1(metadata->text1());
    m_RealWidget->setText2(metadata->text2());
    connect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));

    m_Policy->addItemAtPosition(m_RealWidget, 0);
}



/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "pagefactory.h"
#include "dcpbriefcomponent.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"
#include "dcpbriefwidget.h"
#include "dcpwidgettypes.h"
#include "pages.h"

#include <QGraphicsLinearLayout>
#include <DuiContentItem>


#define DEBUG
#include "../../../lib/src/dcpdebug.h"

DcpBriefComponent::DcpBriefComponent (
        DcpAppletObject   *applet,
        DcpComponent        *category,
        const QString       &logicalId)
: DcpComponent (category, "", 0, logicalId),
    m_BriefWidget (new DcpBriefWidget (applet, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout (this);
    layout->addItem (m_BriefWidget);

    setMattiID ("DcpBriefComponent::" + logicalId + "::" + 
            applet->metadata()->category() + "::" + applet->metadata()->name());
}


DcpBriefComponent::DcpBriefComponent (
        const QString       &line1,
        const QString       &line2,
        DcpComponent        *category,
        const QString       &logicalId)
: DcpComponent (category, "", 0, logicalId)
{
    QGraphicsLinearLayout* layout;
    
    m_BriefWidget = new DcpBriefWidget (DcpWidgetType::Toggle, line1, line2, this);
    layout = new QGraphicsLinearLayout (this);
    layout->addItem (m_BriefWidget);

    connect (m_BriefWidget, SIGNAL (clicked()),
            this, SLOT (activate()));
    
    setMattiID ("DcpBriefComponent::" + logicalId + "::" + "::" + line1);
}

DcpBriefComponent::DcpBriefComponent (
        const QString       &line,
        DcpComponent        *category,
        const QString       &logicalId)
: DcpComponent (category, "", 0, logicalId)
{
    QGraphicsLinearLayout* layout;
    
    DuiContentItem *item = new DuiContentItem(DuiContentItem::SingleTextLabel);
    item->setTitle(line);
    layout = new QGraphicsLinearLayout (this);
    layout->addItem (item);

    connect(item, SIGNAL (clicked()),
            this, SLOT (activate()));
    
    setMattiID ("DcpBriefComponent::" + logicalId + "::" + "::" + line);
}
DcpBriefComponent::~DcpBriefComponent()
{
}


void 
DcpBriefComponent::setApplet(
        DcpAppletObject* applet)
{
    m_BriefWidget->setApplet(applet);
}

void
DcpBriefComponent::activate ()
{
    DCP_DEBUG ("");
    /*
     * This is not very elegant. If the component has metadata the m_BriefWidget
     * will start the applet throught the metadata, if not we connected this
     * slot to the clicked() signal and we create a new page here.
     */
    PageFactory *pageFactory = PageFactory::instance();
    pageFactory->changePage (subPage());
}

#include "dcprecentlyusedcomponent.h"

#include "dcpappletdb.h"
#include "maintranslations.h"

#include "dcpmostusedcategory.h"
#include <duilabel.h>

DcpRecentlyUsedComponent::DcpRecentlyUsedComponent(
                            DcpCategory *category,
                            QGraphicsWidget *parent)
        : DcpBackgroundComponent(category, DcpMain::mostRecentUsedTitle, parent)
{
    createContents();
}
void DcpRecentlyUsedComponent::createContents()
{
    DcpBackgroundComponent::createContents();

    // TODO: to stylesheet
    setContentsMargins(18,10,18,20);
    // --

    m_MostUsedCategory = new DcpMostUsedCategory("TXT");
    connect(m_MostUsedCategory, SIGNAL(openSubPage(Pages::Handle)),
                this, SIGNAL(openSubPage(Pages::Handle)));
    addItem(m_MostUsedCategory);
}


void DcpRecentlyUsedComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    m_MostUsedCategory->onOrientationChange(orientation);
    DcpBackgroundComponent::onOrientationChange(orientation);
}

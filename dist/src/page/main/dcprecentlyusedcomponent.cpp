#include "dcprecentlyusedcomponent.h"

#include "dcpmostusedcontainer.h"

DcpRecentlyUsedComponent::DcpRecentlyUsedComponent(
                            DcpCategory *category,
                            QGraphicsWidget *parent)
        : DcpBackgroundComponent(category, tr("Most recent used"), parent)
{
    createContents();
}

void DcpRecentlyUsedComponent::createContents()
{
    DcpBackgroundComponent::createContents();

    DcpMostUsedContainer *tmpContainer = new DcpMostUsedContainer;
    
    tmpContainer->add("aaaa", "1");
    tmpContainer->add("aaaa", "2");
    
    tmpContainer->add("bbbb", "1", false);
    tmpContainer->add("bbbb", "2");
    
    tmpContainer->add("cccc", "1");
    tmpContainer->add("cccc", "2", false);
    
    addItem(tmpContainer->layout());

    addItem(new DuiWidget());
}


void DcpRecentlyUsedComponent::onOrientationChange (
                                    const Dui::Orientation &orientation)
{
    DcpBackgroundComponent::onOrientationChange(orientation);
}

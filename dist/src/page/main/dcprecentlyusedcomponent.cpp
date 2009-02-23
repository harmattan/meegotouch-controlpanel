#include "dcprecentlyusedcomponent.h"


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

    addItem(new DuiWidget());
}


void DcpRecentlyUsedComponent::onOrientationChange (
                                    const Dui::Orientation &orientation)
{
    DcpBackgroundComponent::onOrientationChange(orientation);
}

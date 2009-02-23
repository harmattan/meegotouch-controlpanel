#include "duirecentlyusedcomponent.h"


DuiRecentlyUsedComponent::DuiRecentlyUsedComponent(
                            DuiSettingsCategory *category,
                            QGraphicsWidget *parent)
        : DuiBackgroundComponent(category, tr("Most recent used"), parent)
{
    createContents();
}

void DuiRecentlyUsedComponent::createContents()
{
    DuiBackgroundComponent::createContents();

    addItem(new DuiWidget());
}


void DuiRecentlyUsedComponent::onOrientationChange (
                                    const Dui::Orientation &orientation)
{
    DuiBackgroundComponent::onOrientationChange(orientation);
}

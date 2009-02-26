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
    

    tmpContainer->add("desktop/ringtone.desktop");
    tmpContainer->add("desktop/profile.desktop");

    tmpContainer->add("desktop/theme.desktop");
    tmpContainer->add("desktop/wallpaper.desktop");


    tmpContainer->add("desktop/language.desktop");
    tmpContainer->add("desktop/region_format.desktop");


/*
language.desktop
ringtone.desktop
region_format.desktop   
wallpaper.desktop
profile.desktop    
theme.desktop      
*/


    /*
    tmpContainer->addButton("aaaa", "1");
    tmpContainer->addButton("aaaa", "2");
    
    tmpContainer->addButton("bbbb", "1", false);
    tmpContainer->addButton("bbbb", "2");
    
    tmpContainer->addLabel("cccc", "1111");
    
    tmpContainer->addButton("cccc", "2", false);
    */
    addItem(tmpContainer->layout());

    addItem(new DuiWidget());
}


void DcpRecentlyUsedComponent::onOrientationChange (
                                    const Dui::Orientation &orientation)
{
    DcpBackgroundComponent::onOrientationChange(orientation);
}

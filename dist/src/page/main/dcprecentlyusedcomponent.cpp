#include "dcprecentlyusedcomponent.h"

#include "dcpmostusedcontainer.h"
#include "dcpappletdb.h"

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
    
    DcpAppletDb *db = DcpAppletDb::instance();   


    tmpContainer->add(db->applet("Ringtone"));
    tmpContainer->add(db->applet("Profile"));

    tmpContainer->add(db->applet("Theme"));
    tmpContainer->add(db->applet("Wallpaper"));


    tmpContainer->add(db->applet("Language"));
    tmpContainer->add(db->applet("Region_format"));


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

  //  addItem(new DuiWidget());
}


void DcpRecentlyUsedComponent::onOrientationChange (
                                    const Dui::Orientation &orientation)
{
    DcpBackgroundComponent::onOrientationChange(orientation);
}

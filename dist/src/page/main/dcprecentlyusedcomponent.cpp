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

    tmpContainer->add(db->applet("spec"));

    tmpContainer->add(db->applet("ringtone.desktop"));
    tmpContainer->add(db->applet("profile.desktop"));


    tmpContainer->addButton("aaaa", "1", true, 2);

    tmpContainer->add(db->applet("theme.desktop"));
    tmpContainer->add(db->applet("wallpaper.desktop"));


    //tmpContainer->add("desktop/language.desktop");
    //tmpContainer->add("desktop/region_format.desktop");


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

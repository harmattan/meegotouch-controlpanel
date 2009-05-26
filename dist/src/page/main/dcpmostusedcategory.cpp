#include "pages.h"

#include <QtDebug>

#include "dcpappletdb.h"
#include "dcprecentlyusedcomponent.h"

#include "dcplabel2component.h"
#include "dcplabel2togglecomponent.h"
#include "dcplabel2imagecomponent.h"
#include "dcplabelbuttoncomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include <DuiSceneManager>

DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{

  	createContents();

    m_LandscapeLayout->setContentsMargins(12, 0, 12, 0);
    setVerticalSpacing(0);

//    layout()->setContentsMargins(30, 0, 30, 0);

   //m_Background = new QPixmap("images/backgroundP.png");

}

void DcpMostUsedCategory::createContents()
{
    setMaxColumns(2);

    //dummy code
  /*  addComponent(DcpAppletDb::instance()->applet("Browser"));
    addComponent(DcpAppletDb::instance()->applet("Wallpaper"));
    addComponent(DcpAppletDb::instance()->applet("Positioning"));
    addComponent(DcpAppletDb::instance()->applet("Display"));
    addComponent(DcpAppletDb::instance()->applet("DateTime"));
    addComponent(DcpAppletDb::instance()->applet("Passcode"));*/

    DcpAppletMetadataList list = DcpAppletDb::instance()->listMostUsed();
	int cnt = 0;
	foreach (DcpAppletMetadata *item, list) {
		cnt++;
		if (cnt == list.count() && cnt % 2 == 1) //last item is impaired
			addComponent(item, true);	
		else
			addComponent(item, false);
    }
    correctLines();
}


void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata, bool fullLine)
{

	DcpComponent *component = 0;

	switch (metadata->widgetTypeID()) {
		case DCPLABEL :
		break;
		case DCPLABEL2 :
			component = new DcpLabel2Component(this, metadata);
		break;
		case DCPLABELBUTTON :
			component = new DcpLabelButtonComponent(this, metadata);
		break;
		case DCPLABEL2TOGGLE :
		case DCPLABEL2BUTTON :	//dummy
			component = new DcpLabel2ToggleComponent(this, metadata);
		break;
		case DCPLABEL2IMAGE :
			component = new DcpLabel2ImageComponent(this, metadata);
		break;
	}

    if (component) {
		qDebug() << "DCP: connecting to " << metadata->name();
		component->setSubPage(Pages::APPLETFROMMOSTUSED, metadata->name());
		connect(component, SIGNAL(openSubPage(Pages::Handle)), this, SIGNAL(openSubPage(Pages::Handle)));
        if (fullLine) {
            add(component);
        } else {
		    append(component);
        }
	}
}


void DcpMostUsedCategory::onOrientationChange(const Dui::Orientation& orientation)
{
    DcpMainCategory::onOrientationChange(orientation);

    // set correct lines
    correctLines();
}

void DcpMostUsedCategory::correctLines()
{
    int itemCount = layout()->count();
    if (itemCount > 0) {
        DcpBasicComponent* lastWidget = 
            static_cast<DcpBasicComponent*>(layout()->itemAt(itemCount-1));
        lastWidget->setLine(false);
        if (itemCount > 1) {
            DcpBasicComponent* lastLastWidget = 
                static_cast<DcpBasicComponent*>(layout()->itemAt(itemCount-2));
            bool isLandscape = (DuiSceneManager::instance()->orientation() == Dui::Landscape);
            bool isPaired = (itemCount % 2 == 0);
            lastLastWidget->setLine(!(isPaired && isLandscape));
        }
    }
}


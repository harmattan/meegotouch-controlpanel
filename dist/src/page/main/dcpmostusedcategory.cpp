#include "dcpmostusedcategory.h"

#include "pages.h"
#include <DcpAppletDb>
#include "dcpbriefcomponent.h"
#include <DcpAppletMetadata>
#include <DcpApplet>

#include <QtDebug>
#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>

/*!
 * \class DcpMostUsedCategory
 * \brief A container which contains buttons that represents the
 * most frequent used applets.
 *
 * Using it on the top of main page inside DcpRecentlyUsedComponent
 */

DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{
  	createContents();

    m_PortraitLayout->setObjectName("MostUsedItems");
    m_LandscapeLayout->setObjectName("MostUsedItems");
    setVerticalSpacing(0);
}

void DcpMostUsedCategory::createContents()
{
    setCreateSeparators(true);
    setMaxColumns(2);

    DcpAppletMetadataList list = DcpAppletDb::instance()->listMostUsed();

	int cnt = 0;
	foreach (DcpAppletMetadata *item, list) {
		cnt++;
		if (cnt == list.count() && cnt % 2 == 1) //last item is impaired
			addComponent(item, true);	
		else
			addComponent(item, false);
    }
}

void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata, bool fullLine)
{
	DcpBriefComponent *component = new DcpBriefComponent(metadata, this);

	component->setSubPage(Pages::APPLET, metadata->name());
	connect(component, SIGNAL(openSubPage(Pages::Handle)), this, SIGNAL(openSubPage(Pages::Handle)));

    if (fullLine)
        add(component);
    else
        append(component);
}

void DcpMostUsedCategory::onOrientationChange(const Dui::Orientation& orientation)
{
    DcpMainCategory::onOrientationChange(orientation);
}

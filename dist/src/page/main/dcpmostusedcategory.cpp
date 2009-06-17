#include "dcpmostusedcategory.h"

#include "pages.h"
#include "dcpappletdb.h"
#include "dcpbriefcomponent.h"
#include "dcpappletmetadata.h"
#include "dcpapplet.h"

#include <QtDebug>
#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>

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

    m_LandscapeLayout->setContentsMargins(12, 0, 12, 12);
    setVerticalSpacing(0);

//    layout()->setContentsMargins(30, 0, 30, 0);

   //m_Background = new QPixmap("images/backgroundP.png");

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
    removeLastSeparators();
}


void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata, bool fullLine)
{

	DcpBriefComponent *component = new DcpBriefComponent(metadata, this);

	component->setSubPage(Pages::APPLETFROMMOSTUSED, metadata->name());
	connect(component, SIGNAL(openSubPage(Pages::Handle)), this, SIGNAL(openSubPage(Pages::Handle)));
    if (fullLine) {
        add(component);
    } else {
        append(component);
    }
}


void DcpMostUsedCategory::onOrientationChange(const Dui::Orientation& orientation)
{
    DcpMainCategory::onOrientationChange(orientation);
}



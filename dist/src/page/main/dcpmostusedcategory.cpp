#include "pages.h"

#include <QtDebug>

#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcprecentlyusedcomponent.h"

#include "dcplabel2component.h"
#include "dcplabel2togglecomponent.h"
#include "dcplabel2imagecomponent.h"
#include "dcplabelbuttoncomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"
#include "dcpapplet.h"

DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{

  	createContents();

    //m_LandscapeLayout->setColumnSpacing(0, 0); //dummy

//    layout()->setContentsMargins(0, 10, 0, 10);

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

	int cnt = 0;
	foreach (DcpAppletMetadata *item, DcpAppletDb::instance()->listMostUsed()) {

		if (cnt==5 || cnt==6) //last items
			addComponent(item, false);	
		else
			addComponent(item);
    }

}

void DcpMostUsedCategory::paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	DuiWidget::paint(painter, option, widget);

	/*//dummy
	const QColor LINECOLOR = QColor(64, 64, 64);
	painter->setPen(LINECOLOR);
	for (int y=0; y<2; y++)
		for (int x=0; x<2; x++)
			painter->drawLine(x*420, 105 + y*100, (x+1)*405 , 105 + y*100);
	*/
}

void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata, bool line)
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
		static_cast<DcpBasicComponent*>(component)->setLine(line);

		qDebug() << "DCP: connecting to " << metadata->name();
		component->setSubPage(Pages::APPLETFROMMOSTUSED, metadata->name());
		connect(component, SIGNAL(openSubPage(Pages::Handle)), this, SIGNAL(openSubPage(Pages::Handle)));
		append(component);

/* ONLY TEST VERSION
static int localCnt = 0;

++localCnt;
if (localCnt == 2 || localCnt ==6)
	add(component);
else
	append(component);
*/
	}
}

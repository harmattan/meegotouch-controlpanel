#include "pages.h"

#include <QtDebug>

#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcprecentlyusedcomponent.h"

#include "dcplabelcomponent.h"
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

    setContentsMargins(0, 10, 0, 10);

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

    foreach (DcpAppletMetadata *item, DcpAppletDb::instance()->listMostUsed()) {
         addComponent(item);
    }

}

void DcpMostUsedCategory::paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	DuiWidget::paint(painter, option, widget);

	painter->setPen(QColor(64, 64, 64));

	for (int y=0; y<2; y++)
		for (int x=0; x<2; x++)
			painter->drawLine(x*420, 105 + y*100, (x+1)*405 , 105 + y*100);
}

void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata)
{

  DcpComponent *component = 0;

  switch (metadata->widgetTypeID()) {
      case DCPLABEL :
          component = new DcpLabelComponent(this, metadata);
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
        append(component);
    }
}

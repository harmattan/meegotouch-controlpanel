#include "dcpmainpage.h"

#include <QtDebug>


#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"

#include "dcpbuttoncomponent.h"
#include "dcplabelcomponent.h"
#include "dcpimagecomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"
#include "dcpapplet.h"

const static int SIZEWIDTH = 760;
const static int SIZEHEIGHT = 400;


DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{
  createContents();

   //m_Background = new QPixmap("images/backgroundP.png");

}

void DcpMostUsedCategory::createContents()
{
    setMaxColumns(2);

//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/language.desktop")));
//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/profile.desktop")));
    
//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/region_format.desktop")));
//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/ringtone.desktop")));
  
//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/theme.desktop")));
//    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/wallpaper.desktop")));


    addWidget(DcpApplet::DefaultPath + "language.desktop");
    addWidget(DcpApplet::DefaultPath + "profile.desktop");
    
    addWidget(DcpApplet::DefaultPath + "region_format.desktop");
    addWidget(DcpApplet::DefaultPath + "ringtone.desktop");
  
    addWidget(DcpApplet::DefaultPath + "theme.desktop");
    addWidget(DcpApplet::DefaultPath + "wallpaper.desktop");

}

void DcpMostUsedCategory::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{
    //Q_UNUSED(option);
    //Q_UNUSED(widget);

//   painter->drawPixmap(0, 0, SIZEWIDTH, SIZEHEIGHT,  *m_Background);

  DuiWidget::paint(painter, option, widget);

}

void DcpMostUsedCategory::addWidget(const QString& file)
{
  
  DcpAppletMetadata* metadata = new DcpAppletMetadata(file);

  if (metadata->widgetType() == "DcpLabel") {
    append(new DcpLabelComponent(this, metadata));
    //addLabelCSS(metadata->text1(), metadata->text2(), metadata->buttonCSS(), metadata->label1CSS(), metadata->label2CSS());
  } else if (metadata->widgetType() == "DcpButton") {
    //addButton(metadata->text1(), metadata->text2());
  } else if (metadata->widgetType() == "DcpImage") {
    append(new DcpImageComponent(this, metadata));
   // addImageCSS(metadata->text1(), metadata->image(), metadata->buttonCSS(), metadata->label1CSS());
  } else if (metadata->widgetType() == "DcpSpec") {
      //dummy  
 //     DcpSpec *tmpSpec = new DcpSpec(metadata->image(), 200, 100, 10, 10, "");
 //     m_Layout->addItem(tmpSpec->layout(), m_PosY, m_PosX, Qt::AlignCenter);
 //     addPos();
  }

  delete metadata;
}

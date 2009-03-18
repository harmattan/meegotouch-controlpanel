#include "dcpmainpage.h"

#include <QtDebug>


#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"

#include "dcpbuttoncomponent.h"
#include "dcplabelcomponent.h"
#include "dcplabel2component.h"
#include "dcpimagecomponent.h"
#include "dcplabel2buttoncomponent.h"
#include "dcplabel2imagecomponent.h"
#include "dcplabelbuttoncomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"

#include "duilinearlayout.h"
#include "duigridlayout.h"

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


    //dummy code
    /*addWidget("desktop/language.desktop");
    addWidget("desktop/profile.desktop");
    addWidget("desktop/region_format.desktop");
    addWidget("desktop/ringtone.desktop");
    addWidget("desktop/theme.desktop");
    addWidget("desktop/wallpaper.desktop");*/

    addWidget("desktop/browser.desktop");
    addWidget("desktop/wallpaper.desktop");
    addWidget("desktop/positioning.desktop");
    addWidget("desktop/display.desktop");
    addWidget("desktop/datetime.desktop");
    addWidget("desktop/passcode.desktop");

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
  } else if (metadata->widgetType() == "DcpLabel2") {
    append(new DcpLabel2Component(this, metadata));
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
  } else if (metadata->widgetType() == "DcpLabelButton") {
    append(new DcpLabelButtonComponent(this, metadata));
  } else if (metadata->widgetType() == "DcpLabel2Button") {
    append(new DcpLabel2ButtonComponent(this, metadata));
  } else if (metadata->widgetType() == "DcpLabel2Image") {
    append(new DcpLabel2ImageComponent(this, metadata));
  }

  delete metadata;
}

void 
DcpMostUsedCategory::onOrientationChange (const Dui::Orientation &orientation)
{

    if (orientation == Dui::Portrait) {

        m_ColCount = 0;
        m_RowCount = 0;

        foreach(DcpComponent *component, m_Children) {
            m_Layout->removeAt(0);
        }

        setMaxColumns(1);

        foreach(DcpComponent *component, m_Children) {
            add(component);
        }


    }
    else {

        m_ColCount = 0;
        m_RowCount = 0;

         foreach(DcpComponent *component, m_Children) {
            m_Layout->removeAt(0);
        }

        setMaxColumns(2);

        foreach(DcpComponent *component, m_Children) {
            add(component);
        }
   }

return;
//DcpMainCategory::onOrientationChange (orientation);

//return;

    if (orientation == Dui::Portrait) {

        DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical);

int cnt = 0;

        foreach(DcpComponent *component, m_Children) {

        qDebug() << "CNT: " << cnt++;

            component->onOrientationChange(orientation);
            layout->addItem(component);
        }

        setLayout(layout);

        //delete m_Layout;
        //m_Layout = 0;

    }
    else {
   /*
      qDebug() << "  ----------------------------------------------  DcpMostUsedCategory   other";
       //DuiLinearLayout *layout = (DuiLinearLayout*)(this->layout());
        m_Layout = new DuiGridLayout();
        foreach(DcpComponent *component, m_Children)
        {
            component->onOrientationChange(orientation);
            if (m_ColSpans[component] == m_MaxColumns)
                add(component);
            else
                append(component);
        }
        //delete layout;
*/
        setLayout(m_Layout);
        qDebug() << "Changing orientation to Dui::Landscape";
   }
}   


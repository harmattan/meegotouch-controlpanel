#include "dcpmainpage.h"

#include <QtDebug>


#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"

#include "dcpbuttoncomponent.h"
#include "dcplabelcomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"


DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{
  createContents();

   m_Background = new QPixmap("images/backgroundP.png");

}

void DcpMostUsedCategory::createContents()
{
    setMaxColumns(2);

    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/language.desktop")));
    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/profile.desktop")));
    
    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/region_format.desktop")));
    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/ringtone.desktop")));
  
    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/theme.desktop")));
    append(new DcpLabelComponent(this, new DcpAppletMetadata("desktop/wallpaper.desktop")));
}

void DcpMostUsedCategory::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{
    //Q_UNUSED(option);
    //Q_UNUSED(widget);

   painter->drawPixmap(0, 0, 760, 400,  *m_Background);

  DuiWidget::paint(painter, option, widget);

}


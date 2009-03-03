
#include "dcpmostusedcontainer.h"

#include "dcpbutton.h"
#include "dcplabel.h"
#include "dcpimage.h"

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>

#include "dcpdesktopentry.h"

#include "dcpspec.h"

DcpMostUsedContainer::DcpMostUsedContainer() :
    m_PosX(0) ,
    m_PosY(0)

{
    m_Layout = new DuiGridLayout;

    for (int xx =0; xx<2; xx++) {
        m_Layout->setColumnMinimumWidth ( xx, layoutFieldWidth );
        m_Layout->setColumnMaximumWidth ( xx, layoutFieldWidth );
    }

    for (int yy =0; yy<3; yy++) {
        m_Layout->setRowMinimumHeight ( yy, layoutFieltHeight );
        m_Layout->setRowMaximumHeight ( yy, layoutFieltHeight );
    }

}

void DcpMostUsedContainer::add(const QString& file)
{
  DcpDesktopEntry* tmp = new DcpDesktopEntry(file);

  if (tmp->widgetType() == "DcpLabel") {
    addLabelCSS(tmp->text1(), tmp->text2(), tmp->buttonCSS(), tmp->label1CSS(), tmp->label2CSS());
  } else if (tmp->widgetType() == "DcpButton") {
    addButton(tmp->text1(), tmp->text2());
  } else if (tmp->widgetType() == "DcpImage") {
    addImageCSS(tmp->text1(), tmp->image(), tmp->buttonCSS(), tmp->label1CSS());
  } else if (tmp->widgetType() == "DcpSpec") {
   
      DcpSpec *tmpSpec = new DcpSpec(tmp->image(), 200, 100, 30, 30, "");
      m_Layout->addItem(tmpSpec->layout(), m_PosY, m_PosX, Qt::AlignCenter);
      addPos();
  }


  delete tmp;
}

void DcpMostUsedContainer::addButton(const QString& text1, const QString& text2, bool enable, int length)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int widthBig = 350;
    if (length==2)
      widthBig = 705;
   
    int heightBig = 100;
    int posXSmall = 250;
    int posYSmall = 10;
    int widthSmall  = 80;
    int heightSmall = 80;

    DcpButton *tmpButton = new DcpButton(text1, widthBig, heightBig, text2, posXSmall, posYSmall, widthSmall, heightSmall, enable);
    //m_Layout->addItem(new DuiButton("test")/*tmpButton*/, m_PosX, m_PosY, Qt::AlignCenter);


    if  (length==2) {
        
        if (m_PosX!=0) {
            m_PosX = 0;
            m_PosY++;
        }
  
        m_Layout->addItem(tmpButton->layout(), m_PosY, m_PosX, 1, 2, Qt::AlignCenter);
        //m_Layout->addItem(tmpButton->layout(), m_PosY, m_PosX, 1, 2, Qt::AlignHCenter|Qt::AlignLeft);
        addPos2();
    } else {
        m_Layout->addItem(tmpButton->layout(), m_PosY, m_PosX, Qt::AlignCenter);
        addPos();
    }
   
}

void DcpMostUsedContainer::addLabel(const QString& text1, const QString& text2)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int width  = 350;
    int upHeight = 50;
    int downHeight = 50;
    
    DcpLabel *tmpLabel = new DcpLabel(text1, text2, width, upHeight, downHeight);
    
    m_Layout->addItem(tmpLabel->layout(), m_PosY, m_PosX, Qt::AlignCenter);

    addPos();
}

void DcpMostUsedContainer::addLabelCSS(const QString& text1, const QString& text2, const QString& cssButton, const QString& cssUpLabel, const QString& cssDownLabel)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int width  = 350;
    int upHeight = 50;
    int downHeight = 50;
    
    DcpLabel *tmpLabel = new DcpLabel(text1, text2, width, upHeight, downHeight, cssButton, cssUpLabel, cssDownLabel);
    
    m_Layout->addItem(tmpLabel->layout(), m_PosY, m_PosX, Qt::AlignCenter);

    addPos();
}

void DcpMostUsedContainer::addImageCSS(const QString& text, const QString& image, const QString& cssButton, const QString& cssLabel)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int width  = 350;
    int upHeight = 50;
    int downHeight = 50;

    int imageHeight = 100;
    
    DcpImage *tmpImage = new DcpImage(text, image, width, upHeight, downHeight, imageHeight, cssButton, cssLabel);

    m_Layout->addItem(tmpImage->layout(), m_PosY, m_PosX, Qt::AlignCenter);

    addPos();
}


DuiGridLayout* DcpMostUsedContainer::layout()
{
    return m_Layout;
}

void DcpMostUsedContainer::addPos()
{
    m_PosX++;

    if (m_PosX>1) {
        m_PosX = 0;
        m_PosY++;
    }
}

void DcpMostUsedContainer::addPos2()
{
    m_PosX+=2;

    if (m_PosX>1) {
        m_PosX = 0;
        m_PosY++;
    }
}


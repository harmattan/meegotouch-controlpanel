
#include "dcpmostusedcontainer.h"

#include "dcpbutton.h"

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>


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

void DcpMostUsedContainer::add(QString text1, QString text2, bool enable)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int widthBig  = 350;
    int heightBig = 100;
    int posXSmall = 250;
    int posYSmall = 10;
    int widthSmall  = 80;
    int heightSmall = 80;

    DcpButton *tmpButton = new DcpButton(text1, widthBig, heightBig, text2, posXSmall, posYSmall, widthSmall, heightSmall, enable);
    //m_Layout->addItem(new DuiButton("test")/*tmpButton*/, m_PosX, m_PosY, Qt::AlignCenter);

    m_Layout->addItem(tmpButton->layout(), m_PosY, m_PosX, Qt::AlignCenter);


    m_PosX++;

    if (m_PosX>1) {
        m_PosX = 0;
        m_PosY++;
    }
}


DuiGridLayout* DcpMostUsedContainer::layout()
{
    return m_Layout;
}


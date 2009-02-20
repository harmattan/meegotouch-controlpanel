#include "button2.h"

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>

#include <duibutton2view.h>

#include <QDir>

MainContainer::MainContainer() :
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

void MainContainer::add(QString text1, QString text2)
{
    //m_Layout->addItem(new DuiButton(text1), xx, yy, Qt::AlignCenter);
    
    //dummy data
    int widthBig  = 350;
    int heightBig = 100;
    int posXSmall = 250;
    int posYSmall = 10;
    int widthSmall  = 80;
    int heightSmall = 80;

    CButton2 *tmpButton = new CButton2(text1, widthBig, heightBig, text2, posXSmall, posYSmall, widthSmall, heightSmall);
    //m_Layout->addItem(new DuiButton("test")/*tmpButton*/, m_PosX, m_PosY, Qt::AlignCenter);

    m_Layout->addItem(tmpButton->layout(), m_PosY, m_PosX, Qt::AlignCenter);


    m_PosX++;

    if (m_PosX>1) {
        m_PosX = 0;
        m_PosY++;
    }
}


DuiGridLayout* MainContainer::layout()
{
    return m_Layout;
}

CButton2::CButton2(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight)
{
    m_Layout = new DuiGridLayout();

    m_Layout->setColumnMinimumWidth ( 0, smallX );
    m_Layout->setColumnMinimumWidth ( 1, smallWidth );
    m_Layout->setColumnMinimumWidth ( 2, bigWidth - smallX - smallWidth );

    m_Layout->setColumnMaximumWidth ( 0, smallX );
    m_Layout->setColumnMaximumWidth ( 1, smallWidth );
    m_Layout->setColumnMaximumWidth ( 2, bigWidth - smallX - smallWidth );


    m_Layout->setRowMinimumHeight ( 0, smallY );
    m_Layout->setRowMinimumHeight ( 1, smallHeight );
    m_Layout->setRowMinimumHeight ( 2, bigHeight - smallY - smallHeight );

    m_Layout->setRowMaximumHeight ( 0, smallY );
    m_Layout->setRowMaximumHeight ( 1, smallHeight );
    m_Layout->setRowMaximumHeight ( 2, bigHeight - smallY - smallHeight );

    /* //only test
    for (int yy =0; yy<3; yy++)
        for (int xx =0; xx<3; xx++)
            m_Layout->addItem(new DuiButton("text"), xx, yy, Qt::AlignCenter);
     */


    m_BigButton = new DuiButton(bigLabel);
    m_SmallButton = new DuiButton(smallLabel);
    
    m_BigButton->setObjectName("BigButton");
    m_SmallButton->setObjectName("SmallButton");

/*
    m_BigButton->setMinimumWidth(bigWidth);
    m_SmallButton->setMinimumWidth(smallWidth);

    m_BigButton->setMaximumWidth(bigWidth);
    m_SmallButton->setMaximumWidth(smallWidth);


    m_BigButton->setMinimumHeight(bigHeight);
    m_SmallButton->setMinimumHeight(smallHeight);

    m_BigButton->setMaximumHeight(bigHeight);
    m_SmallButton->setMaximumHeight(smallHeight);
*/


    /*
    m_BigButtonView = DuiTheme::view(m_BigButton);
    m_BigButtonView->setObjectName("BigButtonView");
    m_BigButton->setView(m_BigButtonView);

    m_SmallButtonView = DuiTheme::view(m_SmallButton);
    m_SmallButtonView->setObjectName("SmallButtonView");
    m_SmallButton->setView(m_SmallButtonView);
*/

    button2 = new DuiButton();
//    button2->setObjectName("TestButton");
    button2->setText("Test");

    view = DuiTheme::view(button2);
    button2->setView(view);



    m_Layout->addItem(button2, 0, 0, 3, 3, Qt::AlignCenter);
    //m_Layout->addItem(m_SmallButton, 1, 1, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButton, SIGNAL(clicked()), this, SLOT(smallClicked()));


//    m_BigButton->hide();


    m_BigButton->setZValue(0);
    m_SmallButton->setZValue(1);


}

DuiGridLayout* CButton2::layout()
{
    return m_Layout;
}

void CButton2::bigClicked()
{
    qDebug() << "bigClicked";
    emit clicked("bigClicked");
}

void CButton2::smallClicked()
{
    qDebug() << "smallClicked";
    emit clicked("smallClicked");
}

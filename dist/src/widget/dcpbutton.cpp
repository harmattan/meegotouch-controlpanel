#include "dcpbutton.h"

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>



DcpButton::DcpButton(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable)
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

    m_BigButton->setObjectName("BigButton");
    m_BigButton->setMinimumWidth(bigWidth);
    m_BigButton->setMaximumWidth(bigWidth);
    m_BigButton->setMinimumHeight(bigHeight);
    m_BigButton->setMaximumHeight(bigHeight);


    m_SmallButtonOn = new DuiButton(smallLabel);
    m_SmallButtonOn->setObjectName("SmallButtonOn");
    m_SmallButtonOn->setMinimumWidth(smallWidth);
    m_SmallButtonOn->setMaximumWidth(smallWidth);
    m_SmallButtonOn->setMinimumHeight(smallHeight);
    m_SmallButtonOn->setMaximumHeight(smallHeight);

    m_SmallButtonOff = new DuiButton(smallLabel);
    m_SmallButtonOff->setObjectName("SmallButtonOff");
    m_SmallButtonOff->setMinimumWidth(smallWidth);
    m_SmallButtonOff->setMaximumWidth(smallWidth);
    m_SmallButtonOff->setMinimumHeight(smallHeight);
    m_SmallButtonOff->setMaximumHeight(smallHeight);

    m_DisableButton = new DuiButton(smallLabel);
    m_DisableButton->setObjectName("SmallButtonDisable");
    m_DisableButton->setMinimumWidth(smallWidth);
    m_DisableButton->setMaximumWidth(smallWidth);
    m_DisableButton->setMinimumHeight(smallHeight);
    m_DisableButton->setMaximumHeight(smallHeight);



    /*
    m_BigButtonView = DuiTheme::view(m_BigButton);
    m_BigButtonView->setObjectName("BigButtonView");
    m_BigButton->setView(m_BigButtonView);

    m_SmallButtonView = DuiTheme::view(m_SmallButton);
    m_SmallButtonView->setObjectName("SmallButtonView");
    m_SmallButton->setView(m_SmallButtonView);
*/

//    button2 = new DuiButton();
//    button2->setObjectName("BigButton");
//    button2->setText("Test");

//    view = DuiTheme::view(button2);
//    button2->setObjectName("BigButtonView");
//    button2->setView(view);


    //m_Layout->addItem(m_BigButton, 0, 0, 3, 3, Qt::AlignCenter);
    m_Layout->addItem(m_BigButton, 0, 0, 3, 3, Qt::AlignLeft);
    m_Layout->addItem(m_SmallButtonOn, 1, 1, Qt::AlignCenter);
    m_Layout->addItem(m_SmallButtonOff, 1, 1, Qt::AlignCenter);
    m_Layout->addItem(m_DisableButton, 1, 1, Qt::AlignCenter);


    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButtonOn, SIGNAL(clicked()), this, SLOT(smallClickedOn()));
    connect(m_SmallButtonOff, SIGNAL(clicked()), this, SLOT(smallClickedOff()));
    connect(m_DisableButton, SIGNAL(clicked()), this, SLOT(disableClicked()));


    setEnable(enable);


    m_BigButton->setZValue(1);
    m_SmallButtonOn->setZValue(2);
    m_SmallButtonOff->setZValue(3);
    m_DisableButton->setZValue(4);

}

void DcpButton::setEnable(bool enable) {

    m_Enable = enable;

    if (m_Enable) {
        m_SmallButtonOn->show();
        m_SmallButtonOff->hide();
        m_DisableButton->hide();
    } else {
        m_SmallButtonOn->hide();
        m_SmallButtonOff->hide();
        m_DisableButton->show();
    }

}

DuiGridLayout* DcpButton::layout()
{
    return m_Layout;
}

void DcpButton::bigClicked()
{
    qDebug() << "bigClicked";
    emit clicked("bigClicked");
}

void DcpButton::smallClickedOn()
{
    m_SmallButtonOn->hide();
    m_SmallButtonOff->show();

    qDebug() << "smallClickedOn";
    emit clicked("smallClickedOn");
}

void DcpButton::smallClickedOff()
{
    m_SmallButtonOn->show();
    m_SmallButtonOff->hide();

    qDebug() << "smallClickedOff";
    emit clicked("smallClickedOff");
}

void DcpButton::disableClicked()
{
    qDebug() << "disableClicked";
    emit clicked("disableClicked");
}

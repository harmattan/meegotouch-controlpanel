#include "dcplabel.h"

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>

const float MINIMALIZE = 0.9f;
#include "dcpbuttonview.h"

DcpLabel::DcpLabel(const QString& upLabel, const QString& downLabel, int width, int upHeight, int downHeight, const QString& cssButton, const QString& cssUpLabel, const QString& cssDownLabel)
{
    m_Layout = new DuiGridLayout();

    m_Layout->setColumnMinimumWidth ( 0, width );
    
    m_Layout->setColumnMaximumWidth ( 0, width );
    
    m_Layout->setRowMinimumHeight ( 0, upHeight );
    m_Layout->setRowMinimumHeight ( 1, downHeight );
    

    m_Layout->setRowMaximumHeight ( 0, upHeight );
    m_Layout->setRowMaximumHeight ( 1, downHeight );

    /* //only test
    for (int yy =0; yy<3; yy++)
        for (int xx =0; xx<3; xx++)
            m_Layout->addItem(new DuiButton("text"), xx, yy, Qt::AlignCenter);
     */

    m_Button = new DuiButton("");


    // TODO: this moves to the view config file when updating to newer dui
    m_Button->setView(new DcpButtonView(m_Button));
    m_Button->setObjectName(cssButton);

    m_Button->setMinimumWidth(width);
    m_Button->setMaximumWidth(width);
    m_Button->setMinimumHeight(upHeight + downHeight);
    m_Button->setMaximumHeight(upHeight + downHeight);


    m_UpLabel = new DuiLabel(upLabel);
    m_UpLabel->setObjectName(cssUpLabel);
    m_UpLabel->setMinimumWidth(width*MINIMALIZE);
    m_UpLabel->setMaximumWidth(width*MINIMALIZE);
    m_UpLabel->setMinimumHeight(upHeight);
    m_UpLabel->setMaximumHeight(upHeight);
    m_UpLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_UpLabel->setAcceptedMouseButtons(0);

    m_DownLabel = new DuiLabel(downLabel);
    m_DownLabel->setObjectName(cssDownLabel);
    m_DownLabel->setMinimumWidth(width*MINIMALIZE);
    m_DownLabel->setMaximumWidth(width*MINIMALIZE);
    m_DownLabel->setMinimumHeight(downHeight);
    m_DownLabel->setMaximumHeight(downHeight);
    m_DownLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_DownLabel->setAcceptedMouseButtons(0);

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


    m_Layout->addItem(m_Button, 0, 0, 2, 1, Qt::AlignCenter);
    m_Layout->addItem(m_UpLabel, 0, 0, Qt::AlignCenter);
    m_Layout->addItem(m_DownLabel, 1, 0, Qt::AlignCenter);


    connect(m_Button, SIGNAL(clicked()), this, SLOT(labelButtonClicked()));

    m_Button->setZValue(1);
    
    m_UpLabel->setZValue(2);
    m_DownLabel->setZValue(3);
}


DuiGridLayout* DcpLabel::layout()
{
    return m_Layout;
}

void DcpLabel::labelButtonClicked()
{
    qDebug() << "labelButtonClicked";
    emit clicked("labelButtonClicked");
}


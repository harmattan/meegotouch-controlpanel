#include "button2.h"

#include <QtDebug>

#include <duigridlayout.h>

CButton2::CButton2(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight)
{
    m_Layout = new DuiGridLayout();

    m_Layout->setColumnMinimumWidth ( 0, smallX );
    m_Layout->setColumnMinimumWidth ( 1, smallWidth );
    m_Layout->setColumnMinimumWidth ( 2, bigWidth - smallX - smallWidth );


    m_Layout->setRowMinimumHeight ( 0, smallY );
    m_Layout->setRowMinimumHeight ( 1, smallHeight );
    m_Layout->setRowMinimumHeight ( 2, bigHeight - smallY - smallHeight );


    m_SmallButton = new DuiButton(smallLabel);
    m_BigButton = new DuiButton(bigLabel);


    m_BigButton->setMinimumWidth(bigWidth);
    m_SmallButton->setMinimumWidth(smallWidth);

    m_BigButton->setMaximumWidth(bigWidth);
    m_SmallButton->setMaximumWidth(smallWidth);


    m_BigButton->setMinimumHeight(bigHeight);
    m_SmallButton->setMinimumHeight(smallHeight);

    m_BigButton->setMaximumHeight(bigHeight);
    m_SmallButton->setMaximumHeight(smallHeight);

    m_Layout->addItem(m_SmallButton, 1, 1, Qt::AlignCenter);
    m_Layout->addItem(m_BigButton, 0, 0, 3, 3, Qt::AlignCenter);

    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));
    connect(m_SmallButton, SIGNAL(clicked()), this, SLOT(smallClicked()));

}

DuiGridLayout* CButton2::layout() {
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

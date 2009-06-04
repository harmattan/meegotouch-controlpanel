#include "dcpbutton2.h"
#include <DuiLabel>
#include <DuiLayout>
#include <DuiGridLayoutPolicy>

// main constructor
DcpButton2::DcpButton2(DuiWidget* parent)
    : DuiButton(parent), m_Label1(0), m_Label2(0)
{
    setObjectName("DcpButton");
    this->setLayout(createLayout());
}

// protected constructor which avoids creating the layout
DcpButton2::DcpButton2(DuiWidget* parent, bool)
    : DuiButton(parent), m_Label1(0), m_Label2(0)
{
    setObjectName("DcpButton");
}

DuiLayout* DcpButton2::createLayout()
{
    // triangle
    m_Triangle = new DuiButton(this);
    m_Triangle->setObjectName("DcpSeeMoreIndicator");
    m_Triangle->setAcceptedMouseButtons(0);

    // create the labels:
    m_Label1 = new DuiLabel (this);
    m_Label1->setAcceptedMouseButtons(0);
//    m_Label1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    m_Label2 = new DuiLabel (this);
    m_Label2->setAcceptedMouseButtons(0);
    m_Label2->setObjectName("DcpButtonLine2");
//    m_Label2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // create the layout:
    m_TextLayout = new DuiLayout(0);
    m_TextLayout->setAnimator(0);
    m_TextLayoutPolicy1 = new DuiGridLayoutPolicy(m_TextLayout);
    m_TextLayout->setPolicy(m_TextLayoutPolicy1);
    m_TextLayoutPolicy1->addItemAtPosition(m_Triangle,0,0);
    m_TextLayoutPolicy1->addItemAtPosition(m_Label1,0,1);
    m_TextLayoutPolicy1->addItemAtPosition(m_Label2,1,1);

    m_TextLayout->setContentsMargins(9,9,9,9);
    updateLabelSizes();
    return m_TextLayout;
}

void DcpButton2::setText1(const QString& text)
{
    m_Label1->setText(text);
}

void DcpButton2::setText2(const QString& text)
{
    if (text == m_Label2->text()) return;
    m_Label2->setText(text);
    updateLabelSizes();
}

void DcpButton2::updateLabelSizes()
{
    m_TextLayout->removeItem(m_Triangle);
    if (m_Label2->text().isEmpty()) {
        m_Label2->setMaximumHeight(0.001); // this magic is to avoid a layout issue
        m_TextLayoutPolicy1->addItemAtPosition(m_Triangle, 0,0, 2,1,
                                               Qt::AlignCenter);
        m_Label1->setObjectName("DcpButtonMain");
    } else {
        m_Label2->setMaximumSize(QSize());
        m_TextLayoutPolicy1->addItemAtPosition(m_Triangle, 0,0, 1,1,
                                               Qt::AlignCenter);
        m_Label1->setObjectName("DcpButtonLine1");
    }
    m_TextLayout->invalidate();
    m_TextLayout->activate();
}


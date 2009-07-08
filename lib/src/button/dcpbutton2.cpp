#include "dcpbutton2.h"
#include <DuiLabel>
#include <QGraphicsGridLayout>

// main constructor
DcpButton2::DcpButton2(DuiWidget* parent)
    : DuiButton(parent), m_TextLayout(0), m_Label1(0), m_Label2(0),
      m_Triangle(0)
{
    setObjectName("DcpButton");
    this->setLayout(createLayout());
}

// protected constructor which avoids creating the layout
DcpButton2::DcpButton2(DuiWidget* parent, bool)
    : DuiButton(parent), m_TextLayout(0), m_Label1(0), m_Label2(0),
      m_Triangle(0)
{
    setObjectName("DcpButton");
}

QGraphicsLayout* DcpButton2::createLayout()
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
    m_TextLayout = new QGraphicsGridLayout();
    m_TextLayout->setContentsMargins(0,0,0,0);
    m_TextLayout->addItem(m_Triangle,0,0, Qt::AlignCenter);
    m_TextLayout->addItem(m_Label1,0,1);
    m_TextLayout->addItem(m_Label2,1,1);

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
    if (m_Label2->text().isEmpty()) {
        m_Label1->setObjectName("DcpButtonMain");
        if (textLayout()->count() > 2) {
            textLayout()->removeAt(2);
        }
    } else {
        m_Label1->setObjectName("DcpButtonLine1");
        if (textLayout()->count() <= 2) {
            textLayout()->addItem(m_Label2, 1,1);
        }
    }
}

// convenience function
void DcpButton2::setText(const QString& text1, const QString& text2)
{
    setText1(text1);
    setText2(text2);
}

QGraphicsGridLayout* DcpButton2::textLayout()
{
    return m_TextLayout;
}


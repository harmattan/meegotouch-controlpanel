#include "dcpbutton.h"
#include <DuiLabel>
#include <QGraphicsGridLayout>

#define DISABLE_BACKGROUND 1

// main constructor
DcpButton::DcpButton(DuiWidget* parent)
    : DuiButton(parent), m_TextLayout(0), m_Label1(0), m_Label2(0),
      m_Triangle(0)
{
    setObjectName("DcpButton");
    this->setLayout(createLayout());
}

// protected constructor which avoids creating the layout
DcpButton::DcpButton(DuiWidget* parent, bool)
    : DuiButton(parent), m_TextLayout(0), m_Label1(0), m_Label2(0),
      m_Triangle(0)
{
    setObjectName("DcpButton");
}

QGraphicsLayout* DcpButton::createLayout()
{
    // triangle
    m_Triangle = new DuiButton(this);
    m_Triangle->setObjectName("DcpSeeMoreIndicator");
    m_Triangle->setAcceptedMouseButtons(0);

    // create the labels:
    m_Label1 = new DuiLabel (this);
    m_Label1->setAcceptedMouseButtons(0);
//    m_Label1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    m_Label2 = new DuiLabel();
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

void DcpButton::setText1(const QString& text)
{
    m_Label1->setText(text);
}

void DcpButton::setText2(const QString& text)
{
    if (text == m_Label2->text()) return;
    m_Label2->setText(text);
    updateLabelSizes();
}

QString DcpButton::text1() const
{
    return m_Label1->text();
}

QString DcpButton::text2() const
{
    return m_Label2->text();
}

void DcpButton::updateLabelSizes()
{
    if (m_Label2->text().isEmpty()) {
        m_Label1->setObjectName("DcpButtonMain");
        if (textLayout()->count() > 2) {
            textLayout()->removeAt(2);
        }
        m_Label2->hide();
    } else {
        m_Label1->setObjectName("DcpButtonLine1");
        if (textLayout()->count() <= 2) {
            textLayout()->addItem(m_Label2, 1,1);
        }
        m_Label2->show();
    }
}

// convenience function
void DcpButton::setText(const QString& text1, const QString& text2)
{
    setText1(text1);
    setText2(text2);
}

QGraphicsGridLayout* DcpButton::textLayout()
{
    return m_TextLayout;
}

#if DISABLE_BACKGROUND
    void DcpButton::paintWindowFrame (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}
    void DcpButton::paint (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}
#else // DISABLE_BACKGROUND
    void DcpButton::paintWindowFrame (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        DuiButton::paintWindowFrame(painter, option, widget);
    }
    void DcpButton::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        DuiButton::paint(painter, option, widget);
    }
#endif // DISABLE_BACKGROUND


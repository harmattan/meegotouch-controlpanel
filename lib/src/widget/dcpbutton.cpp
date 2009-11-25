#include "dcpbutton.h"
#include <DuiLabel>
#include <QGraphicsGridLayout>
#include <QGraphicsSceneMouseEvent>

// main constructor
DcpButton::DcpButton(DuiWidget* parent)
    : DuiStylableWidget(parent), m_TextLayout(0), m_Label1(0), m_Label2(0)
{
    setMaximumSize(999,999); // TODO remove me, it is only a hack, seems to prevent baddrawable error
    setObjectName("DcpButton");
    this->setLayout(createLayout());
}

// protected constructor which avoids creating the layout
DcpButton::DcpButton(DuiWidget* parent, bool)
    : DuiStylableWidget(parent), m_TextLayout(0), m_Label1(0), m_Label2(0)
{
    setObjectName("DcpButton");
}

QGraphicsLayout* DcpButton::createLayout()
{
    // create the labels:
    m_Label1 = new DuiLabel (this);
    m_Label1->setAcceptedMouseButtons(0);
    m_Label1->setTextElide(true);

    m_Label2 = new DuiLabel();
    m_Label2->setTextElide(true);
    m_Label2->setAcceptedMouseButtons(0);
    m_Label2->setObjectName("DcpButtonLine2");

    // create the layout:
    m_TextLayout = new QGraphicsGridLayout();
    m_TextLayout->setContentsMargins(0,0,0,0);
    m_TextLayout->addItem(m_Label1,0,0);
    m_TextLayout->addItem(m_Label2,1,0);

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
    qDebug("XXX c: %d", textLayout()->count());
    if (m_Label2->text().isEmpty()) {
        m_Label1->setObjectName("DcpButtonMain");
        if (textLayout()->count() > 1) {
            textLayout()->removeAt(1);
        }
        m_Label2->hide();
    } else {
        m_Label1->setObjectName("DcpButtonLine1");
        if (textLayout()->count() <= 1) {
            textLayout()->addItem(m_Label2, 1,0);
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

void DcpButton::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event);
    // this function is only for becoming the mouse grabber item
    // so that release event is working
    //
    // visual feedback for user can be implemented here
}

void DcpButton::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    if (QRectF(QPointF(),size()).contains(event->pos())) {
        emit clicked();
    }
}


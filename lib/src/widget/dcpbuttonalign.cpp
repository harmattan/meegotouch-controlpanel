#include "dcpbuttonalign.h"

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>

DcpButtonAlign::DcpButtonAlign(DuiWidget* parent, bool)
    : DcpButton(parent, false),
      m_AlignedWidget(0), m_Alignment(Qt::AlignRight)
{
}

QGraphicsLayout* DcpButtonAlign::createLayout()
{
    Q_ASSERT(alignedWidget());

    // text
    DcpButton::createLayout();
    qreal left, right, top, bottom;
    textLayout()->getContentsMargins(&left, &top, &right, &bottom);
    textLayout()->setContentsMargins(0,0,right,0);

    // putting the widget next to the text
    m_AlignLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    m_AlignLayout->setContentsMargins(left,top,right,bottom);

    putupWidgets();
    return m_AlignLayout;
}

void DcpButtonAlign::setAlignment(Qt::Alignment align)
{
    if (m_Alignment != align)
    m_Alignment = align;

    if (m_AlignLayout != NULL) {
        /* if the layout has already been created, remove and readd the items
         * in the correct order */
        m_AlignLayout->removeAt (0);
        m_AlignLayout->removeAt (1);
        putupWidgets();
    }
}

void DcpButtonAlign::putupWidgets()
{
    Q_ASSERT(alignedWidget());
    Q_ASSERT(textLayout());

    switch (m_Alignment) {
        case Qt::AlignRight:
            m_AlignLayout->addItem(textLayout());
            m_AlignLayout->addItem(alignedWidget());
            break;
        case Qt::AlignLeft:
            m_AlignLayout->addItem(alignedWidget());
            m_AlignLayout->addItem(textLayout());
            break;
        default:
            qFatal("DcpButtonAlign unsupported alignment");
            break;
    }
    m_AlignLayout->setAlignment(alignedWidget(), Qt::AlignVCenter);
}

DuiWidget* DcpButtonAlign::alignedWidget()
{
    return m_AlignedWidget;
}

void DcpButtonAlign::setAlignedWidget(DuiWidget* widget)
{
    Q_ASSERT(!m_AlignedWidget); // only lets to set it up once currently (no widget changing)
    m_AlignedWidget = widget;
}



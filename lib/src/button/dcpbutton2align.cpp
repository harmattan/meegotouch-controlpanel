#include "dcpbutton2align.h"

#include <DuiLayout>
#include <DuiLinearLayoutPolicy>

DcpButton2Align::DcpButton2Align(DuiWidget* parent, bool)
    : DcpButton2(parent, false), m_VertLayout(0),
      m_VertLayoutPolicy(0), m_AlignedWidget(0), m_Alignment(Qt::AlignRight)

{
}

DuiLayout* DcpButton2Align::createLayout()
{
    if (!alignedWidget()){
        qFatal (Q_FUNC_INFO);
    }

    // text
    DuiLayout* textLayout = DcpButton2::createLayout();
    qreal left, right, top, bottom;
    textLayout->getContentsMargins(&left, &top, &right, &bottom);
    textLayout->setContentsMargins(0,0,right,0);

    // putting the widget next to the text
    m_VertLayout = new DuiLayout(0);
    m_VertLayout->setAnimator(0);
    m_VertLayout->setContentsMargins(left,top,right,bottom);
    m_VertLayoutPolicy = new DuiLinearLayoutPolicy(m_VertLayout,
            Qt::Horizontal);

    putupWidgets();
    return m_VertLayout;
}

void DcpButton2Align::setAlignment(Qt::Alignment align)
{
    if (m_Alignment != align)
    m_Alignment = align;

    if (m_VertLayout != NULL) {
        /* if the layout has already been created, remove and readd the items
         * in the correct order */
        m_VertLayout->removeItem (textLayout());
        m_VertLayout->removeItem (alignedWidget());
        putupWidgets();
    }
}

void DcpButton2Align::putupWidgets()
{
    Q_ASSERT(alignedWidget());
    Q_ASSERT(textLayout());

    switch (m_Alignment) {
        case Qt::AlignRight:
            m_VertLayoutPolicy->addItemAtPosition(textLayout(), 0);
            m_VertLayoutPolicy->addItemAtPosition(alignedWidget(), 1);
            break;
        case Qt::AlignLeft:
            m_VertLayoutPolicy->addItemAtPosition(alignedWidget(), 0);
            m_VertLayoutPolicy->addItemAtPosition(textLayout(), 1);
            break;
        default:
            qFatal("DcpButton2Align unsupported alignment");
            break;
    }
}

DuiWidget* DcpButton2Align::alignedWidget()
{
    return m_AlignedWidget;
}

void DcpButton2Align::setAlignedWidget(DuiWidget* widget)
{
    Q_ASSERT(!m_AlignedWidget); // only lets to set it up once currently (no widget changing)
    m_AlignedWidget = widget;
}


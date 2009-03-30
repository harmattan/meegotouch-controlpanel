#include "dcpbackgroundlineview.h"
#include <duitheme.h>
#include <duiwidgetcontroller.h>

DUI_STYLABLE_CPP(DcpBackgroundLineView, DuiWidgetView);

#include <duistyledescription.h>
#include <QtDebug>

enum {
    LineWidthAttribute,
    LineColorAttribute,
    LineSkipAttribute,

    NormalBackgroundNameAttrib,
    BackgroundBoxEdgeAttrib
};


DcpBackgroundLineView::DcpBackgroundLineView(DuiWidgetController* controller):
        DuiWidgetView(controller), m_LinePosition(-1), m_Background(NULL),
        m_Controller(controller)
{
}

DcpBackgroundLineView::~DcpBackgroundLineView()
{
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
    }
}

QSizeF DcpBackgroundLineView::sizeHint(Qt::SizeHint which,
                                     const QSizeF &constraint) const
{
    return m_Controller->sizeHint(which, constraint);
}

void DcpBackgroundLineView::drawBackground(QPainter* painter,
                                const QStyleOptionGraphicsItem* option) const
{
	Q_UNUSED(option);
    //DuiWidgetView::drawBackground(painter, option);

    if (m_Background) {
        painter->drawPixmap(0, 0, *m_Background);
    }

    if (m_LinePosition<0) return;

    QColor lineColor = styleAttribute<QColor>(LineColorAttribute);
    int lineWidth = styleAttribute<int>(LineWidthAttribute);
    int lineSkip = styleAttribute<int>(LineSkipAttribute);

    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(lineWidth);
    painter->setPen(pen);
    painter->drawLine(lineSkip, m_LinePosition,
                      size().width()-2*lineSkip, m_LinePosition);
}

void DcpBackgroundLineView::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    DuiWidgetView::resizeEvent(event);
    updateGraphics();
    update();
}

void DcpBackgroundLineView::styleUpdated()
{
    updateGraphics();
    update();
}

void DcpBackgroundLineView::setLinePosition(int pos)
{
    m_LinePosition = pos;
}

void DcpBackgroundLineView::updateGraphics()
{
    if (m_Background) {
        DuiTheme::releasePixmap(m_Background);
        m_Background = NULL;
    }

    QString pixmapId = styleAttribute<QString>(NormalBackgroundNameAttrib);
    int border = styleAttribute<int>(BackgroundBoxEdgeAttrib);
    QSize size = this->size().toSize();
    if (!pixmapId.isEmpty() && border > 0 && !size.isEmpty()) {
        m_Background = DuiTheme::boxedPixmap(pixmapId,size,
                                         border, border, border, border);
    }
}


void DcpBackgroundLineView::registerStyleAttributes(
        DuiStyleDescription& description)
{
    description.addAttribute(LineWidthAttribute, "lineWidth");
    description.addAttribute(LineColorAttribute, "lineColor");
    description.addAttribute(LineSkipAttribute,  "lineSkip");
    description.addAttribute(NormalBackgroundNameAttrib, "normalBackgroundName");
    description.addAttribute(BackgroundBoxEdgeAttrib, "backgroundBoxEdge");
}


DUI_REGISTER_VIEW("DcpBackgroundLineView", DcpBackgroundLineView,
                  DuiWidgetController);


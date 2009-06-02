
#include "dcpbuttonview.h"
//DUI_STYLABLE_CPP(DcpButtonView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

const QColor LINECOLOR = QColor(64, 64, 64);


/* 
Margins:

marginLeft
V
+----------------+    < marginTop
|Text1           |
+----------------+    < marginMiddle
|           Text2|
+----------------+    < marginBotton
                 A
                marginRight
*/

DcpButtonView::DcpButtonView(DcpButton *button) :
    DuiWidgetView(button),
//    controller(*button),
    m_Bkgr(false),
	m_LineBool(true)
{
//    controller.setZValue(1);
}

DcpButtonView::~DcpButtonView()
{
    //if (m_Background) {
    //    DuiTheme::releasePixmap(m_Background);
    //}
}

void DcpButtonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

	initMargins();

    //paintBackground(painter);
	paintLine(painter);
    paintTriangle(painter);
    paintText(painter);

    return;
}

void DcpButtonView::paintBackground(QPainter *painter)
{

    if (m_Bkgr) {
		const QPixmap *bg = DuiTheme::pixmap(style()->background(), style()->backgroundSize());

        if (bg != 0)
            painter->drawPixmap(0, 0, *bg);
    }

}

void DcpButtonView::paintLine(QPainter *painter)
{
	if (m_LineBool) {
		painter->setPen(LINECOLOR);
		//painter->drawLine(0, height() + 15, width() , height());
		painter->drawLine(0, size().height(), size().width() , size().height());
	}
}

void DcpButtonView::paintTriangle(QPainter *painter)
{

	const QPixmap *triangle = DuiTheme::pixmap(style()->triangleBackground(), style()->triangleBackgroundSize());

	if (m_Text1.size() && m_Text2.size()) {
		QPointF trianglePoint(style()->trianglePos().x() + m_MarginLeft, style()->trianglePos().y() + m_MarginTop);
		painter->drawPixmap(trianglePoint, *triangle);
	} else {
		QPointF trianglePoint(style()->trianglePos().x() + m_MarginLeft,
								height()/2 - triangle->height()/2); //not use margins
		painter->drawPixmap(trianglePoint, *triangle);
	}

}

void DcpButtonView::paintText(QPainter *painter)
{

	if (m_Text1.size() && m_Text2.size())
		paintText2(painter);
	else
		paintText1(painter);

	return;
}

void DcpButtonView::paintText2(QPainter *painter)
{
	int fieldHeight = (style()->backgroundSize().height() - m_MarginTop - m_MarginBottom - m_MarginMiddle) / 2;
	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();
	int fieldWidth = style()->backgroundSize().width() - m_MarginLeft - m_MarginRight - triangleWidth;

	QRectF text1Rect(	style()->textPos1().x() + m_MarginLeft + triangleWidth,
						style()->textPos1().y() + m_MarginTop,
						fieldWidth,
						fieldHeight);

	// Draw text
	painter->setFont(style()->font1());
	painter->setPen(style()->textColor1());
	painter->drawText(text1Rect, style()->textAlign1(), m_Text1);


	QRectF text2Rect(style()->textPos2().x() + m_MarginLeft + triangleWidth,
						style()->textPos2().y() + m_MarginTop,
						fieldWidth,
						fieldHeight);

	painter->setFont(style()->font2());
	painter->setPen(style()->textColor2());
	painter->drawText(text2Rect, style()->textAlign2(), m_Text2);
}


void DcpButtonView::paintText1(QPainter *painter)
{
	int fieldHeight = (style()->backgroundSize().height() - m_MarginTop - m_MarginBottom);
	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();
	int fieldWidth = style()->backgroundSize().width() - m_MarginLeft - m_MarginRight - triangleWidth;

	
	QRectF text1Rect(	style()->textPos1().x() + m_MarginLeft + triangleWidth,
						0,
						fieldWidth,
						height());

	// Draw text
	painter->setFont(style()->font0());
	painter->setPen(style()->textColor0());
	painter->drawText(text1Rect, style()->textAlign0() | Qt::AlignVCenter, m_Text1);
}

void DcpButtonView::initMargins()
{
	m_MarginLeft = style()->fieldMarginLeft();
    m_MarginRight = style()->fieldMarginRight();
    m_MarginTop = style()->fieldMarginTop();
    m_MarginBottom = style()->fieldMarginBottom();
	m_MarginMiddle = style()->fieldMarginMiddle();
}


#if 0
QRectF DcpButtonView::boundingRect() const
{
	return QRectF(QPointF(), style()->backgroundSize());
}
#endif


void DcpButtonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

}

void DcpButtonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
	emit clicked();
}

int DcpButtonView::width()
{
	return style()->backgroundSize().width();
}

int DcpButtonView::height()
{
	return style()->backgroundSize().height();
}

DUI_REGISTER_VIEW("DcpButtonView", DcpButtonView, DcpButton)

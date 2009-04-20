
#include "dcpbuttonview.h"
DUI_STYLABLE_CPP(DcpButtonView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"


DcpButtonView::DcpButtonView(DcpButton &button) :
    DuiWidgetView(&button),
    controller(button)
{
		controller.setZValue(1);
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

		paintBackground(painter);
		paintTriangle(painter);
		paintText(painter);

		return;
}

void DcpButtonView::paintBackground(QPainter *painter)
{
 		const QPixmap *bg = DuiTheme::pixmap(	styleAttribute<const QString>(BackgroundAttribute),
																					styleAttribute<const QSize>(BackgroundSizeAttribute));

		if (bg != NULL)
        painter->drawPixmap(0, 0, *bg);
}

void DcpButtonView::paintTriangle(QPainter *painter)
{
  	int marginLeft = styleAttribute<int>(MarginLeftAttribute);
    int marginTop = styleAttribute<int>(MarginTopAttribute);

		const QPixmap *triangle = DuiTheme::pixmap(	styleAttribute<const QString>(TriangleBackgroundAttribute),
																								styleAttribute<const QSize>(TriangleBackgroundSizeAttribute));

    if (triangle != NULL) {

				QPointF trianglePoint(	styleAttribute<QPointF>(TrianglePosAttribute).x() + marginLeft,
																styleAttribute<QPointF>(TrianglePosAttribute).y() + marginTop		);

        painter->drawPixmap(trianglePoint, *triangle);
		}

}

void DcpButtonView::paintText(QPainter *painter)
{
  	int marginLeft = styleAttribute<int>(MarginLeftAttribute);
    int marginRight = styleAttribute<int>(MarginRightAttribute);
    int marginTop = styleAttribute<int>(MarginTopAttribute);
    int marginBottom = styleAttribute<int>(MarginBottomAttribute);

		QRectF text1Rect(	styleAttribute<QPointF>(TextPos1Attribute).x() + marginLeft,
											styleAttribute<QPointF>(TextPos1Attribute).y() + marginTop,
											width() - marginLeft - marginRight,
											height() - marginTop - marginBottom);

    // Draw text
    painter->setFont(styleAttribute<QFont>(Font1Attribute));
    painter->setPen(styleAttribute<QColor>(TextColor1Attribute));
    painter->drawText(text1Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign1Attribute)),
											m_Text1);

}

QRectF DcpButtonView::boundingRect() const
{
		return QRectF(QPointF(), styleAttribute<const QSize>(BackgroundSizeAttribute));
}

void DcpButtonView::registerStyleAttributes(DuiStyleDescription &description)
{

  	description.addAttribute(MarginLeftAttribute, "marginLeft");
    description.addAttribute(MarginRightAttribute, "marginRight");
    description.addAttribute(MarginTopAttribute, "marginTop");
    description.addAttribute(MarginBottomAttribute, "marginBottom");
//		description.addAttribute(MarginMiddleAttribute, "marginMiddle");


    description.addAttribute(BackgroundAttribute, "backgroundImage");
		description.addAttribute(BackgroundSizeAttribute, "backgroundSize");

    description.addAttribute(Font1Attribute, "font1");
//		description.addAttribute(Font2Attribute, "font2");

    description.addAttribute(TextColor1Attribute, "textColor1");
//		description.addAttribute(TextColor2Attribute, "textColor2");

		description.addAttribute(TextSize1Attribute, "textSize1");
//		description.addAttribute(TextSize2Attribute, "textSize2");

    description.addAttribute(TextPos1Attribute, "textPos1");
//		description.addAttribute(TextPos2Attribute, "textPos2");

		description.addAttribute(TextAlign1Attribute, "textAlign1");
//		description.addAttribute(TextAlign2Attribute, "textAlign2");
		

		description.addAttribute(TriangleBackgroundAttribute, "triangleBackground");
		description.addAttribute(TriangleBackgroundSizeAttribute, "triangleBackgroundSize");
		description.addAttribute(TrianglePosAttribute, "trianglePos");

}

void DcpButtonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

}

void DcpButtonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
		emit clicked();
}

int DcpButtonView::stringToAlign(const QString& align)
{
	
		if (align == "Left")
				return Qt::AlignLeft;

		if (align == "Right")
			return Qt::AlignRight;

		if (align == "Center")
				return Qt::AlignHCenter;

		return 0;
}

int DcpButtonView::width()
{
		return styleAttribute<const QSize>(BackgroundSizeAttribute).width();
}

int DcpButtonView::height()
{
		return styleAttribute<const QSize>(BackgroundSizeAttribute).height();
}

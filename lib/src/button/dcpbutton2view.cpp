
#include "dcpbutton2view.h"
//DUI_STYLABLE_CPP(DcpButton2View, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"


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


DcpButton2View::DcpButton2View(DcpButton *button) :
    DcpButtonView(button)
{
}

DcpButton2View::~DcpButton2View()
{
}

void DcpButton2View::paintText(QPainter *painter)
{

  	int marginLeft = style()->fieldMarginLeft();
    int marginRight = style()->fieldMarginRight();
    int marginTop = style()->fieldMarginTop();
    int marginBottom = style()->fieldMarginBottom();
	int marginMiddle = style()->fieldMarginMiddle();

	//int marginTriangle = styleAttribute<int>(MarginTriangleAttribute);

	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();


	int fieldWidth = style()->backgroundSize().width() - marginLeft - marginRight - triangleWidth;
	int fieldHeight = (style()->backgroundSize().height() - marginTop - marginBottom - marginMiddle) / 2;

	QRectF text1Rect(	style()->textPos1().x() + marginLeft + triangleWidth,
						style()->textPos1().y() + marginTop,
						fieldWidth,
						fieldHeight);

/*
		QRectF text1Rect(	styleAttribute<QPointF>(TextPos1Attribute).x() + marginLeft,
											styleAttribute<QPointF>(TextPos1Attribute).y() + marginTop,
											styleAttribute<QSize>(TextSize1Attribute).width() - marginLeft - marginRight,
											styleAttribute<QSize>(TextSize1Attribute).height()); // ??? -marginTop - marginBottom
*/

    // Draw text
    painter->setFont(style()->font1());
    painter->setPen(style()->textColor1());
    painter->drawText(text1Rect, style()->textAlign1(), m_Text1);


	QRectF text2Rect(style()->textPos2().x() + marginLeft + triangleWidth,
					 style()->textPos2().y() + marginTop,
					 fieldWidth,
					 fieldHeight);

/*
		QRectF text2Rect(	styleAttribute<QPointF>(TextPos2Attribute).x() + marginLeft,
											styleAttribute<QPointF>(TextPos2Attribute).y() + marginTop,
											styleAttribute<QSize>(TextSize2Attribute).width() - marginLeft - marginRight,
											styleAttribute<QSize>(TextSize2Attribute).height()); // ??? -marginTop - marginBottom
*/

    painter->setFont(style()->font2());
    painter->setPen(style()->textColor2());
    painter->drawText(text2Rect, style()->textAlign2(), m_Text2);

	return;
}

QRectF DcpButton2View::boundingRect() const
{
	return QRectF(0, 0, size().width(), size().height());
}

/*
void DcpButton2View::registerStyleAttributes(DuiStyleDescription &description)
{

  	description.addAttribute(MarginLeftAttribute, "marginLeft");
    description.addAttribute(MarginRightAttribute, "marginRight");
    description.addAttribute(MarginTopAttribute, "marginTop");
    description.addAttribute(MarginBottomAttribute, "marginBottom");
	description.addAttribute(MarginMiddleAttribute, "marginMiddle");

    description.addAttribute(BackgroundAttribute, "backgroundImage");
	description.addAttribute(BackgroundSizeAttribute, "backgroundSize");

    description.addAttribute(Font1Attribute, "font1");
	description.addAttribute(Font2Attribute, "font2");

    description.addAttribute(TextColor1Attribute, "textColor1");
	description.addAttribute(TextColor2Attribute, "textColor2");

	description.addAttribute(TextSize1Attribute, "textSize1");
	description.addAttribute(TextSize2Attribute, "textSize2");

    description.addAttribute(TextPos1Attribute, "textPos1");
	description.addAttribute(TextPos2Attribute, "textPos2");

	description.addAttribute(TextAlign1Attribute, "textAlign1");
	description.addAttribute(TextAlign2Attribute, "textAlign2");
		
	description.addAttribute(TriangleBackgroundAttribute, "triangleBackground");
	description.addAttribute(TriangleBackgroundSizeAttribute, "triangleBackgroundSize");
	description.addAttribute(TrianglePosAttribute, "trianglePos");

	description.addAttribute(MarginTriangleAttribute, "marginTriangle");
}*/

DUI_REGISTER_VIEW("DcpButton2View", DcpButton2View, DcpButton)

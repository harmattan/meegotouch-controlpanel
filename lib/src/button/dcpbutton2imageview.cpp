
#include "dcpbutton2imageview.h"

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

//dummy
const QString imageFile    = "/usr/share/themes/dui/duicontrolpanel/images/starfield.png";

/* 
LEFT
Margins:

              marginLeft                  imageSpacer 
                V                            V
                +----------------+-----------+    < marginTop
                |Text1           |           |
marginMiddle >  +----------------+   Image   +
                |           Text2|           |
                +----------------+ ----------+   < marginBotton
                                 A
                            marginRight
*/

/* 
RIGHT
Margins:

              imageSpacer     marginLeft
                V           V
                +-----------+----------------+    < marginTop
                |           |Text1           |
marginMiddle >  +   Image   +----------------+
                |           |           Text2|
                +-----------+ ---------------+    < marginBotton
                                             A
                                        marginRight
*/


DcpButton2ImageView::DcpButton2ImageView(DcpButton *button) :
    DcpButtonView(button)
{

	//QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));

	m_Image = new QPixmap(QPixmap(imageFile).scaled(62, 62)); //dummy
}

DcpButton2ImageView::~DcpButton2ImageView()
{
	delete m_Image;
}

void DcpButton2ImageView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

	initMargins();

	paintBackground(painter);
	paintLine(painter);

	if ( m_Alignment==Qt::AlignLeft ) {
		paintTriangle(painter);

		if (m_Text1.size() && m_Text2.size())
			paintText2(painter);
		else
			paintText1(painter);

		paintImageLeft(painter);

	} else {
  //  if ( m_Alignment==Qt::AlignRight ) {
		paintTriangleRight(painter);
		paintTextRight(painter);
		paintImageRight(painter);

	}

}

void DcpButton2ImageView::paintTextLeft(QPainter *painter, bool textBool)
{
	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();

	int fieldWidth = style()->backgroundSize().width() -
					 m_MarginLeft -
					 m_MarginRight -
					 triangleWidth -
					 style()->imageSize().width() -
					 style()->marginSpacer() ;

	int fieldHeight = (style()->backgroundSize().height() - m_MarginTop - m_MarginBottom - m_MarginMiddle) / 2;

	QRectF text1Rect(style()->textPos1().x() + m_MarginLeft + triangleWidth,
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

	if (textBool) {
		painter->setPen(style()->textColor2());
		painter->drawText(text2Rect, style()->textAlign2(), m_Text2);
	}

	return;
}

void DcpButton2ImageView::paintImageLeft(QPainter *painter)
{

	int marginSpacer = style()->marginSpacer();

    if (m_Image) {
		QPointF imagePoint( size().width() - m_Image->width() + 1 - marginSpacer,
						   (size().height() - m_Image->height()) / 2				);

        painter->drawPixmap(imagePoint, *m_Image);
	}

	const QPixmap *border = DuiTheme::pixmap(style()->backgroundBorder(), QSize(m_Image->width() + 2, m_Image->height() + 2)	);

    if (border) {
		QPointF imagePoint( size().width() - border->width() + (border->width() - m_Image->width()) - marginSpacer,
			 		   (size().height() - border->height()) / 2					);

        painter->drawPixmap(imagePoint, *border);
	}

}

void DcpButton2ImageView::paintTriangleRight(QPainter *painter)
{
	const QPixmap *triangle = DuiTheme::pixmap(	style()->triangleBackground(), style()->triangleBackgroundSize());

    if (triangle) {
		QPointF trianglePoint(style()->trianglePos().x() + style()->marginSpacer() + style()->imageSize().width() + m_MarginLeft,
							  style()->trianglePos().y() + m_MarginTop	);

        painter->drawPixmap(trianglePoint, *triangle);
	}
}

void DcpButton2ImageView::paintTextRight(QPainter *painter, bool textBool)
{
	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();

	int fieldWidth = style()->backgroundSize().width() -
					 m_MarginLeft -
					 m_MarginRight -
					 triangleWidth -
					 style()->imageSize().width() -
					 style()->marginSpacer();

	int fieldHeight = (style()->backgroundSize().height() - m_MarginTop - m_MarginBottom - m_MarginMiddle) / 2;

	QRectF text1Rect(style()->textPos1().x() + style()->marginSpacer() + style()->imageSize().width() + m_MarginLeft + triangleWidth,
					 style()->textPos1().y() + m_MarginTop,
					 fieldWidth,
					 fieldHeight);

    // Draw text
    painter->setFont(style()->font1());
	painter->setPen(style()->textColor1());
	
    painter->drawText(text1Rect, style()->textAlign1(), m_Text1);


	QRectF text2Rect(style()->textPos2().x() + style()->marginSpacer() + style()->imageSize().width() + m_MarginLeft + triangleWidth,
					 style()->textPos2().y() + m_MarginTop,
					 fieldWidth,
					 fieldHeight);

    painter->setFont(style()->font2());

	if (textBool) {
    	painter->setPen(style()->textColor2());
		painter->drawText(text2Rect, style()->textAlign2(), m_Text2);
	}

	return;
}

void DcpButton2ImageView::paintImageRight(QPainter *painter)
{
    int marginSpacer = style()->marginSpacer();

    if (m_Image != 0) {

        QPointF imagePoint( marginSpacer,
                           (height() - m_Image->height()) / 2);

        painter->drawPixmap(imagePoint, *m_Image);
	}

	const QPixmap *border = DuiTheme::pixmap(style()->backgroundBorder(), QSize(m_Image->width() + 2, m_Image->height() + 2) );

    if (border != 0) {
		QPointF imagePoint(marginSpacer + (border->width() - m_Image->width()), (height() - border->height()) / 2);
        painter->drawPixmap(imagePoint, *border);
	}
}

DUI_REGISTER_VIEW("DcpButton2ImageView", DcpButton2ImageView, DcpButton)

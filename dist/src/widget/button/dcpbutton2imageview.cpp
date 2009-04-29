
#include "dcpbutton2imageview.h"
DUI_STYLABLE_CPP(DcpButton2ImageView, DuiWidgetView)

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


DcpButton2ImageView::DcpButton2ImageView(DcpButton &button) :
    DcpButton2View(button)
{

	//QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));

	m_Image = new QPixmap(QPixmap(imageFile).scaled(62, 62)); //dummy
}

DcpButton2ImageView::~DcpButton2ImageView()
{
}

void DcpButton2ImageView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

	paintBackground(painter);

	paintLine(painter);

	if ( m_Alignment==Qt::AlignLeft ) {
		paintTriangle(painter);
		paintTextLeft(painter);
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
	int marginLeft = styleAttribute<int>(MarginLeftAttribute);
	int marginRight = styleAttribute<int>(MarginRightAttribute);
	int marginTop = styleAttribute<int>(MarginTopAttribute);
	int marginBottom = styleAttribute<int>(MarginBottomAttribute);
	int marginMiddle = styleAttribute<int>(MarginMiddleAttribute);

	int triangleWidth = styleAttribute<const QSize>(TriangleBackgroundSizeAttribute).width() + styleAttribute<int>(MarginTriangleAttribute);

	int fieldWidth = styleAttribute<const QSize>(BackgroundSizeAttribute).width() -
												marginLeft -
												marginRight -
												triangleWidth -
												styleAttribute<const QSize>(ImageSizeAttribute).width() -
												styleAttribute<int>(MarginSpacerAttribute) ;

		int fieldHeight = (styleAttribute<const QSize>(BackgroundSizeAttribute).height() - marginTop - marginBottom - marginMiddle) / 2;

		QRectF text1Rect(styleAttribute<QPointF>(TextPos1Attribute).x() + marginLeft + triangleWidth,
												styleAttribute<QPointF>(TextPos1Attribute).y() + marginTop,
												fieldWidth,
												fieldHeight);


    // Draw text
    painter->setFont(styleAttribute<QFont>(Font1Attribute));

	if (textBool)
		painter->setPen(styleAttribute<QColor>(TextColor1Attribute));
	else
		painter->setPen(styleAttribute<QColor>(TextOffColorAttribute));

    painter->drawText(text1Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign1Attribute)),
					  m_Text1);

	QRectF text2Rect(styleAttribute<QPointF>(TextPos2Attribute).x() + marginLeft + triangleWidth,
											styleAttribute<QPointF>(TextPos2Attribute).y() + marginTop,
											fieldWidth,
											fieldHeight);

    painter->setFont(styleAttribute<QFont>(Font2Attribute));

	if (textBool)
		    painter->setPen(styleAttribute<QColor>(TextColor2Attribute));
	else
		painter->setPen(styleAttribute<QColor>(TextOffColorAttribute));

    painter->drawText(text2Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign2Attribute)),
					  m_Text2);

	return;
}

void DcpButton2ImageView::paintImageLeft(QPainter *painter)
{

	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

//		QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));


    if (m_Image != NULL) {

		QPointF imagePoint( width() - m_Image->width() + 1 - marginSpacer,
						   (height() - m_Image->height()) / 2				);

        painter->drawPixmap(imagePoint, *m_Image);
	}

	
	const QPixmap *border = DuiTheme::pixmap(styleAttribute<const QString>(BackgroundBorderAttribute),
											 QSize(m_Image->width() + 2, m_Image->height() + 2)										);

    if (border != NULL) {

		QPointF imagePoint( width() - border->width() + (border->width() - m_Image->width()) - marginSpacer,
			 			   (height() - border->height()) / 2					);

        painter->drawPixmap(imagePoint, *border);
	}

}

void DcpButton2ImageView::paintTriangleRight(QPainter *painter)
{
    int marginLeft = styleAttribute<int>(MarginLeftAttribute);
    int marginTop = styleAttribute<int>(MarginTopAttribute);

	const QPixmap *triangle = DuiTheme::pixmap(	styleAttribute<const QString>(TriangleBackgroundAttribute),
																			  styleAttribute<const QSize>(TriangleBackgroundSizeAttribute));

    if (triangle != NULL) {

		QPointF trianglePoint(styleAttribute<QPointF>(TrianglePosAttribute).x() + styleAttribute<int>(MarginSpacerAttribute) + styleAttribute<const QSize>(ImageSizeAttribute).width() + marginLeft,
							  styleAttribute<QPointF>(TrianglePosAttribute).y() + marginTop		);

        painter->drawPixmap(trianglePoint, *triangle);
	}
}

void DcpButton2ImageView::paintTextRight(QPainter *painter, bool textBool)
{
	int marginLeft = styleAttribute<int>(MarginLeftAttribute);
	int marginRight = styleAttribute<int>(MarginRightAttribute);
	int marginTop = styleAttribute<int>(MarginTopAttribute);
	int marginBottom = styleAttribute<int>(MarginBottomAttribute);
	int marginMiddle = styleAttribute<int>(MarginMiddleAttribute);

	int triangleWidth = styleAttribute<const QSize>(TriangleBackgroundSizeAttribute).width() + styleAttribute<int>(MarginTriangleAttribute);


	int fieldWidth = styleAttribute<const QSize>(BackgroundSizeAttribute).width() -
												 marginLeft -
												 marginRight -
												 triangleWidth -
												 styleAttribute<const QSize>(ImageSizeAttribute).width() -
												 styleAttribute<int>(MarginSpacerAttribute);

	int fieldHeight = (styleAttribute<const QSize>(BackgroundSizeAttribute).height() - marginTop - marginBottom - marginMiddle) / 2;

	QRectF text1Rect(	styleAttribute<QPointF>(TextPos1Attribute).x() + styleAttribute<int>(MarginSpacerAttribute) + styleAttribute<const QSize>(ImageSizeAttribute).width() + marginLeft + triangleWidth,
											styleAttribute<QPointF>(TextPos1Attribute).y() + marginTop,
											fieldWidth,
											fieldHeight);


    // Draw text
    painter->setFont(styleAttribute<QFont>(Font1Attribute));

	if (textBool)
		painter->setPen(styleAttribute<QColor>(TextColor1Attribute));
	else
		painter->setPen(styleAttribute<QColor>(TextOffColorAttribute));

    painter->drawText(text1Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign1Attribute)),
					  m_Text1);


	QRectF text2Rect(styleAttribute<QPointF>(TextPos2Attribute).x() + styleAttribute<int>(MarginSpacerAttribute) + styleAttribute<const QSize>(ImageSizeAttribute).width() + marginLeft + triangleWidth,
											styleAttribute<QPointF>(TextPos2Attribute).y() + marginTop,
											fieldWidth,
											fieldHeight);

    painter->setFont(styleAttribute<QFont>(Font2Attribute));

	if (textBool)
    	painter->setPen(styleAttribute<QColor>(TextColor2Attribute));
	else
		painter->setPen(styleAttribute<QColor>(TextOffColorAttribute));

    painter->drawText(text2Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign2Attribute)),
					  m_Text2);

		return;
}

void DcpButton2ImageView::paintImageRight(QPainter *painter)
{
    int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

    if (m_Image != NULL) {

        QPointF imagePoint( marginSpacer,
                           (height() - m_Image->height()) / 2);

        painter->drawPixmap(imagePoint, *m_Image);
	}

		
	const QPixmap *border = DuiTheme::pixmap(styleAttribute<const QString>(BackgroundBorderAttribute),
											 QSize(m_Image->width() + 2, m_Image->height() + 2) );

    if (border != NULL) {

		QPointF imagePoint(marginSpacer + (border->width() - m_Image->width()),
			 			   (height() - border->height()) / 2);

        painter->drawPixmap(imagePoint, *border);
	}
}

void DcpButton2ImageView::registerStyleAttributes(DuiStyleDescription &description)
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
	description.addAttribute(TextOffColorAttribute, "textOffColor");

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

	description.addAttribute(ImageNameAttribute, "imageName");
	description.addAttribute(ImageSizeAttribute, "imageSize");

	description.addAttribute(MarginSpacerAttribute, "marginSpacer");

	description.addAttribute(BackgroundBorderAttribute, "backgroundBorder");
}


#include "dcpbutton2imageview.h"
DUI_STYLABLE_CPP(DcpButton2ImageView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

/* 
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

DcpButton2ImageView::DcpButton2ImageView(DcpButton &button) :
    DcpButton2View(button)
{
}

DcpButton2ImageView::~DcpButton2ImageView()
{
}

void DcpButton2ImageView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

		paintBackground(painter);
		paintTriangle(painter);
		paintTextLeft(painter);
		paintImageLeft(painter);

		return;
}

void DcpButton2ImageView::paintTextLeft(QPainter *painter)
{
  	int marginLeft = styleAttribute<int>(MarginLeftAttribute);
    int marginRight = styleAttribute<int>(MarginRightAttribute);
    int marginTop = styleAttribute<int>(MarginTopAttribute);
    int marginBottom = styleAttribute<int>(MarginBottomAttribute);
		int marginMiddle = styleAttribute<int>(MarginMiddleAttribute);


		int fieldWidth = 	styleAttribute<const QSize>(BackgroundSizeAttribute).width() -
											marginLeft -
											marginRight -
											styleAttribute<const QSize>(ImageSizeAttribute).width() -
											styleAttribute<int>(ImageSpacerAttribute) ;

		int fieldHeight = (styleAttribute<const QSize>(BackgroundSizeAttribute).height() - marginTop - marginBottom - marginMiddle) / 2;

		QRectF text1Rect(	styleAttribute<QPointF>(TextPos1Attribute).x() + marginLeft,
											styleAttribute<QPointF>(TextPos1Attribute).y() + marginTop,
											fieldWidth,
											fieldHeight);


    // Draw text
    painter->setFont(styleAttribute<QFont>(Font1Attribute));
    painter->setPen(styleAttribute<QColor>(TextColor1Attribute));
    painter->drawText(text1Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign1Attribute)),
											m_Text1);


		QRectF text2Rect(	styleAttribute<QPointF>(TextPos2Attribute).x() + marginLeft,
											styleAttribute<QPointF>(TextPos2Attribute).y() + marginTop,
											fieldWidth,
											fieldHeight);

    painter->setFont(styleAttribute<QFont>(Font2Attribute));
    painter->setPen(styleAttribute<QColor>(TextColor2Attribute));
    painter->drawText(text2Rect,
                      stringToAlign(styleAttribute<QString>(TextAlign2Attribute)),
											m_Text2);

		return;
}

void DcpButton2ImageView::paintImageLeft(QPainter *painter)
{

  	int marginSpacer = styleAttribute<int>(ImageSpacerAttribute);

		QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));


    if (image != NULL) {

				QPointF imagePoint( width() - image->width() - marginSpacer,
										 			 (height() - image->height()) / 2					);

        painter->drawPixmap(imagePoint, *image);
		}

		
		const QPixmap *border = DuiTheme::pixmap(	styleAttribute<const QString>(BackgroundBorderAttribute),
																							QSize(image->width(), image->height())										);

    if (border != NULL) {

				QPointF imagePoint( width() - border->width() - marginSpacer,
										 			 (height() - border->height()) / 2					);

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

		description.addAttribute(TextSize1Attribute, "textSize1");
		description.addAttribute(TextSize2Attribute, "textSize2");

    description.addAttribute(TextPos1Attribute, "textPos1");
		description.addAttribute(TextPos2Attribute, "textPos2");

		description.addAttribute(TextAlign1Attribute, "textAlign1");
		description.addAttribute(TextAlign2Attribute, "textAlign2");
		
		description.addAttribute(TriangleBackgroundAttribute, "triangleBackground");
		description.addAttribute(TriangleBackgroundSizeAttribute, "triangleBackgroundSize");
		description.addAttribute(TrianglePosAttribute, "trianglePos");

		description.addAttribute(ImageNameAttribute, "imageName");
		description.addAttribute(ImageSizeAttribute, "imageSize");
		description.addAttribute(ImageSpacerAttribute, "imageSpacer");

		description.addAttribute(BackgroundBorderAttribute, "backgroundBorder");
}

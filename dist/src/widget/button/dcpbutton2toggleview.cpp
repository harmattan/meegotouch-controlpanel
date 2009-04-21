
#include "dcpbutton2toggleview.h"
DUI_STYLABLE_CPP(DcpButton2ToggleView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

DcpButton2ToggleView::DcpButton2ToggleView(DcpButton &button) :
    DcpButton2ImageView(button)
{
}

DcpButton2ToggleView::~DcpButton2ToggleView()
{
}

void DcpButton2ToggleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

		paintBackground(painter);
		

		//paintTriangle(painter);
		//paintTextLeft(painter);
		//paintToggleLeft(painter);

		paintTriangleRight(painter);
		paintTextRight(painter);
		paintToggleRight(painter);

		return;
}

void DcpButton2ToggleView::paintToggleLeft(QPainter *painter)
{

  	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

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

void DcpButton2ToggleView::paintToggleRight(QPainter *painter)
{
  	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

		QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));


    if (image != NULL) {

				QPointF imagePoint( marginSpacer,
										 			 (height() - image->height()) / 2					);

        painter->drawPixmap(imagePoint, *image);
		}

		
		const QPixmap *border = DuiTheme::pixmap(	styleAttribute<const QString>(BackgroundBorderAttribute),
																							QSize(image->width(), image->height())										);

    if (border != NULL) {

				QPointF imagePoint( marginSpacer,
										 			 (height() - border->height()) / 2					);

        painter->drawPixmap(imagePoint, *border);
		}
}

void DcpButton2ToggleView::registerStyleAttributes(DuiStyleDescription &description)
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
		description.addAttribute(MarginSpacerAttribute, "marginSpacer");

		description.addAttribute(BackgroundBorderAttribute, "backgroundBorder");
}

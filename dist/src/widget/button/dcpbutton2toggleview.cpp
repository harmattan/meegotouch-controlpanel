
#include "dcpbutton2toggleview.h"
DUI_STYLABLE_CPP(DcpButton2ToggleView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

DcpButton2ToggleView::DcpButton2ToggleView(DcpButton &button) :
    DcpButton2ImageView(button),
		m_EnableToggle(false)
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

	paintLine(painter);


	if ( m_Alignment==Qt::AlignLeft ) {
		paintTriangle(painter);
		paintTextLeft(painter, m_EnableToggle);
		paintToggleLeft(painter);
	} else {
  //  if ( m_Alignment==Qt::AlignRight ) {
      	paintTriangleRight(painter);
		paintTextRight(painter, m_EnableToggle);
		paintToggleRight(painter);
	}

	return;
}

void DcpButton2ToggleView::paintToggleLeft(QPainter *painter)
{

	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

	m_ToggleOn = DuiTheme::pixmap( styleAttribute<const QString>(ToggleOnAttribute), styleAttribute<const QSize>(ImageSizeAttribute));

	m_ToggleOff = DuiTheme::pixmap( styleAttribute<const QString>(ToggleOffAttribute), styleAttribute<const QSize>(ImageSizeAttribute));
	
    if (m_ToggleOn && m_ToggleOff)
		if (m_EnableToggle) {
			//QPointF imagePoint(width() - m_ToggleOn->width() - marginSpacer,
			//	 			   (height() - m_ToggleOn->height()) / 2					);
			QPointF imagePoint(size().width() - m_ToggleOn->width() - marginSpacer,
				 			   (size().height() - m_ToggleOn->height()) / 2					);

        	painter->drawPixmap(imagePoint, *m_ToggleOn);
		} else {
			//QPointF imagePoint(width() - m_ToggleOff->width() - marginSpacer,
			//	 			   (height() - m_ToggleOff->height()) / 2					);
			QPointF imagePoint(size().width() - m_ToggleOff->width() - marginSpacer,
				 			   (size().height() - m_ToggleOff->height()) / 2					);

        	painter->drawPixmap(imagePoint, *m_ToggleOff);
		}
}

void DcpButton2ToggleView::paintToggleRight(QPainter *painter)
{
 	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

	m_ToggleOn = DuiTheme::pixmap( styleAttribute<const QString>(ToggleOnAttribute), styleAttribute<const QSize>(ImageSizeAttribute));

	m_ToggleOff = DuiTheme::pixmap( styleAttribute<const QString>(ToggleOffAttribute), styleAttribute<const QSize>(ImageSizeAttribute));

    if (m_ToggleOn && m_ToggleOff)
		if (m_EnableToggle) {
			QPointF imagePoint(marginSpacer,
				 			   (height() - m_ToggleOn->height()) / 2					);

        	painter->drawPixmap(imagePoint, *m_ToggleOn);
		} else {
			QPointF imagePoint(marginSpacer,
				 			   (height() - m_ToggleOff->height()) / 2					);

        	painter->drawPixmap(imagePoint, *m_ToggleOff);
		}
}



QRectF DcpButton2ToggleView::boundingRect() const
{
	return QRectF(0, 0, size().width(), size().height());
}

/*
QSizeF DcpButton2ToggleView::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    QSizeF sh(-1, -1);

    switch (which) {
        case Qt::MinimumSize:
            qDebug() << "Qt::MinimumSize";
            break;
        case Qt::MaximumSize:
            qDebug() << "Qt::MaximumSize";
            break;
        case Qt::PreferredSize:
            qDebug() << "Qt::PreferredSize";
			qDebug() << "size   " << size().width() << "   X   " << size().height();
			return QSizeF(size().width(), size().height());
            break;
        default:
			qDebug() << "default:";
            break;
    }

    return sh;
}*/


void DcpButton2ToggleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

	int marginSpacer = styleAttribute<int>(MarginSpacerAttribute);

	if (m_ToggleOn && m_ToggleOff)

		if ( m_Alignment==Qt::AlignLeft ) {
			if (m_EnableToggle) {
				//QRect rect(	width() - m_ToggleOn->width() - marginSpacer,
				//			(height() - m_ToggleOn->height()) / 2,
				//			width() - marginSpacer,
				//			(height() + m_ToggleOn->height()) / 2					);
				QRect rect(	size().width() - m_ToggleOn->width() - marginSpacer,
							(size().height() - m_ToggleOn->height()) / 2,
							size().width() - marginSpacer,
							(size().height() + m_ToggleOn->height()) / 2					);
		
				if (rect.contains(event->pos().x(), event->pos().y())) {
					m_EnableToggle = !m_EnableToggle;
					update();
					return;
				}
			} else {

				//QRect rect(	width() - m_ToggleOff->width() - marginSpacer,
				//			(height() - m_ToggleOff->height()) / 2,
				//			width() - marginSpacer,
				//			(height() + m_ToggleOff->height()) / 2					);
				QRect rect(	size().width() - m_ToggleOff->width() - marginSpacer,
							(size().height() - m_ToggleOff->height()) / 2,
							size().width() - marginSpacer,
							(size().height() + m_ToggleOff->height()) / 2					);
			
				if (rect.contains(event->pos().x(), event->pos().y())) {
					m_EnableToggle = !m_EnableToggle;
					update();
					return;
				}
			}
		} else {
			if (m_EnableToggle) {
				QRect rect(	marginSpacer,
							(height() - m_ToggleOn->height()) / 2,
							marginSpacer + m_ToggleOn->width(),
							(height() + m_ToggleOn->height()) / 2	);
		
				if (rect.contains(event->pos().x(), event->pos().y())) {
					m_EnableToggle = !m_EnableToggle;
					update();
					return;
				}
			} else {
				QRect rect(	marginSpacer,
							(height() - m_ToggleOff->height()) / 2,
							marginSpacer + m_ToggleOff->width(),
							(height() + m_ToggleOff->height()) / 2	);
			
				if (rect.contains(event->pos().x(), event->pos().y())) {
					m_EnableToggle = !m_EnableToggle;
					update();
					return;
				}
			}
		}

	emit clicked();
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

	description.addAttribute(ImageNameAttribute, "imageName");
	description.addAttribute(ImageSizeAttribute, "imageSize");
	description.addAttribute(MarginSpacerAttribute, "marginSpacer");

//		description.addAttribute(BackgroundBorderAttribute, "backgroundBorder");

	description.addAttribute(ToggleOnAttribute, "toggleOn");
	description.addAttribute(ToggleOffAttribute, "toggleOff");
}

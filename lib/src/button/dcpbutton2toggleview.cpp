
#include "dcpbutton2toggleview.h"
//DUI_STYLABLE_CPP(DcpButton2ToggleView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

DcpButton2ToggleView::DcpButton2ToggleView(DcpButton *button) :
    DcpButton2ImageView(button),
		m_EnableToggle(false)
{}

DcpButton2ToggleView::~DcpButton2ToggleView()
{
    if (m_ToggleOff) DuiTheme::releasePixmap(m_ToggleOff);
    if (m_ToggleOn) DuiTheme::releasePixmap(m_ToggleOn);
}

void DcpButton2ToggleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

	initMargins();

	paintBackground(painter);
	paintLine(painter);

	if ( m_Alignment==Qt::AlignLeft ) {
		paintTriangle(painter);
		

		if (m_Text1.size() && m_Text2.size())
			paintTextLeft(painter, m_EnableToggle);
		else
			paintText1(painter);

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

	int marginSpacer = style()->marginSpacer();

	m_ToggleOn = DuiTheme::pixmap(style()->toggleOn(), style()->imageSize());
	m_ToggleOff = DuiTheme::pixmap(style()->toggleOff(), style()->imageSize());

	const QPixmap* pixmap = m_EnableToggle ? m_ToggleOn : m_ToggleOff;

    QPointF imagePoint(size().width() - pixmap->width() - marginSpacer, (size().height() - pixmap->height()) / 2	);
    painter->drawPixmap(imagePoint, *pixmap);
}

void DcpButton2ToggleView::paintToggleRight(QPainter *painter)
{
	int marginSpacer = style()->marginSpacer();

	m_ToggleOn = DuiTheme::pixmap(style()->toggleOn(), style()->imageSize());
	m_ToggleOff = DuiTheme::pixmap(style()->toggleOff(), style()->imageSize());

 	const QPixmap* pixmap = m_EnableToggle ? m_ToggleOn : m_ToggleOff;

    QPointF imagePoint(marginSpacer, (height() - pixmap->height()) / 2 );
    painter->drawPixmap(imagePoint, *pixmap);
}

#if 0
QRectF DcpButton2ToggleView::boundingRect() const
{
	return QRectF(0, 0, size().width(), size().height());
}
#endif

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

	int marginSpacer = style()->marginSpacer();

    const QPixmap* pixmap = m_EnableToggle ? m_ToggleOn : m_ToggleOff;
    QRect rect;
	if ( m_Alignment==Qt::AlignLeft ) {
	    rect = QRect(size().width() - pixmap->width() - marginSpacer,
							(size().height() - pixmap->height()) / 2,
							size().width() - marginSpacer,
							(size().height() + pixmap->height()) / 2);
    } else {
	    rect = QRect (marginSpacer,
				 	(height() - pixmap->height()) / 2,
					marginSpacer + pixmap->width(),
					(height() + pixmap->height()) / 2);
	}

	if (rect.contains(event->pos().x(), event->pos().y())) {
		m_EnableToggle = !m_EnableToggle;
		update();
		return;
	}

	emit clicked();
}

DUI_REGISTER_VIEW("DcpButton2ToggleView", DcpButton2ToggleView, DcpButton)

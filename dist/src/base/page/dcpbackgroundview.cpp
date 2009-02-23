#include "dcpbackgroundview.h"
#include <QDebug>
#include <duitheme.h>
#include <duiwidgetcontroller.h>

enum {
	BackgroundAttribute
};

DcpBackgroundView::DcpBackgroundView(DuiWidgetController *controller)
	          :DuiStylable<DcpBackgroundView, DuiWidgetView>(controller), 
		  m_viewport(controller)
{
	updateStyle();
	m_background = styleAttribute<QPixmap *>(BackgroundAttribute);
}


void DcpBackgroundView::paint(QPainter *painter, 
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	
	if (m_background != NULL) {
		 // Always draw the background texture without rotation
		 const QTransform w = painter->worldTransform();
		 painter->setWorldTransform(QTransform());
		 
		 QPointF p = w.map(QPointF(0, 0));
		 QPointF offset(-p.x() + w.dx(), -p.y() + w.dy());
		 if (DuiDeviceProfile::instance()->orientation() == Dui::Landscape) {
		 	painter->drawTiledPixmap(QRectF(0, 0, 
						DuiDeviceProfile::instance()->width(), 
						DuiDeviceProfile::instance()->height()), 
						*m_background, offset);
		 } else {
			 painter->drawTiledPixmap(QRectF(0, 0, 
						 DuiDeviceProfile::instance()->height(), 
						 DuiDeviceProfile::instance()->width()), 
					 	 *m_background, offset);
		 }
		 
		 // Reset the transform
		 painter->setWorldTransform(w);
	} else {
		qWarning() << "Pannable viewport's background pixmap is not loaded.";
	}
}


void DcpBackgroundView::setGeometry(const QRectF &rect)
{
	Q_UNUSED(rect);
}

QRectF DcpBackgroundView::boundingRect() const 
{
	return QRectF(0.0, 0.0, 
			m_viewport->geometry().width(),
			m_viewport->geometry().height());
}

QSizeF DcpBackgroundView::sizeHint(Qt::SizeHint which,
		const QSizeF &constraint) const
{
	Q_UNUSED(which);
	Q_UNUSED(constraint);

	return QSizeF(m_viewport->geometry().width(), m_viewport->geometry().height());
}


void DcpBackgroundView::registerStyleAttributes(DuiStyleDescription& description)
{
	description.addAttribute(BackgroundAttribute, "background");
}

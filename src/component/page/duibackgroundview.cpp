#include "duibackgroundview.h"
#include <QDebug>
#include <duitheme.h>

enum {
	BackgroundAttribute
};


DuiBackgroundView::DuiBackgroundView(DuiPannableViewport &widget)
	          :m_viewport(widget)
{
	updateStyle();
}


void DuiBackgroundView::paint(QPainter *painter, 
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	// Q_UNUSED(painter);
	
    QPixmap background(":images/starfield.png");
    if (background.isNull()) {
        return;
    }

	QPixmap *background_ptr = &background;
	// background = styleAttribute<QPixmap *>(BackgroundAttribute);
	// background = DuiTheme::pixmap("C1-container-background");

	if (background_ptr != NULL) {
		 // Always draw the background texture without rotation
		 const QTransform w = painter->worldTransform();
		 painter->setWorldTransform(QTransform());
		 
		 QPointF p = w.map(QPointF(0, 0));
		 QPointF offset(-p.x() + w.dx(), -p.y() + w.dy());
		 if (DuiDeviceProfile::instance()->orientation() == Dui::Landscape) {
		 	painter->drawTiledPixmap(QRectF(0, 0, 
						DuiDeviceProfile::instance()->width(), 
						DuiDeviceProfile::instance()->height()), 
						*background_ptr, offset);
		 } else {
			 painter->drawTiledPixmap(QRectF(0, 0, 
						 DuiDeviceProfile::instance()->height(), 
						 DuiDeviceProfile::instance()->width()), 
					 	 *background_ptr, offset);
		 }
		 
		 // Reset the transform
		 painter->setWorldTransform(w);
	} else {
		qWarning() << "Pannable viewport's background pixmap is not loaded.";
	}
}


void DuiBackgroundView::setGeometry(const QRectF &rect)
{
	Q_UNUSED(rect);
}

QRectF DuiBackgroundView::boundingRect() const 
{
	return QRectF(0.0, 0.0, 
			m_viewport.geometry().width(),
			m_viewport.geometry().height());
}

QSizeF DuiBackgroundView::sizeHint(Qt::SizeHint which,
		const QSizeF &constraint) const
{
	Q_UNUSED(which);
	Q_UNUSED(constraint);

	return QSizeF(m_viewport.geometry().width(), m_viewport.geometry().height());
}


void DuiBackgroundView::registerStyleAttributes(DuiStyleDescription& description)
{
	description.addAttribute(BackgroundAttribute, "background");
}

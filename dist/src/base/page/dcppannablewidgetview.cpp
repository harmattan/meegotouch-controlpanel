#include "dcppannablewidgetview.h"
#include <QDebug>
#include <duitheme.h>
#include <duipannablewidget.h>

enum {
    BackgroundAttribute = 1234
};

DcpPannableWidgetView::DcpPannableWidgetView(DuiPannableWidget *controller)
              :DuiStylable<DcpPannableWidgetView, DuiPannableWidgetView>(controller),
          m_viewport(controller), m_background (NULL)
{
}


DcpPannableWidgetView::~DcpPannableWidgetView()
{
    if (m_background != NULL) {
        DuiTheme::releasePixmap(m_background);
    }
}


void DcpPannableWidgetView::paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget)
{	
    // Always draw the background texture without rotation
    const QTransform w = painter->worldTransform();
    painter->setWorldTransform(QTransform());
    QRectF appRect;
    if (DuiDeviceProfile::instance()->orientation() == Dui::Landscape) {
        appRect = QRectF(0,0,DuiDeviceProfile::instance()->width(),
                         DuiDeviceProfile::instance()->height());
    } else {
        appRect = QRectF(0,0,DuiDeviceProfile::instance()->height(),
                         DuiDeviceProfile::instance()->width());
    }

    if (m_background != NULL) {
        QPointF p = w.map(QPointF(0, 0));
        QPointF offset(-p.x() + w.dx(), -p.y() + w.dy());
        painter->drawTiledPixmap(appRect, *m_background, offset);
		 
    } else {
        // if no bg, draw black: --> TODO move to stylesheet
        painter->setBrush (Qt::black);
        painter->drawRect (appRect);
	}

    // Reset the transform
    painter->setWorldTransform(w);

    DuiPannableWidgetView::paint(painter, option, widget);
}

void DcpPannableWidgetView::styleUpdated ()
{
    if (m_background != NULL) {
        DuiTheme::releasePixmap(m_background);
        m_background = NULL;
    }

    QString bgName = styleAttribute<QString>(BackgroundAttribute);
    if (!bgName.isEmpty()) {
        m_background = DuiTheme::pixmap(bgName);
    }

    DuiPannableWidgetView::styleUpdated();
}

void DcpPannableWidgetView::registerStyleAttributes(DuiStyleDescription& description)
{
	description.addAttribute(BackgroundAttribute, "background");
//    DuiPannableWidgetView::registerStyleAttributes(description);
}


DUI_REGISTER_VIEW("DcpPannableWidgetView", DcpPannableWidgetView, DuiPannableWidget);

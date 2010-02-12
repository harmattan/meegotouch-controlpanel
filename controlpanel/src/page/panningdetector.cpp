#include "panningdetector.h"

#include <DuiPannableViewport>
#include "dcpdebug.h"
#include <QPointF>

PanningDetector::PanningDetector(DuiWidget* parentWidget):
    QObject(parentWidget),
    m_IsPanning(false),
    m_LastY(0)
{
    DuiPannableViewport* pannable = findPannableWidget(parentWidget);
    if (!pannable) {
        DCP_WARNING("PannableWidget not found, panning is not tracked");
        return;
    }
    connect (pannable, SIGNAL(sizePosChanged(QSizeF, QRectF, QPointF)),
             this, SLOT(sizePosChanged(QSizeF, QRectF, QPointF)));
    connect (pannable, SIGNAL(panningStopped()),
             this, SLOT(onPanningStopped()));
}

PanningDetector::~PanningDetector()
{
}

// FIXME, this is a workaround until pannableWidget::positionChanged is
// not emitted correctly
void PanningDetector::sizePosChanged (
                            const QSizeF&, const QRectF&, const QPointF& pos)
{
    if (!m_IsPanning && pos.y() != m_LastY) {
        m_LastY = pos.y();
        onPanningStarted();
    }
}

DuiPannableViewport*
PanningDetector::findPannableWidget(DuiWidget* parentWidget)
{
    QGraphicsWidget *ancestor = parentWidget;
    while (ancestor != 0) {
        DuiPannableViewport* pannable =
            qobject_cast<DuiPannableViewport*>(ancestor);
        if (pannable) return pannable;
        ancestor = ancestor->parentWidget();
    }
    return 0;
}

void PanningDetector::onPanningStarted()
{
    m_IsPanning = true;
}

void PanningDetector::onPanningStopped()
{
    if (m_IsPanning) {
        m_IsPanning = false;
        emit panningStoppedNotifyOnce();
        disconnect (SIGNAL(panningStoppedNotifyOnce()));
    }
}

void PanningDetector::notifyOnNextStop (QObject* receiver, const char* slot)
{
    connect (this, SIGNAL(panningStoppedNotifyOnce()),
             receiver, slot);
}



#ifndef PANNINGDETECTOR_H
#define PANNINGDETECTOR_H

#include <QObject>
class DuiWidget;
class DuiPannableViewport;
class QSizeF;
class QRectF;
class QPointF;

/*!
 * \class PanningDetector
 * \brief Detects if page pans or not
 *
 * This class can be used to detect if the page is panning or not.
 * You have to specify a widget, which is in the pannable area in
 * the constructor.
 *
 * The class assumes that the panning widget can be found amongst
 * the ancestors (parent, parent of parent etc.) at construction
 * time, so create this class in polishEvent or showEvent, or
 * when the parent relationship is ready.
 */
class PanningDetector: public QObject
{
    Q_OBJECT
public:
    PanningDetector(DuiWidget* parentWidget);
    ~PanningDetector();

    bool isPanning();
//    void notifyOnNextStop (QObject* receiver, const char* slot);

    static DuiPannableViewport* findPannableWidget(DuiWidget* parent);


signals:
    void panningStopped();

protected slots:
    void onPanningStarted();
    void onPanningStopped();
    void sizePosChanged (const QSizeF&, const QRectF&, const QPointF& pos);

private:
    bool m_IsPanning;
    qreal m_LastY;
};

inline bool PanningDetector::isPanning()
{
    return m_IsPanning;
}

#endif // PANNINGDETECTOR_H


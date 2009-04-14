#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "dcpwidget.h"

class QPixmap;

class KeyboardWidget : public DcpWidget
{
    Q_OBJECT

public:
    KeyboardWidget(QGraphicsWidget *parent = 0);
    ~KeyboardWidget();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

protected:
    void initWidget();
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    const QPixmap   *m_background;
};
#endif //KEYBOARDWIDGET_H

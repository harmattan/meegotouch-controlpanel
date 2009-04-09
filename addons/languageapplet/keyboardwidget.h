#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "dcpwidget.h"

class QPixmap;
class DuiLabel;

class KeyboardWidget : public DcpWidget
{
    Q_OBJECT

public:
    KeyboardWidget(QGraphicsWidget *parent = 0);
    ~KeyboardWidget();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);

protected:
    void initWidget();

private:
    const QPixmap   *m_background;
    DuiLabel        *m_titleLabel;
};
#endif //KEYBOARDWIDGET_H

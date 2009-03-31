#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "dcpwidget.h"

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
};
#endif //KEYBOARDWIDGET_H

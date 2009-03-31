#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "dcpwidget.h"

class DisplayWidget : public DcpWidget
{
    Q_OBJECT

public:
    DisplayWidget(QGraphicsWidget *parent = 0);
    ~DisplayWidget();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

protected:
    void initWidget();
};
#endif //DISPLAYWIDGET_H

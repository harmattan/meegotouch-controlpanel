#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "dcpwidget.h"

class DuiLayout;
class DuiList;

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

private:
    DuiLayout   *m_mainLayout;
    DuiList     *m_inDeviceList;
};
#endif //DISPLAYWIDGET_H

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "dcpwidget.h"

class QPixmap;
class DuiLabel;

class DisplayWidget : public DcpWidget
{
    Q_OBJECT

public:
    DisplayWidget(QGraphicsWidget *parent = 0);
    ~DisplayWidget();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
signals:
    void clicked();
protected:
    void initWidget();

private:
    const QPixmap   *m_background;
    DuiLabel        *m_titleLabel;

};
#endif //DISPLAYWIDGET_H

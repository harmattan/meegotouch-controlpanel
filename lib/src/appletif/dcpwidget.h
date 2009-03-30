#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <DuiWidget>
class QGraphicsWidget;

class DcpWidget: public DuiWidget {
    Q_OBJECT
public:
    DcpWidget(QGraphicsWidget *parent=0) : DuiWidget(parent){};
    virtual ~DcpWidget(){};
signals:
    void refresh();
};

#endif // DCPWIDGET_H


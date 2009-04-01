#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <DuiWidget>
class QGraphicsWidget;

class DcpWidget: public DuiWidget {
    Q_OBJECT
public:
    DcpWidget(QGraphicsWidget *parent=0) : DuiWidget(parent){};
    virtual ~DcpWidget(){};
    void setReferer(int widgetId) {m_Referer = widgetId;};
    int referer() {return m_Referer;}
signals:
    void changeWidget(int widgetId);
private:
    int m_Referer;
};

#endif // DCPWIDGET_H


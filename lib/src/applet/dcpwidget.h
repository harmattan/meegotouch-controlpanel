#ifndef DCPWIDGET_H
#define DCPWIDGET_H

#include <DuiWidget>
class QGraphicsWidget;
class DuiDialog;
class DcpWidget: public DuiWidget {
    Q_OBJECT
public:
    DcpWidget(QGraphicsWidget *parent=0) : DuiWidget(parent), m_Referer(-1){}
    virtual ~DcpWidget(){}
    virtual void setReferer(int widgetId) {m_Referer = widgetId;}
    int referer() {return m_Referer;}
    virtual bool back() {
	if (referer() > -1) { // emit the changewidget signal if there is a referer set
	    emit changeWidget(referer());
	    return false;
	} else {
   	    return true; // back is handled by main window
                         // by default
	}
    }

signals:
    void changeWidget(int widgetId);
private:
    int m_Referer;
};

#endif // DCPWIDGET_H


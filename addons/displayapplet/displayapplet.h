#ifndef DISPLAYAPPLET_H
#define DISPLAYAPPLET_H

#include "dcpappletif.h"
#include <QObject>
class DcpWidget;

class DisplayApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
	virtual DcpWidget* constructWidget(int widgetId);

	virtual DcpWidget* pageMain();
	virtual DcpWidget* page1();
	virtual DcpWidget* page2();

    virtual QString title() const;
private:
    int m_WidgetIndex;
};
#endif // DISPLAYAPPLET_H

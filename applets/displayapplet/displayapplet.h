#ifndef DISPLAYAPPLET_H
#define DISPLAYAPPLET_H

#include <DcpAppletIf>
#include <QObject>
class DcpWidget;
class DuiAction;

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
    virtual QVector<DuiAction *> viewMenuItems();
    virtual DcpBrief* constructBrief(int);
private:
    int m_WidgetIndex;
};
#endif // DISPLAYAPPLET_H
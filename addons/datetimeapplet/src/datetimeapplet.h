#ifndef DATETIMEAPPLET_H
#define DATETIMEAPPLET_H

#include "dcpappletif.h"
#include <QObject>
class DcpWidget;
class DuiAction;

class DateTimeApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
	virtual DcpWidget* constructWidget(int widgetId);
    virtual DcpWidget* pageMain();
    virtual DcpWidget* pageTimeZone();
    virtual QString title() const;
    virtual QVector<DuiAction *> viewMenuItems();
    virtual DcpBrief* constructBrief();

private:
    int m_WidgetIndex;
    QString m_Title;
};
#endif // DATETIMEAPPLET_H


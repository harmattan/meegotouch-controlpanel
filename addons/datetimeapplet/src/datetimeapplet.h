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
    virtual QString title() const;
    virtual QVector<DuiAction *> viewMenuItems();
};
#endif // DATETIMEAPPLET_H

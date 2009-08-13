#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include "dcpwidget.h"

#include <clock/settingalarm.h>

#include "dcptime.h"

class DuiContainer;

class TimeView : public DcpWidget
{
    Q_OBJECT

public:
    TimeView(QGraphicsWidget *parent = 0);
    virtual ~TimeView();

protected:
    void initWidget();

private:
    DuiContainer *m_Container;

	SettingAlarm *m_TimePicker;

	DcpTime m_Clock;

private slots:
    virtual void orientationChanged();
};
#endif // TIMEVIEW_H

